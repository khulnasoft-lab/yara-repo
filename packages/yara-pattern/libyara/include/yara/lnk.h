#include <yara/integers.h>

#ifndef _LNK_H
#define _LNK_H

#define TICKS_PER_SECOND 10000000
#define EPOCH_DIFFERENCE 11644473600LL

#pragma pack(push)
#pragma pack(1)

typedef struct _shell_link_header_t
{
  uint32_t header_size;
  uint32_t clsid[4];
  uint32_t link_flags;
  uint32_t file_attributes_flags;
  uint64_t creation_time;
  uint64_t access_time;
  uint64_t write_time;
  uint32_t file_size;
  uint32_t icon_index;
  uint32_t show_command;
  uint16_t hotkey_flags;
  uint16_t reserved1;
  uint32_t reserved2;
  uint32_t reserved3;
} shell_link_header_t;

typedef struct _link_info_fixed_header_t
{
  uint32_t link_info_size;
  uint32_t link_info_header_size;
  uint32_t link_info_flags;
  uint32_t volume_id_offset;
  uint32_t local_base_path_offset;
  uint32_t common_network_relative_link_offset;
  uint32_t common_path_suffix_offset;
} link_info_fixed_header_t;

typedef struct _volume_id_t
{
  uint32_t volume_id_size;
  uint32_t drive_type;
  uint32_t drive_serial_number;
  uint32_t volume_label_offset;
} volume_id_t;

typedef struct _common_network_relative_link_t
{
  uint32_t common_network_relative_link_size;
  uint32_t common_network_relative_link_flags;
  uint32_t net_name_offset;
  uint32_t device_name_offset;
  uint32_t network_provider_type;
} common_network_relative_link_t;

typedef struct _console_data_block_t
{
  uint16_t fill_attributes;
  uint16_t popup_fill_attributes;
  int16_t screen_buffer_size_x;
  int16_t screen_buffer_size_y;
  int16_t window_size_x;
  int16_t window_size_y;
  int16_t window_origin_x;
  int16_t window_origin_y;
  uint32_t unused_1;
  uint32_t unused_2;
  uint32_t font_size;
  uint32_t font_family;
  uint32_t font_weight;
  uint16_t face_name[32];
  uint32_t cursor_size;
  uint32_t full_screen;
  uint32_t quick_edit;
  uint32_t insert_mode;
  uint32_t auto_position;
  uint32_t history_buffer_size;
  uint32_t number_of_history_buffers;
  uint32_t history_no_dup;
  uint32_t color_table[16];
} console_data_block_t;

typedef struct _console_fe_data_block_t
{
  uint32_t code_page;
} console_fe_data_block_t;

typedef struct _darwin_data_block_t
{
  char darwin_data_ansi[260];
  uint16_t darwin_data_unicode[260];
} darwin_data_block_t;

typedef struct _environment_variable_data_block_t
{
  char target_ansi[260];
  uint16_t target_unicode[260];
} environment_variable_data_block_t;

typedef struct _icon_environment_data_block_t
{
  char target_ansi[260];
  uint16_t target_unicode[260];
} icon_environment_data_block_t;

typedef struct _known_folder_data_block_t
{
  uint8_t known_folder_id[16];
  uint32_t offset;
} known_folder_data_block_t;

typedef struct _special_folder_data_block_t
{
  uint32_t special_folder_id;
  uint32_t offset;
} special_folder_data_block_t;

typedef struct _tracker_data_block_t
{
  uint32_t length;
  uint32_t version;
  char machine_id[16];
  uint8_t droid_volume_identifier[16];
  uint8_t droid_file_identifier[16];
  uint8_t droid_birth_volume_identifier[16];
  uint8_t droid_birth_file_identifier[16];
} tracker_data_block_t;

#pragma pack(pop)

#define HEADER_SIZE 0x0000004C

#define LINK_CLSID_0 0x00021401
#define LINK_CLSID_1 0x00000000
#define LINK_CLSID_2 0x000000C0
#define LINK_CLSID_3 0x46000000

