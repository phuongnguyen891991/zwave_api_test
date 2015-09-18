
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include "utils.h"
#include "zw_api.h"
#include "SerialAPI/ZW_classcmd.h"
#include "SerialAPI/ZW_SerialAPI.h"

enum COMMAND_IDX {
    CMD_ADD = 0,
    CMD_RM,
    CMD_LIST,
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
    CMD_GET_BATTERY,
    CMD_SENSOR_MULTILEVEL_GET,
    CMD_SENSOR_HEAVY_DUTY_SMART_SWITCH,
    CMD_SET_ALAM_REPORT_ONOFF_BULBS,
    CMD_SET_CONFIGURATION_NODE,
    CMD_V,
    CMD_EXIT,
    CMD_MAX
};

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

int cmd_more(void* arg);

cmd_handler_t cmd_list[CMD_MAX] = {
    {.cmd_idx = CMD_ADD, .help = "Add a something", .cmd_func = cmd_add},
    {.cmd_idx = CMD_RM, .help = "Remove something", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_LIST, .help = "List all of nodes", .cmd_func = cmd_rm},
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
    {.cmd_idx = CMD_GET_BATTERY, .help = "Get battery level ", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_SENSOR_MULTILEVEL_GET, .help = "Get sensor multi level ", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_SENSOR_HEAVY_DUTY_SMART_SWITCH, .help = "Get sensor heavy duty smart switch ", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_SET_ALAM_REPORT_ONOFF_BULBS, .help = "Set Alarm multi sensor turn ON/OFF bulb ", .cmd_func = cmd_rm},
    {.cmd_idx = CMD_SET_CONFIGURATION_NODE, .help = "Set configuration node ", .cmd_func = cmd_rm},
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
                                temperature = (uint16_t)(pTxNotify.SensorMultilevelNotify.sensor_Value1 << 8) | pTxNotify.SensorMultilevelNotify.sensor_Value2;
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
                    printf("\t Percentage value (%) : %d \n",pTxNotify.SensorMultilevelNotify.sensor_Value1 );
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

int main(int argc, char *argv[])
{
    pthread_t   thread_reader;
    gLogLevel=2;
    //ZW_Node_t node;
    //ZW_Node_t node_list[232];
    //uint8_t   node_list_size;  
    char cmd[256];

    //uint8_t group_list[232];
    uint8_t group_size;

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
                    mainlog(logUI,"TEST: NodeID[%02X], node type[%02X] has mID:%02X%02X, pID:%02X%02X::%02X%02X",pzwParam->node.node_id,pzwParam->node.node_type,
                                                                            pzwParam->node.node_manufacture.manufacturerID[0],
                                                                            pzwParam->node.node_manufacture.manufacturerID[1],
                                                                            pzwParam->node.node_manufacture.productTypeID[0],
                                                                            pzwParam->node.node_manufacture.productTypeID[1],
                                                                            pzwParam->node.node_manufacture.productID[0],
                                                                            pzwParam->node.node_manufacture.productID[1]);

                    printf("Command class support");
                    for (i=0;i<pzwParam->node.node_capability.noCapability;i++)
                    {
                        printf(":%02X",pzwParam->node.node_capability.aCapability[i]);
                    }
                    printf("\n");
                }
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
            case CMD_SET_ALAM_REPORT_ONOFF_BULBS:
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
                break;  
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
            case CMD_GET_BATTERY:
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
                            
                                    temperature = (uint16_t)((pzwParam->data_out.cmd[4]<< 8) | pzwParam->data_out.cmd[5]);
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
                                    printf("Percentage value (%) : %ld\n",pzwParam->data_out.cmd[4]);
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
                scanf("%d",&choise);
                if(choise == 1)
                {  
                 printf("Please provide the NodeID and SensorType: ");
                    scanf("%X %X",&NodeID,&SensorType);

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
                                        printf("Percentage value (%) : %ld\n",pzwParam->data_out.cmd[6]);
                                        printf("Absolute humidity (g/cm3) : %2.2lf\n",
                                        (humidity_tmp/precicsion)/100);
                                    break;
                                }
                            }
                        }
                    }
                }
                if(choise == 2)
                {
                    printf("enter nodeID & meter typer: ");
                    if(scanf("%X %X",&NodeID,&Meter_Type) == 2)
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
                            printf("Delta time (s): %ld\n", delta_time);
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
