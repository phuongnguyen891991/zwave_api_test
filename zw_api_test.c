
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include "utils.h"
#include "zw_api.h"
#include "SerialAPI/ZW_classcmd.h"
#include "SerialAPI/ZW_SerialAPI.h"
#define manu_max 161
#define manu_pID_max 179
#define manu_pType_max 15
#define manu_class_suport_max 118
enum COMMAND_IDX {
    CMD_ADD = 0,
    CMD_RM,
    CMD_LIST,
 //   CMD_LIST_FULL,
    CMD_TURN_ON_NODE,
    CMD_TURN_OFF_NODE,
    CMD_GET_STATUS_NODE,
    CMD_SET_COLOR_NODE,
    CMD_SET_MULTILEVEL_NODE,
    CMD_G_ADD_GROUP,
    CMD_G_REMOVE_GROUP,
    CMD_G_GET_LIST,
    CMD_G_ADD_NODE,
    CMD_G_REMOVE_NODE,
    CMD_G_GET_NODES,
    CMD_SET_GROUP_SENSOR,
    CMD_TURN_ON_GROUP,
    CMD_TURN_OFF_GROUP,
    CMD_RESET,
    CMD_SET_LERAN_MODE,
    CMD_SET_SUC_NODE,
    CMD_REQ_NW_UPDATE,
    CMD_SENDDAT,
    CMD_SET_SLAVE_LEARN_MODE,
    CMD_NW_DUMP,
    CMD_NW_TEST_CONNECTION,
    CMD_DOOR_NONCE_GET,
    CMD_DOOR_OPEN,
    CMD_DOOR_CLOSE,
//    CMD_GET_BATTERY,
//   CMD_SENSOR_MULTILEVEL_GET,
//   CMD_SENSOR_HEAVY_DUTY_SMART_SWITCH,
//   CMD_SET_ALAM_REPORT_ONOFF_BULBS,
    CMD_SET_CONFIGURATION_NODE,
    CMD_FEATURE_OPTION_NODE,
    CMD_V,
    CMD_EXIT,
    CMD_MAX
};
typedef struct manu_product_type{
    uint32_t product_type_id_number;
    char product_type_name[128];

}Manu_product_type_t;

typedef struct manu_product_id{
    uint16_t product_id_number;
    char product_id_name[128];

}Manu_product_id_t;

typedef struct manu_class_support{
    uint16_t class_support_number;
    char command_class_suport[128];

}Manu_class_suport_t;

typedef struct Manufacture_ID{
    uint16_t manufacture_id_value;
    char  manufacture[256];

}Manufacture_id_value_t;


typedef struct Feature_option{
    uint16_t feature_id;
    uint16_t feature_num;
    Manu_class_suport_t feature_class[manu_max];
}feature_option_t;

typedef struct cmd_handler_s{
    enum COMMAND_IDX cmd_idx;
    char help[256];
    int (*cmd_func)(void *arg);

}cmd_handler_t;

notify_t g_notify;

int cmd_add(void* arg)
{
    printf("[Debug] add command \n");
    return 0;
}

int cmd_rm(void* arg)
{
    printf("[Debug] rm command \n");
    return 0;

}

Manu_product_type_t product_type_id_t[manu_pType_max] = {
{.product_type_name = " Z-wave Door/Windown Sensor                                                               ",.product_type_id_number = 0x01020059}, /**/
{.product_type_name = " Z-wave Door/Windown Sensor                                                               ",.product_type_id_number = 0x0002001D},
{.product_type_name = " Z-wave Sensor Multilevel 6                                                               ",.product_type_id_number = 0x01020064}, /**/
{.product_type_name = " Z-wave Smart Outlet                                                                      ",.product_type_id_number = 0x49523031},/**/
{.product_type_name = " Z-wave Smart Dimmer                                                                      ",.product_type_id_number = 0x49443031},/**/
{.product_type_name = " Z-wave Heavy Duty Smart Switch                                                           ",.product_type_id_number = 0x0103004E},/**/
{.product_type_name = " Z-wave Led                                                                               ",.product_type_id_number = 0x00040001},/**/
{.product_type_name = " Z-wave Outlet Lamp Module                                                                ",.product_type_id_number = 0x44503030},/**/
{.product_type_name = " Z-wave Motion Sensor (Ecolink)                                                           ",.product_type_id_number = 0x00010001},/**/
{.product_type_name = " Z-wave Sensor Multilevel Gen5                                                            ",.product_type_id_number = 0x0102004A},/**/
{.product_type_name = " Z-wave Siren Alarm Sensor                                                                ",.product_type_id_number = 0x01040050},/**/
{.product_type_name = " Z-wave Aeotec Smartdimmer                                                                ",.product_type_id_number = 0x00030019},/**/
{.product_type_name = " Z-wave Door/Windown Fibaro Systems Sensor                                                ",.product_type_id_number = 0x07002000},/**/
{.product_type_name = " Z-wave Door/Windown Sensor (DWZ)                                                         ",.product_type_id_number = 0x00010002},/**/
{.product_type_name = " Z-wave Smart Switch                                                                      ",.product_type_id_number = 0x4F503031},/**/


};

