CC = gcc
CPPFLAGS = `pkg-config --cflags sdl` -MMD
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -O3 -g -fsanitize=address 
LDFLAGS = -fsanitize=address
LDFLIBS = `pkg-config --libs sdl SDL_image gtk+-3.0` -lm -lSDL_gfx -export_dynamic


SRCS = $(wildcard Scripts/*.c) $(wildcard Scripts/**/*.c)
OBJS = $(SRCS:%.c=%.o)
DEPS = $(OBJS:%.o=%.d)


BIN = OCR

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$%.o: %.c
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CLFAGS)


clean:
	$(RM) $(OBJS) $(DEPS) $(BIN)

.PHONY: all preps clean

-include $(DEPS)

