#ifndef POLARCOORD_H
#define POLARCOORD_H

// 4 bytes for each float, 1 byte for the int
// size is 9 bytes
typedef struct PolarCoord {
  float r;
  float theta;
  int left; // -1 for invalid, 1 for left, 0 for right
} PolarCoord;

#endif