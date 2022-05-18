// khai bao gia tri vol
#define voltage_max 3
float voltage;
float vol_high;

// khai bao gia tri milis()
// unsigned long previousMillis = 0;
//  const long interval = 1000;

// long interval =500;
unsigned long init_time = 0;
const long time_sensor = 1000;

// khai bao led

int ledState = LOW;
const int ledpin = 2;

// thu vien
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "myLoop.h"
LiquidCrystal_I2C lcd(0x27, 20, 4);
// trace arduino lib
myLoop testLoop;
myLoop testLoop_2;

myLed led_13;

myLoop warningLedLoop;

#define KXN_LED_PIN 13

#define KXN_LED_PIN_2 1
// khai bao hang so co dinh bat dau bang 0 va tang dan den khi gap stop
// enum
// {
//   SETUP = 0,
//   LOOP,
//   LEDON,
//   LEDOFF,
//   STOP
// }eState;

void BlinkLed(myLoop *pmyloop)
{
  switch (pmyloop->state)
  {
  case SETUP:
    pinMode(KXN_LED_PIN, OUTPUT);
    debug("Setup led");
    pmyloop->state = LOOP;
    break;

  case LOOP:
  case LEDON:
    debug("ON led");
    digitalWrite(KXN_LED_PIN, 1);
    pmyloop->interval = 1000;
    pmyloop->state = LEDOFF;
    break;

  case LEDOFF:
    debug("OFF led");
    digitalWrite(KXN_LED_PIN, 0);
    pmyloop->interval = 2000;
    pmyloop->state = LEDON;
    break;

  default:
    pmyloop->interval = 0;
    break;
  }
}


void BlinkLed_2(myLoop *pmyloop)
{
  switch (pmyloop->state)
  {
  case SETUP:
    pinMode(KXN_LED_PIN_2, OUTPUT);
    debug("Setup led");
    pmyloop->state = LOOP;
    break;

  case LOOP:
  case LEDON:
    debug("ON led");
    digitalWrite(KXN_LED_PIN_2, 0);
    pmyloop->interval = 1000;
    pmyloop->state = LEDOFF;
    break;

  case LEDOFF:
    debug("OFF led");
    digitalWrite(KXN_LED_PIN_2, 1);
    pmyloop->interval = 2000;
    pmyloop->state = LEDON;
    break;

  default:
    pmyloop->interval = 0;
    break;
  }
}

void setup()
{
  // Serial.begin(9600);
  // Serial.println("Start");

  // testLoop.AddFunction(&BlinkLed);
  // testLoop.state = SETUP;

  testLoop_2.AddFunction(&BlinkLed_2);
  testLoop_2.state = SETUP;

  led_13.begin(13, HIGH);
  led_13.setTime(100,200);


  // lcd.init();         // khoi tao lcd
  // lcd.backlight();     // bat den lcd
  // lcd.setCursor(3, 1); // con tro toi vi tri (3,1)
  // lcd.print("Analog");
  // lcd.setCursor(0, 2);
  // lcd.print("vol:");

  //  Serial.begin(9600);
  // pinMode(ledpin, OUTPUT);
  // vol_high = voltage_max;
}

// void gioi_han()
// {

//   if ((voltage) > vol_high)
//   {
//     char chuoi[] = ("eror");
//     lcd.setCursor(4, 3);
//     lcd.print(chuoi);
//     unsigned long currentMillis = millis();

//     pinMode(A1, OUTPUT);
//     digitalWrite(A1, LOW);
//     if (currentMillis - previousMillis >= interval)
//     {

//       previousMillis = currentMillis;
//       ledState = !ledState;
//       digitalWrite(ledpin, ledState);
//     }
//   }

//   else
//   {
//     digitalWrite(ledpin, LOW);
//     pinMode(A1, INPUT);
//     lcd.setCursor(4, 3);
//     lcd.print("           ");
//     //   // lcd.clear();
//     // }
//     sensor();
//   }
// }

// void sensor()
// {

//   {
//     unsigned long time_sensor_GO = millis();
//     if (time_sensor_GO - init_time >= time_sensor)
//     {
//       init_time = time_sensor_GO;

//       int sensorValue = analogRead(A1);
//       voltage = sensorValue * (5 / 1023.0);
//       lcd.setCursor(5, 2);
//       lcd.print(voltage);
//       // gioi_han();
//     }
//   }
// }

void loop()
{
  // testLoop.loop();
  testLoop_2.loop();
  led_13.loop();
  // sensor();
  // gioi_han();
}
