CC = gcc

ASAN_FLAGS =
ifeq ($(ASAN),1)
    ASAN_FLAGS = -fsanitize=address -fsanitize=undefined -fsanitize-trap=all
else ifeq ($(filter asan,$(MAKECMDGOALS)),asan)
    ASAN_FLAGS = -fsanitize=address -fsanitize=undefined -fsanitize-trap=all
endif

INCDIR = include
SRCDIR = src
SDLDIR = SDL3
OBJDIR = obj

SDL_INCLUDE = $(SDLDIR)/include
SDL_LIB = $(SDLDIR)/lib

CFLAGS = -Wall -Wextra -Wpedantic -O2 $(ASAN_FLAGS) -std=c17 -I$(INCDIR) -I$(SDL_INCLUDE)
LDFLAGS = $(ASAN_FLAGS) -L$(SDL_LIB) -lSDL3

BIN = main

C_FILES = $(wildcard *.c) $(wildcard $(SRCDIR)/*.c)
OBJ_FILES = $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(C_FILES)))

all: $(BIN)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJ_FILES) | $(OBJDIR)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ_FILES)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(BIN)

re: fclean all

asan:
	@$(MAKE) all ASAN=1

.PHONY: all clean fclean re asan
