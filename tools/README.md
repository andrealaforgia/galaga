# Galaga Tools

Utility programs for working with Galaga game assets.

## Sprite Extractor

A utility to extract sprite coordinates from sprite sheet images.

### Building

```bash
cd tools
make
```

### Usage

```bash
./sprite_extractor <sprite_sheet.png>
```

### Example

```bash
./sprite_extractor "../game/assets/sprites/Arcade - Galaga - Miscellaneous - General Sprites.png"
```

### Output

The utility scans the sprite sheet image and identifies rectangular regions containing sprites (non-black pixels surrounded by black borders). It outputs:

1. A table showing sprite index, position (x, y), and dimensions (width, height)
2. A C array declaration that can be copied into your code

### How It Works

1. Loads the PNG image using SDL2_image
2. Scans pixel by pixel to find non-black regions
3. Uses flood-fill algorithm to identify sprite boundaries
4. Extracts bounding box coordinates for each sprite
5. Filters out very small sprites (likely noise)
6. Sorts sprites by position (top to bottom, left to right)

### Notes

- Black pixels are defined as RGB values < 10 or alpha < 10
- Minimum sprite size is 2x2 pixels to filter out noise
- The first sprite (index 0) is typically the entire image and should be ignored
- Sprites are sorted by Y coordinate first, then X coordinate
