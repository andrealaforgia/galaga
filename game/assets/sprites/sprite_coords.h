/**
 * @file sprite_coords.h
 * @brief Sprite coordinates extracted from Galaga sprite sheet
 *
 * Auto-generated sprite coordinates for the Galaga sprite sheet.
 * Each sprite is defined by its x, y position and width, height.
 * Extracted using grid-based detection (grey grid lines at 64,64,64).
 *
 * Source: "Arcade - Galaga - Miscellaneous - General Sprites.png"
 * Sprite sheet dimensions: 458x216
 * Total sprites found: 202
 *
 * Player ship is sprite 6 at (109, 1) - 15x15 pixels
 * Player bullet at (313, 122) - 2x7 pixels
 *
 * Enemy sprites (all 16x16 pixels):
 * Enemy type 0: frames at indices 203, 204
 * Enemy type 1: frames at indices 205, 206
 * Enemy type 2: frames at indices 207, 208
 * Enemy type 3: frames at indices 209, 210
 *
 * Explosion sprites (all 31x31 pixels):
 * Frames at indices 211-215
 */

#ifndef GAME_ASSETS_SPRITES_SPRITE_COORDS_H_
#define GAME_ASSETS_SPRITES_SPRITE_COORDS_H_

typedef struct {
  int x;
  int y;
  int width;
  int height;
} sprite_rect_t;

#define SPRITE_SHEET_WIDTH 458
#define SPRITE_SHEET_HEIGHT 216
#define SPRITE_COUNT 216

// Sprite indices
#define PLAYER_BULLET_SPRITE_INDEX 202

// Enemy sprite indices (type, frame)
#define ENEMY_TYPE0_FRAME0 203
#define ENEMY_TYPE0_FRAME1 204
#define ENEMY_TYPE1_FRAME0 205
#define ENEMY_TYPE1_FRAME1 206
#define ENEMY_TYPE2_FRAME0 207
#define ENEMY_TYPE2_FRAME1 208
#define ENEMY_TYPE3_FRAME0 209
#define ENEMY_TYPE3_FRAME1 210

// Explosion sprite indices
#define EXPLOSION_FRAME0 211
#define EXPLOSION_FRAME1 212
#define EXPLOSION_FRAME2 213
#define EXPLOSION_FRAME3 214
#define EXPLOSION_FRAME4 215

