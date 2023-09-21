package api

import (
	"fmt"
	"time"

	"github.com/Yara-Rules/yara-endpoint/server/context"
	"github.com/Yara-Rules/yara-endpoint/server/models"
	yara "github.com/hillu/go-yara"
	mgo "gopkg.in/mgo.v2"
	"gopkg.in/mgo.v2/bson"
)

func Rules(ctx *context.Context) {
	rules := new([]models.Rule)
	ctx.DB.C(models.Rules).Find(nil).All(rules)
	ctx.JSON(200, rules)
}

func NewRule(ctx *context.Context, newRule NewRuleForm) {
	var msg string
	var yerr, ywarn []yara.CompilerMessage

	msg, yerr, ywarn = validRule(newRule.Data)
	if msg != "" {
		if len(yerr) > 0 {
			ctx.JSON(400, Error{
				Error:    true,
				ErrorID:  1,
				ErrorMsg: prepareErrMsg(msg, yerr),
			})
			return
		}
	}

	rule := &models.Rule{
		Name:     newRule.Name,
		RuleID:   newULID().String(),
		Tags:     newRule.Tags,
		Data:     newRule.Data,
		CreateAt: time.Now(),
		UpdateAt: time.Now(),
	}
	err := ctx.DB.C(models.Rules).Insert(rule)
	if err != nil {
		ctx.JSON(400, Error{
			Error:    true,
			ErrorMsg: fmt.Sprintf("%v", err),
		})
	} else {
		ctx.JSON(200, Error{
			Error:    false,
			ErrorID:  0,
			ErrorMsg: prepareErrMsg(msg, ywarn),
		})
	}
}

func EditRule(ctx *context.Context, newRule EditRuleForm) {
	var msg string
	var yerr, ywarn []yara.CompilerMessage

	msg, yerr, ywarn = validRule(newRule.Data)
	if msg != "" {
		if len(yerr) > 0 {
			ctx.JSON(400, Error{
				Error:    true,
				ErrorID:  1,
				ErrorMsg: prepareErrMsg(msg, yerr),
			})
			return
		}
	}

	ulid := ctx.Params(":id")
	rule := models.Rule{}
	err := ctx.DB.C(models.Rules).Find(bson.M{"rule_id": ulid}).One(&rule)
	if err == mgo.ErrNotFound {
		ctx.JSON(400, Error{
			Error:    true,
			ErrorID:  1,
			ErrorMsg: fmt.Sprintf("%v", err),
		})
		return
	}

	rule.Name = newRule.Name
	rule.Tags = newRule.Tags
	rule.Data = newRule.Data
	rule.UpdateAt = time.Now()

	err = ctx.DB.C(models.Rules).Update(bson.M{"rule_id": ulid}, &rule)
	if err != nil {
		ctx.JSON(400, Error{
			Error:    true,
			ErrorID:  1,
			ErrorMsg: fmt.Sprintf("%v", err),
		})
		return
	}
	ctx.JSON(200, Error{
		Error:    false,
		ErrorID:  0,
		ErrorMsg: prepareErrMsg(msg, ywarn),
	})
}

func DeleteRule(ctx *context.Context) {
	ulid := ctx.Params(":id")
	rule := models.Rule{}
	err := ctx.DB.C(models.Rules).Find(bson.M{"rule_id": ulid}).One(&rule)
	if err == mgo.ErrNotFound {
		ctx.JSON(400, Error{
			Error:    true,
			ErrorID:  1,
			ErrorMsg: fmt.Sprintf("%v", err),
		})
		return
	}
	selector := bson.M{"tasks.status": 0}
	update := bson.M{"$pull": bson.M{"tasks.$.rules": bson.M{"$in": [...]bson.ObjectId{rule.ID}}}}
	ctx.DB.C(models.Schedules).Update(selector, update)

	// Cleaning up empy tasks
	selector = bson.M{"tasks.rules": bson.M{"$size": 0}}
	ctx.DB.C(models.Schedules).Remove(selector)

	err = ctx.DB.C(models.Rules).Remove(bson.M{"rule_id": ulid})
	if err == mgo.ErrNotFound {
		ctx.JSON(400, Error{
			Error:    true,
			ErrorID:  1,
			ErrorMsg: fmt.Sprintf("%v", err),
		})
		return
	}
	ctx.JSON(200, Error{
		Error:    false,
		ErrorID:  0,
		ErrorMsg: "Rule has been removed",
	})
}

func validRule(rule string) (string, []yara.CompilerMessage, []yara.CompilerMessage) {
	yc, err := yara.NewCompiler()
	if err != nil {
		return fmt.Sprintf("%s", err), nil, nil
	}
	yc.AddString(rule, "")

	msg := ""
	if len(yc.Errors) > 0 {
		msg = "Errors found while compiling"
	} else if len(yc.Warnings) > 0 {
		msg = "Warnings found while compiling"
	}
	return msg, yc.Errors, yc.Warnings
}

func prepareErrMsg(msg string, ymsg []yara.CompilerMessage) string {
	if msg == "" {
		return ""
	}
	for _, ym := range ymsg {
		msg += fmt.Sprintf("\nLine(%d): %s", ym.Line, ym.Text)
	}
	return msg
}
