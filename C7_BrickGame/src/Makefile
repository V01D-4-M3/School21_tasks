CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = -lncurses

BRICK_GAME_DIR = brick_game/tetris
GUI_DIR = gui/cli

BRICK_GAME_SOURCES = $(BRICK_GAME_DIR)/tetris.c $(BRICK_GAME_DIR)/timer.c
GUI_SOURCES = $(GUI_DIR)/cli.c
MAIN_SOURCE = main.c

SOURCES = $(MAIN_SOURCE) $(BRICK_GAME_SOURCES) $(GUI_SOURCES)
OBJECTS = $(SOURCES:.c=.o)

TARGET = tetris

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
NC = \033[0m

.PHONY: all clean rebuild format_style style_check

all: $(TARGET)
	@echo "\033[42mCreated by V01D-4-M3; Check my github:\033[0m"
	@echo "\033[42mhttps://github.com/V01D-4-M3         ^-^  \033[0m"

%.o: %.c
	@echo -e "$(YELLOW)Compiling $<$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	@echo -e "$(GREEN)Linking executable...$(NC)"
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo -e "$(GREEN)Build successful! Run with: ./$(TARGET)$(NC)"

run: $(TARGET)
	@echo -e "$(GREEN)Running Tetris...$(NC)"
	./$(TARGET)

clean:
	@echo -e "$(YELLOW)Cleaning build files...$(NC)"
	rm -f $(OBJECTS) $(TARGET) vgcore.* *.gcda *.gcno *.gcov
	@echo -e "$(GREEN)Clean completed!$(NC)"

rebuild: clean all

debug:
	$(MAKE) CFLAGS="$(CFLAGS) -DDEBUG -O0"

valgrind_test: $(TARGET)
	@echo -e "$(YELLOW)Running with Valgrind...$(NC)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

format_style:
	@cp ../materials/linters/.clang-format .
	@clang-format -i **/*.c **/*.h *.h
	@rm ./.clang-format

style_check:
	@cp ../materials/linters/.clang-format .
	@clang-format -n **/*.c **/*.h *.h
	@rm ./.clang-format

help:
	@echo "Available targets:"
	@echo "  all       - Build the project (default)"
	@echo "  run       - Build and run the game"
	@echo "  clean     - Remove build files"
	@echo "  rebuild   - Clean and rebuild"
	@echo "  debug     - Build with debug flags"
	@echo "  valgrind_test  - Run with Valgrind memory checker"
	@echo "  format_style - Format code style"
	@echo "  style_check - Check code style"
	@echo "  help      - Show this help"