#include <Wire.h>
#define AT24C32 0x57
#include "eepromi2c.h"

typedef struct{
    bool current_state = false;       
    bool trigger = false;
    bool relay[4];
    bool fan[4];
    bool change = false;
}SCENE; 

SCENE scene;
SCENE scene1;

bool a[40];

void setup()
{ 
 scene.current_state = true;
 Wire.begin();
 Serial.begin(115200);Serial.println();
 Serial.println(sizeof(a));
 delay(1000); 
 
 for(int i=0;i<(sizeof(a));i++){
  a[i] = true;
  Serial.print(a[i]);
 }Serial.println();

 Serial.println(eeWrite(0,a,true));

 for(int i=0;i<(sizeof(a));i++){
  a[i] = false; 
  Serial.print(a[i]);
 }Serial.println();
 
 eeRead(0,a,true);
 
 for(int i=0;i<(sizeof(a));i++){
  Serial.print(a[i]);
 }Serial.println();
}

void loop()
{
  
}
