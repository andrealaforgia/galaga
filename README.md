# Galaga

A faithful recreation of the classic 1981 Namco arcade game, built with C and SDL2. Command your fighter ship against waves of alien enemies in their distinctive formation attack patterns. Features authentic sprite graphics, smooth animations, collision detection, and the addictive gameplay that made Galaga an arcade legend.

## Setup

This project uses a git submodule for the game engine. The setup process will automatically initialize the submodule.

### Install dependencies
```
make install
```

This will initialize the git submodules and install SDL2 dependencies.

### Development tools (optional)

For linting and formatting:
```
make dev_install
```

This installs development tools (cpplint, clang-format).

## Build the game
```
make clean && make
```

### Show run options
```
./galaga --help
```

## Run the game
```
./galaga
```

### Run the game with custom options

Example: Running the game with FPS display and custom volume:
```
./galaga --show-fps --volume=128
```

### VSync (Vertical Synchronization)

VSync synchronizes the game's frame rendering with your display's refresh rate to eliminate screen tearing and provide smoother visuals.

**Default:** VSync is **disabled** by default for maximum performance and minimal input latency.

**Enable VSync:**
```
./galaga --vsync
```

**When to use VSync:**
- You notice screen tearing (horizontal lines across the screen during fast movement)
- You prefer smoother, more consistent frame pacing
- Your system easily maintains 60+ FPS

**When to disable VSync (default):**
- You want the absolute lowest input latency for responsive controls
- You have a variable refresh rate display (FreeSync/G-Sync/Adaptive Sync)
- You're experiencing stuttering or performance issues with VSync enabled
- You prefer higher framerates over perfect frame synchronization

**Technical details:**
- VSync caps the framerate at your display's refresh rate (typically 60 FPS)
- Without VSync, the game uses manual frame limiting to target 60 FPS
- VSync adds ~1-2 frames of input latency but eliminates tearing
- On high-refresh-rate displays (120Hz+), VSync will cap at the higher rate

**Example - VSync enabled:**
```
./galaga --vsync
```

### FPS Display

Display real-time frames-per-second statistics in the top-left corner during gameplay.

**Default:** FPS display is **disabled** by default.

**Enable FPS display:**
```
./galaga --show-fps
```

**Use cases:**
- Performance monitoring and debugging
- Verifying VSync is working correctly (should show 60 FPS or your display's refresh rate)
- Diagnosing performance issues or frame drops
- Comparing performance between different settings

**Example - FPS display with VSync:**
```
./galaga --show-fps --vsync
```

### Target Frame Rate

Control the game's target frame rate (FPS). The game will attempt to maintain this frame rate through frame limiting.

**Default:** 60 FPS

**Set custom frame rate:**
```
./galaga --fps=120   # High refresh rate displays
./galaga --fps=30    # Lower performance systems
./galaga --fps=144   # Gaming monitors
```

**Valid range:** 1-300 FPS

**Notes:**
- When VSync is enabled, the actual frame rate will be capped at your display's refresh rate
- Higher FPS values provide smoother animation but require more CPU/GPU power
- Lower FPS values reduce resource usage but may feel less responsive
- Most displays are 60Hz, so 60 FPS is optimal for most users

**Example - 120 FPS for high refresh rate display:**
```
./galaga --fps=120
```

### Audio Volume

Control the game's audio volume at startup.

**Default:** Volume is set to **32** (out of 128) for comfortable listening.

**Set custom volume:**
```
./galaga --volume=64   # Half of maximum
./galaga --volume=0    # Mute all sound
./galaga --volume=128  # Maximum volume
```

**Valid range:** 0-128 (0 = silent, 128 = maximum)

### Display Selection

Select which display/monitor to use for the game.

**Default:** Display 0 (primary monitor)

**Set custom display:**
```
./galaga --display=1   # Use second monitor
./galaga --display=2   # Use third monitor
```

**List available displays:**
```
./galaga --graphics-info
```

## Game Controls

### Gameplay
- **Left Arrow** - Move ship left
- **Right Arrow** - Move ship right
- **Space** - Fire bullets

### System Controls
- **ESC** - Quit game

## Technical Details

### Graphics
- **Resolution:** 288×224 pixels (original Galaga arcade resolution)
- **Scaling:** Window automatically scales to 90% of screen height while maintaining aspect ratio
- **Rendering:** SDL2 with logical rendering for pixel-perfect scaling
- **Sprites:** Extracted from original Galaga arcade sprite sheet
- **Transparency:** Black color key for clean sprite rendering

### Audio
- **System:** SDL2_mixer for sound playback
- **Channels:** 256 concurrent audio channels supported
- **Volume:** Adjustable from 0-128

### Gameplay
- **Player Ship:** 15×15 pixels, 3 pixels/frame movement speed
- **Enemies:** 16×16 pixels, 4 different types with 2 animation frames each
- **Formation:** 6×4 grid (24 enemies) with oscillating movement
- **Bullets:** 2×7 pixels, 6 pixels/frame speed, max 10 active
- **Explosions:** 31×31 pixels, 5-frame animation
- **Collision Detection:** AABB (Axis-Aligned Bounding Box) algorithm

## Project Structure

```
galaga/
├── engine/              # Game engine (git submodule)
│   └── core/
│       ├── graphics/    # Graphics and rendering
│       ├── input/       # Keyboard input handling
│       ├── audio/       # Sound system
│       └── ...
├── game/
│   ├── assets/
│   │   ├── sprites/     # Sprite sheets and coordinates
│   │   └── sounds/      # Sound effects
│   └── src/
│       ├── entities/    # Game entities (player, enemies, bullets, explosions)
│       ├── rendering/   # Graphics utilities
│       └── main/        # Game initialization and main loop
└── tools/               # Sprite extraction utilities
```

## Development Tools

The project includes sprite extraction utilities in the `tools/` directory:

- **sprite_extractor:** Extracts sprite coordinates from sprite sheets
- **sprite_viewer:** Visual sprite sheet browser
- **debug_grid:** Debug utility for sprite sheet analysis

Build tools:
```
cd tools && make
```

## Acknowledgments

- Original Galaga by Namco (1981)
- Sprite assets from arcade version
- Built with SDL2 library

---

**Note:** This is a fan remake for educational purposes. Galaga is a trademark of Namco.
