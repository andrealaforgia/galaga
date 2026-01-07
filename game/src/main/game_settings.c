#include "game_settings.h"

game_settings_t init_game_settings(bool show_fps, bool vsync, int display,
                                   int fps, int volume) {
  game_settings_t settings = {.show_fps = show_fps,
                              .vsync = vsync,
                              .display = display,
                              .fps = fps,
                              .volume = volume};
  return settings;
}
