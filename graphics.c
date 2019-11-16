#include "graphics.h"

int init_graphics_mode() {
    #if USE_SDL
    return SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    #endif 
}