// Scan the image to understand its structure
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <image.png>\n", argv[0]);
    return 1;
  }

  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  SDL_Surface* surface = IMG_Load(argv[1]);
  if (!surface) {
    fprintf(stderr, "Failed to load image\n");
    return 1;
  }

  printf("Image: %dx%d, BPP: %d\n", surface->w, surface->h, surface->format->BytesPerPixel);

  // Count different pixel types in first 100x100 area
  int transparent_count = 0;
  int black_count = 0;
  int colored_count = 0;

  for (int y = 0; y < 100 && y < surface->h; y++) {
    for (int x = 0; x < 100 && x < surface->w; x++) {
      Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
      Uint32 pixel = *(Uint32*)p;

      Uint8 r, g, b, a;
      SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);

      if (a < 10) {
        transparent_count++;
      } else if (r < 20 && g < 20 && b < 20) {
        black_count++;
      } else {
        colored_count++;
        if (colored_count <= 10) {
          printf("Colored pixel at (%d, %d): R=%d G=%d B=%d A=%d\n", x, y, r, g, b, a);
        }
      }
    }
  }

  printf("\nIn first 100x100 pixels:\n");
  printf("Transparent: %d\n", transparent_count);
  printf("Black: %d\n", black_count);
  printf("Colored: %d\n", colored_count);

  SDL_FreeSurface(surface);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
