/**
 * @file sprite_extractor.c
 * @brief Utility to extract sprite coordinates from a sprite sheet
 *
 * Scans a sprite sheet image and identifies rectangular regions containing
 * sprites (non-black pixels surrounded by black borders). Outputs the
 * coordinates of each sprite found.
 */

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x;
  int y;
  int width;
  int height;
} sprite_rect_t;

typedef struct {
  sprite_rect_t* rects;
  int count;
  int capacity;
} sprite_list_t;

// Check if a pixel is a grid line (dark grey ~64,64,64 or transparent)
static bool is_grid_line_pixel(Uint32 pixel, SDL_PixelFormat* format) {
  Uint8 r, g, b, a;
  SDL_GetRGBA(pixel, format, &r, &g, &b, &a);

  // Transparent pixels are grid lines
  if (a < 10) {
    return true;
  }

  // Dark grey pixels (64,64,64 or similar) are grid lines
  if (r >= 60 && r <= 70 && g >= 60 && g <= 70 && b >= 60 && b <= 70) {
    return true;
  }

  return false;
}

// Check if a pixel is black (or very close to black)
static bool is_black_pixel(Uint32 pixel, SDL_PixelFormat* format) {
  Uint8 r, g, b, a;
  SDL_GetRGBA(pixel, format, &r, &g, &b, &a);
  // Consider it black if RGB values are all very low
  return (r < 20 && g < 20 && b < 20) || a < 10;
}

// Get pixel at position (x, y) from surface
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

// Find a grid cell (rectangle bounded by grid lines)
static sprite_rect_t find_grid_cell(SDL_Surface* surface, int start_x, int start_y) {
  sprite_rect_t rect = {start_x, start_y, 0, 0};

  // Find right edge (next grid line or image edge)
  int right = start_x;
  while (right < surface->w) {
    Uint32 pixel = get_pixel(surface, right, start_y);
    if (is_grid_line_pixel(pixel, surface->format)) {
      break;
    }
    right++;
  }

  // Find bottom edge (next grid line or image edge)
  int bottom = start_y;
  while (bottom < surface->h) {
    Uint32 pixel = get_pixel(surface, start_x, bottom);
    if (is_grid_line_pixel(pixel, surface->format)) {
      break;
    }
    bottom++;
  }

  rect.width = right - start_x;
  rect.height = bottom - start_y;

  return rect;
}

// Add a sprite rectangle to the list
static void add_sprite(sprite_list_t* list, sprite_rect_t rect) {
  if (list->count >= list->capacity) {
    list->capacity *= 2;
    list->rects = realloc(list->rects, list->capacity * sizeof(sprite_rect_t));
  }
  list->rects[list->count++] = rect;
}

// Extract all sprites from the image
static sprite_list_t extract_sprites(SDL_Surface* surface) {
  sprite_list_t list = {0};
  list.capacity = 500;
  list.rects = malloc(list.capacity * sizeof(sprite_rect_t));

  // Scan for grid cells by looking for non-grid pixels after grid lines
  for (int y = 1; y < surface->h - 1; y++) {
    for (int x = 1; x < surface->w - 1; x++) {
      Uint32 pixel = get_pixel(surface, x, y);
      Uint32 left_pixel = get_pixel(surface, x - 1, y);
      Uint32 top_pixel = get_pixel(surface, x, y - 1);

      // Look for top-left corner of a cell: current pixel is NOT grid,
      // but pixel to left and above ARE grid lines
      if (!is_grid_line_pixel(pixel, surface->format) &&
          is_grid_line_pixel(left_pixel, surface->format) &&
          is_grid_line_pixel(top_pixel, surface->format)) {
        // Found top-left corner of a grid cell
        sprite_rect_t cell = find_grid_cell(surface, x, y);

        // Only add cells that are reasonable sprite sizes
        if (cell.width >= 3 && cell.height >= 3 &&
            cell.width <= 100 && cell.height <= 100) {
          add_sprite(&list, cell);
        }
      }
    }
  }

  return list;
}

// Compare function for sorting sprites (top to bottom, left to right)
static int compare_sprites(const void* a, const void* b) {
  const sprite_rect_t* rect_a = (const sprite_rect_t*)a;
  const sprite_rect_t* rect_b = (const sprite_rect_t*)b;

  // Sort by y first, then by x
  if (rect_a->y != rect_b->y) {
    return rect_a->y - rect_b->y;
  }
  return rect_a->x - rect_b->x;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <sprite_sheet.png>\n", argv[0]);
    return 1;
  }

  const char* filename = argv[1];

  // Initialize SDL and SDL_image
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  int img_flags = IMG_INIT_PNG;
  if (!(IMG_Init(img_flags) & img_flags)) {
    fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());
    SDL_Quit();
    return 1;
  }

  // Load the sprite sheet
  SDL_Surface* surface = IMG_Load(filename);
  if (!surface) {
    fprintf(stderr, "IMG_Load Error: %s\n", IMG_GetError());
    IMG_Quit();
    SDL_Quit();
    return 1;
  }

  printf("Loaded sprite sheet: %s\n", filename);
  printf("Dimensions: %dx%d\n", surface->w, surface->h);
  printf("Extracting sprites...\n\n");

  // Extract sprites
  sprite_list_t sprites = extract_sprites(surface);

  // Sort sprites by position
  qsort(sprites.rects, sprites.count, sizeof(sprite_rect_t), compare_sprites);

  // Output results
  printf("Found %d sprites:\n\n", sprites.count);
  printf("Index | X    | Y    | Width | Height\n");
  printf("------|------|------|-------|-------\n");

  for (int i = 0; i < sprites.count; i++) {
    sprite_rect_t* rect = &sprites.rects[i];
    printf("%-5d | %-4d | %-4d | %-5d | %-6d\n", i, rect->x, rect->y,
           rect->width, rect->height);
  }

  printf("\n");
  printf("// C array format:\n");
  printf("sprite_rect_t sprites[] = {\n");
  for (int i = 0; i < sprites.count; i++) {
    sprite_rect_t* rect = &sprites.rects[i];
    printf("  {%d, %d, %d, %d}%s  // Sprite %d\n", rect->x, rect->y,
           rect->width, rect->height, (i < sprites.count - 1) ? "," : " ", i);
  }
  printf("};\n");

  // Clean up
  free(sprites.rects);
  SDL_FreeSurface(surface);
  IMG_Quit();
  SDL_Quit();

  return 0;
}
