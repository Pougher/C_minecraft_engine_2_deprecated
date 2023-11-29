#ifndef MOUSE_STATE_H
#define MOUSE_STATE_H

typedef struct {
    // action of the mouse
    int action;

    // the button being pressed
    int button;

    // the modifiers on the mousebutton
    int mods;
} MouseState;

#endif
