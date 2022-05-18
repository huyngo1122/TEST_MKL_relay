#pragma once

#include "Arduino.h"

#define debug(x) Serial.println(x)
// typedef void (*FunctionCall)(myLoop *pmyloop);

enum
{
  SETUP = 0,
  LOOP,
  LEDON,
  LEDOFF,
  STOP
}eState;

class myLoop
{
public:
  // khai bao gia tri milis()
  unsigned long previousMillis = 0;
  unsigned long interval = 0;

  typedef void (*FunctionCall)(myLoop *pmyloop);

  FunctionCall p_myFunct;
  unsigned char state = 0;

  void AddFunction(FunctionCall tMyFunct)
  {
    p_myFunct = tMyFunct;
  }

  void loop()
  {
    if (millis() - this->previousMillis >= this->interval)
    {
      this->previousMillis = millis();
      debug("loop running");
      if (this->p_myFunct)
        p_myFunct(this);
    }
  }
};

class myLed
{
public:
  // khai bao gia tri milis()
  unsigned long previousMillis = 0;
  unsigned long interval = 0;

  // typedef void (*FunctionCall)(myLoop *pmyloop);

  // FunctionCall p_myFunct;
  unsigned char state = 0;

  uint8_t pin;
  bool b_active_On;
  unsigned timeOn, timeOff;

  // void AddFunction(FunctionCall tMyFunct)
  // {
  //   p_myFunct = tMyFunct;
  // }

  void begin(uint8_t tPin, bool tActive){
    this->pin = tPin;
    this->b_active_On = tActive;
  }

  void setTime(unsigned long tTimeOn, unsigned long tTimeOff){
    timeOn = tTimeOn;
    timeOff = tTimeOff;
  }

  void loop()
  {
    if (millis() - this->previousMillis >= this->interval)
    {
      this->previousMillis = millis();
      debug("loop running");
      // if (this->p_myFunct)
      //   p_myFunct(this);
      BlinkLed(this);
    }
  }

  void BlinkLed(myLed *pmyloop)
  {
    switch (pmyloop->state)
    {
    case SETUP:
      pinMode(pmyloop->pin, OUTPUT);
      debug("Setup led");
      pmyloop->state = LOOP;
      break;

    case LOOP:
    case LEDON:
      debug("ON led");
      digitalWrite(pmyloop->pin, pmyloop->b_active_On);
      pmyloop->interval = pmyloop->timeOn;
      pmyloop->state = LEDOFF;
      break;

    case LEDOFF:
      debug("OFF led");
      digitalWrite(pmyloop->pin, !pmyloop->b_active_On);
      pmyloop->interval = pmyloop->timeOff;
      pmyloop->state = LEDON;
      break;

    default:
      pmyloop->interval = 0;
      break;
    }
  }
};