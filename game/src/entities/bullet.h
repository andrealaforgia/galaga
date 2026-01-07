/**
 * @file bullet.h
 * @brief Player bullet entity
 *
 * Manages player bullets that are fired upward when space is pressed.
 */

#ifndef GAME_SRC_ENTITIES_BULLET_H_
#define GAME_SRC_ENTITIES_BULLET_H_

#include <stdbool.h>

#include "graphics.h"
#include "texture.h"

#define MAX_BULLETS 10
#define BULLET_SPEED 6  // Galaga bullet speed (pixels per frame at 60 FPS)

typedef struct {
  float x;
  float y;
  bool active;
} bullet_t;

typedef struct {
  bullet_t bullets[MAX_BULLETS];
  texture_t sprite_sheet;
} bullet_manager_t;

/**
 * Initialize the bullet manager
 */
bullet_manager_t init_bullet_manager(
    const graphics_context_ptr graphics_context, const char* sprite_sheet_path);

/**
 * Fire a bullet from the given position
 */
void fire_bullet(bullet_manager_t* manager, float x, float y);

/**
 * Update all active bullets
 */
void update_bullets(bullet_manager_t* manager);

/**
 * Render all active bullets
 */
void render_bullets(const bullet_manager_t* manager,
                    const graphics_context_ptr graphics_context);

/**
 * Get bullet at index (for collision detection)
 */
bullet_t* get_bullet(bullet_manager_t* manager, int index);

/**
 * Clean up bullet manager resources
 */
void cleanup_bullet_manager(bullet_manager_t* manager);

#endif  // GAME_SRC_ENTITIES_BULLET_H_
