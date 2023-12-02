#include "block.h"

void block_init(void) {
    BLOCK_DECL(dirt);
    BLOCK_DECL(grass);
    BLOCK_DECL(air);
    BLOCK_DECL(stone);
    BLOCK_DECL(sand);
    BLOCK_DECL(water);
    BLOCK_DECL(bedrock);
    BLOCK_DECL(wood);
    BLOCK_DECL(planks);
    BLOCK_DECL(glass);
    BLOCK_DECL(leaves);
}

void block_print_name(BlockType id) {
    switch(id) {
        BLOCK_LOG_ID(DIRT);
        BLOCK_LOG_ID(GRASS);
        BLOCK_LOG_ID(AIR);
        BLOCK_LOG_ID(STONE);
        BLOCK_LOG_ID(SAND);
        BLOCK_LOG_ID(WATER);
        BLOCK_LOG_ID(BEDROCK);
        BLOCK_LOG_ID(WOOD);
        BLOCK_LOG_ID(PLANKS);
        BLOCK_LOG_ID(GLASS);
        BLOCK_LOG_ID(LEAVES);
        default: {
            log_warning("Block ID not known");
            break;
        }
    }
}
