#include "printf.h"
#include <stdio.h>

void _putchar(char character) {
	putchar(character);
}

int main(int argc, const char** argv) {
	printf_(argv[1]);
	return 0;
}