Manu_product_id_t product_id_t[manu_pID_max]={

{.product_id_name = "MFG_ID_NOT_DEFINED_OR_UNDEFINED                           ", .product_id_number =0xFFFF  }, //Not defined or un-defined
{.product_id_name = "MFG_ID_2B_ELECTRONICS                                     ", .product_id_number =0x0028  }, //2B Electronics
{.product_id_name = "MFG_ID_2GIG_TECHNOLOGIES_INC                              ", .product_id_number =0x009B  }, //2gig Technologies Inc.
{.product_id_name = "MFG_ID_3E_TECHNOLOGIES                                    ", .product_id_number =0x002A  }, //3e Technologies
{.product_id_name = "MFG_ID_A1_COMPONENTS                                      ", .product_id_number =0x0022  }, //A-1 Components
{.product_id_name = "MFG_ID_ABILIA                                             ", .product_id_number =0x0117  }, //Abilia
{.product_id_name = "MFG_ID_ACT_ADVANCED_CONTROL_TECHNOLOGIES                  ", .product_id_number =0x0001  }, //ACT - Advanced Control Technologies
{.product_id_name = "MFG_ID_AEON_LABS                                          ", .product_id_number =0x0086  }, //AEON Labs
{.product_id_name = "MFG_ID_AIRLINE_MECHANICAL_CO_LTD                          ", .product_id_number =0x0111  }, //Airline Mechanical Co., Ltd.
{.product_id_name = "MFG_ID_ALARMCOM                                           ", .product_id_number =0x0094  }, //Alarm.com
{.product_id_name = "MFG_ID_ASIA_HEADING                                       ", .product_id_number =0x0029  }, //Asia Heading
{.product_id_name = "MFG_ID_ATECH                                              ", .product_id_number =0x002B  }, //Atech
{.product_id_name = "MFG_ID_BALBOA_INSTRUMENTS                                 ", .product_id_number =0x0018  }, //Balboa Instruments
{.product_id_name = "MFG_ID_BENEXT                                             ", .product_id_number =0x008A  }, //BeNext
{.product_id_name = "MFG_ID_BESAFER                                            ", .product_id_number =0x002C  }, //BeSafer
{.product_id_name = "MFG_ID_BFT_SPA                                            ", .product_id_number =0x014B  }, //BFT S.p.A.
{.product_id_name = "MFG_ID_BOCA_DEVICES                                       ", .product_id_number =0x0023  }, //Boca Devices
{.product_id_name = "MFG_ID_BROADBAND_ENERGY_NETWORKS_INC                      ", .product_id_number =0x002D  }, //Broadband Energy Networks Inc.
{.product_id_name = "MFG_ID_BULOGICS                                           ", .product_id_number =0x0026  }, //BuLogics
{.product_id_name = "MFG_ID_CAMEO_COMMUNICATIONS_INC                           ", .product_id_number =0x009C  }, //Cameo Communications Inc.
{.product_id_name = "MFG_ID_CARRIER                                            ", .product_id_number =0x002E  }, //Carrier
{.product_id_name = "MFG_ID_CASAWORKS                                          ", .product_id_number =0x000B  }, //CasaWorks
{.product_id_name = "MFG_ID_CHECKIT_SOLUTIONS_INC                              ", .product_id_number =0x014E  }, //Check-It Solutions Inc.
{.product_id_name = "MFG_ID_CHROMAGIC_TECHNOLOGIES_CORPORATION                 ", .product_id_number =0x0116  }, //Chromagic Technologies Corporation
{.product_id_name = "MFG_ID_COLOR_KINETICS_INCORPORATED                        ", .product_id_number =0x002F  }, //Color Kinetics Incorporated
{.product_id_name = "MFG_ID_COMPUTIME                                          ", .product_id_number =0x0140  }, //Computime
{.product_id_name = "MFG_ID_CONNECTED_OBJECT                                   ", .product_id_number =0x011B  }, //Connected Object
{.product_id_name = "MFG_ID_CONTROLTHINK_LC                                    ", .product_id_number =0x0019  }, //ControlThink LC
{.product_id_name = "MFG_ID_CONVERGEX_LTD                                      ", .product_id_number =0x000F  }, //ConvergeX Ltd.
{.product_id_name = "MFG_ID_COOPER_LIGHTING                                    ", .product_id_number =0x0079  }, //Cooper Lighting
{.product_id_name = "MFG_ID_COOPER_WIRING_DEVICES                              ", .product_id_number =0x001A  }, //Cooper Wiring Devices
{.product_id_name = "MFG_ID_CORNUCOPIA_CORP                                    ", .product_id_number =0x012D  }, //Cornucopia Corp
{.product_id_name = "MFG_ID_COVENTIVE_TECHNOLOGIES_INC                         ", .product_id_number =0x009D  }, //Coventive Technologies Inc.
{.product_id_name = "MFG_ID_CYBERHOUSE                                         ", .product_id_number =0x0014  }, //Cyberhouse
{.product_id_name = "MFG_ID_CYBERTAN_TECHNOLOGY_INC                            ", .product_id_number =0x0067  }, //CyberTAN Technology, Inc.
{.product_id_name = "MFG_ID_CYTECH_TECHNOLOGY_PRE_LTD                          ", .product_id_number =0x0030  }, //Cytech Technology Pre Ltd.
{.product_id_name = "MFG_ID_DANFOSS                                            ", .product_id_number =0x0002  }, //Danfoss
{.product_id_name = "MFG_ID_DEFACONTROLS_BV                                    ", .product_id_number =0x013F  }, //Defacontrols BV
{.product_id_name = "MFG_ID_DESTINY_NETWORKS                                   ", .product_id_number =0x0031  }, //Destiny Networks
{.product_id_name = "MFG_ID_DIEHL_AKO                                          ", .product_id_number =0x0103  }, //Diehl AKO
{.product_id_name = "MFG_ID_DIGITAL_5_INC                                      ", .product_id_number =0x0032  }, //Digital 5, Inc.
{.product_id_name = "MFG_ID_DYNAQUIP_CONTROLS                                  ", .product_id_number =0x0132  }, //DynaQuip Controls
{.product_id_name = "MFG_ID_ECOLINK                                            ", .product_id_number =0x014A  }, //Ecolink
{.product_id_name = "MFG_ID_EKA_SYSTEMS                                        ", .product_id_number =0x0087  }, //Eka Systems
{.product_id_name = "MFG_ID_ELECTRONIC_SOLUTIONS                               ", .product_id_number =0x0033  }, //Electronic Solutions
{.product_id_name = "MFG_ID_ELGEV_ELECTRONICS_LTD                              ", .product_id_number =0x0034  }, //El-Gev Electronics LTD
{.product_id_name = "MFG_ID_ELK_PRODUCTS_INC                                   ", .product_id_number =0x001B  }, //ELK Products, Inc.
{.product_id_name = "MFG_ID_EMBEDIT_AS                                         ", .product_id_number =0x0035  }, //Embedit A/S
{.product_id_name = "MFG_ID_ENBLINK_CO_LTD                                     ", .product_id_number =0x014D  }, //Enblink Co. Ltd
{.product_id_name = "MFG_ID_EUROTRONICS                                        ", .product_id_number =0x0148  }, //Eurotronics
{.product_id_name = "MFG_ID_EVERSPRING                                         ", .product_id_number =0x0060  }, //Everspring
{.product_id_name = "MFG_ID_EVOLVE                                             ", .product_id_number =0x0113  }, //Evolve
{.product_id_name = "MFG_ID_EXCEPTIONAL_INNOVATIONS                            ", .product_id_number =0x0036  }, //Exceptional Innovations
{.product_id_name = "MFG_ID_EXHAUSTO                                           ", .product_id_number =0x0004  }, //Exhausto
{.product_id_name = "MFG_ID_EXIGENT_SENSORS                                    ", .product_id_number =0x009F  }, //Exigent Sensors
{.product_id_name = "MFG_ID_EXPRESS_CONTROLS                                   ", .product_id_number =0x001E  }, //Express Controls (former Ryherd Ventures)
{.product_id_name = "MFG_ID_FAKRO                                              ", .product_id_number =0x0085  }, //Fakro
{.product_id_name = "MFG_ID_FIBARGROUP                                         ", .product_id_number =0x010F  }, //Fibargroup
{.product_id_name = "MFG_ID_FIBARO                                             ", .product_id_number =0x2000  }, //Fibaro
{.product_id_name = "MFG_ID_FOARD_SYSTEMS                                      ", .product_id_number =0x0037  }, //Foard Systems
{.product_id_name = "MFG_ID_FOLLOWGOOD_TECHNOLOGY_COMPANY_LTD                  ", .product_id_number =0x0137  }, //FollowGood Technology Company Ltd.
{.product_id_name = "MFG_ID_FORTREZZ_LLC                                       ", .product_id_number =0x0084  }, //FortrezZ LLC
{.product_id_name = "MFG_ID_FOXCONN                                            ", .product_id_number =0x011D  }, //Foxconn
{.product_id_name = "MFG_ID_FROSTDALE                                          ", .product_id_number =0x0110  }, //Frostdale
{.product_id_name = "MFG_ID_GOOD_WAY_TECHNOLOGY_CO_LTD                         ", .product_id_number =0x0068  }, //Good Way Technology Co., Ltd
{.product_id_name = "MFG_ID_GREENWAVE_REALITY_INC                              ", .product_id_number =0x0099  }, //GreenWave Reality Inc.
{.product_id_name = "MFG_ID_HITECH_AUTOMATION                                  ", .product_id_number =0x0017  }, //HiTech Automation
{.product_id_name = "MFG_ID_HOLTEC_ELECTRONICS_BV                              ", .product_id_number =0x013E  }, //Holtec Electronics BV
{.product_id_name = "MFG_ID_HOME_AUTOMATED_INC                                 ", .product_id_number =0x005B  }, //Home Automated Inc.
{.product_id_name = "MFG_ID_HOME_AUTOMATED_LIVING                              ", .product_id_number =0x000D  }, //Home Automated Living
{.product_id_name = "MFG_ID_HOME_AUTOMATION_EUROPE                             ", .product_id_number =0x009A  }, //Home Automation Europe
{.product_id_name = "MFG_ID_HOME_DIRECTOR                                      ", .product_id_number =0x0038  }, //Home Director
{.product_id_name = "MFG_ID_HOMEMANAGEABLES_INC                                ", .product_id_number =0x0070  }, //Homemanageables, Inc.
{.product_id_name = "MFG_ID_HOMEPRO                                            ", .product_id_number =0x0050  }, //Homepro
{.product_id_name = "MFG_ID_HOMESCENARIO                                       ", .product_id_number =0x0162  }, //HomeScenario
{.product_id_name = "MFG_ID_HOMESEER_TECHNOLOGIES                              ", .product_id_number =0x000C  }, //HomeSeer Technologies
{.product_id_name = "MFG_ID_HONEYWELL                                          ", .product_id_number =0x0039  }, //Honeywell
{.product_id_name = "MFG_ID_HORSTMANN_CONTROLS_LIMITED                         ", .product_id_number =0x0059  }, //Horstmann Controls Limited
{.product_id_name = "MFG_ID_ICOM_TECHNOLOGY_BV                                 ", .product_id_number =0x0011  }, //iCOM Technology b.v.
{.product_id_name = "MFG_ID_INGERSOLL_RAND_SCHLAGE                             ", .product_id_number =0x006C  }, //Ingersoll Rand (Schlage)
{.product_id_name = "MFG_ID_INGERSOLL_RAND_ECOLINK                             ", .product_id_number =0x011F  }, //Ingersoll Rand (Former Ecolink)
{.product_id_name = "MFG_ID_INLON_SRL                                          ", .product_id_number =0x003A  }, //Inlon Srl
{.product_id_name = "MFG_ID_INNOBAND_TECHNOLOGIES_INC                          ", .product_id_number =0x0141  }, //Innoband Technologies, Inc
{.product_id_name = "MFG_ID_INNOVUS                                            ", .product_id_number =0x0077  }, //INNOVUS
{.product_id_name = "MFG_ID_INTEL                                              ", .product_id_number =0x0006  }, //Intel
{.product_id_name = "MFG_ID_INTELLICON                                         ", .product_id_number =0x001C  }, //IntelliCon
{.product_id_name = "MFG_ID_INTERMATIC                                         ", .product_id_number =0x0005  }, //Intermatic
{.product_id_name = "MFG_ID_INTERNET_DOM                                       ", .product_id_number =0x0013  }, //Internet Dom
{.product_id_name = "MFG_ID_IR_SEC_SAFETY                                      ", .product_id_number =0x003B  }, //IR Sec. & Safety
{.product_id_name = "MFG_ID_IWATSU                                             ", .product_id_number =0x0123  }, //IWATSU
{.product_id_name = "MFG_ID_JASCO_PRODUCTS                                     ", .product_id_number =0x3031  }, //Jasco Products
{.product_id_name = "MFG_ID_KAMSTRUP_AS                                        ", .product_id_number =0x0091  }, //Kamstrup A/S
{.product_id_name = "MFG_ID_LAGOTEK_CORPORATION                                ", .product_id_number =0x0051  }, //Lagotek Corporation
{.product_id_name = "MFG_ID_LEVITON                                            ", .product_id_number =0x001D  }, //Leviton
{.product_id_name = "MFG_ID_LIFESTYLE_NETWORKS                                 ", .product_id_number =0x003C  }, //Lifestyle Networks
{.product_id_name = "MFG_ID_LINEAR_CORP                                        ", .product_id_number =0x014F  }, //Linear Corp
{.product_id_name = "MFG_ID_LIVING_STYLE_ENTERPRISES_LTD                       ", .product_id_number =0x013A  }, //Living Style Enterprises, Ltd.
{.product_id_name = "MFG_ID_LOGITECH                                           ", .product_id_number =0x007F  }, //Logitech
{.product_id_name = "MFG_ID_LOUDWATER_TECHNOLOGIES_LLC                         ", .product_id_number =0x0025  }, //Loudwater Technologies, LLC
{.product_id_name = "MFG_ID_LS_CONTROL                                         ", .product_id_number =0x0071  }, //LS Control
{.product_id_name = "MFG_ID_MARMITEK_BV                                        ", .product_id_number =0x003D  }, //Marmitek BV
{.product_id_name = "MFG_ID_MARTEC_ACCESS_PRODUCTS                             ", .product_id_number =0x003E  }, //Martec Access Products
{.product_id_name = "MFG_ID_MB_TURN_KEY_DESIGN                                 ", .product_id_number =0x008F  }, //MB Turn Key Design
{.product_id_name = "MFG_ID_MERTEN                                             ", .product_id_number =0x007A  }, //Merten
{.product_id_name = "MFG_ID_MITSUMI                                            ", .product_id_number =0x0112  }, //MITSUMI
{.product_id_name = "MFG_ID_MONSTER_CABLE                                      ", .product_id_number =0x007E  }, //Monster Cable
{.product_id_name = "MFG_ID_MOTOROLA                                           ", .product_id_number =0x003F  }, //Motorola
{.product_id_name = "MFG_ID_MTC_MAINTRONIC_GERMANY                             ", .product_id_number =0x0083  }, //MTC Maintronic Germany
{.product_id_name = "MFG_ID_NAPCO_SECURITY_TECHNOLOGIES_INC                    ", .product_id_number =0x0121  }, //Napco Security Technologies, Inc.
{.product_id_name = "MFG_ID_NORTHQ                                             ", .product_id_number =0x0096  }, //NorthQ
{.product_id_name = "MFG_ID_NOVAR_ELECTRICAL_DEVICES_AND_SYSTEMS_EDS           ", .product_id_number =0x0040  }, //Novar Electrical Devices and Systems (EDS)
{.product_id_name = "MFG_ID_OMNIMA_LIMITED                                     ", .product_id_number =0x0119  }, //Omnima Limited
{.product_id_name = "MFG_ID_ONSITE_PRO                                         ", .product_id_number =0x014C  }, //OnSite Pro
{.product_id_name = "MFG_ID_OPENPEAK_INC                                       ", .product_id_number =0x0041  }, //OpenPeak Inc.
{.product_id_name = "MFG_ID_PHILIO_TECHNOLOGY_CORP                             ", .product_id_number =0x013C  }, //Philio Technology Corp
{.product_id_name = "MFG_ID_POLYCONTROL                                        ", .product_id_number =0x010E  }, //Poly-control
{.product_id_name = "MFG_ID_POWERLYNX                                          ", .product_id_number =0x0016  }, //PowerLynx
{.product_id_name = "MFG_ID_PRAGMATIC_CONSULTING_INC                           ", .product_id_number =0x0042  }, //Pragmatic Consulting Inc.
{.product_id_name = "MFG_ID_PULSE_TECHNOLOGIES_ASPALIS                         ", .product_id_number =0x005D  }, //Pulse Technologies (Aspalis)
{.product_id_name = "MFG_ID_QEES                                               ", .product_id_number =0x0095  }, //Qees
{.product_id_name = "MFG_ID_QUBY                                               ", .product_id_number =0x0130  }, //Quby
{.product_id_name = "MFG_ID_RADIO_THERMOSTAT_COMPANY_OF_AMERICA_RTC            ", .product_id_number =0x0098  }, //Radio Thermostat Company of America (RTC)
{.product_id_name = "MFG_ID_RARITAN                                            ", .product_id_number =0x008E  }, //Raritan
{.product_id_name = "MFG_ID_REITZGROUPDE                                       ", .product_id_number =0x0064  }, //Reitz-Group.de
{.product_id_name = "MFG_ID_REMOTEC_TECHNOLOGY_LTD                             ", .product_id_number =0x5254  }, //Remotec Technology Ltd
{.product_id_name = "MFG_ID_RESIDENTIAL_CONTROL_SYSTEMS_INC_RCS                ", .product_id_number =0x0010  }, //Residential Control Systems, Inc. (RCS)
{.product_id_name = "MFG_ID_RIMPORT_LTD                                        ", .product_id_number =0x0147  }, //R-import Ltd.
{.product_id_name = "MFG_ID_RS_SCENE_AUTOMATION                                ", .product_id_number =0x0065  }, //RS Scene Automation
{.product_id_name = "MFG_ID_SAECO                                              ", .product_id_number =0x0139  }, //Saeco
{.product_id_name = "MFG_ID_SAN_SHIH_ELECTRICAL_ENTERPRISE_CO_LTD              ", .product_id_number =0x0093  }, //San Shih Electrical Enterprise Co., Ltd.
{.product_id_name = "MFG_ID_SANAV                                              ", .product_id_number =0x012C  }, //SANAV
{.product_id_name = "MFG_ID_SCIENTIA_TECHNOLOGIES_INC                          ", .product_id_number =0x001F  }, //Scientia Technologies, Inc.
{.product_id_name = "MFG_ID_SECURE_WIRELESS                                    ", .product_id_number =0x011E  }, //Secure Wireless
{.product_id_name = "MFG_ID_SELUXIT                                            ", .product_id_number =0x0069  }, //Seluxit
{.product_id_name = "MFG_ID_SENMATIC_AS                                        ", .product_id_number =0x0043  }, //Senmatic A/S
{.product_id_name = "MFG_ID_SEQUOIA_TECHNOLOGY_LTD                             ", .product_id_number =0x0044  }, //Sequoia Technology LTD
{.product_id_name = "MFG_ID_SIGMA_DESIGNS                                      ", .product_id_number =0x0000  }, //Sigma Designs
{.product_id_name = "MFG_ID_SINE_WIRELESS                                      ", .product_id_number =0x0045  }, //Sine Wireless
{.product_id_name = "MFG_ID_SMART_PRODUCTS_INC                                 ", .product_id_number =0x0046  }, //Smart Products, Inc.
{.product_id_name = "MFG_ID_SMK_MANUFACTURING_INC                              ", .product_id_number =0x0102  }, //SMK Manufacturing Inc.
{.product_id_name = "MFG_ID_SOMFY                                              ", .product_id_number =0x0047  }, //Somfy
{.product_id_name = "MFG_ID_SYLVANIA                                           ", .product_id_number =0x0009  }, //Sylvania
{.product_id_name = "MFG_ID_SYSTECH_CORPORATION                                ", .product_id_number =0x0136  }, //Systech Corporation
{.product_id_name = "MFG_ID_TEAM_PRECISION_PCL                                 ", .product_id_number =0x0089  }, //Team Precision PCL
{.product_id_name = "MFG_ID_TECHNIKU                                           ", .product_id_number =0x000A  }, //Techniku
{.product_id_name = "MFG_ID_TELL_IT_ONLINE                                     ", .product_id_number =0x0012  }, //Tell It Online
{.product_id_name = "MFG_ID_TELSEY                                             ", .product_id_number =0x0048  }, //Telsey
{.product_id_name = "MFG_ID_THERE_CORPORATION                                  ", .product_id_number =0x010C  }, //There Corporation
{.product_id_name = "MFG_ID_TKB_HOME                                           ", .product_id_number =0x0118  }, //TKB Home
{.product_id_name = "MFG_ID_TKH_GROUP_EMINENT                                  ", .product_id_number =0x011C  }, //TKH Group / Eminent
{.product_id_name = "MFG_ID_TRANE_CORPORATION                                  ", .product_id_number =0x008B  }, //Trane Corporation
{.product_id_name = "MFG_ID_TRICKLESTAR                                        ", .product_id_number =0x0066  }, //TrickleStar
{.product_id_name = "MFG_ID_TRICKLESTAR_LTD_EMPOWER_CONTROLS_LTD               ", .product_id_number =0x006B  }, //Tricklestar Ltd. (former Empower Controls Ltd.)
{.product_id_name = "MFG_ID_TRIDIUM                                            ", .product_id_number =0x0055  }, //Tridium
{.product_id_name = "MFG_ID_TWISTHINK                                          ", .product_id_number =0x0049  }, //Twisthink
{.product_id_name = "MFG_ID_UNIVERSAL_ELECTRONICS_INC                          ", .product_id_number =0x0020  }, //Universal Electronics Inc.
{.product_id_name = "MFG_ID_VDA                                                ", .product_id_number =0x010A  }, //VDA
{.product_id_name = "MFG_ID_VERO_DUCO                                          ", .product_id_number =0x0080  }, //Vero Duco
{.product_id_name = "MFG_ID_VIEWSONIC_CORPORATION                              ", .product_id_number =0x005E  }, //ViewSonic Corporation
{.product_id_name = "MFG_ID_VIMAR_CRS                                          ", .product_id_number =0x0007  }, //Vimar CRS
{.product_id_name = "MFG_ID_VISION_SECURITY                                    ", .product_id_number =0x0109  }, //Vision Security
{.product_id_name = "MFG_ID_VISUALIZE                                          ", .product_id_number =0x004A  }, //Visualize
{.product_id_name = "MFG_ID_WATT_STOPPER                                       ", .product_id_number =0x004B  }, //Watt Stopper
{.product_id_name = "MFG_ID_WAYNE_DALTON                                       ", .product_id_number =0x0008  }, //Wayne Dalton
{.product_id_name = "MFG_ID_WENZHOU_MTLC_ELECTRIC_APPLIANCES_COLTD             ", .product_id_number =0x011A  }, //Wenzhou MTLC Electric Appliances Co.,Ltd.
{.product_id_name = "MFG_ID_WIDOM                                              ", .product_id_number =0x0149  }, //wiDom
{.product_id_name = "MFG_ID_WILSHINE_HOLDING_CO_LTD                            ", .product_id_number =0x012D  }, //Wilshine Holding Co., Ltd
{.product_id_name = "MFG_ID_WINTOP                                             ", .product_id_number =0x0097  }, //Wintop
{.product_id_name = "MFG_ID_WOODWARD_LABS                                      ", .product_id_number =0x004C  }, //Woodward Labs
{.product_id_name = "MFG_ID_WRAP                                               ", .product_id_number =0x0003  }, //Wrap
{.product_id_name = "MFG_ID_WUHAN_NWD_TECHNOLOGY_CO_LTD                        ", .product_id_number =0x012E  }, //Wuhan NWD Technology Co., Ltd.
{.product_id_name = "MFG_ID_XANBOO                                             ", .product_id_number =0x004D  }, //Xanboo
{.product_id_name = "MFG_ID_ZDATA_LLC                                          ", .product_id_number =0x004E  }, //Zdata, LLC.
{.product_id_name = "MFG_ID_ZIPATO                                             ", .product_id_number =0x0131  }, //Zipato
{.product_id_name = "MFG_ID_ZONOFF                                             ", .product_id_number =0x0120  }, //Zonoff
{.product_id_name = "MFG_ID_ZWAVE_TECHNOLOGIA                                  ", .product_id_number =0x004F  }, //Z-Wave Technologia
{.product_id_name = "MFG_ID_ZWAVEME                                            ", .product_id_number =0x0115  }, //Z-Wave.Me
{.product_id_name = "MFG_ID_ZYKRONIX                                           ", .product_id_number =0x0021  }, //Zykronix
{.product_id_name = "MFG_ID_ZYXEL                                              ", .product_id_number =0x0135  }, //ZyXEL

};

