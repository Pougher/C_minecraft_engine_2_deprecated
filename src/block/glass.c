#include "block.h"
#include "../common/gamestate.h"

static int get_texture_location(Direction dir) {
    (void) dir;
    return 193;
}

void glass_init(void) {
    Block blk = {
        .id = GLASS,
        .transparent = 1,
        .fluid = false,
        .get_texture_location = get_texture_location
    };

    state->blocks[GLASS] = blk;
}
