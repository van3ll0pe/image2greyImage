#include "../include/prototypes.h"


void setColor(SDL_Surface *surface, int W, int H, Uint32 *pixels) {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    Uint8 tallerValue;  //la plus grande valeur RGB du pixel
    Uint8 smallerValue; //la plus petite valeur RGB du pixel

    //on parcourt le tableau afin de récupérer les valeurs RGB de chaque pixels
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) { //                                 on décale pour que ça rentre dans 8bits uniquement
            r = (pixels[y * W + x] & 0b11111111000000000000000000000000) >> 24; //recupérer les 8bits forts pour R
            g = (pixels[y * W + x] & 0b00000000111111110000000000000000) >> 16; //recupérer les 8bits un peu moins forts pour G
            b = (pixels[y * W + x] & 0b00000000000000001111111100000000) >> 8; //récupérer les 8bits encore moins forts pour B
            a = (pixels[y * W + x] & 0b00000000000000000000000011111111); //récupérer les 8 bits faibles pour A

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
            //on set le pixels avec sa nouvelle valeur
            pixels[y * W + x] = (((tallerValue + smallerValue) / 2) << 24) + (((tallerValue + smallerValue) / 2) << 16) + (((tallerValue + smallerValue) / 2) << 8) + a;
        }
    }
}


int change_image(char *path_image) {
    SDL_Surface *tmp = NULL;  //the surface to get the picture
    SDL_Surface *surfaceImage = NULL; //the surface with the good format
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    int WIDTH;  //the width of the picture
    int HEIGHT; //the height of the picture
    Uint32 *pixels = NULL; //the tableau de pixels (du nombre de pixel sur l'image) pour stocker les couleurs
    char *newPathName = NULL;

    //get the image
    tmp = IMG_Load(path_image);
    if (tmp == NULL) {
        printf("erreur récupération d'image\n");
        return EXIT_FAILURE;
    }

    //get the size of the picture (to browse array)
    WIDTH = tmp->w;
    HEIGHT = tmp->h;

    //set the new surface with the picture in tmp and the good format
    surfaceImage = SDL_ConvertSurface(tmp, format, 0);
    if (surfaceImage == NULL) {
        printf("erreur convertion surface\n");
        return EXIT_FAILURE;
    }
    SDL_FreeSurface(tmp);

    //get all pixels in the array
    SDL_LockSurface(surfaceImage);
    pixels = surfaceImage->pixels;
    SDL_UnlockSurface(surfaceImage);


    //parcours de l'image et le transforme en gris
    setColor(surfaceImage, WIDTH, HEIGHT, pixels);
   

    //set the name of the new image like "copy_image"
    newPathName =(char *)malloc(sizeof(char) * strlen("copy_image")+1);
    newPathName[strlen("copy_image")] = '\0'; 
    strcpy(newPathName, "copy_image");
    
    //save the picture in the new file
    SDL_SaveBMP(surfaceImage, newPathName);

    return EXIT_SUCCESS;

}
