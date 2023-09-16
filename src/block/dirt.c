#include "block.h"
#include "../common/gamestate.h"

static TexUVi get_texture_location(Direction dir) {
    (void) dir;
    return (TexUVi) { .u = 0, .v = 0 };
}

void dirt_init(void) {
    Block blk = {
        .id = DIRT,
        .transparent = false,
        .get_texture_location = get_texture_location
    };

    state->blocks[DIRT] = blk;
}
