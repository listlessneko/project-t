#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "utils.h"
#include "terminal.h"

#define MAX_PRINT_BUFFER 1024

void print_text(int seconds, const char *text, ...) {
  char buffer[MAX_PRINT_BUFFER];
  va_list args;
  va_start(args, text);
  vsnprintf(buffer, sizeof(buffer), text, args);
  va_end(args);

  for (int i = 0; buffer[i] != '\0'; i++) {
        #ifdef _WIN32
            if (_kbhit()) {
                _getch();
                printf("%s", buffer + i);
                fflush(stdout);
                return;
            }
        #else
            if (kbhit_unix()) {
                getchar(); // consume the keypress
                printf("%s", buffer + i);
                fflush(stdout);
                return;
            }
        #endif

        printf("%c", buffer[i]);
        fflush(stdout);
        SLEEP(seconds);
    }
}
