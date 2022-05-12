#include "printf.h"
#include <stdio.h>

void _putchar(char character) {
	putchar(character);
}

int LLVMFuzzerTestOneInput(char *data, size_t size) {
  printf_((const char*) data);
  return 0;
}