Manu_class_suport_t class_suport_t[manu_class_suport_max] = {
{.command_class_suport =  " ALARM                                                             ",.class_support_number = 0x71},
{.command_class_suport =  " APPLICATION_STATUS                                                ",.class_support_number = 0x22},
{.command_class_suport =  " ASSOCIATION_COMMAND_CONFIGURATION                                 ",.class_support_number = 0x9B},
{.command_class_suport =  " ASSOCIATION                                                       ",.class_support_number = 0x85},
{.command_class_suport =  " AV_CONTENT_DIRECTORY_MD                                           ",.class_support_number = 0x95},
{.command_class_suport =  " AV_CONTENT_SEARCH_MD                                              ",.class_support_number = 0x97},
{.command_class_suport =  " AV_RENDERER_STATUS                                                ",.class_support_number = 0x96},
{.command_class_suport =  " AV_TAGGING_MD                                                     ",.class_support_number = 0x99},
{.command_class_suport =  " BASIC_TARIFF_INFO                                                 ",.class_support_number = 0x36},
{.command_class_suport =  " BASIC_WINDOW_COVERING                                             ",.class_support_number = 0x50},
{.command_class_suport =  " BASIC                                                             ",.class_support_number = 0x20},
{.command_class_suport =  " BATTERY                                                           ",.class_support_number = 0x80},
{.command_class_suport =  " CHIMNEY_FAN                                                       ",.class_support_number = 0x2A},
{.command_class_suport =  " CLIMATE_CONTROL_SCHEDULE                                          ",.class_support_number = 0x46},
{.command_class_suport =  " CLOCK                                                             ",.class_support_number = 0x81},
{.command_class_suport =  " CONFIGURATION                                                     ",.class_support_number = 0x70},
{.command_class_suport =  " CONTROLLER_REPLICATION                                            ",.class_support_number = 0x21},
{.command_class_suport =  " CRC_16_ENCAP                                                      ",.class_support_number = 0x56},
{.command_class_suport =  " DCP_CONFIG                                                        ",.class_support_number = 0x3A},
{.command_class_suport =  " DCP_MONITOR                                                       ",.class_support_number = 0x3B},
{.command_class_suport =  " DOOR_LOCK_LOGGING                                                 ",.class_support_number = 0x4C},
{.command_class_suport =  " DOOR_LOCK                                                         ",.class_support_number = 0x62},
{.command_class_suport =  " ENERGY_PRODUCTION                                                 ",.class_support_number = 0x90},
{.command_class_suport =  " FIRMWARE_UPDATE_MD                                                ",.class_support_number = 0x7A},
{.command_class_suport =  " GEOGRAPHIC_LOCATION                                               ",.class_support_number = 0x8C},
{.command_class_suport =  " GROUPING_NAME                                                     ",.class_support_number = 0x7B},
{.command_class_suport =  " HAIL                                                              ",.class_support_number = 0x82},
{.command_class_suport =  " HRV_CONTROL                                                       ",.class_support_number = 0x39},
{.command_class_suport =  " HRV_STATUS                                                        ",.class_support_number = 0x37},
{.command_class_suport =  " INDICATOR                                                         ",.class_support_number = 0x87},
{.command_class_suport =  " IP_CONFIGURATION                                                  ",.class_support_number = 0x9A},
{.command_class_suport =  " LANGUAGE                                                          ",.class_support_number = 0x89},
{.command_class_suport =  " LOCK                                                              ",.class_support_number = 0x76},
{.command_class_suport =  " MANUFACTURER_PROPRIETARY                                          ",.class_support_number = 0x91},
{.command_class_suport =  " MANUFACTURER_SPECIFIC                                             ",.class_support_number = 0x72},
{.command_class_suport =  " MARK                                                              ",.class_support_number = 0xEF},
{.command_class_suport =  " METER_PULSE                                                       ",.class_support_number = 0x35},
{.command_class_suport =  " METER_TBL_CONFIG                                                  ",.class_support_number = 0x3C},
{.command_class_suport =  " METER_TBL_MONITOR                                                 ",.class_support_number = 0x3D},
{.command_class_suport =  " METER_TBL_PUSH                                                    ",.class_support_number = 0x3E},
{.command_class_suport =  " METER                                                             ",.class_support_number = 0x32},
{.command_class_suport =  " MTP_WINDOW_COVERING                                               ",.class_support_number = 0x51},
{.command_class_suport =  " MULTI_CHANNEL_ASSOCIATION_V2                                      ",.class_support_number = 0x8E},
{.command_class_suport =  " MULTI_CHANNEL_V2                                                  ",.class_support_number = 0x60},
{.command_class_suport =  " MULTI_CMD                                                         ",.class_support_number = 0x8F},
{.command_class_suport =  " MULTI_INSTANCE_ASSOCIATION                                        ",.class_support_number = 0x8E}, /*Discontinued*/
{.command_class_suport =  " MULTI_INSTANCE                                                    ",.class_support_number = 0x60}, /*Discontinued*/
{.command_class_suport =  " NETWORK_MANAGEMENT_PROXY                                          ",.class_support_number = 0x52},
{.command_class_suport =  " NETWORK_MANAGEMENT_BASIC                                          ",.class_support_number = 0x4D},
{.command_class_suport =  " NETWORK_MANAGEMENT_INCLUSION                                      ",.class_support_number = 0x34},
{.command_class_suport =  " NO_OPERATION                                                      ",.class_support_number = 0x00},
{.command_class_suport =  " NODE_NAMING                                                       ",.class_support_number = 0x77},
{.command_class_suport =  " NON_INTEROPERABLE                                                 ",.class_support_number = 0xF0},
{.command_class_suport =  " POWERLEVEL                                                        ",.class_support_number = 0x73},
{.command_class_suport =  " PREPAYMENT_ENCAPSULATION                                          ",.class_support_number = 0x41},
{.command_class_suport =  " PREPAYMENT                                                        ",.class_support_number = 0x3F},
{.command_class_suport =  " PROPRIETARY                                                       ",.class_support_number = 0x88},
{.command_class_suport =  " PROTECTION                                                        ",.class_support_number = 0x75},
{.command_class_suport =  " RATE_TBL_CONFIG                                                   ",.class_support_number = 0x48},
{.command_class_suport =  " RATE_TBL_MONITOR                                                  ",.class_support_number = 0x49},
{.command_class_suport =  " REMOTE_ASSOCIATION_ACTIVATE                                       ",.class_support_number = 0x7C},
{.command_class_suport =  " REMOTE_ASSOCIATION                                                ",.class_support_number = 0x7D},
{.command_class_suport =  " SCENE_ACTIVATION                                                  ",.class_support_number = 0x2B},
{.command_class_suport =  " SCENE_ACTUATOR_CONF                                               ",.class_support_number = 0x2C},
{.command_class_suport =  " SCENE_CONTROLLER_CONF                                             ",.class_support_number = 0x2D},
{.command_class_suport =  " SCHEDULE_ENTRY_LOCK                                               ",.class_support_number = 0x4E},
{.command_class_suport =  " SCREEN_ATTRIBUTES                                                 ",.class_support_number = 0x93},
{.command_class_suport =  " SCREEN_ATTRIBUTES_V2                                              ",.class_support_number = 0x93},
{.command_class_suport =  " SCREEN_MD                                                         ",.class_support_number = 0x92},
{.command_class_suport =  " SCREEN_MD_V2                                                      ",.class_support_number = 0x92},
{.command_class_suport =  " SECURITY_PANEL_MODE                                               ",.class_support_number = 0x24},
{.command_class_suport =  " SECURITY_PANEL_ZONE_SENSOR                                        ",.class_support_number = 0x2F},
{.command_class_suport =  " SECURITY_PANEL_ZONE                                               ",.class_support_number = 0x2E},
{.command_class_suport =  " SECURITY                                                          ",.class_support_number = 0x98},
{.command_class_suport =  " SENSOR_ALARM                                                      ",.class_support_number = 0x9C}, /*SDS10963-4 The Sensor Alarm {.command_class_suport = "COMMAND class can be used to realize Sensor Alarms.*/
{.command_class_suport =  " SENSOR_BINARY                                                     ",.class_support_number = 0x30},
{.command_class_suport =  " SENSOR_CONFIGURATION                                              ",.class_support_number = 0x9E}, /*This {.command_class_suport = "COMMAND class adds the possibility for sensors to act on either a measured value or on a*/
{.command_class_suport =  " SENSOR_MULTILEVEL                                                 ",.class_support_number = 0x31},
{.command_class_suport =  " SILENCE_ALARM                                                     ",.class_support_number = 0x9D}, /*SDS10963-4 The Alarm Silence {.command_class_suport = "COMMAND class can be used to nuisance silence to temporarily disable the sounding*/
{.command_class_suport =  " SIMPLE_AV_CONTROL                                                 ",.class_support_number = 0x94},
{.command_class_suport =  " SWITCH_ALL                                                        ",.class_support_number = 0x27},
{.command_class_suport =  " SWITCH_BINARY                                                     ",.class_support_number = 0x25},
{.command_class_suport =  " SWITCH_MULTILEVEL                                                 ",.class_support_number = 0x26},
{.command_class_suport =  " SWITCH_TOGGLE_BINARY                                              ",.class_support_number = 0x28},
{.command_class_suport =  " SWITCH_TOGGLE_MULTILEVEL                                          ",.class_support_number = 0x29},
{.command_class_suport =  " TARIFF_CONFIG                                                     ",.class_support_number = 0x4A},
{.command_class_suport =  " TARIFF_TBL_MONITOR                                                ",.class_support_number = 0x4B},
{.command_class_suport =  " THERMOSTAT_FAN_MODE                                               ",.class_support_number = 0x44},
{.command_class_suport =  " THERMOSTAT_FAN_STATE                                              ",.class_support_number = 0x45},
{.command_class_suport =  " THERMOSTAT_HEATING                                                ",.class_support_number = 0x38},
{.command_class_suport =  " THERMOSTAT_MODE                                                   ",.class_support_number = 0x40},
{.command_class_suport =  " THERMOSTAT_OPERATING_STATE                                        ",.class_support_number = 0x42},
{.command_class_suport =  " THERMOSTAT_SETBACK                                                ",.class_support_number = 0x47},
{.command_class_suport =  " THERMOSTAT_SETPOINT                                               ",.class_support_number = 0x43},
{.command_class_suport =  " TIME_PARAMETERS                                                   ",.class_support_number = 0x8B},
{.command_class_suport =  " TIME                                                              ",.class_support_number = 0x8A},
{.command_class_suport =  " TRANSPORT_SERVICE                                                 ",.class_support_number = 0x55},
{.command_class_suport =  " USER_CODE                                                         ",.class_support_number = 0x63},
{.command_class_suport =  " VERSION                                                           ",.class_support_number = 0x86},
{.command_class_suport =  " WAKE_UP                                                           ",.class_support_number = 0x84},
{.command_class_suport =  " ZIP_6LOWPAN                                                       ",.class_support_number = 0x4F},
{.command_class_suport =  " ZIP                                                               ",.class_support_number = 0x23},
{.command_class_suport =  " APPLICATION_CAPABILITY                                            ",.class_support_number = 0x57},
{.command_class_suport =  " COLOR_CONTROL                                                     ",.class_support_number = 0x33},
{.command_class_suport =  " SCHEDULE                                                          ",.class_support_number = 0x53},
{.command_class_suport =  " NETWORK_MANAGEMENT_PRIMARY                                        ",.class_support_number = 0x54},
{.command_class_suport =  " ZIP_ND                                                            ",.class_support_number = 0x58},
{.command_class_suport =  " ASSOCIATION_GRP_INFO                                              ",.class_support_number = 0x59},
{.command_class_suport =  " DEVICE_RESET_LOCALLY                                              ",.class_support_number = 0x5A},
{.command_class_suport =  " CENTRAL_SCENE                                                     ",.class_support_number = 0x5B},
{.command_class_suport =  " IP_ASSOCIATION                                                    ",.class_support_number = 0x5C},
{.command_class_suport =  " ANTITHEFT                                                         ",.class_support_number = 0x5D},
{.command_class_suport =  " ZWAVEPLUS_INFO                                                    ",.class_support_number = 0x5E}, /*SDS11907-3*/
{.command_class_suport =  " ZIP_GATEWAY                                                       ",.class_support_number = 0x5F},
{.command_class_suport =  " ZIP_PORTAL                                                        ",.class_support_number = 0x61},
{.command_class_suport =  " APPLIANCE                                                         ",.class_support_number = 0x64},
{.command_class_suport =  " DMX                                                               ",.class_support_number = 0x65},
{.command_class_suport =  " BARRIER_OPERATOR                                                  ",.class_support_number = 0x66},
};

