#include "Box.h"

Box::Box(int n, int r, int c, bool fixedVal) {
  num = n;
  row = r;
  col = c;
  fixed = fixedVal;
}

void Box::fillAns(int n) {
  num = n;
}