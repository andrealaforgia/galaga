/**
 * @file sprite_viewer.h
 * @brief Sprite viewer for inspecting sprite sheet
 *
 * Provides a simple viewer to display sprites from the sprite sheet
 * one at a time with their coordinates and dimensions.
 */

#ifndef GAME_SRC_RENDERING_SPRITE_VIEWER_H_
#define GAME_SRC_RENDERING_SPRITE_VIEWER_H_

#include "graphics.h"
#include "keyboard.h"
#include "texture.h"

typedef struct {
  texture_t sprite_sheet;
  int current_sprite_index;
  int total_sprites;
} sprite_viewer_t;

/**
 * Initialize the sprite viewer
 */
sprite_viewer_t init_sprite_viewer(const graphics_context_ptr graphics_context,
                                   const char* sprite_sheet_path);

/**
 * Update the sprite viewer (handle input)
 */
void update_sprite_viewer(sprite_viewer_t* viewer,
                         const keyboard_state_ptr keyboard_state);

/**
 * Render the current sprite with information
 */
void render_sprite_viewer(const sprite_viewer_t* viewer,
                         const graphics_context_ptr graphics_context);

/**
 * Clean up sprite viewer resources
 */
void cleanup_sprite_viewer(sprite_viewer_t* viewer);

#endif  // GAME_SRC_RENDERING_SPRITE_VIEWER_H_