Manufacture_id_value_t manu_id[manu_pID_max] = {
{.manufacture = " NOT_DEFINED_OR_UNDEFINED                           ", .manufacture_id_value =0xFFFF  }, //Not defined or un-defined
{.manufacture = " 2B_ELECTRONICS                                     ", .manufacture_id_value =0x0028  }, //2B Electronics
{.manufacture = " 2GIG_TECHNOLOGIES_INC                              ", .manufacture_id_value =0x009B  }, //2gig Technologies Inc.
{.manufacture = " 3E_TECHNOLOGIES                                    ", .manufacture_id_value =0x002A  }, //3e Technologies
{.manufacture = " A1_COMPONENTS                                      ", .manufacture_id_value =0x0022  }, //A-1 Components
{.manufacture = " ABILIA                                             ", .manufacture_id_value =0x0117  }, //Abilia
{.manufacture = " ACT_ADVANCED_CONTROL_TECHNOLOGIES                  ", .manufacture_id_value =0x0001  }, //ACT - Advanced Control Technologies
{.manufacture = " AEON_LABS                                          ", .manufacture_id_value =0x0086  }, //AEON Labs
{.manufacture = " AIRLINE_MECHANICAL_CO_LTD                          ", .manufacture_id_value =0x0111  }, //Airline Mechanical Co., Ltd.
{.manufacture = " ALARMCOM                                           ", .manufacture_id_value =0x0094  }, //Alarm.com
{.manufacture = " ASIA_HEADING                                       ", .manufacture_id_value =0x0029  }, //Asia Heading
{.manufacture = " ATECH                                              ", .manufacture_id_value =0x002B  }, //Atech
{.manufacture = " BALBOA_INSTRUMENTS                                 ", .manufacture_id_value =0x0018  }, //Balboa Instruments
{.manufacture = " BENEXT                                             ", .manufacture_id_value =0x008A  }, //BeNext
{.manufacture = " BESAFER                                            ", .manufacture_id_value =0x002C  }, //BeSafer
{.manufacture = " BFT_SPA                                            ", .manufacture_id_value =0x014B  }, //BFT S.p.A.
{.manufacture = " BOCA_DEVICES                                       ", .manufacture_id_value =0x0023  }, //Boca Devices
{.manufacture = " BROADBAND_ENERGY_NETWORKS_INC                      ", .manufacture_id_value =0x002D  }, //Broadband Energy Networks Inc.
{.manufacture = " BULOGICS                                           ", .manufacture_id_value =0x0026  }, //BuLogics
{.manufacture = " CAMEO_COMMUNICATIONS_INC                           ", .manufacture_id_value =0x009C  }, //Cameo Communications Inc.
{.manufacture = " CARRIER                                            ", .manufacture_id_value =0x002E  }, //Carrier
{.manufacture = " CASAWORKS                                          ", .manufacture_id_value =0x000B  }, //CasaWorks
{.manufacture = " CHECKIT_SOLUTIONS_INC                              ", .manufacture_id_value =0x014E  }, //Check-It Solutions Inc.
{.manufacture = " CHROMAGIC_TECHNOLOGIES_CORPORATION                 ", .manufacture_id_value =0x0116  }, //Chromagic Technologies Corporation
{.manufacture = " COLOR_KINETICS_INCORPORATED                        ", .manufacture_id_value =0x002F  }, //Color Kinetics Incorporated
{.manufacture = " COMPUTIME                                          ", .manufacture_id_value =0x0140  }, //Computime
{.manufacture = " CONNECTED_OBJECT                                   ", .manufacture_id_value =0x011B  }, //Connected Object
{.manufacture = " CONTROLTHINK_LC                                    ", .manufacture_id_value =0x0019  }, //ControlThink LC
{.manufacture = " CONVERGEX_LTD                                      ", .manufacture_id_value =0x000F  }, //ConvergeX Ltd.
{.manufacture = " COOPER_LIGHTING                                    ", .manufacture_id_value =0x0079  }, //Cooper Lighting
{.manufacture = " COOPER_WIRING_DEVICES                              ", .manufacture_id_value =0x001A  }, //Cooper Wiring Devices
{.manufacture = " CORNUCOPIA_CORP                                    ", .manufacture_id_value =0x012D  }, //Cornucopia Corp
{.manufacture = " COVENTIVE_TECHNOLOGIES_INC                         ", .manufacture_id_value =0x009D  }, //Coventive Technologies Inc.
{.manufacture = " CYBERHOUSE                                         ", .manufacture_id_value =0x0014  }, //Cyberhouse
{.manufacture = " CYBERTAN_TECHNOLOGY_INC                            ", .manufacture_id_value =0x0067  }, //CyberTAN Technology, Inc.
{.manufacture = " CYTECH_TECHNOLOGY_PRE_LTD                          ", .manufacture_id_value =0x0030  }, //Cytech Technology Pre Ltd.
{.manufacture = " DANFOSS                                            ", .manufacture_id_value =0x0002  }, //Danfoss
{.manufacture = " DEFACONTROLS_BV                                    ", .manufacture_id_value =0x013F  }, //Defacontrols BV
{.manufacture = " DESTINY_NETWORKS                                   ", .manufacture_id_value =0x0031  }, //Destiny Networks
{.manufacture = " DIEHL_AKO                                          ", .manufacture_id_value =0x0103  }, //Diehl AKO
{.manufacture = " DIGITAL_5_INC                                      ", .manufacture_id_value =0x0032  }, //Digital 5, Inc.
{.manufacture = " DYNAQUIP_CONTROLS                                  ", .manufacture_id_value =0x0132  }, //DynaQuip Controls
{.manufacture = " ECOLINK                                            ", .manufacture_id_value =0x014A  }, //Ecolink
{.manufacture = " EKA_SYSTEMS                                        ", .manufacture_id_value =0x0087  }, //Eka Systems
{.manufacture = " ELECTRONIC_SOLUTIONS                               ", .manufacture_id_value =0x0033  }, //Electronic Solutions
{.manufacture = " ELGEV_ELECTRONICS_LTD                              ", .manufacture_id_value =0x0034  }, //El-Gev Electronics LTD
{.manufacture = " ELK_PRODUCTS_INC                                   ", .manufacture_id_value =0x001B  }, //ELK Products, Inc.
{.manufacture = " EMBEDIT_AS                                         ", .manufacture_id_value =0x0035  }, //Embedit A/S
{.manufacture = " ENBLINK_CO_LTD                                     ", .manufacture_id_value =0x014D  }, //Enblink Co. Ltd
{.manufacture = " EUROTRONICS                                        ", .manufacture_id_value =0x0148  }, //Eurotronics
{.manufacture = " EVERSPRING                                         ", .manufacture_id_value =0x0060  }, //Everspring
{.manufacture = " EVOLVE                                             ", .manufacture_id_value =0x0113  }, //Evolve
{.manufacture = " EXCEPTIONAL_INNOVATIONS                            ", .manufacture_id_value =0x0036  }, //Exceptional Innovations
{.manufacture = " EXHAUSTO                                           ", .manufacture_id_value =0x0004  }, //Exhausto
{.manufacture = " EXIGENT_SENSORS                                    ", .manufacture_id_value =0x009F  }, //Exigent Sensors
{.manufacture = " EXPRESS_CONTROLS                                   ", .manufacture_id_value =0x001E  }, //Express Controls (former Ryherd Ventures)
{.manufacture = " FAKRO                                              ", .manufacture_id_value =0x0085  }, //Fakro
{.manufacture = " FIBARGROUP                                         ", .manufacture_id_value =0x010F  }, //Fibargroup
{.manufacture = " FOARD_SYSTEMS                                      ", .manufacture_id_value =0x0037  }, //Foard Systems
{.manufacture = " FOLLOWGOOD_TECHNOLOGY_COMPANY_LTD                  ", .manufacture_id_value =0x0137  }, //FollowGood Technology Company Ltd.
{.manufacture = " FORTREZZ_LLC                                       ", .manufacture_id_value =0x0084  }, //FortrezZ LLC
{.manufacture = " FOXCONN                                            ", .manufacture_id_value =0x011D  }, //Foxconn
{.manufacture = " FROSTDALE                                          ", .manufacture_id_value =0x0110  }, //Frostdale
{.manufacture = " GOOD_WAY_TECHNOLOGY_CO_LTD                         ", .manufacture_id_value =0x0068  }, //Good Way Technology Co., Ltd
{.manufacture = " GREENWAVE_REALITY_INC                              ", .manufacture_id_value =0x0099  }, //GreenWave Reality Inc.
{.manufacture = " HITECH_AUTOMATION                                  ", .manufacture_id_value =0x0017  }, //HiTech Automation
{.manufacture = " HOLTEC_ELECTRONICS_BV                              ", .manufacture_id_value =0x013E  }, //Holtec Electronics BV
{.manufacture = " HOME_AUTOMATED_INC                                 ", .manufacture_id_value =0x005B  }, //Home Automated Inc.
{.manufacture = " HOME_AUTOMATED_LIVING                              ", .manufacture_id_value =0x000D  }, //Home Automated Living
{.manufacture = " HOME_AUTOMATION_EUROPE                             ", .manufacture_id_value =0x009A  }, //Home Automation Europe
{.manufacture = " HOME_DIRECTOR                                      ", .manufacture_id_value =0x0038  }, //Home Director
{.manufacture = " HOMEMANAGEABLES_INC                                ", .manufacture_id_value =0x0070  }, //Homemanageables, Inc.
{.manufacture = " HOMEPRO                                            ", .manufacture_id_value =0x0050  }, //Homepro
{.manufacture = " HOMESCENARIO                                       ", .manufacture_id_value =0x0162  }, //HomeScenario
{.manufacture = " HOMESEER_TECHNOLOGIES                              ", .manufacture_id_value =0x000C  }, //HomeSeer Technologies
{.manufacture = " HONEYWELL                                          ", .manufacture_id_value =0x0039  }, //Honeywell
{.manufacture = " HORSTMANN_CONTROLS_LIMITED                         ", .manufacture_id_value =0x0059  }, //Horstmann Controls Limited
{.manufacture = " ICOM_TECHNOLOGY_BV                                 ", .manufacture_id_value =0x0011  }, //iCOM Technology b.v.
{.manufacture = " INGERSOLL_RAND_SCHLAGE                             ", .manufacture_id_value =0x006C  }, //Ingersoll Rand (Schlage)
{.manufacture = " INGERSOLL_RAND_ECOLINK                             ", .manufacture_id_value =0x011F  }, //Ingersoll Rand (Former Ecolink)
{.manufacture = " INLON_SRL                                          ", .manufacture_id_value =0x003A  }, //Inlon Srl
{.manufacture = " INNOBAND_TECHNOLOGIES_INC                          ", .manufacture_id_value =0x0141  }, //Innoband Technologies, Inc
{.manufacture = " INNOVUS                                            ", .manufacture_id_value =0x0077  }, //INNOVUS
{.manufacture = " INTEL                                              ", .manufacture_id_value =0x0006  }, //Intel
{.manufacture = " INTELLICON                                         ", .manufacture_id_value =0x001C  }, //IntelliCon
{.manufacture = " INTERMATIC                                         ", .manufacture_id_value =0x0005  }, //Intermatic
{.manufacture = " INTERNET_DOM                                       ", .manufacture_id_value =0x0013  }, //Internet Dom
{.manufacture = " IR_SEC_SAFETY                                      ", .manufacture_id_value =0x003B  }, //IR Sec. & Safety
{.manufacture = " IWATSU                                             ", .manufacture_id_value =0x0123  }, //IWATSU
{.manufacture = " JASCO_PRODUCTS                                     ", .manufacture_id_value =0x0063  }, //Jasco Products
{.manufacture = " KAMSTRUP_AS                                        ", .manufacture_id_value =0x0091  }, //Kamstrup A/S
{.manufacture = " LAGOTEK_CORPORATION                                ", .manufacture_id_value =0x0051  }, //Lagotek Corporation
{.manufacture = " LEVITON                                            ", .manufacture_id_value =0x001D  }, //Leviton
{.manufacture = " LIFESTYLE_NETWORKS                                 ", .manufacture_id_value =0x003C  }, //Lifestyle Networks
{.manufacture = " LINEAR_CORP                                        ", .manufacture_id_value =0x014F  }, //Linear Corp
{.manufacture = " LIVING_STYLE_ENTERPRISES_LTD                       ", .manufacture_id_value =0x013A  }, //Living Style Enterprises, Ltd.
{.manufacture = " LOGITECH                                           ", .manufacture_id_value =0x007F  }, //Logitech
{.manufacture = " LOUDWATER_TECHNOLOGIES_LLC                         ", .manufacture_id_value =0x0025  }, //Loudwater Technologies, LLC
{.manufacture = " LS_CONTROL                                         ", .manufacture_id_value =0x0071  }, //LS Control
{.manufacture = " MARMITEK_BV                                        ", .manufacture_id_value =0x003D  }, //Marmitek BV
{.manufacture = " MARTEC_ACCESS_PRODUCTS                             ", .manufacture_id_value =0x003E  }, //Martec Access Products
{.manufacture = " MB_TURN_KEY_DESIGN                                 ", .manufacture_id_value =0x008F  }, //MB Turn Key Design
{.manufacture = " MERTEN                                             ", .manufacture_id_value =0x007A  }, //Merten
{.manufacture = " MITSUMI                                            ", .manufacture_id_value =0x0112  }, //MITSUMI
{.manufacture = " MONSTER_CABLE                                      ", .manufacture_id_value =0x007E  }, //Monster Cable
{.manufacture = " MOTOROLA                                           ", .manufacture_id_value =0x003F  }, //Motorola
{.manufacture = " MTC_MAINTRONIC_GERMANY                             ", .manufacture_id_value =0x0083  }, //MTC Maintronic Germany
{.manufacture = " NAPCO_SECURITY_TECHNOLOGIES_INC                    ", .manufacture_id_value =0x0121  }, //Napco Security Technologies, Inc.
{.manufacture = " NORTHQ                                             ", .manufacture_id_value =0x0096  }, //NorthQ
{.manufacture = " NOVAR_ELECTRICAL_DEVICES_AND_SYSTEMS_EDS           ", .manufacture_id_value =0x0040  }, //Novar Electrical Devices and Systems (EDS)
{.manufacture = " OMNIMA_LIMITED                                     ", .manufacture_id_value =0x0119  }, //Omnima Limited
{.manufacture = " ONSITE_PRO                                         ", .manufacture_id_value =0x014C  }, //OnSite Pro
{.manufacture = " OPENPEAK_INC                                       ", .manufacture_id_value =0x0041  }, //OpenPeak Inc.
{.manufacture = " PHILIO_TECHNOLOGY_CORP                             ", .manufacture_id_value =0x013C  }, //Philio Technology Corp
{.manufacture = " POLYCONTROL                                        ", .manufacture_id_value =0x010E  }, //Poly-control
{.manufacture = " POWERLYNX                                          ", .manufacture_id_value =0x0016  }, //PowerLynx
{.manufacture = " PRAGMATIC_CONSULTING_INC                           ", .manufacture_id_value =0x0042  }, //Pragmatic Consulting Inc.
{.manufacture = " PULSE_TECHNOLOGIES_ASPALIS                         ", .manufacture_id_value =0x005D  }, //Pulse Technologies (Aspalis)
{.manufacture = " QEES                                               ", .manufacture_id_value =0x0095  }, //Qees
{.manufacture = " QUBY                                               ", .manufacture_id_value =0x0130  }, //Quby
{.manufacture = " RADIO_THERMOSTAT_COMPANY_OF_AMERICA_RTC            ", .manufacture_id_value =0x0098  }, //Radio Thermostat Company of America (RTC)
{.manufacture = " RARITAN                                            ", .manufacture_id_value =0x008E  }, //Raritan
{.manufacture = " REITZGROUPDE                                       ", .manufacture_id_value =0x0064  }, //Reitz-Group.de
{.manufacture = " REMOTEC_TECHNOLOGY_LTD                             ", .manufacture_id_value =0x5254  }, //Remotec Technology Ltd
{.manufacture = " RESIDENTIAL_CONTROL_SYSTEMS_INC_RCS                ", .manufacture_id_value =0x0010  }, //Residential Control Systems, Inc. (RCS)
{.manufacture = " RIMPORT_LTD                                        ", .manufacture_id_value =0x0147  }, //R-import Ltd.
{.manufacture = " RS_SCENE_AUTOMATION                                ", .manufacture_id_value =0x0065  }, //RS Scene Automation
{.manufacture = " SAECO                                              ", .manufacture_id_value =0x0139  }, //Saeco
{.manufacture = " SAN_SHIH_ELECTRICAL_ENTERPRISE_CO_LTD              ", .manufacture_id_value =0x0093  }, //San Shih Electrical Enterprise Co., Ltd.
{.manufacture = " SANAV                                              ", .manufacture_id_value =0x012C  }, //SANAV
{.manufacture = " SCIENTIA_TECHNOLOGIES_INC                          ", .manufacture_id_value =0x001F  }, //Scientia Technologies, Inc.
{.manufacture = " SECURE_WIRELESS                                    ", .manufacture_id_value =0x011E  }, //Secure Wireless
{.manufacture = " SELUXIT                                            ", .manufacture_id_value =0x0069  }, //Seluxit
{.manufacture = " SENMATIC_AS                                        ", .manufacture_id_value =0x0043  }, //Senmatic A/S
{.manufacture = " SEQUOIA_TECHNOLOGY_LTD                             ", .manufacture_id_value =0x0044  }, //Sequoia Technology LTD
{.manufacture = " SIGMA_DESIGNS                                      ", .manufacture_id_value =0x0000  }, //Sigma Designs
{.manufacture = " SINE_WIRELESS                                      ", .manufacture_id_value =0x0045  }, //Sine Wireless
{.manufacture = " SMART_PRODUCTS_INC                                 ", .manufacture_id_value =0x0046  }, //Smart Products, Inc.
{.manufacture = " SMK_MANUFACTURING_INC                              ", .manufacture_id_value =0x0102  }, //SMK Manufacturing Inc.
{.manufacture = " SOMFY                                              ", .manufacture_id_value =0x0047  }, //Somfy
{.manufacture = " SYLVANIA                                           ", .manufacture_id_value =0x0009  }, //Sylvania
{.manufacture = " SYSTECH_CORPORATION                                ", .manufacture_id_value =0x0136  }, //Systech Corporation
{.manufacture = " TEAM_PRECISION_PCL                                 ", .manufacture_id_value =0x0089  }, //Team Precision PCL
{.manufacture = " TECHNIKU                                           ", .manufacture_id_value =0x000A  }, //Techniku
{.manufacture = " TELL_IT_ONLINE                                     ", .manufacture_id_value =0x0012  }, //Tell It Online
{.manufacture = " TELSEY                                             ", .manufacture_id_value =0x0048  }, //Telsey
{.manufacture = " THERE_CORPORATION                                  ", .manufacture_id_value =0x010C  }, //There Corporation
{.manufacture = " TKB_HOME                                           ", .manufacture_id_value =0x0118  }, //TKB Home
{.manufacture = " TKH_GROUP_EMINENT                                  ", .manufacture_id_value =0x011C  }, //TKH Group / Eminent
{.manufacture = " TRANE_CORPORATION                                  ", .manufacture_id_value =0x008B  }, //Trane Corporation
{.manufacture = " TRICKLESTAR                                        ", .manufacture_id_value =0x0066  }, //TrickleStar
{.manufacture = " TRICKLESTAR_LTD_EMPOWER_CONTROLS_LTD               ", .manufacture_id_value =0x006B  }, //Tricklestar Ltd. (former Empower Controls Ltd.)
{.manufacture = " TRIDIUM                                            ", .manufacture_id_value =0x0055  }, //Tridium
{.manufacture = " TWISTHINK                                          ", .manufacture_id_value =0x0049  }, //Twisthink
{.manufacture = " UNIVERSAL_ELECTRONICS_INC                          ", .manufacture_id_value =0x0020  }, //Universal Electronics Inc.
{.manufacture = " VDA                                                ", .manufacture_id_value =0x010A  }, //VDA
{.manufacture = " VERO_DUCO                                          ", .manufacture_id_value =0x0080  }, //Vero Duco
{.manufacture = " VIEWSONIC_CORPORATION                              ", .manufacture_id_value =0x005E  }, //ViewSonic Corporation
{.manufacture = " VIMAR_CRS                                          ", .manufacture_id_value =0x0007  }, //Vimar CRS
{.manufacture = " VISION_SECURITY                                    ", .manufacture_id_value =0x0109  }, //Vision Security
{.manufacture = " VISUALIZE                                          ", .manufacture_id_value =0x004A  }, //Visualize
{.manufacture = " WATT_STOPPER                                       ", .manufacture_id_value =0x004B  }, //Watt Stopper
{.manufacture = " WAYNE_DALTON                                       ", .manufacture_id_value =0x0008  }, //Wayne Dalton
{.manufacture = " WENZHOU_MTLC_ELECTRIC_APPLIANCES_COLTD             ", .manufacture_id_value =0x011A  }, //Wenzhou MTLC Electric Appliances Co.,Ltd.
{.manufacture = " WIDOM                                              ", .manufacture_id_value =0x0149  }, //wiDom
{.manufacture = " WILSHINE_HOLDING_CO_LTD                            ", .manufacture_id_value =0x012D  }, //Wilshine Holding Co., Ltd
{.manufacture = " WINTOP                                             ", .manufacture_id_value =0x0097  }, //Wintop
{.manufacture = " WOODWARD_LABS                                      ", .manufacture_id_value =0x004C  }, //Woodward Labs
{.manufacture = " WRAP                                               ", .manufacture_id_value =0x0003  }, //Wrap
{.manufacture = " WUHAN_NWD_TECHNOLOGY_CO_LTD                        ", .manufacture_id_value =0x012E  }, //Wuhan NWD Technology Co., Ltd.
{.manufacture = " XANBOO                                             ", .manufacture_id_value =0x004D  }, //Xanboo
{.manufacture = " ZDATA_LLC                                          ", .manufacture_id_value =0x004E  }, //Zdata, LLC.
{.manufacture = " ZIPATO                                             ", .manufacture_id_value =0x0131  }, //Zipato
{.manufacture = " ZONOFF                                             ", .manufacture_id_value =0x0120  }, //Zonoff
{.manufacture = " ZWAVE_TECHNOLOGIA                                  ", .manufacture_id_value =0x004F  }, //Z-Wave Technologia
{.manufacture = " ZWAVEME                                            ", .manufacture_id_value =0x0115  }, //Z-Wave.Me
{.manufacture = " ZYKRONIX                                           ", .manufacture_id_value =0x0021  }, //Zykronix
{.manufacture = " ZYXEL                                              ", .manufacture_id_value =0x0135  }, //ZyXEL

};

