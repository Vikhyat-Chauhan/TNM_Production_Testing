/*
 Copyright (c) 2015 NicoHood
 See the readme for credit to other people.

 AnalogTouch example
 Lights an Led if pin is touched and prints values to the Serial
*/

// AnalogTouch
#include <AnalogTouch.h>

// Choose your analog and led pin
#define pinAnalog A6
#define pinLed LED_BUILTIN

// Slow down the automatic calibration cooldown
#define offset 2
#if offset > 6
#error "Too big offset value"
#endif

void setup()
{
  // Led setup
  pinMode(pinLed, OUTPUT);

  // Start Serial for debugging
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(pinLed,touchRead(A6));
}

bool touchRead(int pinAnalog){
  // No second parameter will use 1 sample
  uint16_t value;// = analogTouchRead(pinAnalog);
  value = analogTouchRead(pinAnalog, 100);
  Serial.print(value);
  Serial.print("\t");
  // Self calibrate
  static uint16_t ref = 0xFFFF;
  if (value < (ref >> offset))
    ref = (value << offset);
  // Cool down
  else if (value > (ref >> offset))
    ref++;
    
  // Print touched?
  bool touched = (value - (ref >> offset)) > 40;
  Serial.print(touched);
  Serial.println("\t");

  return touched;
}
