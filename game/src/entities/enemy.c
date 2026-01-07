#include "enemy.h"

#include <math.h>
#include <stdlib.h>

#include "../../assets/sprites/sprite_coords.h"
#include "logger.h"

// Get the sprite index for an enemy based on type and animation frame
static int get_enemy_sprite_index(int type, int frame) {
  const int sprite_indices[4][2] = {{ENEMY_TYPE0_FRAME0, ENEMY_TYPE0_FRAME1},
                                    {ENEMY_TYPE1_FRAME0, ENEMY_TYPE1_FRAME1},
                                    {ENEMY_TYPE2_FRAME0, ENEMY_TYPE2_FRAME1},
                                    {ENEMY_TYPE3_FRAME0, ENEMY_TYPE3_FRAME1}};
  return sprite_indices[type][frame];
}

enemy_manager_t init_enemy_manager(const graphics_context_ptr graphics_context,
                                   const char* sprite_sheet_path) {
  enemy_manager_t manager = {0};

  // Load sprite sheet texture
  manager.sprite_sheet =
      load_texture(graphics_context->renderer, sprite_sheet_path);
  if (!manager.sprite_sheet.texture) {
    LOG_ERROR("Failed to load sprite sheet for enemies");
    return manager;
  }

  // Calculate starting position to center the formation
  float formation_width = (ENEMY_FORMATION_COLS - 1) * ENEMY_SPACING_X + 15;
  float start_x = (graphics_context->screen_width - formation_width) / 2.0f;
  float start_y = 40.0f;  // Start near top of screen

  // Initialize enemies in a 6x4 formation
  int index = 0;
  for (int row = 0; row < ENEMY_FORMATION_ROWS; row++) {
    for (int col = 0; col < ENEMY_FORMATION_COLS; col++) {
      enemy_t* enemy = &manager.enemies[index];

      enemy->base_x = start_x + col * ENEMY_SPACING_X;
      enemy->base_y = start_y + row * ENEMY_SPACING_Y;
      enemy->oscillation_offset =
          (float)(rand() % 100) / 100.0f * 6.28f;  // Random phase
      enemy->type = rand() % 4;                    // Random enemy type (0-3)
      enemy->animation_frame = 0;
      enemy->animation_counter = 0;
      enemy->active = true;

      index++;
    }
  }

  manager.formation_time = 0.0f;

  LOG_INFO_FMT("Enemy manager initialized with %d enemies in formation",
               MAX_ENEMIES);

  return manager;
}

void update_enemies(enemy_manager_t* manager) {
  manager->formation_time += ENEMY_OSCILLATION_SPEED;

  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (manager->enemies[i].active) {
      enemy_t* enemy = &manager->enemies[i];

      // Update animation
      enemy->animation_counter++;
      if (enemy->animation_counter >= ENEMY_ANIMATION_SPEED) {
        enemy->animation_counter = 0;
        enemy->animation_frame =
            1 - enemy->animation_frame;  // Toggle between 0 and 1
      }
    }
  }
}

void render_enemies(const enemy_manager_t* manager,
                    const graphics_context_ptr graphics_context) {
  if (!manager->sprite_sheet.texture) {
    return;
  }

  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (manager->enemies[i].active) {
      const enemy_t* enemy = &manager->enemies[i];

      // Calculate oscillating X position
      float oscillation =
          sinf(manager->formation_time + enemy->oscillation_offset) *
          ENEMY_OSCILLATION_AMPLITUDE;
      float x = enemy->base_x + oscillation;
      float y = enemy->base_y;

      // Get the appropriate sprite for this enemy's type and animation frame
      int sprite_index =
          get_enemy_sprite_index(enemy->type, enemy->animation_frame);
      sprite_rect_t sprite = galaga_sprites[sprite_index];

      // Set up source rectangle (from sprite sheet)
      SDL_Rect src_rect = {sprite.x, sprite.y, sprite.width, sprite.height};

      // Set up destination rectangle (where to draw on screen)
      SDL_FRect dst_rect = {x, y, (float)sprite.width, (float)sprite.height};

      // Render the enemy sprite
      SDL_RenderCopyF(graphics_context->renderer, manager->sprite_sheet.texture,
                      &src_rect, &dst_rect);
    }
  }
}

enemy_t* get_enemy(enemy_manager_t* manager, int index) {
  if (index >= 0 && index < MAX_ENEMIES) {
    return &manager->enemies[index];
  }
  return NULL;
}

void get_enemy_position(const enemy_manager_t* manager, int index, float* x,
                        float* y) {
  if (index >= 0 && index < MAX_ENEMIES && manager->enemies[index].active) {
    const enemy_t* enemy = &manager->enemies[index];
    float oscillation =
        sinf(manager->formation_time + enemy->oscillation_offset) *
        ENEMY_OSCILLATION_AMPLITUDE;
    *x = enemy->base_x + oscillation;
    *y = enemy->base_y;
  }
}

void cleanup_enemy_manager(enemy_manager_t* manager) {
  if (manager->sprite_sheet.texture) {
    free_texture(&manager->sprite_sheet);
  }
}
