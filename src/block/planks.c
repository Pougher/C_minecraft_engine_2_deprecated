#include "block.h"
#include "../common/gamestate.h"

static int get_texture_location(Direction dir) {
    (void) dir;
    return 244;
}

void planks_init(void) {
    Block blk = {
        .id = PLANKS,
        .transparent = false,
        .fluid = false,
        .get_texture_location = get_texture_location
    };

    state->blocks[PLANKS] = blk;
}
