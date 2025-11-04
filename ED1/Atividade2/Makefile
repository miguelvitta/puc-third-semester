CC = clang
CFLAGS = -Wall -Wextra -Wshadow
DEBUG_FLAGS = -O0 -g3 -fsanitize=address -fno-omit-frame-pointer

# All source files
SRCS = main.c list.c
# Object files generated from each .c
OBJS = $(SRCS:.c=.o)
# Name of your final executable
TARGET = list1

all: $(TARGET)

# Link all object files into the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lm

# Compile each .c into a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
