/**
 * @file explosion.h
 * @brief Explosion animation system
 *
 * Manages explosion animations when enemies are destroyed.
 */

#ifndef GAME_SRC_ENTITIES_EXPLOSION_H_
#define GAME_SRC_ENTITIES_EXPLOSION_H_

#include <stdbool.h>

#include "graphics.h"
#include "texture.h"

#define MAX_EXPLOSIONS 10
#define EXPLOSION_FRAME_DURATION 4  // Frames per explosion sprite

typedef struct {
  float x;
  float y;
  int current_frame;  // 0-4
  int frame_counter;
  bool active;
} explosion_t;

typedef struct {
  explosion_t explosions[MAX_EXPLOSIONS];
  texture_t sprite_sheet;
} explosion_manager_t;

/**
 * Initialize the explosion manager
 */
explosion_manager_t init_explosion_manager(const graphics_context_ptr graphics_context,
                                           const char* sprite_sheet_path);

/**
 * Create an explosion at the given position
 */
void create_explosion(explosion_manager_t* manager, float x, float y);

/**
 * Update all active explosions
 */
void update_explosions(explosion_manager_t* manager);

/**
 * Render all active explosions
 */
void render_explosions(const explosion_manager_t* manager,
                      const graphics_context_ptr graphics_context);

/**
 * Clean up explosion manager resources
 */
void cleanup_explosion_manager(explosion_manager_t* manager);

#endif  // GAME_SRC_ENTITIES_EXPLOSION_H_
