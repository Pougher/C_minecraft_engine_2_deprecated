#include "timer.h"

bool timer_ready(Timer *timer) {
    const double time = glfwGetTime();
    if (time - timer->last_time >= timer->interval) {
        timer->last_time = time;
        return true;
    }
    return false;
}
