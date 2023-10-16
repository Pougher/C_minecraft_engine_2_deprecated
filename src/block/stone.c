#include "block.h"
#include "../common/gamestate.h"

static int get_texture_location(Direction dir) {
    (void) dir;
    return 241;
}

void stone_init(void) {
    Block blk = {
        .id = STONE,
        .transparent = false,
        .fluid = false,
        .get_texture_location = get_texture_location
    };

    state->blocks[STONE] = blk;
}
