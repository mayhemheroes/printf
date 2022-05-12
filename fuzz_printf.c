#include "printf.h"
#include <stdio.h>

void _putchar(char character) {
	putchar(character);
}

int main(int argc, const char** argv) {
	if (argc > 1)
		printf_(argv[1]);
	return 0;
}
