CC = gcc

ASAN_FLAGS =
ifeq ($(ASAN),1)
    ASAN_FLAGS = -fsanitize=address -fsanitize=undefined -fsanitize-trap=all
else ifeq ($(filter asan,$(MAKECMDGOALS)),asan)
    ASAN_FLAGS = -fsanitize=address -fsanitize=undefined -fsanitize-trap=all
endif

INCDIR = include
SRCDIR = src
SDLDIR = shared
OBJDIR = obj

SDL_INCLUDE = $(SDLDIR)/include
SDL_IMAGE_INCLUDE = $(SDLDIR)/include
SDL_LIB = $(SDLDIR)/lib

CFLAGS = -Wall -Wextra -Wpedantic -O2 $(ASAN_FLAGS) -std=c17 -I$(INCDIR) -I$(SDL_INCLUDE) -I$(SDL_IMAGE_INCLUDE)

# Updated LDFLAGS for MinGW with .dll.a files
LDFLAGS = $(ASAN_FLAGS) -L$(SDL_LIB) -lmingw32 -lSDL3 -lSDL3_image

BIN = main

C_FILES = $(wildcard *.c) $(wildcard $(SRCDIR)/*.c)
OBJ_FILES = $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(C_FILES)))

all: $(BIN) cpydlls

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJ_FILES) | $(OBJDIR)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

cpydlls:
	cp $(SDLDIR)/bin/*.dll .

run: $(BIN) copy-dlls
	./$(BIN)

clean:
	rm -f $(OBJ_FILES)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(BIN)
	rm -f *.dll

re: fclean all

asan:
	@$(MAKE) all ASAN=1

.PHONY: all clean fclean re asan cpydlls run