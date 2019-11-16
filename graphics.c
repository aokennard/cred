#include "graphics.h"

int init_graphics_mode() {
    #if USE_SDL
    return SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    #endif 
}

video_buffer* create_window(int size_x, int size_y) {
    video_buffer* newbuf = malloc(sizeof(video_buffer));
    #if USE_SDL
    newbuf->buffer = SDL_SetVideoMode(size_x, size_y, sizeof(int) * 8, SDL_DOUBLEBUF | SDL_SWSURFACE);
    #endif

    return newbuf;
}

void scale_video_buffer(video_buffer* buf, int desired_x, int desired_y) {
    #if USE_SDL
    buf->buffer = ScaleSurface(buf->buffer, desired_x, desired_y);
    #endif
}

void destroy_window(video_buffer* buf) {
    // platform dependant frees
    #if USE_SDL
    SDL_FreeSurface(buf->buffer);
    #endif
    free(buf);
}