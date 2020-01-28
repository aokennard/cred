#define SDL2 1

#if SDL2
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>

void set_pixel(SDL_Surface *surface, int x, int y, unsigned int pixel);
unsigned int get_pixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

SDL_Surface *ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height);

#endif

#include <stdio.h>

