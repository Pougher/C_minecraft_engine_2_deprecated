#include "block.h"
#include "../common/gamestate.h"

static int get_texture_location(Direction dir) {
    if (dir == UP) return 229;
    if (dir == DOWN) return 229;
    return 228;
}

void wood_init(void) {
    Block blk = {
        .id = WOOD,
        .transparent = false,
        .fluid = false,
        .get_texture_location = get_texture_location
    };

    state->blocks[WOOD] = blk;
}
