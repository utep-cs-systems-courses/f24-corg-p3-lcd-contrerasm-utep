#include "triangle.h"
#include "lcddraw.h"
#include "lcdutils.h"

//used to draw diffrent triangles, built from the base

void triangleDown(int startX, int startY, int size, unsigned int color) {
  
  for (int y = 0; y < size; y++) {
    
    int halfWidth = size-y-1;//used to decrease the width of the row
    
    for (int x = startX - halfWidth; x <= startX + halfWidth; x++) {//left to right go through row
      drawPixel(x, startY + y, color);//used to fill in the pixel
    }
  }
}

void triangleUp(int startX, int startY, int size, unsigned int color) {
  for (int y = 0; y < size; y++) {
    
    int halfWidth = size - y - 1;//used to decrease the width of the row
    
    for (int x = startX - halfWidth; x <= startX + halfWidth; x++) {//left to right
      drawPixel(x, startY - y, color);//changed to -y to change direction of build
    }
  }
}

void triangleRight(int startX, int startY, int size, unsigned int color) {
  for (int x = 0; x < size; x++) {
    
    int halfHeight = size-x-1;//used to decrease the height
    
    for (int y = startY - halfHeight; y <= startY + halfHeight; y++) {
      drawPixel(startX + x, y, color);//+x to decrease to the right
    }
  }
}

void triangleLeft(int startX, int startY, int size, unsigned int color) {
  for (int x = 0; x < size; x++) {
    
    int halfHeight = size - x - 1;//used to decrease the height
    for (int y = startY - halfHeight; y <= startY + halfHeight; y++) {
      drawPixel(startX - x, y, color);//-x to decrease to the left
    }
  }
}
