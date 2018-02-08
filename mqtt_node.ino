#include <SPI.h>
#include "PubSubClient.h"



#include "mqtt_node_common.h"

#include "conf/dav.h"




#ifdef board_ARDUINO
#ifdef ethernet_ENC
#include <UIPEthernet.h>
#else 
#include <Ethernet.h>
#endif
byte mac[] = {  0xDE, 0xED, 0xBA, MAC1, MAC2, MAC3 };
byte ip[]  = { 192, 168, IP4_NET, IP4_ADDR};
#endif

#ifdef board_ESP 
#include <ESP8266WiFi.h>
const char* ssid = WIFISSID;
const char* password = WIFIPASS;
#endif


//DH temperature sensor
#ifdef DH
#include <dht_nonblocking.h>
float temperature;
float humidity;
unsigned long measurement_timestamp=0;
DHT_nonblocking dht_sensor(DHTPIN, DHTTYPE);
#define value_dh_string "{\"t\":%d,\"h\":%d}" 
#endif

#if defined(SERIALPORT) or defined(SERIALPORT1) or defined(SERIALPORT2) or defined(SERIALPORT3)
char serial_buffer[SERIAL_BUFFER];
byte serial_index=0; 
char serial_in;
#endif

#ifdef DHTBL
#include "DHT.h"
unsigned long dh_timestamp=0;
float temperature;
float humidity;
DHT dht(DHTPIN, DHTTYPE);
#define value_dh_string "{\"t\":%d,\"h\":%d}"
#endif

#ifdef RFID
#include <Wiegand.h>
WIEGAND wg;
#endif

#ifdef BME280
char temperature[6];
char humidity[6];
#include <Wire.h>
#include "cactus_io_BME280_I2C.h"
unsigned long bme_timestamp=0;
BME280_I2C bme(0x76);
#define value_bme_string "{\"t\":%s,\"h\":%s}"
#endif


unsigned long lastReconnectAttempt = 0;
unsigned long now=0;
char char_payload[5]; //для числа
bool alarm_mode=false;


#ifdef board_ARDUINO
EthernetClient ethClient;
PubSubClient client(ethClient);
#endif
#ifdef board_ESP
WiFiClient espClient;
PubSubClient client(espClient);  

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  #ifdef DEBUG 
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  #endif
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    #ifdef DEBUG 
    Serial.print(".");
    #endif
  }

  randomSeed(micros());

  #ifdef DEBUG
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  #endif
}
#endif




void send_status_char(int id, const char* type, const char* value){

  #ifdef DEBUG
  Serial.print("send type=");
  Serial.print(type);
  Serial.print(" id=");
  Serial.print(id);
  Serial.print(" value=");
  Serial.println(value);
  #endif
  #ifdef ALARM
  if (pins[id].alarm==true and type[0]=='p' and value[0]=='1' and alarm_mode==true) alarm();
  #endif
  char text_to_send[20];
  memset(text_to_send, ' ', 20);
  snprintf(text_to_send, 20, out_string, id, type);
  client.publish(text_to_send,value,true);
}

#ifdef ALARM
void alarm(){
   
   alarm_mode=0;
   send_status_char(0, "a","alarm");
   
   Serial.println("AT"); // Sends AT command to wake up cell phone
   delay(500);
   Serial.println("AT+CMGF=1"); // Puts phone into SMS mode
   delay(1000); // Wait a second
   Serial.println(ALARM_NUMBER); // Creates new message to number
   //79856461436
   delay(1000);
   //Serial.print('Alarm dev=');
   //Serial.print(dev_id);
   //Serial.print(' id=');
   Serial.println("alarm!");
   //Serial.println(id);
   //Serial.print(value);
   delay(500);
   Serial.write(26);
   
}
#endif


#ifdef DH
bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > REPORT_INTERVAL )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}
#endif