static const sprite_rect_t galaga_sprites[SPRITE_COUNT] = {
    {1, 1, 16, 16},      // Sprite 0
    {19, 1, 16, 16},     // Sprite 1
    {37, 1, 16, 16},     // Sprite 2
    {55, 1, 16, 16},     // Sprite 3
    {73, 1, 16, 16},     // Sprite 4
    {91, 1, 16, 16},     // Sprite 5
    {109, 1, 15, 15},    // Sprite 6 - PLAYER SHIP
    {145, 1, 32, 32},    // Sprite 7
    {179, 1, 32, 32},    // Sprite 8
    {213, 1, 32, 32},    // Sprite 9
    {247, 1, 32, 32},    // Sprite 10
    {289, 1, 32, 32},    // Sprite 11
    {323, 1, 32, 32},    // Sprite 12
    {357, 1, 32, 32},    // Sprite 13
    {391, 1, 32, 32},    // Sprite 14
    {425, 1, 32, 32},    // Sprite 15
    {1, 19, 16, 16},     // Sprite 16
    {19, 19, 16, 16},    // Sprite 17
    {37, 19, 16, 16},    // Sprite 18
    {55, 19, 16, 16},    // Sprite 19
    {73, 19, 16, 16},    // Sprite 20
    {91, 19, 16, 16},    // Sprite 21
    {109, 19, 16, 16},   // Sprite 22
    {289, 36, 48, 80},   // Sprite 23
    {339, 36, 48, 80},   // Sprite 24
    {389, 36, 48, 80},   // Sprite 25
    {1, 37, 16, 16},     // Sprite 26
    {19, 37, 16, 16},    // Sprite 27
    {37, 37, 16, 16},    // Sprite 28
    {55, 37, 16, 16},    // Sprite 29
    {73, 37, 16, 16},    // Sprite 30
    {91, 37, 16, 16},    // Sprite 31
    {109, 37, 16, 16},   // Sprite 32
    {127, 37, 16, 16},   // Sprite 33
    {145, 37, 16, 16},   // Sprite 34
    {163, 37, 16, 16},   // Sprite 35
    {181, 37, 16, 16},   // Sprite 36
    {199, 37, 16, 16},   // Sprite 37
    {217, 37, 16, 16},   // Sprite 38
    {235, 37, 16, 16},   // Sprite 39
    {253, 37, 16, 16},   // Sprite 40
    {271, 37, 16, 16},   // Sprite 41
    {1, 55, 16, 16},     // Sprite 42
    {19, 55, 16, 16},    // Sprite 43
    {37, 55, 16, 16},    // Sprite 44
    {55, 55, 16, 16},    // Sprite 45
    {73, 55, 16, 16},    // Sprite 46
    {91, 55, 16, 16},    // Sprite 47
    {109, 55, 16, 16},   // Sprite 48
    {127, 55, 16, 16},   // Sprite 49
    {145, 55, 16, 16},   // Sprite 50
    {163, 55, 16, 16},   // Sprite 51
    {181, 55, 16, 16},   // Sprite 52
    {199, 55, 16, 16},   // Sprite 53
    {217, 55, 16, 16},   // Sprite 54
    {235, 55, 16, 16},   // Sprite 55
    {253, 55, 16, 16},   // Sprite 56
    {271, 55, 16, 16},   // Sprite 57
    {1, 73, 16, 16},     // Sprite 58
    {19, 73, 16, 16},    // Sprite 59
    {37, 73, 16, 16},    // Sprite 60
    {55, 73, 16, 16},    // Sprite 61
    {73, 73, 16, 16},    // Sprite 62
    {91, 73, 16, 16},    // Sprite 63
    {109, 73, 16, 16},   // Sprite 64
    {127, 73, 16, 16},   // Sprite 65
    {145, 73, 16, 16},   // Sprite 66
    {163, 73, 16, 16},   // Sprite 67
    {181, 73, 16, 16},   // Sprite 68
    {199, 73, 16, 16},   // Sprite 69
    {217, 73, 16, 16},   // Sprite 70
    {235, 73, 16, 16},   // Sprite 71
    {253, 73, 16, 16},   // Sprite 72
    {271, 73, 16, 16},   // Sprite 73
    {1, 91, 16, 16},     // Sprite 74
    {19, 91, 16, 16},    // Sprite 75
    {37, 91, 16, 16},    // Sprite 76
    {55, 91, 16, 16},    // Sprite 77
    {73, 91, 16, 16},    // Sprite 78
    {91, 91, 16, 16},    // Sprite 79
    {109, 91, 16, 16},   // Sprite 80
    {127, 91, 16, 16},   // Sprite 81
    {145, 91, 16, 16},   // Sprite 82
    {163, 91, 16, 16},   // Sprite 83
    {181, 91, 16, 16},   // Sprite 84
    {199, 91, 16, 16},   // Sprite 85
    {217, 91, 16, 16},   // Sprite 86
    {235, 91, 16, 16},   // Sprite 87
    {253, 91, 16, 16},   // Sprite 88
    {1, 109, 16, 16},    // Sprite 89
    {19, 109, 16, 16},   // Sprite 90
    {37, 109, 16, 16},   // Sprite 91
    {55, 109, 16, 16},   // Sprite 92
    {73, 109, 16, 16},   // Sprite 93
    {91, 109, 16, 16},   // Sprite 94
    {109, 109, 16, 16},  // Sprite 95
    {127, 109, 16, 16},  // Sprite 96
    {145, 109, 16, 16},  // Sprite 97
    {163, 109, 16, 16},  // Sprite 98
    {181, 109, 16, 16},  // Sprite 99
    {199, 109, 16, 16},  // Sprite 100
    {217, 109, 16, 16},  // Sprite 101
    {235, 109, 16, 16},  // Sprite 102
    {253, 109, 16, 16},  // Sprite 103
    {1, 127, 16, 16},    // Sprite 104
    {19, 127, 16, 16},   // Sprite 105
    {37, 127, 16, 16},   // Sprite 106
    {55, 127, 16, 16},   // Sprite 107
    {73, 127, 16, 16},   // Sprite 108
    {91, 127, 16, 16},   // Sprite 109
    {109, 127, 16, 16},  // Sprite 110
    {127, 127, 16, 16},  // Sprite 111
    {145, 127, 16, 16},  // Sprite 112
    {163, 127, 16, 16},  // Sprite 113
    {181, 127, 16, 16},  // Sprite 114
    {199, 127, 16, 16},  // Sprite 115
    {217, 127, 16, 16},  // Sprite 116
    {235, 127, 16, 16},  // Sprite 117
    {253, 127, 16, 16},  // Sprite 118
    {288, 118, 16, 16},  // Sprite 119
    {306, 118, 16, 16},  // Sprite 120
    {324, 118, 16, 16},  // Sprite 121
    {342, 118, 16, 16},  // Sprite 122
    {360, 118, 16, 16},  // Sprite 123
    {378, 118, 16, 16},  // Sprite 124
    {396, 118, 16, 16},  // Sprite 125
    {414, 118, 16, 16},  // Sprite 126
    {432, 118, 16, 16},  // Sprite 127
    {288, 136, 16, 16},  // Sprite 128
    {306, 136, 16, 16},  // Sprite 129
    {324, 136, 16, 16},  // Sprite 130
    {342, 136, 16, 16},  // Sprite 131
    {360, 136, 16, 16},  // Sprite 132
    {378, 136, 16, 16},  // Sprite 133
    {396, 136, 16, 16},  // Sprite 134
    {414, 136, 16, 16},  // Sprite 135
    {432, 136, 16, 16},  // Sprite 136
    {1, 145, 16, 16},    // Sprite 137
    {19, 145, 16, 16},   // Sprite 138
    {37, 145, 16, 16},   // Sprite 139
    {55, 145, 16, 16},   // Sprite 140
    {73, 145, 16, 16},   // Sprite 141
    {91, 145, 16, 16},   // Sprite 142
    {109, 145, 16, 16},  // Sprite 143
    {127, 145, 16, 16},  // Sprite 144
    {145, 145, 16, 16},  // Sprite 145
    {163, 145, 16, 16},  // Sprite 146
    {181, 145, 16, 16},  // Sprite 147
    {199, 145, 16, 16},  // Sprite 148
    {217, 145, 16, 16},  // Sprite 149
    {235, 145, 16, 16},  // Sprite 150
    {253, 145, 16, 16},  // Sprite 151
    {288, 154, 16, 16},  // Sprite 152
    {306, 154, 16, 16},  // Sprite 153
    {324, 154, 16, 16},  // Sprite 154
    {1, 163, 16, 16},    // Sprite 155
    {19, 163, 16, 16},   // Sprite 156
    {37, 163, 16, 16},   // Sprite 157
    {55, 163, 16, 16},   // Sprite 158
    {73, 163, 16, 16},   // Sprite 159
    {91, 163, 16, 16},   // Sprite 160
    {109, 163, 16, 16},  // Sprite 161
    {288, 172, 32, 16},  // Sprite 162
    {438, 172, 16, 16},  // Sprite 163
    {1, 181, 16, 16},    // Sprite 164
    {19, 181, 16, 16},   // Sprite 165
    {37, 181, 16, 16},   // Sprite 166
    {55, 181, 16, 16},   // Sprite 167
    {73, 181, 16, 16},   // Sprite 168
    {91, 181, 16, 16},   // Sprite 169
    {109, 181, 16, 16},  // Sprite 170
    {145, 181, 16, 16},  // Sprite 171
    {163, 181, 16, 16},  // Sprite 172
    {181, 181, 16, 16},  // Sprite 173
    {199, 181, 16, 16},  // Sprite 174
    {217, 181, 16, 16},  // Sprite 175
    {235, 181, 16, 16},  // Sprite 176
    {1, 199, 16, 16},    // Sprite 177
    {19, 199, 16, 16},   // Sprite 178
    {37, 199, 16, 16},   // Sprite 179
    {55, 199, 16, 16},   // Sprite 180
    {73, 199, 16, 16},   // Sprite 181
    {91, 199, 16, 16},   // Sprite 182
    {109, 199, 16, 16},  // Sprite 183
    {145, 199, 16, 16},  // Sprite 184
    {163, 199, 16, 16},  // Sprite 185
    {181, 199, 16, 16},  // Sprite 186
    {199, 199, 16, 16},  // Sprite 187
    {217, 199, 16, 16},  // Sprite 188
    {235, 199, 16, 16},  // Sprite 189
    {307, 207, 4, 6},    // Sprite 190
    {372, 207, 4, 6},    // Sprite 191
    {406, 207, 3, 6},    // Sprite 192
    {145, 208, 12, 6},   // Sprite 193
    {159, 208, 8, 6},    // Sprite 194
    {169, 208, 10, 6},   // Sprite 195
    {181, 208, 12, 6},   // Sprite 196
    {195, 208, 10, 6},   // Sprite 197
    {207, 208, 8, 6},    // Sprite 198
    {217, 208, 8, 6},    // Sprite 199
    {227, 208, 10, 6},   // Sprite 200
    {239, 208, 8, 6},    // Sprite 201
    {313, 122, 2, 7},    // Sprite 202 - PLAYER BULLET
    {109, 37, 16, 16},   // Sprite 203 - ENEMY TYPE 0 FRAME 0
    {127, 37, 16, 16},   // Sprite 204 - ENEMY TYPE 0 FRAME 1
    {109, 55, 16, 16},   // Sprite 205 - ENEMY TYPE 1 FRAME 0
    {127, 55, 16, 16},   // Sprite 206 - ENEMY TYPE 1 FRAME 1
    {109, 73, 16, 16},   // Sprite 207 - ENEMY TYPE 2 FRAME 0
    {127, 73, 16, 16},   // Sprite 208 - ENEMY TYPE 2 FRAME 1
    {109, 91, 16, 16},   // Sprite 209 - ENEMY TYPE 3 FRAME 0
    {127, 91, 16, 16},   // Sprite 210 - ENEMY TYPE 3 FRAME 1
    {289, 1, 31, 31},    // Sprite 211 - EXPLOSION FRAME 0
    {323, 1, 31, 31},    // Sprite 212 - EXPLOSION FRAME 1
    {357, 1, 31, 31},    // Sprite 213 - EXPLOSION FRAME 2
    {391, 1, 31, 31},    // Sprite 214 - EXPLOSION FRAME 3
    {425, 1, 31, 31}     // Sprite 215 - EXPLOSION FRAME 4
};

#endif  // GAME_ASSETS_SPRITES_SPRITE_COORDS_H_
