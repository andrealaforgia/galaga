// Quick test to see what colors are in the sprite sheet
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

  printf("Image: %dx%d\n", surface->w, surface->h);
  printf("Sampling pixels to find grid line color:\n\n");

  // Sample some pixels that should be grid lines
  int test_positions[][2] = {
      {0, 0},    {17, 0},   {18, 0},  {35, 0}, {36, 0},  // Top row
      {0, 17},   {0, 18},   {0, 35},  {0, 36},           // Left column
      {100, 50}, {100, 68}, {100, 69}                    // Middle area
  };

  for (int i = 0; i < sizeof(test_positions) / sizeof(test_positions[0]); i++) {
    int x = test_positions[i][0];
    int y = test_positions[i][1];

    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch +
               x * surface->format->BytesPerPixel;
    Uint32 pixel = *(Uint32*)p;

    Uint8 r, g, b, a;
    SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);

    printf("Pixel (%3d, %3d): R=%3d G=%3d B=%3d A=%3d | Avg=%3d\n", x, y, r, g,
           b, a, (r + g + b) / 3);
  }

  SDL_FreeSurface(surface);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
