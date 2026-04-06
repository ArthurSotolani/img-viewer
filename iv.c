#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  _setmode(_fileno(stdin), _O_BINARY);
  FILE *in = stdin;
  char *pthroway = calloc(1000, sizeof(char));
  // Le primeira linha
  fgets(pthroway, 1000, in); // Especifica p3 ou p6
  // Le segunda linha
  fgets(pthroway, 1000, in); // comentario
  // Le a terceira linha
  char *pdimensions = calloc(1000, sizeof(char));
  fgets(pdimensions, 1000, in);
  // Le a quarta linha (maximum color value, inutil pois todo arquivo moderno
  // sera 255)
  fgets(pthroway, 1000, in);

  int pwidth = -1;
  int pheight = -1;
  sscanf(pdimensions, "%d %d\n", &pwidth, &pheight);
  free(pdimensions);
  printf("width=%d, height=%d\n", pwidth, pheight);

  SDL_Window *pwindow =
      SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, pwidth, pheight, 0);
  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
  SDL_Rect pixel = (SDL_Rect){0, 0, 1, 1};
  for (int y = 0; y < pheight; y++) {
    for (int x = 0; x < pwidth; x++) {
      Uint8 r, g, b;
      if (fread(&r, 1, 1, in) != 1 || fread(&g, 1, 1, in) != 1 ||
          fread(&b, 1, 1, in) != 1) {
        printf("Failed at pixel %d,%d\n", x, y);
        break;
      }
      Uint32 color = SDL_MapRGB(psurface->format, r, g, b);
      pixel.x = x;
      pixel.y = y;
      SDL_FillRect(psurface, &pixel, color);
    }
  }
  printf("Done reading pixels\n");

  SDL_UpdateWindowSurface(pwindow);
  SDL_Delay(10000);
  free(pthroway);
}
