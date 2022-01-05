#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"

int init_SDL(); //function to init the SDL and SDL_image

int change_image(char *path_image); //the function to get the picture and will change to grey color
void setColor(SDL_Surface *surface, int W, int H, Uint32 *pixels); //get the color of the pixel and change to grey
void applyColor(SDL_Surface *surface, int W, int H, Uint32 *pixels); //now apply the grey color on the surface

#endif