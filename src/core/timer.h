#ifndef TIMER_H
#define TIMER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>
#include "../common/types.h"

typedef struct {
    // the interval at which the timers event will be fired
    double interval;

    // the last time the event was fired
    double last_time;
} Timer;

// returns true if the timers event cycle has concluded, else it will return
// false
bool timer_ready(Timer *timer);

#endif
