#include "FS.h"
#include <ESP8266WiFi.h>
#define RELAY_MAX_NUMBER 5

String SINRICAPI ;
String SINRICRELAYID[RELAY_MAX_NUMBER];
  
void sinric_SPIFFS_read() {
  SPIFFS.begin();
  File f = SPIFFS.open("/sinric.txt", "r");
  if (!f) {
    Serial.println("Cant open sinric.txt file for reading");
  } 
  else {
    while(f.available()) {
        //Lets read line by line from the file
        SINRICAPI  = f.readStringUntil('\n');
        for(int i=0;i<RELAY_MAX_NUMBER;i++){
          SINRICRELAYID[i] = f.readStringUntil('\n');
        }
    }
  f.close();
  }
  SPIFFS.end();
}

void sinric_SPIFFS_write() {
  SPIFFS.begin();
  String curCnt = "Black";
  String cur1 = "while";
  String cur2 = "ye;low";
  String cur3 = "blue";
  //opening "w" will truncate the file, so we know we only store our 1 value.
  File f = SPIFFS.open("/sinric.txt", "w"); 

  if (!f) {
    Serial.println("Cant open sinric.txt file for writing");
  } 
  else {
    //Lets read line by line from the file
    f.println(SINRICAPI);  
    for(int i=0;i<RELAY_MAX_NUMBER;i++){
      f.println(SINRICRELAYID[i]); 
    }
    f.close();
    Serial.println("Adding one");
  }
  SPIFFS.end();
}

void setup() {
  
  Serial.begin(74880);
  delay(10);
  //Serial.println("Writing");
  //sinric_SPIFFS_write();
  sinric_SPIFFS_read();
  Serial.println("Reading");
  Serial.println(SINRICAPI);
  for(int i=0;i<RELAY_MAX_NUMBER;i++){
    Serial.println(SINRICRELAYID[i]);
  }
}


void loop() {

  //nothing to do here, since deep sleep prevents it from getting this far...
    
}
