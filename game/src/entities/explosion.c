#include "explosion.h"

#include "../../assets/sprites/sprite_coords.h"
#include "logger.h"

explosion_manager_t init_explosion_manager(const graphics_context_ptr graphics_context,
                                           const char* sprite_sheet_path) {
  explosion_manager_t manager = {0};

  // Load sprite sheet texture
  manager.sprite_sheet = load_texture(graphics_context->renderer, sprite_sheet_path);
  if (!manager.sprite_sheet.texture) {
    LOG_ERROR("Failed to load sprite sheet for explosions");
    return manager;
  }

  // Initialize all explosions as inactive
  for (int i = 0; i < MAX_EXPLOSIONS; i++) {
    manager.explosions[i].active = false;
  }

  LOG_INFO("Explosion manager initialized");

  return manager;
}

void create_explosion(explosion_manager_t* manager, float x, float y) {
  // Find an inactive explosion slot
  for (int i = 0; i < MAX_EXPLOSIONS; i++) {
    if (!manager->explosions[i].active) {
      manager->explosions[i].x = x;
      manager->explosions[i].y = y;
      manager->explosions[i].current_frame = 0;
      manager->explosions[i].frame_counter = 0;
      manager->explosions[i].active = true;
      return;
    }
  }
  // If we get here, all explosion slots are full
}

void update_explosions(explosion_manager_t* manager) {
  for (int i = 0; i < MAX_EXPLOSIONS; i++) {
    if (manager->explosions[i].active) {
      explosion_t* explosion = &manager->explosions[i];

      explosion->frame_counter++;

      if (explosion->frame_counter >= EXPLOSION_FRAME_DURATION) {
        explosion->frame_counter = 0;
        explosion->current_frame++;

        // Deactivate when animation is complete (5 frames: 0-4)
        if (explosion->current_frame >= 5) {
          explosion->active = false;
        }
      }
    }
  }
}

void render_explosions(const explosion_manager_t* manager,
                      const graphics_context_ptr graphics_context) {
  if (!manager->sprite_sheet.texture) {
    return;
  }

  for (int i = 0; i < MAX_EXPLOSIONS; i++) {
    if (manager->explosions[i].active) {
      const explosion_t* explosion = &manager->explosions[i];

      // Get the appropriate explosion sprite frame
      int sprite_index = EXPLOSION_FRAME0 + explosion->current_frame;
      sprite_rect_t sprite = galaga_sprites[sprite_index];

      // Set up source rectangle (from sprite sheet)
      SDL_Rect src_rect = {sprite.x, sprite.y, sprite.width, sprite.height};

      // Set up destination rectangle (where to draw on screen)
      // Center the explosion on the given position
      SDL_FRect dst_rect = {
        explosion->x - sprite.width / 2.0f,
        explosion->y - sprite.height / 2.0f,
        (float)sprite.width,
        (float)sprite.height
      };

      // Render the explosion sprite
      SDL_RenderCopyF(graphics_context->renderer, manager->sprite_sheet.texture,
                      &src_rect, &dst_rect);
    }
  }
}

void cleanup_explosion_manager(explosion_manager_t* manager) {
  if (manager->sprite_sheet.texture) {
    free_texture(&manager->sprite_sheet);
  }
}
