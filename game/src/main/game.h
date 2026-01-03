/**
 * @file game.h
 * @brief Main game state and lifecycle management
 *
 * Defines the core game structure containing settings and all major
 * subsystems like graphics, keyboard, and audio. Manages game
 * initialization, termination, and reset operations.
 */

#ifndef GAME_SRC_MAIN_GAME_H_
#define GAME_SRC_MAIN_GAME_H_

#include "audio.h"
#include "game_settings.h"
#include "graphics.h"
#include "keyboard.h"

#define COPYRIGHT_TEXT "2026 GALAGA REMAKE"

typedef struct {
  game_settings_t settings;
  graphics_context_t graphics_context;
  keyboard_state_t keyboard_state;
  audio_context_t audio_context;
} game_t, *game_ptr;

game_t init_game(game_settings_t game_settings);
void terminate_game(const game_ptr game);

#endif  // GAME_SRC_MAIN_GAME_H_
