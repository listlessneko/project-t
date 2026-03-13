#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "utils.h"

void print_text(int seconds, const char *text, ...) {
  char buffer[256];
  va_list args;
  va_start(args, text);
  vsnprintf(buffer, sizeof(buffer), text, args);
  va_end(args);
  for (int i = 0; buffer[i] != '\0'; i++) {
    printf("%c", buffer[i]);
    fflush(stdout);
    usleep(seconds);
  }
}
