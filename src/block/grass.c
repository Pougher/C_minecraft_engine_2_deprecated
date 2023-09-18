#include "block.h"
#include "../common/gamestate.h"

static int get_texture_location(Direction dir) {
    if (dir == UP) return 0;
    return 1;
}

void grass_init(void) {
    Block blk = {
        .id = GRASS,
        .transparent = false,
        .get_texture_location = get_texture_location
    };

    state->blocks[GRASS] = blk;
}
