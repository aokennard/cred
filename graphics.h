#include <SDL/SDL.h>
#include "stdtypes.h"

#define USE_SDL 1

typedef struct video_buffer video_buffer;

struct video_buffer {
    void* buffer;
};


int init_graphics_mode();

