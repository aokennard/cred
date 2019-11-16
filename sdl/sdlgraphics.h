#include <SDL/SDL.h>

void set_pixel(SDL_Surface *surface, int x, int y, unsigned int pixel);
unsigned int get_pixel(SDL_Surface *surface, int x, int y);

SDL_Surface *ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height);