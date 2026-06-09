// mayhem/fuzz_printf.c — libFuzzer harness for mpaland/printf's format-string engine.
//
// Ported from the original mayhemheroes integration (target: fuzz_printf). The old harness fed the
// raw fuzz bytes straight to printf_() WITHOUT a NUL terminator — printf_ reads a C string, so that
// tripped an out-of-bounds read on essentially every input (the fuzzer never reached the format
// parser). Here we NUL-terminate the input first so the engine actually parses it as a format string,
// then drive the bounded snprintf_ path (count-limited buffer + the full conversion machinery), which
// is the natural surface for this tiny embedded printf: %d/%x/%f/%s, width/precision/flags, %n, etc.
#include "printf.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// printf.h requires the integrator to supply _putchar (the sink for printf_/vprintf_). We never call
// those direct-output variants in the harness, but the symbol must exist to link; make it a no-op.
void _putchar(char character) {
  (void)character;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Make a NUL-terminated copy so the format string is a valid C string (no OOB read on the format).
  char *fmt = (char *)malloc(size + 1);
  if (!fmt) return 0;
  memcpy(fmt, data, size);
  fmt[size] = '\0';

  // Drive the bounded path: a fixed-size destination + the count limit exercises the truncation logic
  // alongside the conversion parser. Supply a handful of varied varargs so width/precision/conversion
  // specifiers in the fuzzed format have arguments to consume.
  char out[256];
  snprintf_(out, sizeof(out), fmt,
            (int)0x41424344, (unsigned)0xDEADBEEFu, "harness",
            (double)3.14159, (void *)out, (long)-1L, (char)'Z');

  free(fmt);
  return 0;
}
