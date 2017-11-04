#include <Wire.h>
#include "PolarCoord.h"

#define BYTES_REQUESTED 10

bool VALID_DATA = false;
PolarCoord new_coord;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.requestFrom(8, BYTES_REQUESTED);
  int flag;
  while(Wire.available())
  {
      flag = readCoord(new_coord);
      if(flag == 0)
        VALID_DATA = false;
      else
        VALID_DATA = true;
        
      Serial.print("Angle: "); Serial.println(new_coord.theta);
      Serial.print("Distance: "); Serial.println(new_coord.r);
      Serial.print("Left: "); Serial.println(new_coord.left);
  }
  

  delay(500);

}
int readCoord(PolarCoord &coord)
{
  byte *p = (byte*) &coord;
  unsigned int i;
  
  for(int i = 0; i < sizeof coord; i ++)
    *p++ = Wire.read();
    
  return i;
}
