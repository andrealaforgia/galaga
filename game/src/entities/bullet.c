#include "bullet.h"

#include "../../assets/sprites/sprite_coords.h"
#include "logger.h"

bullet_manager_t init_bullet_manager(const graphics_context_ptr graphics_context,
                                     const char* sprite_sheet_path) {
  bullet_manager_t manager = {0};

  // Load sprite sheet texture
  manager.sprite_sheet = load_texture(graphics_context->renderer, sprite_sheet_path);
  if (!manager.sprite_sheet.texture) {
    LOG_ERROR("Failed to load sprite sheet for bullets");
    return manager;
  }

  // Initialize all bullets as inactive
  for (int i = 0; i < MAX_BULLETS; i++) {
    manager.bullets[i].active = false;
  }

  LOG_INFO("Bullet manager initialized");

  return manager;
}

void fire_bullet(bullet_manager_t* manager, float x, float y) {
  // Find an inactive bullet slot
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!manager->bullets[i].active) {
      manager->bullets[i].x = x;
      manager->bullets[i].y = y;
      manager->bullets[i].active = true;
      return;
    }
  }
  // If we get here, all bullet slots are full
}

void update_bullets(bullet_manager_t* manager) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (manager->bullets[i].active) {
      // Move bullet upward
      manager->bullets[i].y -= BULLET_SPEED;

      // Deactivate bullet if it goes off screen
      if (manager->bullets[i].y < -10) {
        manager->bullets[i].active = false;
      }
    }
  }
}

void render_bullets(const bullet_manager_t* manager,
                   const graphics_context_ptr graphics_context) {
  if (!manager->sprite_sheet.texture) {
    return;
  }

  // Get bullet sprite coordinates
  sprite_rect_t sprite = galaga_sprites[PLAYER_BULLET_SPRITE_INDEX];

  for (int i = 0; i < MAX_BULLETS; i++) {
    if (manager->bullets[i].active) {
      // Set up source rectangle (from sprite sheet)
      SDL_Rect src_rect = {sprite.x, sprite.y, sprite.width, sprite.height};

      // Set up destination rectangle (where to draw on screen)
      SDL_FRect dst_rect = {
        manager->bullets[i].x,
        manager->bullets[i].y,
        (float)sprite.width,
        (float)sprite.height
      };

      // Render the bullet sprite
      SDL_RenderCopyF(graphics_context->renderer, manager->sprite_sheet.texture,
                      &src_rect, &dst_rect);
    }
  }
}

bullet_t* get_bullet(bullet_manager_t* manager, int index) {
  if (index >= 0 && index < MAX_BULLETS) {
    return &manager->bullets[index];
  }
  return NULL;
}

void cleanup_bullet_manager(bullet_manager_t* manager) {
  if (manager->sprite_sheet.texture) {
    free_texture(&manager->sprite_sheet);
  }
}
