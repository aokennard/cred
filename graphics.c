#include "graphics.h"

int init_graphics_mode() {
    #if USE_SDL
    return SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    #endif 
}

video_buffer* create_window(int size_x, int size_y) {
    video_buffer* newbuf = malloc(sizeof(video_buffer));
    #if USE_SDL && !SDL2
    newbuf->buffer = SDL_SetVideoMode(size_x, size_y, sizeof(int) * 8, SDL_SWSURFACE);
    #elif SDL2
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_CreateWindowAndRenderer(size_x, size_y, 0, &window, &renderer);
    //SDL_SetWindowPosition(window, horizontal_res , vertical_res );
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    newbuf->buffer = renderer;
    newbuf->window = window;
    #endif

    return newbuf;
}

void scale_video_buffer(video_buffer* buf, int desired_x, int desired_y) {
    #if USE_SDL && !SDL2
    buf->buffer = ScaleSurface(buf->buffer, desired_x, desired_y);
    #endif
}

void show_text_window(video_buffer* buf, int pos_x, int pos_y, int size_x, int size_y) {
    #if USE_SDL && !SDL2
    SDL_Surface* s = ((SDL_Surface*)buf->buffer);
    Uint8 pixels[s->h * s->pitch];
    Uint32 yellow = SDL_MapRGB(s->format, 0xff, 0xff, 0x00);
    for(int x = pos_x; x < pos_x + size_x; x++) {
        for(int y = pos_y; y < pos_y + size_y; y++) {
            pixels[x + (y * s->pitch)] = 0;
            pixels[x + (y * s->pitch)  + 1] = 255;
            pixels[x + (y * s->pitch) + 2] = 0;
        }
    }
    SDL_LockSurface(s);
    memcpy(s->pixels, pixels, s->pitch * s->h);
    SDL_UnlockSurface(s);
    //SDL_UpdateRect(buf->buffer, 0,0,0,0); //pos_x, pos_y, size_y, size_y);
    #elif SDL2
    SDL_SetRenderDrawColor(buf->buffer, 0, 255, 0, 255);
    for(int i = pos_x; i < pos_x + size_x; i++) {
        for(int j = pos_y; j < pos_y + size_y; j++) {
            SDL_RenderDrawPoint(buf->buffer, i, j);
        }
    }
        
    SDL_RenderPresent(buf->buffer);
    #endif 
    //SDL_Flip(buf->buffer);
    printf("Updated window\n");
}

void destroy_window(video_buffer* buf) {
    // platform dependant frees
    #if USE_SDL && !SDL2
    SDL_FreeSurface(buf->buffer);
    #elif SDL2
    SDL_DestroyRenderer(buf->buffer);
    SDL_DestroyWindow(buf->window);
    #endif
    free(buf);
}