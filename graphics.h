#include "stdtypes.h"

#define USE_SDL 1

#if USE_SDL
#include "sdl/sdlgraphics.h"
#endif

typedef struct video_buffer video_buffer;

struct video_buffer {
    void* buffer;
};


int init_graphics_mode();

video_buffer* create_window(int size_x, int size_y);

void scale_video_buffer(video_buffer* buf, int desired_x, int desired_y);

void destroy_window(video_buffer* buf);
