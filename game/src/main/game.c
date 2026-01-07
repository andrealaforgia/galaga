#include "game.h"

#include <SDL.h>

#include "galaga_graphics.h"
#include "game_constants.h"
#include "logger.h"

game_t init_game(game_settings_t game_settings) {
  game_t game = {0};

  game.settings = game_settings;

  // Get display bounds to calculate scaled window size
  SDL_Rect display_bounds;
  if (SDL_GetDisplayBounds(game_settings.display, &display_bounds) != 0) {
    LOG_SDL_ERROR("SDL_GetDisplayBounds");
    display_bounds.h = 1080;  // Fallback to common height
  }

  // Calculate window dimensions:
  // Height = 90% of screen height
  // Width maintains aspect ratio (288:224)
  int window_height = (int)(display_bounds.h * WINDOW_SCALE_PERCENTAGE);
  int window_width = (int)(window_height * ((double)GAME_WIDTH / GAME_HEIGHT));

  LOG_INFO_FMT("Game resolution: %dx%d", GAME_WIDTH, GAME_HEIGHT);
  LOG_INFO_FMT("Window size: %dx%d (%.0f%% of screen height)", window_width,
               window_height, WINDOW_SCALE_PERCENTAGE * 100);

  // Initialize graphics with scaled window
  game.graphics_context = init_graphics_context_with_logical_size(
      game_settings.display, window_width, window_height, GAME_WIDTH,
      GAME_HEIGHT, game_settings.vsync);

  // Initialize keyboard
  game.keyboard_state = init_keyboard_state();

  // Initialize audio (max 10 sounds for now)
  game.audio_context = init_audio_context(10, game_settings.volume);

  return game;
}

void terminate_game(const game_ptr game) {
  terminate_audio_context(&game->audio_context);
  terminate_graphics_context(&game->graphics_context);
}
