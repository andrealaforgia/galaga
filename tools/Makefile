CC = gcc

SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LFLAGS := $(shell sdl2-config --libs) -lSDL2_image

CFLAGS := -ggdb3 -O2 --std=c99 -Wall -Wextra -pedantic-errors $(SDL2_CFLAGS)
LFLAGS := $(SDL2_LFLAGS)

TARGET = sprite_extractor

.PHONY: all clean

all: $(TARGET)

$(TARGET): sprite_extractor.c
	$(CC) $(CFLAGS) -o $@ $< $(LFLAGS)

clean:
	rm -f $(TARGET)
