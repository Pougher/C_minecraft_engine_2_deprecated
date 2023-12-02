#include "ecs_block_place.h"
#include "../common/gamestate.h"

void ecs_blockplace_init(ECSblockplace *bp) {
    bp->cam = NULL;
    bp->pos = NULL;
    bp->id = DIRT;
}

void ecs_blockplace_tick(ECSblockplace *bp) {
    if (glfwGetKey(state->window->window, GLFW_KEY_1) == GLFW_PRESS) {
        bp->id = LEAVES;
    }
    if (glfwGetKey(state->window->window, GLFW_KEY_2) == GLFW_PRESS) {
        bp->id = GLASS;
    }
    if (glfwGetKey(state->window->window, GLFW_KEY_3) == GLFW_PRESS) {
        bp->id = PLANKS;
    }
    if (glfwGetKey(state->window->window, GLFW_KEY_4) == GLFW_PRESS) {
        bp->id = WOOD;
    }
}

void ecs_blockplace_mouse_tick(ECSblockplace *bp, MouseState *ms) {
    if (ms->button == GLFW_MOUSE_BUTTON_RIGHT && ms->action == GLFW_PRESS) {
        Ray ray = {
            .step = 2048.0f
        };

        glm_vec3_copy(bp->cam->cam.front, ray.direction);
        glm_vec3_copy(*(bp->pos), ray.pos);

        ray_init(&ray);

        BlockType id;

        for (int i = 0; i < BLOCK_REACH * 2048; i++) {
            id = world_get_block(state->world,
                ray.pos[0],
                ray.pos[1],
                ray.pos[2]);
            if (id != AIR) {
                break;
            }
            ray_step(&ray);
        }
        if (id == AIR) return;

        // we have intersected with a block, retrace the ray back 1 space to
        // find the coordinates of the adjacent block

        glm_vec3_sub(ray.pos, ray.direction, ray.pos);

        world_set_block(
            state->world, ray.pos[0], ray.pos[1], ray.pos[2], bp->id);
    }
}
