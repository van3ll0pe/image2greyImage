#include "../include/prototypes.h"


void setColor(SDL_Surface *surface) {
    Uint32 *pixels = NULL;
    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;
    Uint8 a = 0;

    Uint8 tallerValue = 0;  //la plus grande valeur RGB du pixel
    Uint8 smallerValue = 0; //la plus petite valeur RGB du pixel

    if (SDL_LockSurface(surface) < 0) { //on lock la surface pour modifier les pixels directement
        printf("problème pour bloquer la surface\n");
        return ;
    } 
    pixels = surface->pixels; //pixels est égal à la même adresse mémoire que surface->pixels. On faisant les modifications sur les valeurs stockées dans l'adresse enregistrée dans pixels, on change change les valeurs pour surface->pixels également puisqu'il pointe aussi sur les mêmes adresses
    //on parcourt le tableau afin de récupérer les valeurs RGB de chaque pixels
    for (int y = 0; y < surface->h; y++) {
        for (int x = 0; x < surface->w; x++) { //                                 on décale pour que ça rentre dans 8bits uniquement
            r = (pixels[y * surface->w + x] & 0b11111111000000000000000000000000) >> 24; //recupérer les 8bits forts pour R
            g = (pixels[y * surface->w + x] & 0b00000000111111110000000000000000) >> 16; //recupérer les 8bits un peu moins forts pour G
            b = (pixels[y * surface->w + x] & 0b00000000000000001111111100000000) >> 8; //récupérer les 8bits encore moins forts pour B
            a = (pixels[y * surface->w + x] & 0b00000000000000000000000011111111); //récupérer les 8 bits faibles pour A

            //on cherche la valeur la plus grande et la plus petite
            if (r > g) {
                if (r > b) {
                    //r le plus grand
                    tallerValue = r;
                    //g le plus petit
                    smallerValue = g;
                } else {
                    //b le plus grand
                    tallerValue = b;
                    //g le plus petit
                    smallerValue = g;
                }
            } else {
                if (g > b) {
                    //g le plus grand
                    tallerValue = g;
                    //r le plus petit
                    smallerValue = r;
                }
                else {
                    //b le plus grand
                    tallerValue = b;
                    //r le plus petit
                    smallerValue = r;
                }
            }
            //on set le pixels à y * surface->w + x avec sa nouvelle valeur
            pixels[y * surface->w + x] = (((tallerValue + smallerValue) / 2) << 24) + (((tallerValue + smallerValue) / 2) << 16) + (((tallerValue + smallerValue) / 2) << 8) + a;
        }
    }
    SDL_UnlockSurface(surface);
}


int change_image(char *path_image) {
    SDL_Surface *tmp = NULL;  //the surface to get the picture
    SDL_Surface *surfaceImage = NULL; //the surface with the good format
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    char *newPathName = NULL;

    //get the image
    tmp = IMG_Load(path_image);
    if (tmp == NULL) {
        printf("erreur récupération d'image\n");
        return EXIT_FAILURE;
    }

    //set the new surface with the picture in tmp and the good format
    surfaceImage = SDL_ConvertSurface(tmp, format, 0);
    SDL_FreeSurface(tmp);
    if (surfaceImage == NULL) {
        printf("erreur convertion surface\n");
        return EXIT_FAILURE;
    }


    //parcours de l'image et le transforme en gris
    setColor(surfaceImage);
   

    //set the name of the new image like "copy_image"
    newPathName =(char *)malloc(sizeof(char) * strlen("copy_image")+1);
    newPathName[strlen("copy_image")] = '\0'; 
    strcpy(newPathName, "copy_image");
    
    //save the picture in the new file
    SDL_SaveBMP(surfaceImage, newPathName);
    free(surfaceImage);

    return EXIT_SUCCESS;
}
