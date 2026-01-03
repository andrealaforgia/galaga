// Debug grid detection
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

static bool is_grid_line_pixel(Uint32 pixel, SDL_PixelFormat* format) {
  Uint8 r, g, b, a;
  SDL_GetRGBA(pixel, format, &r, &g, &b, &a);

  if (a < 10) {
    return true;
  }

  if (r >= 60 && r <= 70 && g >= 60 && g <= 70 && b >= 60 && b <= 70) {
    return true;
  }

  return false;
}

static Uint32 get_pixel(SDL_Surface* surface, int x, int y) {
  if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) {
    return 0;
  }

  int bpp = surface->format->BytesPerPixel;
  Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

  switch (bpp) {
    case 1:
      return *p;
    case 2:
      return *(Uint16*)p;
    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        return p[0] << 16 | p[1] << 8 | p[2];
      } else {
        return p[0] | p[1] << 8 | p[2] << 16;
      }
    case 4:
      return *(Uint32*)p;
    default:
      return 0;
  }
}

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

  printf("Testing grid detection in first 20x20 pixels:\n\n");

  int grid_count = 0;
  int non_grid_count = 0;
  int found_cells = 0;

  for (int y = 0; y < 20 && y < surface->h; y++) {
    for (int x = 0; x < 20 && x < surface->w; x++) {
      Uint32 pixel = get_pixel(surface, x, y);
      bool is_grid = is_grid_line_pixel(pixel, surface->format);

      Uint8 r, g, b, a;
      SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);

      if (is_grid) {
        grid_count++;
        if (x < 5 && y < 5) {
          printf("Grid at (%2d,%2d): R=%3d G=%3d B=%3d A=%3d\n", x, y, r, g, b, a);
        }

        // Check for cell start
        if (x < surface->w - 1 && y < surface->h - 1) {
          Uint32 right_pixel = get_pixel(surface, x + 1, y);
          Uint32 bottom_pixel = get_pixel(surface, x, y + 1);

          bool right_is_grid = is_grid_line_pixel(right_pixel, surface->format);
          bool bottom_is_grid = is_grid_line_pixel(bottom_pixel, surface->format);

          if (!right_is_grid && !bottom_is_grid) {
            found_cells++;
            printf("Found cell start at (%d, %d)\n", x, y);
          }
        }
      } else {
        non_grid_count++;
      }
    }
  }

  printf("\nSummary:\n");
  printf("Grid pixels: %d\n", grid_count);
  printf("Non-grid pixels: %d\n", non_grid_count);
  printf("Potential cells found: %d\n", found_cells);

  SDL_FreeSurface(surface);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
