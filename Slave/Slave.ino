#include <Wire.h>
#include "PolarCoord.h"

#define FAILED_TO_SEND 0

PolarCoord coord_to_send;
bool ready_to_send = false;

void setup() {
  Wire.begin(8);
  Wire.onRequest(requestCoordEvent);
}

void loop() {
  PolarCoord test_point;
  test_point.r = 5.7;
  test_point.theta = 67.22;
  test_point.left = 1;
  
  prepareToSend(test_point);
  
  delay(100);
}

// sends "coord_to_send"
void requestCoordEvent()
{
  if(ready_to_send)
  {
    Wire.write((byte*) &coord_to_send, sizeof(PolarCoord));
  }
  else
  {
    Wire.write(FAILED_TO_SEND);
  }
}

void prepareToSend(PolarCoord new_coord)
{
  coord_to_send = new_coord;
  ready_to_send = true;
}