#define HAS_LINK_TARGET_ID_LIST           0x00000001
#define HAS_LINK_INFO                     0x00000002
#define HAS_NAME                          0x00000004
#define HAS_RELATIVE_PATH                 0x00000008
#define HAS_WORKING_DIR                   0x00000010
#define HAS_ARGUMENTS                     0x00000020
#define HAS_ICON_LOCATION                 0x00000040
#define IS_UNICODE                        0x00000080
#define FORCE_NO_LINK_INFO                0x00000100
#define HAS_EXP_STRING                    0x00000200
#define RUN_IN_SEPARATE_PROCESS           0x00000400
#define UNUSED_1                          0x00000800
#define HAS_DARWIN_ID                     0x00001000
#define RUN_AS_USER                       0x00002000
#define HAS_EXP_ICON                      0x00004000
#define NO_PIDL_ALIAS                     0x00008000
#define UNUSED_2                          0x00010000
#define RUN_WITH_SHIM_LAYER               0x00020000
#define FORCE_NO_LINK_TRACK               0x00040000
#define ENABLE_TARGET_METADATA            0x00080000
#define DISABLE_LINK_PATH_TRACKING        0x00100000
#define DISABLE_KNOWN_FOLDER_TRACKING     0x00200000
#define DISABLE_KNOWN_FOLDER_ALIAS        0x00400000
#define ALLOW_LINK_TO_LINK                0x00800000
#define UNALIAS_ON_SAVE                   0x01000000
#define PREFER_ENVIRONMENT_PATH           0x02000000
#define KEEP_LOCAL_ID_LIST_FOR_UNC_TARGET 0x04000000

#define FILE_ATTRIBUTE_READONLY            0x00000001
#define FILE_ATTRIBUTE_HIDDEN              0x00000002
#define FILE_ATTRIBUTE_SYSTEM              0x00000004
#define RESERVED_1                         0x00000008
#define FILE_ATTRIBUTE_DIRECTORY           0x00000010
#define FILE_ATTRIBUTE_ARCHIVE             0x00000020
#define RESERVED_2                         0x00000040
#define FILE_ATTRIBUTE_NORMAL              0x00000080
#define FILE_ATTRIBUTE_TEMPORARY           0x00000100
#define FILE_ATTRIBUTE_SPARSE_FILE         0x00000200
#define FILE_ATTRIBUTE_REPARSE_POINT       0x00000400
#define FILE_ATTRIBUTE_COMPRESSED          0x00000800
#define FILE_ATTRIBUTE_OFFLINE             0x00001000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED 0x00002000
#define FILE_ATTRIBUTE_ENCRYPTED           0x00004000

#define SW_SHOWNORMAL      0x00000001
#define SW_SHOWMAXIMIZED   0x00000003
#define SW_SHOWMINNOACTIVE 0x00000007

#define HOTKEYF_SHIFT   0x01
#define HOTKEYF_CONTROL 0x02
#define HOTKEYF_ALT     0x04

#define VOLUME_ID_AND_LOCAL_BASE_PATH                0x01
#define COMMON_NETWORK_RELATIVE_LINK_AND_PATH_SUFFIX 0x02

#define DRIVE_UNKNOWN     0x00
#define DRIVE_NO_ROOT_DIR 0x01
#define DRIVE_REMOVABLE   0x02
#define DRIVE_FIXED       0x03
#define DRIVE_REMOTE      0x04
#define DRIVE_CDROM       0x05
#define DRIVE_RAMDISK     0x06

#define VALID_DEVICE   0x01
#define VALID_NET_TYPE 0x02

