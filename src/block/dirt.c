#include "block.h"
#include "../common/gamestate.h"

static int get_texture_location(Direction dir) {
    (void) dir;
    return 242;
}

void dirt_init(void) {
    Block blk = {
        .id = DIRT,
        .transparent = false,
        .fluid = false,
        .get_texture_location = get_texture_location
    };

    state->blocks[DIRT] = blk;
}
