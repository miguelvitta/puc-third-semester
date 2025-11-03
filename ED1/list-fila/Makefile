CC       = clang
CFLAGS   = -Wall -Wextra -Wshadow -std=c11
LDFLAGS  = -lm
DEBUG_FLAGS = -O0 -g3 -fsanitize=address -fno-omit-frame-pointer

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

TARGET   = list-fila
TARGET_D = $(TARGET)_debug

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET_D)

$(TARGET_D): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET_D)

.PHONY: all debug clean