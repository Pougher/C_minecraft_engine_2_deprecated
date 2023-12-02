#include "block.h"
#include "../common/gamestate.h"

static int get_texture_location(Direction dir) {
    (void) dir;
    return 196;
}

void leaves_init(void) {
    Block blk = {
        .id = LEAVES,
        .transparent = 1,
        .fluid = false,
        .get_texture_location = get_texture_location
    };

    state->blocks[LEAVES] = blk;
}