int cmd_more(void* arg);

cmd_handler_t cmd_list[CMD_MAX] = {
    {.cmd_idx = CMD_ADD, .help = "Add a something", .cmd_func = cmd_add},
    {.cmd_idx = CMD_RM, .help = "Remove something", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_LIST, .help = "List all of nodes", .cmd_func = cmd_rm},
//    {.cmd_idx = CMD_LIST_FULL, .help = "List full of nodes", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_TURN_ON_NODE, .help = "Turn on  node", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_TURN_OFF_NODE, .help = "Turn off  node", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_GET_STATUS_NODE, .help = "Get status node", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_SET_COLOR_NODE, .help = "Set RGB color for node", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_SET_MULTILEVEL_NODE, .help = "Set multilevel for node", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_G_ADD_GROUP, .help = "Add new group", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_G_REMOVE_GROUP, .help = "Remove group", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_G_GET_LIST, .help = "List group", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_G_ADD_NODE, .help = "Add node to group", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_G_REMOVE_NODE, .help = "Remove node from group", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_G_GET_NODES, .help = "List nodes in group", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_SET_GROUP_SENSOR, .help = "Set group sensor", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_TURN_ON_GROUP, .help = "Turn on group", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_TURN_OFF_GROUP, .help = "Turn off group", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_RESET, .help = "Reset Controller to Default", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_SET_LERAN_MODE, .help = "Set Learn Mode to Controller", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_SET_SUC_NODE, .help = "Set SUC  to Controller", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_REQ_NW_UPDATE, .help = "Request network Update", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_SENDDAT, .help = "Send data to SUC", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_SET_SLAVE_LEARN_MODE, .help = "Set slave learn mode", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_NW_DUMP, .help = "Dump all network infomation of nodes", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_NW_TEST_CONNECTION, .help = "Test connection to destination NodeID ", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_DOOR_NONCE_GET, .help = "Door nonce get ", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_DOOR_OPEN, .help = "Door open ", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_DOOR_CLOSE, .help = "Door close ", .cmd_func = cmd_rm},
  //  {.cmd_idx = CMD_GET_BATTERY, .help = "Get battery level ", .cmd_func = cmd_rm},
  //  {.cmd_idx = CMD_SENSOR_MULTILEVEL_GET, .help = "Get sensor multi level ", .cmd_func = cmd_rm},
  //  {.cmd_idx = CMD_SENSOR_HEAVY_DUTY_SMART_SWITCH, .help = "Get sensor heavy duty smart switch ", .cmd_func = cmd_rm},
  //  {.cmd_idx = CMD_SET_ALAM_REPORT_ONOFF_BULBS, .help = "Set Alarm multi sensor turn ON/OFF bulb ", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_SET_CONFIGURATION_NODE, .help = "Set Configuration node ", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_FEATURE_OPTION_NODE, .help = "Using Feature of node ", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_V, .help = "Verbose", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_EXIT, .help = "Exit program", .cmd_func = NULL}
};



void cmd_print_help()
{
    int i = 0;
    printf("\n");
    for (i = 0; i < CMD_MAX; i++)
        printf("%d: \t: %s \n", cmd_list[i].cmd_idx, cmd_list[i].help);
}


int is_valid_int(const char *str)
{

    //
    if (!*str)
        return 0;
    while (*str)
    {
        if (!isdigit(*str))
            return 0;
        else
            ++str;
    }

    return 1;
}
void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}  
void itoa(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}  
int change_temparature(unsigned long value)
{
    char buffer[10];
    char *char_hex;
    int hextodec;
    /*convert hex to string*/
    itoa(value,buffer);
    //printf("%s \n",buffer);
    /*convert hex string to dec*/
    hextodec = strtol(buffer,NULL,16);
    return hextodec;
}
int expo(int n)
{
    int i;
    int result = 1;
    for(i=0;i<n;i++)
    {
        result = result*10;
    }
    return result;
}

