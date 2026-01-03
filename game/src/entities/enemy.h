/**
 * @file enemy.h
 * @brief Enemy entity system
 *
 * Manages enemies in a formation with animation and movement.
 */

#ifndef GAME_SRC_ENTITIES_ENEMY_H_
#define GAME_SRC_ENTITIES_ENEMY_H_

#include <stdbool.h>

#include "graphics.h"
#include "texture.h"

#define ENEMY_FORMATION_COLS 6
#define ENEMY_FORMATION_ROWS 4
#define MAX_ENEMIES (ENEMY_FORMATION_COLS * ENEMY_FORMATION_ROWS)
#define ENEMY_SPACING_X 30  // Increased to prevent overlap (16px sprite + 14px margin)
#define ENEMY_SPACING_Y 20
#define ENEMY_OSCILLATION_SPEED 0.05f
#define ENEMY_OSCILLATION_AMPLITUDE 10.0f  // Reduced to prevent overlap
#define ENEMY_ANIMATION_SPEED 15  // Frames between animation changes

typedef struct {
  float base_x;  // Base position in formation
  float base_y;
  float oscillation_offset;  // Time offset for oscillation
  int type;  // 0-3 (enemy type)
  int animation_frame;  // 0 or 1
  int animation_counter;
  bool active;
} enemy_t;

typedef struct {
  enemy_t enemies[MAX_ENEMIES];
  texture_t sprite_sheet;
  float formation_time;  // Global time for movement
} enemy_manager_t;

/**
 * Initialize the enemy manager with a 6x4 formation
 */
enemy_manager_t init_enemy_manager(const graphics_context_ptr graphics_context,
                                   const char* sprite_sheet_path);

/**
 * Update all active enemies (movement and animation)
 */
void update_enemies(enemy_manager_t* manager);

/**
 * Render all active enemies
 */
void render_enemies(const enemy_manager_t* manager,
                   const graphics_context_ptr graphics_context);

/**
 * Get enemy at index (for collision detection)
 */
enemy_t* get_enemy(enemy_manager_t* manager, int index);

/**
 * Get current position of enemy (accounting for oscillation)
 */
void get_enemy_position(const enemy_manager_t* manager, int index, float* x, float* y);

/**
 * Clean up enemy manager resources
 */
void cleanup_enemy_manager(enemy_manager_t* manager);

#endif  // GAME_SRC_ENTITIES_ENEMY_H_
