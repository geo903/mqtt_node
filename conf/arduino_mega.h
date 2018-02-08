#define ID_CONNECT "test"
#define in_string "test/in/#"
#define out_string "test/out/%d/%s"
#define dh_string "test/out/dh"
#define serial_string "test/serial"
#define rfid_string "1f_d1/rfid"

#define IP4_NET 7
#define IP4_ADDR 54
#define MAC1 0x7e
#define MAC2 0x38
#define MAC3 0xdf
#define WIFISSID ""
#define WIFIPASS ""

#define board_ARDUINO
//#define board_ESP
//#define ethernet_ENC

//#define DHTBL
//#define DH
//#define BME280
//#define PWMON
//#define SERIALPORT
//#define SERIALPORT1
//#define SERIALPORT2
//#define SERIALPORT3
//#define ALARM  // test-> main/in/0/t on->main/in/0/a   value:1    off-> value:0
//#define RFID //pin2 green rx, pin3 white tx

#define DHTPIN 7
#define DHTTYPE 0 //0-dh11 1-dh21, 2-dh22
#define REPORT_INTERVAL 10000 // in msec must > 2000
#define SERIAL_SPEED 9600
#define SERIAL_BUFFER 15
#define SIM900_SPEED 19200
#define ALARM_NUMBER "AT+CMGS=\"+0000000000\""
byte server[] = { 192, 168, 7, 7 };
#define MQTT_USER ""
#define MQTT_PASSWORD ""
//#define DEBUG
//#define INIT



#define pins_size 66



//pins ethercard
//SCK - Pin 52
//SO  - Pin 50
//SI  - Pin 51
//CS  - Pin 53

//BINARY,SENSOR,SENSOR_TEMP,SENSOR_GAS,SENSOR_LIGHT,SWITCH
//pin/type/value/invert/delay_time

pins_str pins[pins_size] = {
    {0, NONE, 0,0,0}, //0 
    {1, NONE, 0,0,0}, //1 - 
    {2, BINARY, 0,1,0}, //2 - 
    {3, NONE, 0,0,0}, //3 - 
    {4, NONE, 0,0,0}, //4 - 
    {5, NONE, 0,0,0}, //5 - 
    {6, NONE, 0,0,0}, //6 - 
    {7, SWITCH, 0,0,0}, //7 -
    {8, NONE, 0,0,0}, //8 - 
    {9, NONE, 0,0,0}, //9 -
    {10, NONE, 0,0,0}, //10
    {11, NONE, 0,0,0}, //11
    {12, NONE, 0,0,0}, //12
    {13, NONE, 0,0,0}, //13
    {14, NONE, 0,0,0}, //14
    {15, NONE, 0,0,0}, //15
    {16, NONE, 0,0,0}, //16
    {17, NONE, 0,0,0}, //17
    {18, NONE, 0,0,0}, //18
    {19, NONE, 0,0,0}, //19 
    {20, NONE, 0,0,0}, //20 
    {21, NONE, 0,0,0}, //11
    {22, NONE, 0,0,0}, //12
    {23, NONE, 0,0,0}, //13
    {24, NONE, 0,0,0}, //14
    {25, NONE, 0,0,0}, //15
    {26, NONE, 0,0,0}, //16
    {27, NONE, 0,0,0}, //17
    {28, NONE, 0,0,0}, //18
    {29, NONE, 0,0,0}, //19 
    {30, NONE, 0,0,0}, //30 
    {31, NONE, 0,0,0}, //31
    {32, NONE, 0,0,0}, //32
    {33, NONE, 0,0,0}, //33
    {34, NONE, 0,0,0}, //34
    {35, NONE, 0,0,0}, //35
    {36, NONE, 0,0,0}, //36
    {37, NONE, 0,0,0}, //37
    {38, NONE, 0,0,0}, //38
    {39, NONE, 0,0,0}, //39 
    {40, NONE, 0,0,0}, //40 
    {41, NONE, 0,0,0}, //41
    {42, NONE, 0,0,0}, //42
    {43, NONE, 0,0,0}, //43
    {44, NONE, 0,0,0}, //44
    {45, NONE, 0,0,0}, //45
    {46, NONE, 0,0,0}, //46
    {47, NONE, 0,0,0}, //47
    {48, NONE, 0,0,0}, //48
    {49, NONE, 0,0,0}, //49 


    {54, NONE, 0,0,0}, //50 - 0
    {55, NONE, 0,0,0}, //51 - 1
    {56, NONE, 0,0,0}, //52 - 2
    {57, NONE, 0,0,0}, //53 - 3
    {58, NONE, 0,0,0}, //54 - 4
    {59, NONE, 0,0,0}, //55 - 5
    {60, NONE, 0,0,0}, //56 - 6
    {61, NONE, 0,0,0}, //57 - 7
    {62, NONE, 0,0,0}, //58 - 8
    {63, NONE, 0,0,0}, //59 - 9
    {64, NONE, 0,0,0}, //60 - 10
    {65, NONE, 0,0,0}, //61 - 11
    {66, NONE, 0,0,0}, //62 - 12
    {67, NONE, 0,0,0}, //63 - 13
    {68, NONE, 0,0,0}, //64 - 14
    {69, NONE, 0,0,0}, //65 - 15


};