//установка параметров устройства в соответствии с присланными данными по подписке
void callback(char* topic, byte* payload, unsigned int length) {


#ifdef DEBUG
  Serial.println("str_len>5");
#endif  
  if (length<6)
  {
  
  byte i;
  
  for (i = 0; i < length; i++) {
    char_payload[i]=((char)payload[i]);
  }

  char_payload[length]='\0';
  //payload[length] = '\0';
  //String strPayload = String((char*)payload);

  //Serial.println(payload[0]);
  //Serial.println(payload[1]);
  //Serial.println(payload[2]);
  //Serial.println(payload[3]);
  //Serial.println(payload[4]);
  //Serial.println("string: ");
  //Serial.println(char_payload[0]);
  //Serial.println(char_payload[1]);
  //Serial.println(char_payload[2]);
  //Serial.println(char_payload[3]);
  //Serial.println(char_payload[4]);
  
  int value=atoi(char_payload);
  //int value=strPayload.toInt();
  
  uint8_t id;
  char* type;
  strtok(topic,"/");
  strtok(NULL, "/");
  id=atoi(strtok(NULL, "/"));
  type=strtok(NULL, "/");

  #ifdef DEBUG
  Serial.print("receive ");
  Serial.print(topic);
  Serial.print(" id=");
  Serial.print(id);
  Serial.print(" type=");
  Serial.print(type);
  Serial.print(" len=");
  Serial.print(length);
  Serial.print(" value=");
  Serial.print(value);
  Serial.print(" char=");
  Serial.println(char_payload);
  
  #endif
  
  #ifdef ALARM
  if (id==0 and type[0]=='t') alarm();
  if (id==0 and type[0]=='a') alarm_mode=value;
  #endif
    
  if (pins[id].type==SWITCH)
       {
                   
           
           if (value==1) 
           {
            pins[id].value=1;
            digitalWrite(pins[id].pin, HIGH);
            send_status_char(id, "p","1");
           }
           else 
           {
            pins[id].value=0;
            digitalWrite(pins[id].pin, LOW);
            send_status_char(id, "p","0");
           }
       }
  #ifdef PWMON  
  if (pins[id].type==PWM)
       {
            
            if (value==0 and type[0]=='p')
            {
              pins[id].invert=pins[id].value;
              pins[id].value=0;
              analogWrite(pins[id].pin, 0);
              Serial.println(0);
              send_status_char(id, "p","0");
              //send_status_char(id, "i",char_payload);
            }
            if (value==1 and type[0]=='p' and pins[id].value==0)
            {
              pins[id].value=pins[id].invert;
              analogWrite(pins[id].pin, pins[id].value);
              Serial.println(pins[id].value);
              send_status_char(id, "p","1");
              //send_status_char(id, "i",char_payload);
            }

            if (type[0]=='i')
            {
              pins[id].value=value;
              analogWrite(pins[id].pin, value);
              Serial.println(value);
              send_status_char(id, "i",char_payload);
            }
            
       }
  #endif


  }
}

float get_analog_value(byte type, int sensorValue) {
  
  
  
  switch (type) {
  
      case SENSOR_LIGHT:
     
        return (float)(1023-sensorValue)*10/sensorValue;
      
      case SENSOR_TEMP:
        {
        float resistance=(float)(1023-sensorValue)*10000/sensorValue; 
        return (float)1/(log(resistance/10000)/3975+1/298.15)-273.15;
        }
      
      case SENSOR_GAS:
        return (float)sensorValue/1024*5.0;
      
      case SENSOR:
        return (float)sensorValue;
  
  }

}




boolean reconnect() {
  if (client.connect(ID_CONNECT,MQTT_USER,MQTT_PASSWORD)) {
    
    #ifdef DEBUG
    Serial.println("connect");
    #endif
    client.publish("connect",ID_CONNECT);
    //delay(3000);
    client.subscribe(in_string); //подписка на смену состояния
     
  
  }
  return client.connected();
}

#if defined(SERIALPORT) or defined(SERIALPORT1) or defined(SERIALPORT2) or defined(SERIALPORT3)



#endif


void setup()
{
  #ifdef DEBUG
  Serial.begin(57600);
  #else
  #ifdef ALARM
  Serial.begin(SIM900_SPEED);
  #endif
  #ifdef SERIALPORT
  Serial.begin(SERIAL_SPEED);
  #endif
  #ifdef SERIALPORT1
  Serial1.begin(SERIAL1_SPEED);
  #endif
  #ifdef SERIALPORT2
  Serial2.begin(SERIAL2_SPEED);
  #endif
  #ifdef SERIALPORT3
  Serial3.begin(SERIAL3_SPEED);
  #endif
  #endif

  
  
  #ifdef board_ESP
  setup_wifi();
  #endif
  
  client.setServer(server, 1883);
  client.setCallback(callback);

  #ifdef board_ARDUINO
  Ethernet.begin(mac, ip);
  #endif

  
  #ifdef DHTBL
   dht.begin();
  #endif

  #ifdef RFID
  wg.begin();
  #endif

  #ifdef BME280
  bme.begin();
  bme.setTempCal(-1);
  #endif
  
  lastReconnectAttempt = 0;



    for (byte i=0;i<pins_size;i++)
    {
      
      if (pins[i].type==BINARY or pins[i].type==SENSOR or pins[i].type==SENSOR_TEMP or pins[i].type==SENSOR_GAS or pins[i].type==SENSOR_LIGHT)
      {
          pinMode(pins[i].pin, INPUT);
          digitalWrite(pins[i].pin, HIGH);
      }

      if (pins[i].type==SWITCH) //реле
      {
          pinMode(pins[i].pin, OUTPUT);
          digitalWrite(pins[i].pin, pins[i].value);
      }
  
      if (pins[i].type==PWM) //ШИМ
      {
        //pinMode(pins[i].pin, OUTPUT);
        analogWrite(pins[i].pin, pins[i].value);
      }
    }

 
}








