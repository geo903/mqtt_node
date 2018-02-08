//структура описания пина

typedef struct 
{
  uint8_t pin; //номер ножки
  uint8_t type; //тип
  int value; //текущее и начальное значение
  unsigned int invert; //(для BINARY: gnd нормально не притянут к 5 v (сенсор на замыкание) invert=1, если нормально притянут (сенсор на размыкание) invert=0), хранит предыдущее значение для Light, интервал срабатывания аналогового сенсора 1-1024
  unsigned long delay_time; //величина задержки для срабатывания сенсоров в ms
  unsigned long start_delay_time; //от этого времени идет отсчет задержки срабатывания для кнопок и сенсоров
  bool alarm;

} pins_str;




//типы устройств
#define NONE 0 //пин отключен

#define BINARY 10 //бинарный сенсор (контакт, кнопка) 1 pin - только цифровые пины

//только аналоговые пины
#define SENSOR 20 //сенсор стандартный аналоговый 1 pin 
#define SENSOR_TEMP 24 //сенсор 1 pin
#define SENSOR_GAS 25 //сенсор 1 pin
#define SENSOR_LIGHT 26 //сенсор 1 pin

#define SWITCH 30 //реле 1 pin

#define COVER 40 //привод

#define PWM 50 //плавное управление нагрузкой (0-255)
#define LIGHT_RGB 51 //свет(RGB) next 3 pin PWM analogWrite
