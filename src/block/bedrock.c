#include "block.h"
#include "../common/gamestate.h"

static int get_texture_location(Direction dir) {
    (void) dir;
    return 4;
}

void bedrock_init(void) {
    Block blk = {
        .id = BEDROCK,
        .transparent = false,
        .get_texture_location = get_texture_location
    };

    state->blocks[BEDROCK] = blk;
}
