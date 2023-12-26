#ifndef ECS_RECIPE_H
#define ECS_RECIPE_H

// the total number of components
#define TOTAL_COMPONENTS 6

// the value of an empty component slot
#define ECS_EMPTY 18446744073709551615ULL

typedef enum {
    POSITION         = 0,
    CAMERA           = 1,
    BLOCKBREAK       = 2,
    BLOCKPLACE       = 3,
    PHYSICS          = 4,
    PLAYERCONTROLLER = 5
} ECSType;

#endif
