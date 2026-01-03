# Galaga Clone

A classic arcade game remake of Galaga built from scratch in C using SDL2.

## Features

- **Authentic Galaga Gameplay**: Classic shoot 'em up action with a modern implementation
- **Player Ship**: Smooth horizontal movement with responsive controls
- **Enemy Formation**: 6×4 grid of enemies with 4 different types
- **Animated Sprites**: Enemy sprites cycle through 2 animation frames
- **Dynamic Movement**: Enemies oscillate left and right in formation
- **Combat System**:
  - Shoot bullets with rapid fire capability
  - Collision detection between bullets and enemies
  - Explosion animations with 5 frames
- **Sound Effects**:
  - Shooting sound when firing bullets
  - Explosion sound when destroying enemies
- **Graphics**:
  - Original Galaga sprite sheet
  - Black transparency for clean sprite rendering
  - 288×224 native resolution (classic arcade dimensions)
  - Automatic scaling to 90% of screen height while maintaining aspect ratio

## Prerequisites

### macOS
```bash
brew install sdl2 sdl2_image sdl2_mixer
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
```

## Building

1. Clone the repository with submodules:
```bash
git clone --recursive <repository-url>
cd galaga
```

2. Build the game:
```bash
make
```

3. Run the game:
```bash
./galaga
```

## Controls

- **LEFT/RIGHT Arrow Keys**: Move the ship horizontally
- **SPACE**: Fire bullets
- **ESC**: Quit the game

## Command Line Options

```bash
./galaga [OPTIONS]

Options:
  --help              Show help message
  --display=N         Use display N (default: 0)
  --vsync             Enable vertical sync
  --fps=N             Set target FPS (default: 60)
  --volume=N          Set audio volume 0-128 (default: 32)
  --show-fps          Display FPS counter
  --graphics-info     Show graphics capabilities
```

### Examples

Run with maximum volume:
```bash
./galaga --volume=128
```

Run with VSync enabled and FPS counter:
```bash
./galaga --vsync --show-fps
```

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

## Technical Details

### Graphics
- **Resolution**: 288×224 pixels (original Galaga arcade resolution)
- **Rendering**: SDL2 with logical rendering for automatic scaling
- **Sprites**: Extracted from original Galaga sprite sheet
- **Transparency**: Black color key for clean sprite rendering
- **Frame Rate**: 60 FPS target with configurable VSync

### Audio
- **System**: SDL2_mixer for sound playback
- **Format**: MP3 sound effects
- **Channels**: 256 concurrent audio channels supported
- **Volume**: Adjustable from 0-128

### Game Logic
- **Collision Detection**: AABB (Axis-Aligned Bounding Box) algorithm
- **Movement**: Sub-pixel precision for smooth animation
- **Enemy AI**: Oscillating formation movement with individual phase offsets
- **Animation**: Frame-based sprite animation system

## Sprite Information

### Player Ship
- Size: 15×15 pixels
- Position: Sprite 6 at (109, 1)
- Speed: 3 pixels per frame

### Enemies
- Size: 16×16 pixels
- Types: 4 different enemy types
- Animation: 2 frames per type
- Movement: Sine wave oscillation (±10 pixels)

### Bullets
- Size: 2×7 pixels
- Speed: 6 pixels per frame
- Max Active: 10 bullets on screen

### Explosions
- Size: 31×31 pixels
- Animation: 5 frames at 4 ticks per frame

## Development Tools

The project includes sprite extraction utilities in the `tools/` directory:

- **sprite_extractor**: Extracts sprite coordinates from sprite sheets
- **sprite_viewer**: Visual sprite sheet browser
- **debug_grid**: Debug utility for sprite sheet analysis

Build tools:
```bash
cd tools
make
```

## License

This is an educational project recreating the classic Galaga arcade game.

## Acknowledgments

- Original Galaga by Namco (1981)
- Sprite assets from arcade version
- Built with SDL2 library
- Created with assistance from Claude Code

## Credits

🤖 Generated with [Claude Code](https://claude.com/claude-code)

---

**Note**: This is a fan remake for educational purposes. Galaga is a trademark of Namco.
