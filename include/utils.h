#pragma once

#define MAX_PRINT_BUFFER 1024
#define PRINT_VERY_SLOW50 500000
#define PRINT_SLOW10 100000
#define PRINT_NORMAL5 50000
#define PRINT_FAST3 30000
#define PRINT_FAST1 10000

void print_text(int seconds, const char *text,...);