#define WNNC_NET_AVID        0x001A0000
#define WNNC_NET_DOCUSPACE   0x001B0000
#define WNNC_NET_MANGOSOFT   0x001C0000
#define WNNC_NET_SERNET      0x001D0000
#define WNNC_NET_RIVERFRONT1 0X001E0000
#define WNNC_NET_RIVERFRONT2 0x001F0000
#define WNNC_NET_DECORB      0x00200000
#define WNNC_NET_PROTSTOR    0x00210000
#define WNNC_NET_FJ_REDIR    0x00220000
#define WNNC_NET_DISTINCT    0x00230000
#define WNNC_NET_TWINS       0x00240000
#define WNNC_NET_RDR2SAMPLE  0x00250000
#define WNNC_NET_CSC         0x00260000
#define WNNC_NET_3IN1        0x00270000
#define WNNC_NET_EXTENDNET   0x00290000
#define WNNC_NET_STAC        0x002A0000
#define WNNC_NET_FOXBAT      0x002B0000
#define WNNC_NET_YAHOO       0x002C0000
#define WNNC_NET_EXIFS       0x002D0000
#define WNNC_NET_DAV         0x002E0000
#define WNNC_NET_KNOWARE     0x002F0000
#define WNNC_NET_OBJECT_DIRE 0x00300000
#define WNNC_NET_MASFAX      0x00310000
#define WNNC_NET_HOB_NFS     0x00320000
#define WNNC_NET_SHIVA       0x00330000
#define WNNC_NET_IBMAL       0x00340000
#define WNNC_NET_LOCK        0x00350000
#define WNNC_NET_TERMSRV     0x00360000
#define WNNC_NET_SRT         0x00370000
#define WNNC_NET_QUINCY      0x00380000
#define WNNC_NET_OPENAFS     0x00390000
#define WNNC_NET_AVID1       0X003A0000
#define WNNC_NET_DFS         0x003B0000
#define WNNC_NET_KWNP        0x003C0000
#define WNNC_NET_ZENWORKS    0x003D0000
#define WNNC_NET_DRIVEONWEB  0x003E0000
#define WNNC_NET_VMWARE      0x003F0000
#define WNNC_NET_RSFX        0x00400000
#define WNNC_NET_MFILES      0x00410000
#define WNNC_NET_MS_NFS      0x00420000
#define WNNC_NET_GOOGLE      0x00430000

#define FOREGROUND_BLUE      0x0001
#define FOREGROUND_GREEN     0x0002
#define FOREGROUND_RED       0x0004
#define FOREGROUND_INTENSITY 0x0008
#define BACKGROUND_BLUE      0x0010
#define BACKGROUND_GREEN     0x0020
#define BACKGROUND_RED       0x0040
#define BACKGROUND_INTENSITY 0x0080

#define FF_DONTCARE   0x0000
#define FF_ROMAN      0x0010
#define FF_SWISS      0x0020
#define FF_MODERN     0x0030
#define FF_SCRIPT     0x0040
#define FF_DECORATIVE 0x0050

#define TMPF_NONE        0x0000
#define TMPF_FIXED_PITCH 0x0001
#define TMPF_VECTOR      0x0002
#define TMPF_TRUETYPE    0x0004
#define TMPF_DEVICE      0x0008

#define CONSOLE_DATA_BLOCK_SIZE                     0x000000CC
#define CONSOLE_FE_DATA_BLOCK_SIZE                  0x0000000C
#define DARWIN_DATA_BLOCK_SIZE                      0x00000314
#define ENVIRONMENT_VARIABLE_DATA_BLOCK_SIZE        0x00000314
#define ICON_ENVIRONMENT_DATA_BLOCK_SIZE            0x00000314
#define KNOWN_FOLDER_DATA_BLOCK_SIZE                0x0000001C
#define PROPERTY_STORE_DATA_BLOCK_MIN_SIZE          0x0000000C
#define SHIM_DATA_BLOCK_MIN_SIZE                    0x00000088
#define SPECIAL_FOLDER_DATA_BLOCK_SIZE              0x00000010
#define TRACKER_DATA_BLOCK_SIZE                     0x00000060
#define VISTA_AND_ABOVE_ID_LIST_DATA_BLOCK_MIN_SIZE 0x0000000A

#define CONSOLE_DATA_BLOCK_SIGNATURE                 0xA0000002
#define CONSOLE_FE_DATA_BLOCK_SIGNATURE              0xA0000004
#define DARWIN_DATA_BLOCK_SIGNATURE                  0xA0000006
#define ENVIRONMENT_VARIABLE_DATA_BLOCK_SIGNATURE    0xA0000001
#define ICON_ENVIRONMENT_DATA_BLOCK_SIGNATURE        0xA0000007
#define KNOWN_FOLDER_DATA_BLOCK_SIGNATURE            0xA000000B
#define PROPERTY_STORE_DATA_BLOCK_SIGNATURE          0xA0000009
#define SHIM_DATA_BLOCK_SIGNATURE                    0xA0000008
#define SPECIAL_FOLDER_DATA_BLOCK_SIGNATURE          0xA0000005
#define TRACKER_DATA_BLOCK_SIGNATURE                 0xA0000003
#define VISTA_AND_ABOVE_ID_LIST_DATA_BLOCK_SIGNATURE 0xA000000C

#endif