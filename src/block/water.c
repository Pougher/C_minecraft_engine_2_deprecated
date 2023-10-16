#include "block.h"
#include "../common/gamestate.h"

static int get_texture_location(Direction dir) {
    (void) dir;
    return 47;
}

void water_init(void) {
    Block blk = {
        .id = WATER,
        .transparent = false,
        .fluid = true,
        .get_texture_location = get_texture_location
    };

    state->blocks[WATER] = blk;
}
