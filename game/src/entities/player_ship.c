#include "player_ship.h"

#include "../../assets/sprites/sprite_coords.h"
#include "logger.h"

player_ship_t init_player_ship(const graphics_context_ptr graphics_context,
                               const char* sprite_sheet_path) {
  player_ship_t ship = {0};

  // Load sprite sheet texture
  ship.sprite_sheet =
      load_texture(graphics_context->renderer, sprite_sheet_path);
  if (!ship.sprite_sheet.texture) {
    LOG_ERROR("Failed to load sprite sheet for player ship");
    return ship;
  }

  // Get player ship sprite dimensions
  sprite_rect_t sprite = galaga_sprites[PLAYER_SHIP_SPRITE_INDEX];

  // Position ship at bottom center of screen
  ship.x = (graphics_context->screen_width - sprite.width) / 2.0f;
  ship.y =
      graphics_context->screen_height - sprite.height - 20;  // 20px from bottom

  LOG_INFO_FMT("Player ship initialized at (%.1f, %.1f)", ship.x, ship.y);

  return ship;
}

void update_player_ship(player_ship_t* ship,
                        const keyboard_state_ptr keyboard_state,
                        const graphics_context_ptr graphics_context) {
  sprite_rect_t sprite = galaga_sprites[PLAYER_SHIP_SPRITE_INDEX];

  // Handle left movement
  if (is_left_key_pressed(keyboard_state)) {
    ship->x -= PLAYER_SHIP_SPEED;
    // Keep ship on screen
    if (ship->x < 0) {
      ship->x = 0;
    }
  }

  // Handle right movement
  if (is_right_key_pressed(keyboard_state)) {
    ship->x += PLAYER_SHIP_SPEED;
    // Keep ship on screen
    if (ship->x + sprite.width > graphics_context->screen_width) {
      ship->x = graphics_context->screen_width - sprite.width;
    }
  }
}

void render_player_ship(const player_ship_t* ship,
                        const graphics_context_ptr graphics_context) {
  if (!ship->sprite_sheet.texture) {
    return;
  }

  // Get player ship sprite coordinates
  sprite_rect_t sprite = galaga_sprites[PLAYER_SHIP_SPRITE_INDEX];

  // Set up source rectangle (from sprite sheet)
  SDL_Rect src_rect = {sprite.x, sprite.y, sprite.width, sprite.height};

  // Set up destination rectangle (where to draw on screen) - using float for
  // smooth movement
  SDL_FRect dst_rect = {ship->x, ship->y, (float)sprite.width,
                        (float)sprite.height};

  // Render the sprite with sub-pixel precision
  SDL_RenderCopyF(graphics_context->renderer, ship->sprite_sheet.texture,
                  &src_rect, &dst_rect);
}

float get_player_ship_center_x(const player_ship_t* ship) {
  sprite_rect_t sprite = galaga_sprites[PLAYER_SHIP_SPRITE_INDEX];
  return ship->x + sprite.width / 2.0f;
}

float get_player_ship_top_y(const player_ship_t* ship) { return ship->y; }

void cleanup_player_ship(player_ship_t* ship) {
  if (ship->sprite_sheet.texture) {
    free_texture(&ship->sprite_sheet);
  }
}
