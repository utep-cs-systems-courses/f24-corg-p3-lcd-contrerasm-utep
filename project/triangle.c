#include "triangle.h"
#include "lcddraw.h"
#include "lcdutils.h"

void drawUp(int startX, int startY, int size, unsigned int color) {
  for (int y = 0; y < size; y++) {
    int halfWidth = y;
    for (int x = startX - halfWidth; x <= startX + halfWidth; x++) {
      drawPixel(x, startY + y, color);
    }
  }
}

void drawDown(int startX, int startY, int size, unsigned int color) {
  for (int y = 0; y < size; y++) {
    int halfWidth = size - y - 1;
    for (int x = startX - halfWidth; x <= startX + halfWidth; x++) {
      drawPixel(x, startY - y, color);
    }
  }
}

void drawLeft(int startX, int startY, int size, unsigned int color) {
  for (int x = 0; x < size; x++) {
    int halfHeight = x;
    for (int y = startY - halfHeight; y <= startY + halfHeight; y++) {
      drawPixel(startX + x, y, color);
    }
  }
}

void drawRight(int startX, int startY, int size, unsigned int color) {
  for (int x = 0; x < size; x++) {
    int halfHeight = size - x - 1;
    for (int y = startY - halfHeight; y <= startY + halfHeight; y++) {
      drawPixel(startX - x, y, color);
    }
  }
}
