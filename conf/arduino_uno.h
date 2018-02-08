#define ID_CONNECT "test1"
#define in_string "test1/in/#"
#define out_string "test1/out/%d/%s"
#define dh_string "test1/out/dh"
#define serial_string "test1/serial"
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



#define pins_size 18

//BINARY,SENSOR,SENSOR_TEMP,SENSOR_GAS,SENSOR_LIGHT,SWITCH
//pin/type/value/invert/delay_time

//SCK - Pin 13
//SO  - Pin 12
//SI  - Pin 11
//CS  - Pin  10


pins_str pins[pins_size] = {
    {0, NONE, 0,0,0}, //0 
    {1, NONE, 0,0,0}, //1 - 
    {2, NONE, 0,0,0}, //2 - 
    {3, NONE, 0,0,0}, //3 - 
    {4, NONE, 0,0,0}, //4 - 
    {5, NONE, 0,0,0}, //5 - 
    {6, NONE, 0,0,0}, //6 - 
    {7, NONE, 0,0,0}, //7 -
    {8, NONE, 0,0,0}, //8 - 
    {9, NONE, 0,0,0}, //9 -
    
    {14, NONE, 0,0,0}, //0 - 10
    {15, NONE, 0,0,0}, //1 - 11
    {16, NONE, 0,0,0}, //2 - 12
    {17, NONE, 0,0,0}, //3 - 13
    {18, NONE, 0,0,0}, //4 - 14
    {19, NONE, 0,0,0}, //5 - 15 
    {20, NONE, 0,0,0}, //6 - 16 
    {21, NONE, 0,0,0}  //7 - 17 
};
