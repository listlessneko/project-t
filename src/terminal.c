#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "terminal.h"

#ifdef _WIN32
  #include <conio.h>
  #include <windows.h>

#else
  #include <termios.h>
  #include <fcntl.h>
  #include <unistd.h>

  static struct termios orig_termios;

  void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
  }

  void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);

    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
  }

  int kbhit_unix() {
    int ch = getchar();
    if (ch != EOF) {
      ungetc(ch, stdin);
      return 1;
    }
    return 0;
  }

#endif

char *read_input(char *buffer, int size) {
  disable_raw_mode();
  fgets(buffer, size, stdin);
  enable_raw_mode();
  buffer[strcspn(buffer, "\n")] = '\0';
  return buffer;
}
