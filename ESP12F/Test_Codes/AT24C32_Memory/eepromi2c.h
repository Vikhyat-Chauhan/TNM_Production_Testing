#define rom_address 0x57
//in the normal write anything the eeaddress is incrimented after the writing of each byte. The Wire library does this behind the scenes.

// NOTE: Currently has issues with storing data in internal EEPROM

byte highAddressByte(word address)
{
  byte BYTE_1;
  BYTE_1 = address >> 8;
  return BYTE_1;
}

byte lowAddressByte(word address)
{
  byte BYTE_1;
  byte BYTE_2;
  BYTE_1 = address >> 8;
  BYTE_2 = address - (BYTE_1 << 8);
  return BYTE_2;
}

template <class T>
int eeWrite(int ee, const T& value,bool external){
  if(external){
    const byte* p = (const byte*)(const void*)&value;
    int i;
    for (i = 0; i < sizeof(value); i++)
      if(i==0){
        Serial.println("Write Size 0");
        Wire.beginTransmission(rom_address);
        Wire.write(highAddressByte(ee));      //First Word Address
        Wire.write(lowAddressByte(ee));      //Second Word 
        Wire.write(*p++);
      }
      else if(i==32){
        Wire.endTransmission();delay(4);
        Serial.println("Write Size 28");
        Wire.beginTransmission(rom_address);
        Wire.write(highAddressByte(ee+28));      //First Word Address
        Wire.write(lowAddressByte(ee+28));      //Second Word 
        Wire.write(*p++);
      }
    Wire.endTransmission();delay(4);
    return i;
  }
  else{
    const byte* p = (const byte*)(const void*)&value;
    int i;
    for (i = 0; i < sizeof(value); i++)
      //EEPROM.write(ee+i,*p++);delay(20);
      //EEPROM.commit();
    return i;
  }
}

template <class T>
int eeRead(int ee, T& value,bool external){
  if(external){
    byte* p = (byte*)(void*)&value;
    int i;
    Wire.beginTransmission(rom_address);
    Wire.write(highAddressByte(ee));      //First Word Address
    Wire.write(lowAddressByte(ee));      //Second Word 
    Wire.endTransmission();
    Wire.requestFrom(rom_address,sizeof(value));
    for (i = 0; i < sizeof(value); i++)
      if(i==32){
        Serial.println("Write Size Exceeded 28");
        break;
        //Wire.endTransmission();delay(4)
        //Wire.beginTransmission(rom_address+28);
        //Wire.write(highAddressByte(ee+));      //First Word Address
        //Wire.write(lowAddressByte(ee));      //Second Word
      }
      if(Wire.available())
        *p++ = Wire.read();
    return i;
  }
  else{
    byte* p = (byte*)(void*)&value;
    int i;
    for (i = 0; i < sizeof(value); i++)
        //*p++ = EEPROM.read(ee+i);
    return i;
  }
}
