/**
 * @file player_ship.h
 * @brief Player ship entity
 *
 * Defines the player ship entity with position, movement, and rendering.
 */

#ifndef GAME_SRC_ENTITIES_PLAYER_SHIP_H_
#define GAME_SRC_ENTITIES_PLAYER_SHIP_H_

#include "graphics.h"
#include "keyboard.h"
#include "texture.h"

// Player ship sprite is sprite 6: 16x16 pixels at (109, 1)
// 6th sprite (0-indexed) on the first row of the left grid
#define PLAYER_SHIP_SPRITE_INDEX 6
#define PLAYER_SHIP_SPEED 3

typedef struct {
  float x;
  float y;
  texture_t sprite_sheet;
} player_ship_t;

/**
 * Initialize the player ship
 */
player_ship_t init_player_ship(const graphics_context_ptr graphics_context,
                               const char* sprite_sheet_path);

/**
 * Update player ship (handle input and movement)
 */
void update_player_ship(player_ship_t* ship,
                       const keyboard_state_ptr keyboard_state,
                       const graphics_context_ptr graphics_context);

/**
 * Render the player ship
 */
void render_player_ship(const player_ship_t* ship,
                       const graphics_context_ptr graphics_context);

/**
 * Get the center X position of the ship (for bullet firing)
 */
float get_player_ship_center_x(const player_ship_t* ship);

/**
 * Get the top Y position of the ship (for bullet firing)
 */
float get_player_ship_top_y(const player_ship_t* ship);

/**
 * Clean up player ship resources
 */
void cleanup_player_ship(player_ship_t* ship);

#endif  // GAME_SRC_ENTITIES_PLAYER_SHIP_H_
