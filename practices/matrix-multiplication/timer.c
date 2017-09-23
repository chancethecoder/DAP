#include <stdio.h>
#include <sys/time.h>
#include "timer.h"

static timestamp_t t0;

static timestamp_t get_timestamp() {
    struct timeval now;
    gettimeofday (&now, NULL);
    return now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

void init_timer(void) {
    t0 = get_timestamp();
}

void print_time(char* tag) {
    timestamp_t t1 = get_timestamp();
    printf("%s:\n %.4Lf (sec)\n", tag, (t1 - t0) / 1000000.0L);
}
