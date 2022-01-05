#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/prototypes.h"

int init_SDL();

int init_SDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return EXIT_FAILURE;
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int main(int ac, char **av) {

    if (init_SDL() == EXIT_FAILURE) {
        printf("erreur probleme Initialisation SDL\n");
        return EXIT_FAILURE;
    }

    if (ac != 2) {  //s'il n'y a pas deux arguments
        printf("erreur probleme d'arguments\n");
        return EXIT_FAILURE;
    } else {
        if (change_image(av[1]) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}