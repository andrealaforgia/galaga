#include "sprite_viewer.h"

#include <stdio.h>

#include "../../assets/sprites/sprite_coords.h"
#include "color.h"
#include "geometry.h"
#include "logger.h"
#include "text.h"

sprite_viewer_t init_sprite_viewer(const graphics_context_ptr graphics_context,
                                   const char* sprite_sheet_path) {
  sprite_viewer_t viewer = {0};

  // Load sprite sheet texture
  viewer.sprite_sheet = load_texture(graphics_context->renderer, sprite_sheet_path);
  if (!viewer.sprite_sheet.texture) {
    LOG_ERROR("Failed to load sprite sheet");
    return viewer;
  }

  // Start at sprite 1 (skip sprite 0 which is the full image)
  viewer.current_sprite_index = 1;
  viewer.total_sprites = SPRITE_COUNT;

  LOG_INFO_FMT("Sprite viewer initialized with %d sprites",
               viewer.total_sprites);

  return viewer;
}

void update_sprite_viewer(sprite_viewer_t* viewer,
                         const keyboard_state_ptr keyboard_state) {
  // Navigate to next sprite with right arrow or space
  if (is_right_key_pressed(keyboard_state) ||
      is_space_key_pressed(keyboard_state)) {
    viewer->current_sprite_index++;
    if (viewer->current_sprite_index >= viewer->total_sprites) {
      viewer->current_sprite_index = 1;  // Skip sprite 0
    }
    LOG_INFO_FMT("Sprite: %d", viewer->current_sprite_index);
  }

  // Navigate to previous sprite with left arrow
  if (is_left_key_pressed(keyboard_state)) {
    viewer->current_sprite_index--;
    if (viewer->current_sprite_index < 1) {
      viewer->current_sprite_index = viewer->total_sprites - 1;
    }
    LOG_INFO_FMT("Sprite: %d", viewer->current_sprite_index);
  }

  // Jump forward/backward by 10 with up/down arrows
  if (is_up_key_pressed(keyboard_state)) {
    viewer->current_sprite_index -= 10;
    if (viewer->current_sprite_index < 1) {
      viewer->current_sprite_index = 1;
    }
    LOG_INFO_FMT("Sprite: %d", viewer->current_sprite_index);
  }

  // Note: We don't have is_down_key_pressed, so we'll skip this for now
}

void render_sprite_viewer(const sprite_viewer_t* viewer,
                         const graphics_context_ptr graphics_context) {
  if (!viewer->sprite_sheet.texture) {
    return;
  }

  // Draw title
  write_text(graphics_context, "All Sprites - Find the Player Ship",
             point(10, 5), 1, COLOR_WHITE);

  // Matrix layout parameters
  int start_x = 5;
  int start_y = 20;
  int spacing_x = 25;  // Horizontal spacing between sprites
  int spacing_y = 25;  // Vertical spacing between sprites
  int sprites_per_row = 11;  // Number of sprites per row

  int current_x = start_x;
  int current_y = start_y;

  // Skip sprite 0 (full image) and render sprites 1 onwards
  for (int i = 1; i < viewer->total_sprites; i++) {
    sprite_rect_t sprite = galaga_sprites[i];

    // Draw the sprite
    SDL_Rect src_rect = {sprite.x, sprite.y, sprite.width, sprite.height};
    SDL_Rect dst_rect = {current_x, current_y, sprite.width, sprite.height};
    SDL_RenderCopy(graphics_context->renderer, viewer->sprite_sheet.texture,
                   &src_rect, &dst_rect);

    // Draw sprite index number below sprite (small text)
    char index_text[8];
    snprintf(index_text, sizeof(index_text), "%d", i);
    write_text(graphics_context, index_text,
               point(current_x, current_y + sprite.height + 2), 1, COLOR_GRAY);

    // Move to next position
    current_x += spacing_x;

    // Check if we need to move to next row
    if ((i % sprites_per_row) == 0) {
      current_x = start_x;
      current_y += spacing_y;
    }

    // Stop if we run out of vertical space
    if (current_y > graphics_context->screen_height - 30) {
      break;
    }
  }

  // Draw instructions at bottom
  const char* controls = "Find the player ship sprite and note its number";
  write_text(graphics_context, controls,
             point(10, graphics_context->screen_height - 15), 1, COLOR_YELLOW);
}

void cleanup_sprite_viewer(sprite_viewer_t* viewer) {
  if (viewer->sprite_sheet.texture) {
    free_texture(&viewer->sprite_sheet);
  }
}
