#include "log.h"

void log_error(char *err) {
    time_t now = time(0);
    char* dt = ctime(&now);

    dt[strlen(dt) - 1] = 0;
    fprintf(stderr, "[%s \033[38;5;196mERROR\033[0m]: %s\n", dt, err);
}

void log_info(char *info) {
    time_t now = time(0);
    char* dt = ctime(&now);

    dt[strlen(dt) - 1] = 0;
    printf("[%s \033[38;5;33mINFO\033[0m]: %s\n", dt, info);
}

void log_warning(char *warning) {
    time_t now = time(0);
    char* dt = ctime(&now);

    dt[strlen(dt) - 1] = 0;
    printf("[%s \033[38;5;208mWARNING\033[0m]: %s\n", dt, warning);
}
