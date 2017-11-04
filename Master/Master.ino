#include <Wire.h>
#include "PolarCoord.h"

#define BYTES_REQUESTED 10
#define SIZE_OF_SET 10

bool VALID_DATA = false;
PolarCoord new_coord;
PolarCoord *new_set;

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
      int set_index = 0;
      new_set = (PolarCoord*)calloc(SIZE_OF_SET, sizeof(PolarCoord));
      flag = readCoord(new_coord);
      if(flag == 0)
        VALID_DATA = false;
      else
        VALID_DATA = true;
        
      printCoord(new_coord);
      Serial.println("Added to set");    
      Serial.println();
      
      new_set[set_index] = new_coord;
      set_index++;
      printDataset(new_set);
      Serial.println();
  }
  
  delay(500);

}
int readCoord(PolarCoord &coord)
{
  byte *p = (byte*) &coord;
  unsigned int i;
  
  for(int i = 0; i < sizeof coord; i++)
    *p++ = Wire.read();
    
  return i;
}

void printCoord(PolarCoord print_me)
{
      Serial.print("Angle: "); Serial.println(print_me.theta);
      Serial.print("Distance: "); Serial.println(print_me.r);
      Serial.print("Left: "); Serial.println(print_me.left);
}

void printDataset(PolarCoord *print_me)
{
  Serial.println("Printing Full Dataset...");
  for(int i = 0; i < SIZE_OF_SET && print_me[i].r != 0; i++)
    printCoord(print_me[i]);
}

