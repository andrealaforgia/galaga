#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../assets/sprites/sprite_coords.h"
#include "bullet.h"
#include "command_line.h"
#include "enemy.h"
#include "explosion.h"
#include "frame.h"
#include "game.h"
#include "graphics.h"
#include "keyboard.h"
#include "logger.h"
#include "player_ship.h"

// Sound effect indices
#define SOUND_SHOOT 0
#define SOUND_EXPLOSION 1

// Simple AABB collision detection
static bool check_collision(float x1, float y1, float w1, float h1, float x2,
                            float y2, float w2, float h2) {
  return x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2;
}

static void run_game(const game_ptr game) {
  // Initialize player ship
  player_ship_t ship = init_player_ship(&game->graphics_context,
                                        "game/assets/sprites/Arcade - Galaga - "
                                        "Miscellaneous - General Sprites.png");

  if (!ship.sprite_sheet.texture) {
    LOG_ERROR("Failed to initialize player ship");
    return;
  }

  // Initialize bullet manager
  bullet_manager_t bullet_manager =
      init_bullet_manager(&game->graphics_context,
                          "game/assets/sprites/Arcade - Galaga - Miscellaneous "
                          "- General Sprites.png");

  if (!bullet_manager.sprite_sheet.texture) {
    LOG_ERROR("Failed to initialize bullet manager");
    cleanup_player_ship(&ship);
    return;
  }

  // Initialize enemy manager
  enemy_manager_t enemy_manager =
      init_enemy_manager(&game->graphics_context,
                         "game/assets/sprites/Arcade - Galaga - Miscellaneous "
                         "- General Sprites.png");

  if (!enemy_manager.sprite_sheet.texture) {
    LOG_ERROR("Failed to initialize enemy manager");
    cleanup_bullet_manager(&bullet_manager);
    cleanup_player_ship(&ship);
    return;
  }

  // Initialize explosion manager
  explosion_manager_t explosion_manager =
      init_explosion_manager(&game->graphics_context,
                             "game/assets/sprites/Arcade - Galaga - "
                             "Miscellaneous - General Sprites.png");

  if (!explosion_manager.sprite_sheet.texture) {
    LOG_ERROR("Failed to initialize explosion manager");
    cleanup_enemy_manager(&enemy_manager);
    cleanup_bullet_manager(&bullet_manager);
    cleanup_player_ship(&ship);
    return;
  }

  // Load sound effects
  if (!load_sound(&game->audio_context, SOUND_SHOOT,
                  "game/assets/sounds/split_effects", "sound_effect_01.mp3")) {
    LOG_ERROR("Failed to load shoot sound effect");
  }

  if (!load_sound(&game->audio_context, SOUND_EXPLOSION,
                  "game/assets/sounds/split_effects", "sound_effect_02.mp3")) {
    LOG_ERROR("Failed to load explosion sound effect");
  }

  LOG_INFO("Use LEFT/RIGHT arrow keys to move the ship, SPACE to fire.");

  bool quit = false;
  bool space_was_pressed = false;

  while (!quit) {
    // Handle events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          quit = true;
        }
      }
    }

    // Update player ship
    update_player_ship(&ship, &game->keyboard_state, &game->graphics_context);

    // Handle firing
    bool space_is_pressed = is_space_key_pressed(&game->keyboard_state);
    if (space_is_pressed && !space_was_pressed) {
      // Fire bullet from center of ship
      float bullet_x =
          get_player_ship_center_x(&ship) - 1.0f;  // Center the 2px bullet
      float bullet_y = get_player_ship_top_y(&ship);
      fire_bullet(&bullet_manager, bullet_x, bullet_y);

      // Play shoot sound
      play_sound(&game->audio_context, SOUND_SHOOT);
    }
    space_was_pressed = space_is_pressed;

    // Update bullets
    update_bullets(&bullet_manager);

    // Update enemies
    update_enemies(&enemy_manager);

    // Update explosions
    update_explosions(&explosion_manager);

    // Check collisions between bullets and enemies
    sprite_rect_t bullet_sprite = galaga_sprites[PLAYER_BULLET_SPRITE_INDEX];
    for (int i = 0; i < MAX_BULLETS; i++) {
      bullet_t* bullet = get_bullet(&bullet_manager, i);
      if (bullet && bullet->active) {
        for (int j = 0; j < MAX_ENEMIES; j++) {
          enemy_t* enemy = get_enemy(&enemy_manager, j);
          if (enemy && enemy->active) {
            float enemy_x, enemy_y;
            get_enemy_position(&enemy_manager, j, &enemy_x, &enemy_y);

            // Check collision (using 16x16 for enemy size)
            if (check_collision(bullet->x, bullet->y, bullet_sprite.width,
                                bullet_sprite.height, enemy_x, enemy_y, 16,
                                16)) {
              // Collision detected!
              bullet->active = false;
              enemy->active = false;

              // Create explosion at enemy center
              create_explosion(&explosion_manager,
                               enemy_x + 8.0f,   // Center of 16px wide enemy
                               enemy_y + 8.0f);  // Center of 16px high enemy

              // Play explosion sound
              play_sound(&game->audio_context, SOUND_EXPLOSION);

              break;  // Bullet can only hit one enemy
            }
          }
        }
      }
    }

    // Clear screen to black
    clear_frame(&game->graphics_context);

    // Render
    render_enemies(&enemy_manager, &game->graphics_context);
    render_explosions(&explosion_manager, &game->graphics_context);
    render_player_ship(&ship, &game->graphics_context);
    render_bullets(&bullet_manager, &game->graphics_context);

    // Present frame
    render_frame(&game->graphics_context);

    // Simple frame limiting (60 FPS)
    SDL_Delay(16);
  }

  // Cleanup
  cleanup_explosion_manager(&explosion_manager);
  cleanup_enemy_manager(&enemy_manager);
  cleanup_bullet_manager(&bullet_manager);
  cleanup_player_ship(&ship);
}

int main(int argc, char* argv[]) {
  srand(time(NULL));

  command_line_options_t command_line_options =
      parse_command_line_options(argc, argv);

  if (command_line_options.help) {
    print_help();
    return 0;
  }

  if (command_line_options.graphics_info) {
    print_graphics_info();
    return 0;
  }

  game_settings_t game_settings = init_game_settings(
      command_line_options.show_fps, command_line_options.vsync,
      command_line_options.display, command_line_options.fps,
      command_line_options.volume);

  // Log game configuration
  LOG_INFO("=== Galaga Configuration ===");
  LOG_INFO_FMT("Display: %d", game_settings.display);
  LOG_INFO_FMT("VSync: %s", game_settings.vsync ? "Enabled" : "Disabled");
  LOG_INFO_FMT("Target FPS: %d", game_settings.fps);
  LOG_INFO_FMT("Show FPS: %s", game_settings.show_fps ? "Yes" : "No");
  LOG_INFO_FMT("Audio Volume: %d/128", game_settings.volume);
  LOG_INFO("============================");

  game_t game = init_game(game_settings);

  run_game(&game);

  terminate_game(&game);

  return 0;
}
