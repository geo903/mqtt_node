#define ID_CONNECT "test2"
#define in_string "test2/in/#"
#define out_string "test2/out/%d/%s"
#define dh_string "test2/out/dh"
#define serial_string "test2/serial"
#define rfid_string "1f_d1/rfid"

#define IP4_NET 7
#define IP4_ADDR 54
#define MAC1 0x43
#define MAC2 0x8F
#define MAC3 0x54
#define WIFISSID ""
#define WIFIPASS ""

//#define board_ARDUINO
#define board_ESP
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

#define DHTPIN D3
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



#define pins_size 4

//BINARY,SENSOR,SENSOR_TEMP,SENSOR_GAS,SENSOR_LIGHT,SWITCH
//pin/type/value/invert/delay_time
//need draw to +5 in
//no analog read
//3.3 volts power!
pins_str pins[pins_size] = {
    {0, SWITCH, 0,0,0,0}, //0 - GPIO0 prog pin
    {1, BINARY, 0,0,0,0}, //1 - tx
    {2, NONE, 0,0,0,0}, //2 - GPIO2 
    {3, BINARY, 0,0,0,0}  //3 - rx
    
};
