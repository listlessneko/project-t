#pragma once

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(us) Sleep((us) / 1000)
#else
    #include <unistd.h>
    #define SLEEP(us) usleep(us)
    void enable_raw_mode();
    void disable_raw_mode();
    int kbhit_unix();
#endif

char *read_input(char *buffer, int size);