char *fgets_s(char *buffer, size_t buflen, FILE *fp)
{
    if (fgets(buffer, buflen, fp) != 0)
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
        return buffer;
    }
    return 0;
}
void *command_handling_loop(void *unused) 
{
    NOTIFY_TX_BUFFER_T pTxNotify;

    while(1)
    {
        if (g_notify.notify_status>0)
        {
            if (g_notify.notify_status==ALARM_NOTIFY)
            {
                memcpy((uint8_t*)&pTxNotify.AlarmNotify,g_notify.notify_message,sizeof(ALARM_NOTIFY_T));
                printf("Node[%02X] has alarm [%02X] with alarmType:%02X\n",pTxNotify.AlarmNotify.node_id,pTxNotify.AlarmNotify.alarm_status,pTxNotify.AlarmNotify.alarm_type);
            }else if(g_notify.notify_status==BATTERY_NOTIFY)
            {
                memcpy((uint8_t*)&pTxNotify.BatteryNotify,g_notify.notify_message,sizeof(BATTERY_NOTIFY_T));
                printf("Node[%02X] has battery level :%03u\n",pTxNotify.BatteryNotify.node_id,pTxNotify.BatteryNotify.battery_level);
            }
            else if(g_notify.notify_status==SENSOR_MULTILEVEL)
            {
                int precicsion;
                memcpy((uint8_t*)&pTxNotify.SensorMultilevelNotify,g_notify.notify_message,sizeof(SENSOR_MULTILEVEL_NOTITFY_T));
                printf("Node[%02X] has multi level :%03u\n",pTxNotify.SensorMultilevelNotify.node_id,pTxNotify.SensorMultilevelNotify.sensor_type);
                printf("Sensor typer: [%02x] precicsion: [%02x] : scale: [%02x] : size: [%02x]\n",
                            pTxNotify.SensorMultilevelNotify.sensor_type,
                            (pTxNotify.SensorMultilevelNotify.sensor_PScS & SENSOR_MULTILEVEL_REPORT_LEVEL_PRECISION_MASK_V4)>>5,
                            (pTxNotify.SensorMultilevelNotify.sensor_PScS & SENSOR_MULTILEVEL_REPORT_LEVEL_SCALE_MASK_V4)>>3,
                            pTxNotify.SensorMultilevelNotify.sensor_PScS & SENSOR_MULTILEVEL_REPORT_LEVEL_SIZE_MASK_V4);
                    precicsion = (uint16_t)expo((uint8_t)(pTxNotify.SensorMultilevelNotify.sensor_PScS & SENSOR_MULTILEVEL_REPORT_LEVEL_PRECISION_MASK_V4)>>5);

                switch(pTxNotify.SensorMultilevelNotify.sensor_type)
                {
                case SENSOR_MULTILEVEL_REPORT_TEMPERATURE_VERSION_1_V4 : //0x01
                {
                            float temperature;
                            printf("TEMPARATURE : \n");
                                if(((pTxNotify.SensorMultilevelNotify.sensor_PScS & SENSOR_MULTILEVEL_REPORT_LEVEL_SIZE_MASK_V4) == 0x01) &
                                     (((pTxNotify.SensorMultilevelNotify.sensor_PScS & SENSOR_MULTILEVEL_REPORT_LEVEL_SCALE_MASK_V4)>>3) == 0x00))
                                    {
                                         temperature = (uint16_t)(pTxNotify.SensorMultilevelNotify.sensor_Value1);
                                         printf("\t Celsius (C) : %2.2lf \n",temperature/precicsion);
                                         printf("\t Fahrenheit (F): %2.2lf\n",
                                                (temperature/precicsion)*1.8 + 32);
                                         break;
                                    }
                                else if((pTxNotify.SensorMultilevelNotify.sensor_PScS & SENSOR_MULTILEVEL_REPORT_LEVEL_SIZE_MASK_V4) == 0x02)
                                    {
                                         temperature = (uint16_t)(pTxNotify.SensorMultilevelNotify.sensor_Value1 << 8) | pTxNotify.SensorMultilevelNotify.sensor_Value2;
                                    }

                                printf("\t Fahrenheit (F) : %2.2lf \n",temperature/precicsion);
                                printf("\t Celsius (C) : %2.2lf\n",
                                    ((temperature/precicsion)-32.0)*5.0/9.0);
                                break;
                 }
                case SENSOR_MULTILEVEL_REPORT_RELATIVE_HUMIDITY_VERSION_2_V4 : //05
                {
                    float humidity;
                    printf("HUMIDITY: \n");
                    humidity = (uint16_t)pTxNotify.SensorMultilevelNotify.sensor_Value1 * 27.2;  //humidity stadard (28oC: 27.2)
                    printf("\t Percentage value (%%) : %d \n",pTxNotify.SensorMultilevelNotify.sensor_Value1);
                    printf("\t Absolute humidity (g/m3) : %2.2lf\n",(humidity/precicsion)/100);
                    break;
                }
               case SENSOR_MULTILEVEL_GET_LUMINANCE_VERSION_1_V6 : //03
                {
                    float luminance ;
                    luminance = (uint16_t)((pTxNotify.SensorMultilevelNotify.sensor_Value1 << 8) | pTxNotify.SensorMultilevelNotify.sensor_Value2);
                    printf("LUMINANCE: \n");
                    printf("\t luminance value (LUX) : %2.2lf \n",luminance);
                    break;
                }
                case SENSOR_MULTILEVEL_GET_ULTRAVIOLET_V5_V6 : //1B
                {
                   // float velocity;
                    printf("ULTRAVIOLET: \n");
                    printf("\t ultraviolet value (UV) : %2d \n",pTxNotify.SensorMultilevelNotify.sensor_Value1);
                    break ;
                }
                default:
                 break;
                }
            }
             else if(g_notify.notify_status==ASSOCIATION_GET)
             {
                 memcpy((uint8_t*)&pTxNotify.SensorMultilevelNotify,g_notify.notify_message,sizeof(SENSOR_MULTILEVEL_NOTITFY_T));
             }
            g_notify.notify_status=0;
        }
        usleep(10000);
    }
    return NULL;
}
feature_option_t feature_option[50];
int main(int argc, char *argv[])
{
    pthread_t   thread_reader;
    gLogLevel=2;
    char cmd[256];

    uint8_t group_size;
    uint8_t feature_count = 0;
   
    TZWParam *pzwParam = (TZWParam*)malloc(sizeof(TZWParam));

    uint8_t i;
    int GroupID,NodeID,SensorType,NodeID_ad,Meter_Type;
    int ret;
    ret = pthread_create(&thread_reader, NULL, command_handling_loop, NULL);
    if (ret) {
        printf("Cannot create reader thread: \n");
        exit(1);
    }
    sprintf(cmd,"%d",CMD_MAX);
    if (argc>1)
    {
        zwaveInitialize(argv[1],&g_notify);
    }
    else
    {
        zwaveInitialize("/dev/ttyUSB0",&g_notify);
    }

    //while (printf(">>>") && gets_s(&cmd[0]) != NULL)
    do
    {
        //printf("cmd: %s \n", cmd);
        if (is_valid_int(cmd))
        {
            int idx = atoi(cmd);
            switch (idx)
            {
            case CMD_ADD:
                pzwParam->command=COMMAND_CLASS_SPECIFIC_NODE_ADD;
                zwaveSendCommand(pzwParam);
                if (pzwParam->ret==0)
                {
                    uint16_t manufacturerID_temp ,productTypeID_temp,productID_temp;
                    int manu_count,command_class_count,product_id_count,product_type_count;
                    uint32_t type_pro_temp;
                   
                    
             /*       mainlog(logUI,"TEST: NodeID[%02X], node type[%02X] has mID:%02X%02X, pID:%02X%02X::%02X%02X",pzwParam->node.node_id,pzwParam->node.node_type,
                                                                            pzwParam->node.node_manufacture.manufacturerID[0],
                                                                            pzwParam->node.node_manufacture.manufacturerID[1],
                                                                            pzwParam->node.node_manufacture.productTypeID[0],
                                                                            pzwParam->node.node_manufacture.productTypeID[1],
                                                                            pzwParam->node.node_manufacture.productID[0],
                                                                            pzwParam->node.node_manufacture.productID[1]); */
                    //manufacture_id.manufacture_id_value = pzwParam->node.node_manufacture.manufacturerID[0] ;
                    mainlog(logUI,"TEST: NodeID[%02X], node type[%02X]", pzwParam->node.node_id,pzwParam->node.node_type ) ;
                    feature_option[feature_count].feature_id = pzwParam->node.node_id;
                    

                    manufacturerID_temp  = (pzwParam->node.node_manufacture.manufacturerID[0] << 8)
                                                               | pzwParam->node.node_manufacture.manufacturerID[1];

                    productTypeID_temp = (pzwParam->node.node_manufacture.productTypeID[0] << 8 ) 
                                                                | pzwParam->node.node_manufacture.productTypeID[1];

                    productID_temp = ( pzwParam->node.node_manufacture.productID[0] << 8 ) 
                                                                | pzwParam->node.node_manufacture.productID[1];

                    type_pro_temp = (uint32_t)(productTypeID_temp << 16) | productID_temp;
                    for(manu_count =0;manu_count<manu_max;manu_count++)
                    {
                        if(manufacturerID_temp == manu_id[manu_count].manufacture_id_value)
                        {
                            printf("Manufacturer: %s \n",manu_id[manu_count].manufacture);
                        }
                    }
                    //printf("%X  ",type_pro_temp);
                    for(product_type_count =0;product_type_count < manu_pType_max;product_type_count++)
                    {
                        
                        if(type_pro_temp == product_type_id_t[product_type_count].product_type_id_number)
                        {
                            //printf("%02X",productTypeID_temp);
                            printf("Product type: %s \n",product_type_id_t[product_type_count].product_type_name);
                        }
                    }
                    for(product_id_count = 0;product_id_count < manu_pID_max;product_id_count++)
                    {
                        if( productID_temp == product_id_t[product_id_count].product_id_number )
                        {
                            printf("product_id_name: %s \n",product_id_t[product_id_count].product_id_name);
                        }
                    } 
                   // feature_option[feature_count].feature_num = 0;
                    int feature_class_count = 0;
                    printf("\tCommand class support: \n");
                    for (i=0;i<pzwParam->node.node_capability.noCapability;i++)
                    {
                       // printf(":%02X",pzwParam->node.node_capability.aCapability[i]);
                        for(command_class_count = 0;command_class_count<manu_class_suport_max;command_class_count++)
                        {
                            if(pzwParam->node.node_capability.aCapability[i] == class_suport_t[command_class_count].class_support_number)
                            {
                                printf("\t\t%s\n",class_suport_t[command_class_count].command_class_suport);
                                feature_option[feature_count].feature_class[feature_class_count] = class_suport_t[command_class_count] ;
                              //  feature_option[feature_count].feature_num ++;
                                feature_class_count++;
                                
                            }
                        }
                    }
                    feature_option[feature_count].feature_num = feature_class_count;
                }feature_count++;
                break;
            case CMD_RM:
                pzwParam->command=COMMAND_CLASS_SPECIFIC_NODE_REMOVE;
                zwaveSendCommand(pzwParam);
                if (pzwParam->ret==0)
                {
                    mainlog(logUI,"TEST: NodeID=0x%02X, NodeType=0x%02X",pzwParam->node.node_id,pzwParam->node.node_type);
                }
                break;
            case CMD_LIST:
                pzwParam->command=COMMAND_CLASS_SPECIFIC_NODE_GET_LIST;
                zwaveSendCommand(pzwParam);
                for (i=0;i<pzwParam->param1;i++)
                {
                    mainlog(logUI,"TEST: NodeID=0x%02X, NodeType=0x%02X",pzwParam->node_list[i].node_id,pzwParam->node_list[i].node_type);   
                }

                break;
    
            case CMD_TURN_ON_NODE:
                printf("Please provide the NodeID: ");
                if (scanf("%X",&NodeID)==1)
                {
                    pzwParam->command=COMMAND_CLASS_SWITCH_ALL;
                    pzwParam->param1=COMMAND_IN_NODE;
                    pzwParam->param2=NodeID;
                    pzwParam->param3=SWITCH_ALL_ON;
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0) 
                    {
                        mainlog(logUI,"TEST: Turn on node[0x%02X] is successful! ",NodeID);
                    }
                    else if (pzwParam->ret==-1)
                    {
                        mainlog(logUI,"TEST: Turn on node[0x%02X] is timeout! ",NodeID);
                    }
                    else 
                    {
                        mainlog(logUI,"Node [0x%02X] is not added to network",NodeID);
                    }
                }
                else
                {
                    break;
                }
                break;
            case CMD_TURN_OFF_NODE:
                printf("Please provide the NodeID: ");
                if (scanf("%X",&NodeID)==1)
                {
                    pzwParam->command=COMMAND_CLASS_SWITCH_ALL;
                    pzwParam->param1=COMMAND_IN_NODE;
                    pzwParam->param2=NodeID;
                    pzwParam->param3=SWITCH_ALL_OFF;
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0) 
                    {
                        mainlog(logUI,"TEST: Turn off node[0x%02X] is successful! ",NodeID);
                    }
                    else if (pzwParam->ret==-1)
                    {
                        mainlog(logUI,"TEST: Turn off node[0x%02X] is timeout! ",NodeID);
                    }
                    else 
                    {
                        mainlog(logUI,"TEST: Node [0x%02X] is not added to network",NodeID);
                    }
                }
                else
                {
                    break;
                }
                break;

            case CMD_GET_STATUS_NODE:
                printf("Please provide the NodeID: ");
                if (scanf("%X",&NodeID)==1)
                {
                    pzwParam->command=COMMAND_CLASS_SPECIFIC_NODE_GET_STATUS;
                    pzwParam->param1=NodeID;
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0) 
                    {
                        mainlog(logUI,"TEST: Status node[0x%02X] =%02X! ",NodeID,pzwParam->param2);
                    }
                    else if (pzwParam->ret==-1)
                    {
                        mainlog(logUI,"TEST: Get status node[0x%02X] is timeout! ",NodeID);
                    }
                }
                else
                {
                    break;
                }
                break;
            case CMD_SET_GROUP_SENSOR:
                 printf("Please enter nodeID sensor, NodeID need to add and GroupID : ");
                //int NodeID_ad;
                if(scanf("%X %X %X",&NodeID,&NodeID_ad, &GroupID) == 3)
                {
                    pzwParam->command=COMMAND_CLASS_SPECIFIC_SET_SPECIFICAION_DATA ; 
                    pzwParam->param2=NodeID;
                    pzwParam->param3 = 0x01;
                    pzwParam->cmd_set.cmd[0]=COMMAND_CLASS_ASSOCIATION;
                    pzwParam->cmd_set.cmd[1]= ASSOCIATION_SET;
                    pzwParam->cmd_set.cmd[2]= GroupID;
                    pzwParam->cmd_set.cmd[3]=NodeID_ad;
                    pzwParam->cmd_set.cmd_length=4;
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0)
                    {
                        mainlog(logUI,"TEST: Node[%02X] and Node[%02X] Alarm water group ID:%03x! ",NodeID,NodeID_ad,GroupID);
                    }
                }
                break;
            case CMD_SET_MULTILEVEL_NODE:
                printf("Please provide the NodeID and level: ");
                int level;
                if (scanf("%X %X",&NodeID,&level)==2)
                {
                    pzwParam->command=COMMAND_CLASS_SWITCH_MULTILEVEL;
                    pzwParam->param1=COMMAND_IN_NODE;
                    pzwParam->param2=NodeID;
                    pzwParam->param3=(level&0xFF);
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0) 
                    {
                        mainlog(logUI,"TEST: Set multilevel node[0x%02X] is successful! ",NodeID);
                    }
                    else if (pzwParam->ret==-1)
                    {
                        mainlog(logUI,"TEST: Set multilevel node[0x%02X] is timeout! ",NodeID);
                    }
                    else 
                    {
                        mainlog(logUI,"TEST: Node [0x%02X] is not added to network",NodeID);
                    }
                }
                else
                {
                    break;
                }
                break;
       /*     case CMD_SET_ALAM_REPORT_ONOFF_BULBS:
                printf("Please enter nodeID sensor, NodeID_ad need to add and GroupID : ");
                //int NodeID_ad;
                if(scanf("%X %X %X",&NodeID,&NodeID_ad, &GroupID) == 3)
                {
                    pzwParam->command=COMMAND_CLASS_SPECIFIC_SET_SPECIFICAION_DATA ; 
                    pzwParam->param2=NodeID;
                    pzwParam->cmd_set.cmd[0]=COMMAND_CLASS_ASSOCIATION;
                    pzwParam->cmd_set.cmd[1]= ASSOCIATION_SET;
                    pzwParam->cmd_set.cmd[2]= GroupID;
                    pzwParam->cmd_set.cmd[3]=NodeID_ad;
                    pzwParam->cmd_set.cmd_length=4;
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0)
                    {
                        mainlog(logUI,"TEST: Node[%02X] and Node[%02X] Alarm ON/OFF bulb group ID:%03x! ",NodeID,NodeID_ad,GroupID);
                    }
                }
                break;  */
            case CMD_SET_CONFIGURATION_NODE:
            printf("set timer configuration \n");
            int timer_configuration_set;
                printf("Please provide the NodeID and times to set: ");
                if (scanf("%X %X",&NodeID,&timer_configuration_set)==2)
                {
                    pzwParam->command=COMMAND_CLASS_SPECIFIC_SET_SPECIFICAION_DATA;
                    pzwParam->param2=NodeID ;
                    pzwParam->cmd_set.cmd[0] = COMMAND_CLASS_CONFIGURATION;
                    pzwParam->cmd_set.cmd[1]= CONFIGURATION_SET;
                    pzwParam->cmd_set.cmd[2]=0x03;
                  //  pzwParam->cmd_set.cmd[3]=0x01;
                    pzwParam->cmd_set.cmd[4]=timer_configuration_set;
                    pzwParam->cmd_set.cmd_length=5;
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0) 
                    {
                        mainlog(logUI,"TEST: Set configuration node[0x%02X] is successful! ",NodeID);
                    }
                    else if (pzwParam->ret==-1)
                    {
                        mainlog(logUI,"TEST: Set configuration node[0x%02X] is timeout! ",NodeID);
                    }
                    else 
                    {
                        mainlog(logUI,"TEST: Node [0x%02X] is not added to network",NodeID);
                    }
                }
                else
                {
                    break;
                }
                break;
               
            case CMD_SET_COLOR_NODE:
                printf("Please provide the NodeID and RGB: ");
                int RGB;
                if (scanf("%X %X",&NodeID,&RGB)==2)
                {
                    pzwParam->command=COMMAND_CLASS_COLOR_CONTROL;
                    pzwParam->param1=COMMAND_IN_NODE;
                    pzwParam->param2=NodeID;
                    pzwParam->param3=3;
                    pzwParam->cmd_set.cmd[0]=2;
                    pzwParam->cmd_set.cmd[1]=((RGB>>16)&0xFF);
                    pzwParam->cmd_set.cmd[2]=3;
                    pzwParam->cmd_set.cmd[3]=((RGB>>8)&0xFF);
                    pzwParam->cmd_set.cmd[4]=4;
                    pzwParam->cmd_set.cmd[5]=((RGB>>0)&0xFF);
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0) 
                    {
                        mainlog(logUI,"TEST: Set color node[0x%02X] is successful! ",NodeID);
                    }
                    else if (pzwParam->ret==-1)
                    {
                        mainlog(logUI,"TEST: Set color node[0x%02X] is timeout! ",NodeID);
                    }
                    else 
                    {
                        mainlog(logUI,"TEST: Node [0x%02X] is not added to network",NodeID);
                    }
                }
                else
                {
                    break;
                }
                break;
               
            case CMD_G_ADD_GROUP:
                printf("Please provide the GroupID: ");
                if (scanf("%X",&GroupID)==1)
                {
                    pzwParam->command=COMMAND_CLASS_SPECIFIC_GROUP_ADD_GROUP;
                    pzwParam->param1=GroupID;
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0) 
                    {
                        mainlog(logUI,"TEST: Group[0x%02X]  add new group success",GroupID);
                    }
                    else if (pzwParam->ret==-1)
                    {
                        mainlog(logUI,"TEST: Group[0x%02X] add new group error",GroupID);
                    }
                    else
                    {
                        mainlog(logUI,"TEST: Group[0x%02X] add new group already existed",GroupID);
                    }

                }
                else
                {
                    break;
                }
                break;
            case CMD_G_REMOVE_GROUP:
                printf("Please provide the GroupID: ");
                if (scanf("%X",&GroupID)==1)
                {
                    pzwParam->command=COMMAND_CLASS_SPECIFIC_GROUP_REMOVE_GROUP;
                    pzwParam->param1=GroupID;
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0) 
                    {
                        mainlog(logUI,"TEST: Group[0x%02X] remove group success",GroupID);
                    }
                    else if (pzwParam->ret==-1)
                    {
                        mainlog(logUI,"TEST: Group[0x%02X] remove group not existed",GroupID);
                    }

                }
                else
                {
                    break;
                }
                break;
            case CMD_G_GET_LIST:
                pzwParam->command=COMMAND_CLASS_SPECIFIC_GROUP_GET_LIST;
                zwaveSendCommand(pzwParam);
                group_size=pzwParam->param1;
                for(i=0;i<group_size;i++)
                {
                    mainlog(logUI,"TEST: Group %u has  GroupID=0x%02X",i,pzwParam->group_list[i]);
                }
                break;
            case CMD_G_ADD_NODE:
                pzwParam->command=COMMAND_CLASS_SPECIFIC_GROUP_ADD_NODE;
                printf("Please provide the NodeID and GroupID: ");
                if (scanf("%X %X",&NodeID,&GroupID)==2)
                {
                    pzwParam->param1=NodeID;
                    pzwParam->param2=GroupID;
                    zwaveSendCommand(pzwParam);
                }
                else
                {
                    break;
                }

                break;
            case CMD_G_REMOVE_NODE:
                pzwParam->command=COMMAND_CLASS_SPECIFIC_GROUP_REMOVE_NODE;
                printf("Please provide the NodeID and GroupID: ");
                if (scanf("%X %X",&NodeID,&GroupID)==2)
                {
                    pzwParam->param1=NodeID;
                    pzwParam->param2=GroupID;
                    zwaveSendCommand(pzwParam);
                }
                else
                {
                    break;
                }
                break;
            case CMD_G_GET_NODES:
                printf("Please provide the GroupID: ");
                if (scanf("%X",&GroupID)==1)
                {
                    pzwParam->command=COMMAND_CLASS_SPECIFIC_GROUP_GET_NODES;
                    pzwParam->param1=GroupID;
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret>0) 
                    {
                        for (i=0;i<pzwParam->ret;i++)
                        {
                            mainlog(logUI,"TEST: Group[0x%02X] includes node %u which has NodeID=0x%02X, NodeType=0x%02X",GroupID,i,pzwParam->node_list[i].node_id,pzwParam->node_list[i].node_type);
                        }
                    }
                    else
                    {
                        mainlog(logUI,"TEST: Error: Invalid group id");
                    }

                }
                else
                {
                    break;
                }
                break;
            case CMD_TURN_ON_GROUP:
                printf("Please provide the GroupID: ");
                if (scanf("%X",&GroupID)==1)
                {
                    pzwParam->command=COMMAND_CLASS_SWITCH_ALL;
                    pzwParam->param1=COMMAND_IN_GROUP;
                    pzwParam->param2=GroupID;
                    pzwParam->param3=SWITCH_ALL_ON;
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0) 
                    {
                        mainlog(logUI,"TEST: Turn on group[0x%02X] is successful! ",GroupID);
                    }
                    else if (pzwParam->ret==-1)
                    {
                        mainlog(logUI,"TEST: Turn on group[0x%02X] is timeout! ",GroupID);
                    }
                    else 
                    {
                        mainlog(logUI,"group [0x%02X] is not added to network",GroupID);
                    }
                }
                else
                {
                    break;
                }
                break;
            case CMD_TURN_OFF_GROUP:
                printf("Please provide the GroupID: ");
                if (scanf("%X",&GroupID)==1)
                {
                    pzwParam->command=COMMAND_CLASS_SWITCH_ALL;
                    pzwParam->param1=COMMAND_IN_GROUP;
                    pzwParam->param2=GroupID;
                    pzwParam->param3=SWITCH_ALL_OFF;
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0) 
                    {
                        mainlog(logUI,"TEST: Turn off group[0x%02X] is successful! ",GroupID);
                    }
                    else if (pzwParam->ret==-1)
                    {
                        mainlog(logUI,"TEST: Turn off group[0x%02X] is timeout! ",GroupID);
                    }
                    else 
                    {
                        mainlog(logUI,"group [0x%02X] is not added to network",GroupID);
                    }
                }
                else
                {
                    break;
                }
                break;
            case CMD_V:
                if (gLogLevel==99)
                {
                    gLogLevel=2;
                }
                else
                {
                    gLogLevel=99;
                }
                break;
            case CMD_RESET:
                pzwParam->command=COMMAND_CLASS_SPECIFIC_NODE_SET_DEFAULT;
                zwaveSendCommand(pzwParam);
                if (pzwParam->ret==0) 
                    {
                        mainlog(logUI,"TEST: SET DEFAULT COMMAND is successful! ");
                    }
                    else if (pzwParam->ret==-1)
                    {
                        mainlog(logUI,"TEST: SET DEFAULT COMMAND is timeout! ");
                    }
                break;

            case CMD_SET_LERAN_MODE:
                pzwParam->command=COMMAND_CLASS_SPECIFIC_NODE_SET_LEARN_MODE;
                zwaveSendCommand(pzwParam);
                break;

            case CMD_SET_SUC_NODE:

                printf("Please provide the NodeID: ");
                if (scanf("%X",&NodeID)==1)
                {
                    pzwParam->command=COMMAND_CLASS_SPECIFIC_NODE_SET_SUC_SIS_MODE;
                    pzwParam->param1=NodeID;
                    pzwParam->param2=ZW_SUC_FUNC_NODEID_SERVER;
                    zwaveSendCommand(pzwParam);
                }
                else
                {
                    break;
                }
                break;
             case CMD_SET_SLAVE_LEARN_MODE:

                printf("Please provide the NodeID: ");
                if (scanf("%X",&NodeID)==1)
                {
                    pzwParam->command=COMMAND_CLASS_SPECIFIC_NODE_SET_SLAVE_LEARN_MODE;
                    pzwParam->param1=NodeID;
                    zwaveSendCommand(pzwParam);
                }
                else
                {
                    break;
                }
                break;

            case CMD_REQ_NW_UPDATE:
                pzwParam->command=COMMAND_CLASS_SPECIFIC_NODE_REQUEST_UPDATE;
                zwaveSendCommand(pzwParam);
                break;

            case CMD_NW_DUMP:
                pzwParam->command=COMMAND_CLASS_SPECIFIC_NETWORK_DUMP_NEIGHBORS;
                zwaveSendCommand(pzwParam);
                break;

            case CMD_NW_TEST_CONNECTION:

                printf("Please provide the NodeID: ");
                if (scanf("%X",&NodeID)==1)
                {
                    pzwParam->command=COMMAND_CLASS_SPECIFIC_NETWORK_TEST_CONNECTION;
                    pzwParam->param1=NodeID;
                    zwaveSendCommand(pzwParam);
                }
                else
                {
                    break;
                }
                break;
            case CMD_DOOR_NONCE_GET:

                printf("Please provide the NodeID: ");
                if (scanf("%X",&NodeID)==1)
                {
                   nodeNonceGet((uint8_t)NodeID);
                }
                else
                {
                    break;
                }
                break;

            case CMD_DOOR_OPEN:

                printf("Please provide the NodeID: ");
                if (scanf("%X",&NodeID)==1)
                {
                   nodeDoorOpen((uint8_t)NodeID);
                }
                else
                {
                    break;
                }
                break;
            case CMD_DOOR_CLOSE:

                printf("Please provide the NodeID: ");
                if (scanf("%X",&NodeID)==1)
                {
                   nodeDoorClose((uint8_t)NodeID);
                }
                else
                {
                    break;
                }
                break;    
    /*        case CMD_GET_BATTERY:
                printf("Please provide the NodeID: ");
                if (scanf("%X",&NodeID)==1)
                {
                    pzwParam->command=COMMAND_CLASS_SPECIFIC_GET_SPECIFICAION_DATA;
                    pzwParam->param2=NodeID;
                    pzwParam->cmd_set.cmd[0]=COMMAND_CLASS_BATTERY;
                    pzwParam->cmd_set.cmd[1]=BATTERY_GET;
                    pzwParam->cmd_set.cmd_length=2;
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0)
                    {
                        mainlog(logUI,"TEST: Node[%02X] says battery level:%03u! \n",NodeID,pzwParam->data_out.cmd[2]);
                    }

                }
                else
                {
                    break;
                }
                break;
            case CMD_SENSOR_MULTILEVEL_GET:
                   // unsigned long choice = 1;
                  //  choice = (choice<<3);
                    
                    printf("Please provide the NodeID and SensorType: ");
                if(scanf("%X %X",&NodeID,&SensorType)== 2)
                {
                    pzwParam->command=COMMAND_CLASS_SPECIFIC_GET_SPECIFICAION_DATA;
                    pzwParam->param2=NodeID;
                    pzwParam->cmd_set.cmd[0]= COMMAND_CLASS_SENSOR_MULTILEVEL;
                    pzwParam->cmd_set.cmd[1]= SENSOR_MULTILEVEL_GET;
                    pzwParam->cmd_set.cmd[2]= (uint8_t)SensorType;
                    pzwParam->cmd_set.cmd[3]= 0x2A;//(1<<3); 
                    pzwParam->cmd_set.cmd[5] = 0x80;
                    pzwParam->cmd_set.cmd_length=6;
                    zwaveSendCommand(pzwParam);
                    if (pzwParam->ret==0) 
                    {
                        unsigned long result_from_hex;
                        int precicsion;
                        mainlog(logUI,"TEST: Node[%02X] says sensor level:%03u! ",NodeID,pzwParam->data_out.cmd[2]);
                        printf("Sensor typer: [%02x] precicsion: [%02x] : scale: [%02x] : size: [%02x]\n",
                            pzwParam->data_out.cmd[2],(pzwParam->data_out.cmd[3]&0x20)>>5,(pzwParam->data_out.cmd[3]& 0x18)>>3,pzwParam->data_out.cmd[3]& 0x07);
                        precicsion = (uint16_t)expo((uint8_t)(pzwParam->data_out.cmd[3]>>5));

                        switch(SensorType)
                        {
                            case SENSOR_MULTILEVEL_REPORT_TEMPERATURE_VERSION_1_V4:
                            {
                                float temperature;
                                printf("TEMPARATURE ! \n");
                                    if((pzwParam->data_out.cmd[3]& 0x07) == 0x01)
                                    {
                                         temperature = (uint16_t)pzwParam->data_out.cmd[4];
                                    }
                                    else if((pzwParam->data_out.cmd[3]& 0x07) == 0x02)
                                    {
                                         temperature = (uint16_t)((pzwParam->data_out.cmd[4]<< 8) | pzwParam->data_out.cmd[5]);
                                    }
                                    else if((pzwParam->data_out.cmd[3]& 0x07) == 0x04)
                                    {
                                         temperature = (uint16_t)((pzwParam->data_out.cmd[4]<< 24) | (pzwParam->data_out.cmd[5] <<16) 
                                                                        | (pzwParam->data_out.cmd[6]<< 8) | pzwParam->data_out.cmd[7]);  
                                    }
                                    printf("Fahrenheit (F) : %2.2lf \n",temperature/precicsion);
                                    printf("Celsius (C) : %2.2lf\n",
                                        ((temperature/precicsion)-32.0)*5.0/9.0);
                                    break;

                            }
                            case SENSOR_MULTILEVEL_REPORT_RELATIVE_HUMIDITY_VERSION_2_V4:
                            {
                                float humidity_tmp;
                                printf("HUMIDITY ! \n");
                                    humidity_tmp = (uint16_t)pzwParam->data_out.cmd[4] * 27.2 ;
                                    printf("Percentage value (%%) : %d\n",pzwParam->data_out.cmd[4]);
                                    printf("Absolute humidity (g/cm3) : %2.2lf\n",
                                    (humidity_tmp/precicsion)/100);
                                break;
                            }
                            case SENSOR_MULTILEVEL_GET_LUMINANCE_VERSION_1_V6 : //03
                            {
                                float luminance_tmp ;
                                luminance_tmp = (uint16_t)((pzwParam->data_out.cmd[4]<< 8) | pzwParam->data_out.cmd[5]);
                                printf("LUMINANCE: \n");
                                printf("\t luminance value (LUX) : %2.2lf \n",luminance_tmp);
                                break;
                            }
                            case SENSOR_MULTILEVEL_GET_ULTRAVIOLET_V5_V6 : //1B
                            {
                               // float velocity;
                                printf("ULTRAVIOLET: \n");
                                printf("\t ultraviolet value (UV) : %2d \n",pzwParam->data_out.cmd[4]);
                                break ;
                            }
                            
                        }
                    }
                }
                else
                {
                    break;
                }
                break; 
            case CMD_SENSOR_HEAVY_DUTY_SMART_SWITCH:
                    //printf("Please provide the NodeID and SensorType: ");
                    printf("1. sensor \t 2.meter \n");
                int choise;
                if(scanf("%d",&choise) == 1)
                {
                    if(choise == 1)
                    {  
                     printf("Please provide the NodeID and SensorType: ");
                    if(scanf("%X %X",&NodeID,&SensorType) == 2)
                    {
                            if((SensorType == 0x01) | (SensorType == 0x05))
                            {
                                 printf("you have chosen temperature or humidity measurement! \n");
                                pzwParam->command=COMMAND_CLASS_SPECIFIC_GET_SPECIFICAION_DATA;
                                pzwParam->param2=NodeID;
                                pzwParam->cmd_set.cmd[0]= COMMAND_CLASS_SENSOR_MULTILEVEL;
                                pzwParam->cmd_set.cmd[1]= SENSOR_MULTILEVEL_GET;
                                pzwParam->cmd_set.cmd[2]= (uint8_t)SensorType;
                                pzwParam->cmd_set.cmd[3]= (1<<3); 
                                //pzwParam->cmd_set.cmd[5] = 0x80;
                                pzwParam->cmd_set.cmd_length=8;
                                zwaveSendCommand(pzwParam);
                                if (pzwParam->ret==0) 
                                {
                                    unsigned long result_from_hex;
                                    int precicsion;
                                    mainlog(logUI,"TEST: Node[%02X] says sensor level:%02x! ",NodeID,pzwParam->data_out.cmd[2]);
                                    printf("Sensor typer: [%02x] precicsion: [%02x] : scale: [%02x] : size: [%02x]\n",
                                        pzwParam->data_out.cmd[2],(pzwParam->data_out.cmd[3]&0x20)>>5,(pzwParam->data_out.cmd[3]& 0x18)>>3,pzwParam->data_out.cmd[3]& 0x07);
                                    precicsion = (uint16_t)expo((uint8_t)(pzwParam->data_out.cmd[3]>>5));

                                    switch(SensorType)
                                    {
                                        case SENSOR_MULTILEVEL_REPORT_TEMPERATURE_VERSION_1_V4:
                                        {
                                            float temperature;
                                            printf("TEMPARATURE ! \n");
                                        
                                                temperature = (uint16_t)((pzwParam->data_out.cmd[4]<< 24) | (pzwParam->data_out.cmd[5] <<16) | (pzwParam->data_out.cmd[6]<< 8) | pzwParam->data_out.cmd[7]);
                                                printf("Fahrenheit (F) : %2.2lf \n",temperature/precicsion);
                                                printf("Celsius (C) : %2.2lf\n",
                                                    (temperature/precicsion -32.0)*5.0/9.0);
                                                break;
                                        }
                                        case SENSOR_MULTILEVEL_REPORT_RELATIVE_HUMIDITY_VERSION_2_V4:
                                        {
                                            float humidity_tmp;
                                            printf("HUMIDITY ! \n");
                                                humidity_tmp = (uint16_t)pzwParam->data_out.cmd[6] * 27.2 ;
                                                printf("Percentage value (%%) : %d\n",pzwParam->data_out.cmd[6]);
                                                printf("Absolute humidity (g/cm3) : %2.2lf\n",
                                                (humidity_tmp/precicsion)/100);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    if(choise == 2)
                    {
                        printf("enter nodeID & meter typer: ");
                        if(scanf("%X %X",&NodeID,&Meter_Type) == 2)  //0x01
                        {
                            printf("you have chosen Power measurement! \n");
                            pzwParam->command=COMMAND_CLASS_SPECIFIC_GET_SPECIFICAION_DATA;
                            pzwParam->param2=NodeID;
                            pzwParam->cmd_set.cmd[0]= COMMAND_CLASS_METER;
                            pzwParam->cmd_set.cmd[1]= METER_GET;
                            pzwParam->cmd_set.cmd[2]= (uint8_t)Meter_Type;
                            pzwParam->cmd_set.cmd[3]= 0x21 ;//(1<<4); 
                            //pzwParam->cmd_set.cmd[5] = 0x80;
                            pzwParam->cmd_set.cmd_length=10;
                            zwaveSendCommand(pzwParam);
                            if (pzwParam->ret==0) 
                            {
                                unsigned long result_from_hex;
                                int precicsion;
                                int delta_time;
                                mainlog(logUI,"TEST: Node[%02X] says sensor level:%02X! ",NodeID,pzwParam->data_out.cmd[2]);
                                printf("Sensor typer: [%02x] precicsion: [%02x] : scale: [%02x] : size: [%02x]\n",
                                    pzwParam->data_out.cmd[2],(pzwParam->data_out.cmd[3]&0x20)>>5,(pzwParam->data_out.cmd[3]& 0x18)>>3,pzwParam->data_out.cmd[3]& 0x07);
                                precicsion = (uint16_t)expo((uint8_t)(pzwParam->data_out.cmd[3]&0x020>>5));

                                
                                float  watt_measurement;
                                printf("kWah ! \n");
                            
                                watt_measurement = (uint32_t)((pzwParam->data_out.cmd[4]<< 24) | (pzwParam->data_out.cmd[5]<< 16 ) | (pzwParam->data_out.cmd[6]<< 8) | pzwParam->data_out.cmd[7]);
                                delta_time = (uint16_t)((pzwParam->data_out.cmd[8]<< 8) | pzwParam->data_out.cmd[9]);

                                printf("Electric Meter (W) : %2.2lf \n",watt_measurement/precicsion);
                                printf("Delta time (s): %d\n", delta_time);
                                printf("Power consumption(Wh): %2.5lf \n",(watt_measurement/precicsion)*delta_time /3600 );
                                printf("BTu/h (btu/h) : %2.2lf\n",
                                    ((watt_measurement/precicsion)/1000)*1.36);
                            }
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                break; */
            case CMD_FEATURE_OPTION_NODE:
                {
                    int feature_option_count,count_feature_enum , choise_feature ;
                    int count1,count2,flag,check = 1;
                    uint16_t feature_class_support_number[15];
                    printf("NodeID : ");
                    if(scanf("%X",&NodeID) == 1)
                    {
                        printf("there are main feature: \n");
                    }
                    count_feature_enum = 0;
                    count2 = 1;

                    for(count1 = 0;count1<feature_count;count1++)
                    {
                        if(NodeID == feature_option[count1].feature_id)
                        {
                              for(feature_option_count =0;feature_option_count<feature_option[count1].feature_num;feature_option_count++)
                              {  
                                if( (feature_option[count1].feature_class[feature_option_count].class_support_number == 0x31 )
                                    || (feature_option[count1].feature_class[feature_option_count].class_support_number == 0x32) 
                                    || (feature_option[count1].feature_class[feature_option_count].class_support_number == 0x71) 
                                    || (feature_option[count1].feature_class[feature_option_count].class_support_number == 0x80)
                                   // || (feature_option[count1].feature_class[feature_option_count].class_support_number == 0x84)
                                    || (feature_option[count1].feature_class[feature_option_count].class_support_number == 0x85) )
                                {
                                        printf("\t%d.\t%s\n",count_feature_enum,feature_option[count1].feature_class[feature_option_count].command_class_suport);
                                        feature_class_support_number[count_feature_enum] = feature_option[count1].feature_class[feature_option_count].class_support_number;
                                        count_feature_enum++;
                                }
                              }  flag = count1;    
                        }
                    }
                    printf("\n %d",count_feature_enum);
                    do
                    {
                        printf("Please choose your feature. \n");
                      // printf("1 .Battery Get Feature \n2 .Wake Up Feature \n3 .Association \n4 .Sensor Multilevel Feature \n5 .Metter Feature \n0. Exit \n");
                         for(feature_option_count =0;feature_option_count<=count_feature_enum;feature_option_count++)
                              { 
                                if(feature_class_support_number[feature_option_count] == 0x80)
                                    {
                                        printf(" '1' - Battery Get  \n");
                                        count2++;
                                    }
                                else if(feature_class_support_number[feature_option_count] == 0x84)
                                    {
                                        printf(" '2' - Alarm   \n");
                                        count2++;
                                    }
                                else if(feature_class_support_number[feature_option_count] == 0x85)
                                    {
                                        printf(" '3' - Association  \n");
                                        count2++;
                                    }
                                else if(feature_class_support_number[feature_option_count] == 0x31)
                                    {
                                        printf(" '4' - Sensor Multilevel  \n");
                                        count2++;
                                    }
                                else if(feature_class_support_number[feature_option_count] == 0x32)
                                    {
                                        printf(" '5' - Metter  \n");
                                        count2++;
                                    }
                              }   printf(" '0' - exit \n");
                          //    do
                            //     {
                                    
                        scanf("%d",&choise_feature);
                        switch(choise_feature)
                        {
                            case 1:
                            {
                                printf("Battery Get Feature. \n");
                                pzwParam->command=COMMAND_CLASS_SPECIFIC_GET_SPECIFICAION_DATA;
                                pzwParam->param2=NodeID;
                                pzwParam->cmd_set.cmd[0]=COMMAND_CLASS_BATTERY;
                                pzwParam->cmd_set.cmd[1]=BATTERY_GET;
                                pzwParam->cmd_set.cmd_length=2;
                                zwaveSendCommand(pzwParam);
                                if (pzwParam->ret==0)
                                {
                                    mainlog(logUI,"TEST: Node[%02X] says battery level:%03u! \n",NodeID,pzwParam->data_out.cmd[2]);
                                }

                            break;
                            }
                            case 2:
                            printf("Alarm Feature. \n");
                            break;
                            case 3:
                            {
                                    printf("Association. \n");
                                    int choise_association;
                                    printf("1. add group \t2. remove group \n");
                                    scanf("%d",&choise_association);
                                    switch(choise_association)
                                    {
                                        case 1:
                                        {
                                            printf("Please enter NodeID_ad and GroupID : ");
                                            if(scanf("%X %X",&NodeID_ad, &GroupID) == 2)
                                            {
                                                pzwParam->command=COMMAND_CLASS_SPECIFIC_SET_SPECIFICAION_DATA ; 
                                                pzwParam->param2=NodeID;
                                                pzwParam->param3 = 0x01;
                                                pzwParam->cmd_set.cmd[0]=COMMAND_CLASS_ASSOCIATION;
                                                pzwParam->cmd_set.cmd[1]= ASSOCIATION_SET;
                                                pzwParam->cmd_set.cmd[2]= GroupID;
                                                pzwParam->cmd_set.cmd[3]=NodeID_ad;
                                                pzwParam->cmd_set.cmd_length=4;
                                                zwaveSendCommand(pzwParam);
                                                if (pzwParam->ret==0)
                                                {
                                                    mainlog(logUI,"TEST: Node[%02X] and Node[%02X] Alarm water group ID:%03x! ",NodeID,NodeID_ad,GroupID);
                                                }
                                            }
                                            break;
                                        }
                                        case 2:
                                        {
                                            printf("Please enter NodeID_ad and GroupID need to remove: ");
                                            if(scanf("%X %X",&NodeID_ad, &GroupID) == 2)
                                            {
                                                pzwParam->command=COMMAND_CLASS_SPECIFIC_SET_SPECIFICAION_DATA ; 
                                                pzwParam->param2=NodeID;
                                                pzwParam->param3 = 0x01;
                                                pzwParam->cmd_set.cmd[0]=COMMAND_CLASS_ASSOCIATION;
                                                pzwParam->cmd_set.cmd[1]= ASSOCIATION_REMOVE;
                                                pzwParam->cmd_set.cmd[2]= GroupID;
                                                pzwParam->cmd_set.cmd[3]=NodeID_ad;
                                                pzwParam->cmd_set.cmd_length=4;
                                                zwaveSendCommand(pzwParam);
                                                if (pzwParam->ret==0)
                                                {
                                                    mainlog(logUI,"TEST: Node[%02X] and Node[%02X] Alarm water group ID:%03x! ",NodeID,NodeID_ad,GroupID);
                                                }
                                            }
                                            break;
                                        }
                                    }
                              break;
                            }
                            case 4:
                            {
                                int SensorType_choise;
                                printf("Sensor Multilevel Feature. \n");
                                printf("Please provide the SensorType: \n");
                                printf("1. TEMPARATURE \n2. HUMIDITY \n3. LUMINANCE \n4. ULTRAVIOLET\n5. Exit \n");
                                    if(scanf("%X",&SensorType_choise)== 1)
                                    {
                                        if(SensorType_choise == 1)
                                        {
                                            SensorType = 0x01;
                                        }
                                        else if(SensorType_choise == 2)
                                        {
                                            SensorType = 0x05;
                                        }
                                        else if(SensorType_choise == 3)
                                        {
                                            SensorType = 0x03;
                                        }
                                        else if(SensorType_choise == 4)
                                        {
                                            SensorType = 0x1B;
                                        }
                                        else if(SensorType_choise == 5)
                                        {
                                            break;
                                        }
                                        pzwParam->command=COMMAND_CLASS_SPECIFIC_GET_SPECIFICAION_DATA;
                                        pzwParam->param2=NodeID;
                                        pzwParam->cmd_set.cmd[0]= COMMAND_CLASS_SENSOR_MULTILEVEL;
                                        pzwParam->cmd_set.cmd[1]= SENSOR_MULTILEVEL_GET;
                                        pzwParam->cmd_set.cmd[2]= (uint8_t)SensorType;
                                        pzwParam->cmd_set.cmd[3]= 0x2A;//(1<<3); 
                                        pzwParam->cmd_set.cmd[5] = 0x80;
                                        pzwParam->cmd_set.cmd_length=6;
                                        zwaveSendCommand(pzwParam);
                                        if (pzwParam->ret==0) 
                                        {
                                            unsigned long result_from_hex;
                                            int precicsion;
                                            mainlog(logUI,"TEST: Node[%02X] says sensor level:%03u! ",NodeID,pzwParam->data_out.cmd[2]);
                                            printf("Sensor typer: [%02x] precicsion: [%02x] : scale: [%02x] : size: [%02x]\n",
                                                pzwParam->data_out.cmd[2],(pzwParam->data_out.cmd[3]&0x20)>>5,(pzwParam->data_out.cmd[3]& 0x18)>>3,pzwParam->data_out.cmd[3]& 0x07);
                                            precicsion = (uint16_t)expo((uint8_t)(pzwParam->data_out.cmd[3]>>5));

                                            switch(SensorType_choise)
                                            {
                                                case 1:
                                                {
                                                    float temperature;
                                                    printf("TEMPARATURE ! \n");
                                                        if((pzwParam->data_out.cmd[3]& 0x07) == 0x01)
                                                        {
                                                             temperature = (uint16_t)pzwParam->data_out.cmd[4];
                                                        }
                                                        else if((pzwParam->data_out.cmd[3]& 0x07) == 0x02)
                                                        {
                                                             temperature = (uint16_t)((pzwParam->data_out.cmd[4]<< 8) | pzwParam->data_out.cmd[5]);
                                                        }
                                                        else if((pzwParam->data_out.cmd[3]& 0x07) == 0x04)
                                                        {
                                                             temperature = (uint32_t)((pzwParam->data_out.cmd[4]<< 24) | (pzwParam->data_out.cmd[5] <<16) 
                                                                                            | (pzwParam->data_out.cmd[6]<< 8) | pzwParam->data_out.cmd[7]);  
                                                        }
                                                        printf("Fahrenheit (F) : %2.2lf \n",temperature/precicsion);
                                                        printf("Celsius (C) : %2.2lf\n",
                                                            ((temperature/precicsion)-32.0)*5.0/9.0);
                                                        break;

                                                }
                                                case 2:
                                                {
                                                    float humidity_tmp;
                                                    printf("HUMIDITY ! \n");
                                                    if((pzwParam->data_out.cmd[3]& 0x07) == 0x01)
                                                    {
                                                        humidity_tmp = (uint16_t)pzwParam->data_out.cmd[4] * 27.2 /100;
                                                        printf("Percentage value (%%) : %d\n",pzwParam->data_out.cmd[4]);
                                                    }
                                                    else if((pzwParam->data_out.cmd[3]& 0x07) == 0x02)
                                                    {
                                                        humidity_tmp = (uint16_t)((pzwParam->data_out.cmd[4]<< 8) | pzwParam->data_out.cmd[5]) * 27.2 /100;
                                                        printf("Percentage value (%%) : %d\n",pzwParam->data_out.cmd[4]);
                                                    }
                                                    else if((pzwParam->data_out.cmd[3]& 0x07) == 0x04)
                                                    {
                                                        humidity_tmp = (uint16_t)pzwParam->data_out.cmd[6] * 27.2 ;
                                                        printf("Percentage value (%%) : %d\n",pzwParam->data_out.cmd[6]);
                                                    }
                                                        printf("Absolute humidity (g/cm3) : %2.2lf\n",
                                                                                humidity_tmp/precicsion);
                                                    break;
                                                }
                                                case 3 : //03
                                                {
                                                    float luminance_tmp ;
                                                    luminance_tmp = (uint16_t)((pzwParam->data_out.cmd[4]<< 8) | pzwParam->data_out.cmd[5]);
                                                    printf("LUMINANCE: \n");
                                                    printf("\t luminance value (LUX) : %2.2lf \n",luminance_tmp);
                                                    break;
                                                }
                                                case 4 : //1B
                                                {
                                                   // float velocity;
                                                    printf("ULTRAVIOLET: \n");
                                                    printf("\t ultraviolet value (UV) : %2d \n",pzwParam->data_out.cmd[4]);
                                                    break ;
                                                }    
                                            }
                                        }
                                    }
                                break;    
                            }
                            case 5:
                            {
                            printf("Metter Feature. \n");
                            printf("1. Electric Meter \n2. Gas Meter \n3. Water Meter \n");
                            if(scanf("%X",&Meter_Type) == 1)  //0x01
                                {
                                    if(Meter_Type == 1)
                                    {
                                        Meter_Type = 0x01;
                                    printf("you have chosen Power measurement! \n");
                                    pzwParam->command=COMMAND_CLASS_SPECIFIC_GET_SPECIFICAION_DATA;
                                    pzwParam->param2=NodeID;
                                    pzwParam->cmd_set.cmd[0]= COMMAND_CLASS_METER;
                                    pzwParam->cmd_set.cmd[1]= METER_GET;
                                    pzwParam->cmd_set.cmd[2]= (uint8_t)Meter_Type;
                                    pzwParam->cmd_set.cmd[3]= 0x21 ;//(1<<4); 
                                    //pzwParam->cmd_set.cmd[5] = 0x80;
                                    pzwParam->cmd_set.cmd_length=10;
                                    zwaveSendCommand(pzwParam);
                                        if (pzwParam->ret==0) 
                                        {
                                            unsigned long result_from_hex;
                                            int precicsion;
                                            int delta_time;
                                            mainlog(logUI,"TEST: Node[%02X] says sensor level:%02X! ",NodeID,pzwParam->data_out.cmd[2]);
                                            printf("Sensor typer: [%02x] precicsion: [%02x] : scale: [%02x] : size: [%02x]\n",
                                                pzwParam->data_out.cmd[2],(pzwParam->data_out.cmd[3]&0x20)>>5,(pzwParam->data_out.cmd[3]& 0x18)>>3,pzwParam->data_out.cmd[3]& 0x07);
                                            precicsion = (uint16_t)expo((uint8_t)(pzwParam->data_out.cmd[3]&0x020>>5));

                                            
                                            float  watt_measurement;
                                            printf("kWah ! \n");
                                        
                                            watt_measurement = (uint32_t)((pzwParam->data_out.cmd[4]<< 24) | (pzwParam->data_out.cmd[5]<< 16 ) | (pzwParam->data_out.cmd[6]<< 8) | pzwParam->data_out.cmd[7]);
                                            delta_time = (uint16_t)((pzwParam->data_out.cmd[8]<< 8) | pzwParam->data_out.cmd[9]);

                                            printf("Electric Meter (W) : %2.2lf \n",watt_measurement/precicsion);
                                            printf("Delta time (s): %d\n", delta_time);
                                            printf("Power consumption(Wh): %2.5lf \n",(watt_measurement/precicsion)*delta_time /3600 );
                                            printf("BTu/h (btu/h) : %2.2lf\n",
                                                ((watt_measurement/precicsion)/1000)*1.36);
                                        }
                                    }
                                }
                            break;
                            }
                            case 0:
                            break;
                            
                        }
                        printf("1.continue \t0.stop and exit\n");
                        scanf("%d",&check);
                    }while(check != 0);

                }
                break;
            case CMD_EXIT:
                mainlog(logQuerry,"BYE BYE :-*, :-*");
                exit(0);
            default:
                cmd_print_help();
                break;
            }
        }else
            cmd_print_help();
        memset(cmd, 0, 256);
    } while (printf(">>>") && (fgets_s(cmd, sizeof(cmd), stdin) != NULL));
    zwaveDestruction();
    return 0;
}
