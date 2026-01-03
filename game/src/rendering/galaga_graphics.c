#include "galaga_graphics.h"

#include <SDL.h>
#include <stdlib.h>

#include "geometry.h"
#include "logger.h"

graphics_context_t init_graphics_context_with_logical_size(
    int display, int window_width, int window_height,
    int logical_width, int logical_height, bool vsync) {
  graphics_context_t graphics_context = {0};

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    LOG_SDL_ERROR("SDL_Init");
    abort();
  }

  // Set SDL hints for optimal performance
  if (!SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal")) {
    LOG_WARN("Failed to set Metal renderer hint");
  }

  // Use linear filtering for smooth scaling
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    LOG_WARN("Failed to set render scale quality hint");
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1")) {
    LOG_WARN("Failed to set render batching hint");
  } else {
    LOG_INFO("Render batching enabled");
  }

  if (!SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "1")) {
    LOG_WARN("Failed to set framebuffer acceleration hint");
  }

  if (!SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0")) {
    LOG_WARN("Failed to set minimize on focus loss hint");
  }

  SDL_ShowCursor(SDL_DISABLE);

  // Validate display index
  int num_displays = SDL_GetNumVideoDisplays();
  if (num_displays < 1) {
    LOG_SDL_ERROR("SDL_GetNumVideoDisplays");
    abort();
  }

  if (display < 0 || display >= num_displays) {
    LOG_WARN_FMT("Invalid display index %d (valid range: 0-%d)", display,
                 num_displays - 1);
    LOG_INFO("Falling back to display 0");
    display = 0;
  }

  // Set logical dimensions (game coordinates)
  graphics_context.screen_width = logical_width;
  graphics_context.screen_height = logical_height;
  graphics_context.screen_center = point(logical_width / 2, logical_height / 2);

  // Create window with specified physical size, centered
  Uint32 window_flags = SDL_WINDOW_ALLOW_HIGHDPI;

  graphics_context.window = SDL_CreateWindow(
      "Galaga", SDL_WINDOWPOS_CENTERED_DISPLAY(display),
      SDL_WINDOWPOS_CENTERED_DISPLAY(display), window_width, window_height,
      window_flags);

  if (!graphics_context.window) {
    LOG_SDL_ERROR("SDL_CreateWindow");
    abort();
  }

  int actual_w, actual_h;
  SDL_GetWindowSize(graphics_context.window, &actual_w, &actual_h);
  LOG_INFO_FMT("Window Size: w=%d h=%d", actual_w, actual_h);

  // Create renderer
  Uint32 renderer_flags = SDL_RENDERER_ACCELERATED;
  if (vsync) {
    renderer_flags |= SDL_RENDERER_PRESENTVSYNC;
  }

  graphics_context.renderer =
      SDL_CreateRenderer(graphics_context.window, -1, renderer_flags);

  if (!graphics_context.renderer) {
    LOG_WARN("Hardware-accelerated renderer failed, trying software renderer");
    LOG_SDL_ERROR("SDL_CreateRenderer (hardware)");

    renderer_flags = SDL_RENDERER_SOFTWARE;
    if (vsync) {
      renderer_flags |= SDL_RENDERER_PRESENTVSYNC;
    }

    graphics_context.renderer =
        SDL_CreateRenderer(graphics_context.window, -1, renderer_flags);

    if (!graphics_context.renderer) {
      LOG_SDL_ERROR("SDL_CreateRenderer (software fallback)");
      LOG_ERROR("Failed to create any renderer - aborting");
      abort();
    } else {
      LOG_INFO("Using software renderer (performance may be reduced)");
    }
  }

  // Log renderer info
  SDL_RendererInfo renderer_info;
  if (SDL_GetRendererInfo(graphics_context.renderer, &renderer_info) == 0) {
    LOG_INFO_FMT("Renderer: %s", renderer_info.name);

    if (renderer_info.flags & SDL_RENDERER_ACCELERATED) {
      LOG_INFO("Renderer: Hardware-accelerated");
    } else if (renderer_info.flags & SDL_RENDERER_SOFTWARE) {
      LOG_INFO("Renderer: Software");
    }

    if (renderer_info.flags & SDL_RENDERER_PRESENTVSYNC) {
      LOG_INFO("VSync: Enabled");
    } else {
      LOG_INFO("VSync: Disabled (using manual frame limiting)");
    }
  }

  // Set logical size for automatic scaling
  if (SDL_RenderSetLogicalSize(graphics_context.renderer, logical_width,
                                logical_height) != 0) {
    LOG_SDL_ERROR("SDL_RenderSetLogicalSize");
    abort();
  }

  LOG_INFO_FMT("Logical Size: w=%d h=%d", logical_width, logical_height);

  return graphics_context;
}
