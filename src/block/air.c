#include "block.h"
#include "../common/gamestate.h"

static int get_texture_location(Direction dir) {
    (void) dir;
    return 0;
}

void air_init(void) {
    Block blk = {
        .id = AIR,
        .transparent = true,
        .get_texture_location = get_texture_location
    };

    state->blocks[AIR] = blk;
}
