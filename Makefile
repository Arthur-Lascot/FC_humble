CC = gcc
CPPFLAGS = `pkg-config --cflags sdl gtk+-3.0` -rdynamic -MMD
CFLAGS = -Wall -Wextra -Werror -std=c99 -O3 -g -fsanitize=address 
LDFLAGS = -fsanitize=address
LDLIBS = `pkg-config --libs sdl SDL_image gtk+-3.0` -lm -lSDL_gfx -rdynamic


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

