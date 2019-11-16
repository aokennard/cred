#include "sdlgraphics.h"

void set_pixel(SDL_Surface *surface, int x, int y, unsigned int pixel)
{
  unsigned int *target_pixel = (unsigned char *) surface->pixels + y * surface->pitch +
                                                     x * sizeof *target_pixel;
  *target_pixel = pixel;
}

unsigned int get_pixel(SDL_Surface *surface, int x, int y)
{
  unsigned int *target_pixel = (unsigned char *) surface->pixels + y * surface->pitch +
                                                     x * sizeof *target_pixel;
  return *target_pixel;
}

SDL_Surface *ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height)
{
    if(!Surface || !Width || !Height)
        return 0;
     
    SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,
        Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);
 
    double    _stretch_factor_x = ((double)(Width)  / (double)(Surface->w)),
        _stretch_factor_y = ((double)(Height) / (double)(Surface->h));
 
    for(Sint32 y = 0; y < Surface->h; y++)
        for(Sint32 x = 0; x < Surface->w; x++)
            for(Sint32 o_y = 0; o_y < _stretch_factor_y; ++o_y)
                for(Sint32 o_x = 0; o_x < _stretch_factor_x; ++o_x)
                    set_pixel(_ret, (int)(_stretch_factor_x * x) + o_x, 
                        (int)(_stretch_factor_y * y) + o_y, get_pixel(Surface, x, y));
 
    return _ret;
}