void loop()
{
  
  now = millis();
  
  if (!client.connected()) {
    
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      #ifdef DEBUG
       Serial.println("reconnect");
       #endif
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
        
      }
    }
  } else {
    // Client connected

    client.loop();


   
#ifdef DH


      if( measure_environment( &temperature, &humidity ) == true )
      {

            char value_to_send[20];
            memset(value_to_send, ' ', 20);
            #ifdef DEBUG
            Serial.print("read dh: t=");
            Serial.print(temperature,1);
            Serial.print("; h=");
            Serial.println(humidity,1);
            Serial.println("send dh");
            #endif
            snprintf(value_to_send, 20, value_dh_string, (int)temperature, (int)humidity);
            client.publish(dh_string,value_to_send);
    
      }

#endif    
      
#ifdef DHTBL


if( now - dh_timestamp > REPORT_INTERVAL )
  {

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

if (!isnan(humidity) and !isnan(temperature)) {
  #ifdef DEBUG
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.println("send dh");
  #endif
  dh_timestamp = now;
  char value_to_send[20];
  memset(value_to_send, ' ', 20);
  snprintf(value_to_send, 20, value_dh_string, (int)temperature, (int)humidity);         
  client.publish(dh_string,value_to_send);

  
}
    
  }


  
#endif  


#ifdef SERIALPORT


if (Serial.available())
{
while(Serial.available())                                          
  {
      //client.publish(serial_string,Serial.read());
      
          byte serial_in = (byte)Serial.read(); // Read a character
          serial_buffer[serial_index] = (char)serial_in; // Store it
          serial_index=serial_index+1;
          
          if ((char)serial_in=='\n' or serial_index==SERIAL_BUFFER or serial_in==3 or (char)serial_in=='\r')
          {
          serial_index=0;
          client.publish(serial_string,serial_buffer);
          memset(serial_buffer,NULL,SERIAL_BUFFER); // Null terminate the string
          Serial.flush();
          break;  
          }
  }
}

#endif

#ifdef RFID

if(wg.available())
{
  #ifdef DEBUG
  Serial.print(wg.getCode());
  #endif
char buf [8];
ultoa (wg.getCode(), buf, 10);
client.publish(rfid_string,buf);
}

#endif

#ifdef BME280
if( now - bme_timestamp > REPORT_INTERVAL )
  {
    bme.readSensor();
    bme_timestamp = now;
    char value_to_send[20];
    memset(value_to_send, ' ', 20);

    dtostrf(bme.getTemperature_C(), 1, 1, temperature);  
    dtostrf(bme.getHumidity(), 1, 1, humidity);
  
    snprintf(value_to_send, 20, value_bme_string, temperature, humidity);
         
    client.publish(dh_string,value_to_send);
  
  }
#endif




   for (byte i=0;i<pins_size;i++)
    {
   

   //проверка изменения значений

   if (pins[i].type==BINARY)
   {
     int delay_time;
     if (pins[i].delay_time!=0) delay_time=pins[i].delay_time;  
     else delay_time=500;
     
     if (pins[i].start_delay_time+delay_time < now)
     {
     byte value=digitalRead(pins[i].pin);
      
       if (pins[i].value != value)  //кнопка нажата
       {
        pins[i].start_delay_time=now;

        
        if (pins[i].invert==0)
        {
          if (value==1) send_status_char(i, "p","1");
          else send_status_char(i, "p","0");
        }
        else
        {
          if (value==1) send_status_char(i, "p","0");
          else send_status_char(i, "p","1");
        }

        pins[i].value=value;
        
       } 
     }
   }


  if (pins[i].type==SENSOR or pins[i].type==SENSOR_TEMP or pins[i].type==SENSOR_GAS or pins[i].type==SENSOR_LIGHT)
   {
     unsigned long delay_time=1000; //секунда интервал между чтениями ms
     if (pins[i].delay_time!=0) delay_time=pins[i].delay_time;
     
     if (pins[i].start_delay_time+delay_time < now)
     {

       int read_value = analogRead(pins[i].pin);
       float value = get_analog_value(pins[i].type, read_value);
       int interval=1;
       if (pins[i].invert!=0) interval=pins[i].invert;  
        
       if ((read_value<pins[i].value-interval) or (pins[i].value+interval<read_value)) 
       //if (constrain(read_value,pins[i].value-interval,pins[i].value+interval)!=pins[i].value) 
       {

      
           
       

       #ifdef DEBUG

       //Serial.print(pins[i].value-interval);
       //Serial.print("<");
       //Serial.print(read_value);
       //Serial.print("<");
       //Serial.println(pins[i].value+interval);
       
       Serial.print("update analog pin=");
       Serial.print(pins[i].pin);
       Serial.print(" value=");
       Serial.println(value);
       #endif
        
       //char char_value[8];
       pins[i].start_delay_time=now;
       //dtostrf(value, 1, 1, char_value);
       pins[i].value=read_value;

       char char_value[7];
       dtostrf(value, 1, 1, char_value);
       //itoa(sensorValue, buf, 10)
       
       send_status_char(i, "p",char_value);
       } 

     
     }
   }
   


   

 }

    
  }
  

}














