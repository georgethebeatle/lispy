#include <stdio.h>

#include "lispy.h"

int main(int argc, char** argv) {

  printf("Hello %d!\n", eval("world"));
  return 0;
}


