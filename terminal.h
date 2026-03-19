#ifndef TERMINAL_H
#define TERMINAL_H

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(us) Sleep((us) / 1000)
#else
    #include <unistd.h>
    #define SLEEP(us) usleep(us)
#endif

#ifndef _WIN32
    void enable_raw_mode();
    void disable_raw_mode();
    int kbhit_unix();
#endif

#endif
