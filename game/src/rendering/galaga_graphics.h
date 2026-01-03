/**
 * @file galaga_graphics.h
 * @brief Galaga-specific graphics initialization
 *
 * Provides custom graphics initialization for Galaga with fixed
 * logical resolution and scaled window size.
 */

#ifndef GAME_SRC_RENDERING_GALAGA_GRAPHICS_H_
#define GAME_SRC_RENDERING_GALAGA_GRAPHICS_H_

#include <stdbool.h>

#include "graphics.h"

/**
 * Initialize graphics context with custom window size and logical resolution
 *
 * @param display Display index to use
 * @param window_width Physical window width in pixels
 * @param window_height Physical window height in pixels
 * @param logical_width Logical rendering width (game coordinates)
 * @param logical_height Logical rendering height (game coordinates)
 * @param vsync Enable VSync
 * @return Initialized graphics context
 */
graphics_context_t init_graphics_context_with_logical_size(
    int display, int window_width, int window_height,
    int logical_width, int logical_height, bool vsync);

#endif  // GAME_SRC_RENDERING_GALAGA_GRAPHICS_H_
