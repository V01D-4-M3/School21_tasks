RED = \033[0;31m
YELLOW = \033[1;33m
GREEN = \033[0;32m
BOLD = \033[1m
NC = \033[0m 

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -I brick_game/tetris -I gui/cli -Wpedantic
POSIX = -D_POSIX_C_SOURCE=200809L

SOURCE_DIRS = ./brick_game/tetris ./gui/cli
TEST_FILES = $(wildcard ./tests/*.c)
FSM_OBJECTS = tetris.o
CLI_OBJECTS = cli.o
INSTALL_DIRECTORY = ./bin
VERSION = 1.0
PROJECT_NAME = tetris
DISTRIBUTION_DIR = $(PROJECT_NAME)-$(VERSION)
DISTRIBUTION_SOURCES = ./Makefile ./tests ./gui ./brick_game ./main.c

.PHONY: all clean install uninstall dist dvi doxy rebuild tetris test gcov_report format formati cppcheck valgrind help

all: build_and_run

install: clean build_executable
	@echo -e "$(GREEN)Installing executable...$(NC)"
	mkdir -p $(INSTALL_DIRECTORY)
	cp $(PROJECT_NAME) $(INSTALL_DIRECTORY)
	@echo -e "$(GREEN)Installation complete!$(NC)"

uninstall:
	@echo -e "$(YELLOW)Removing installation...$(NC)"
	rm -rf $(INSTALL_DIRECTORY)
	@echo -e "$(GREEN)Uninstallation complete!$(NC)"

dist: clean 
	@echo -e "$(GREEN)Creating distribution...$(NC)"
	mkdir -p $(DISTRIBUTION_DIR)
	cp -r $(DISTRIBUTION_SOURCES) $(DISTRIBUTION_DIR)
	tar -czf $(DISTRIBUTION_DIR).tar.gz $(DISTRIBUTION_DIR)
	rm -rf $(DISTRIBUTION_DIR)
	@echo -e "$(GREEN)Distribution created: $(DISTRIBUTION_DIR).tar.gz$(NC)"

dvi: clean generate_documentation
	@echo -e "$(GREEN)Generating PDF documentation...$(NC)"
	(cd ./doxygen/latex && sudo pdflatex refman.tex)

doxy: clean
	@echo -e "$(GREEN)Generating documentation...$(NC)"
	sudo doxygen
	@echo -e "$(GREEN)Documentation generated!$(NC)"

clean:
	@echo -e "$(YELLOW)Cleaning build files...$(NC)"
	rm -rf *.a *.o *.gcno *.gcda unit_test *.css *.html *.gcov $(PROJECT_NAME) *.txt ./doxygen
	@echo -e "$(GREEN)Clean complete!$(NC)"

rebuild: clean all

build_and_run: clean build_executable
	@echo -e "$(GREEN)Build successful! Running...$(NC)"
	./$(PROJECT_NAME)

build_executable: create_static_library $(CLI_OBJECTS) main.o
	@echo -e "$(GREEN)Linking executable...$(NC)"
	$(CC) $(CFLAGS) $(POSIX) $(CLI_OBJECTS) main.o -o $(PROJECT_NAME) tetris.a -lncurses
	@echo -e "$(GREEN)Executable linked successfully!$(NC)"

create_static_library: $(FSM_OBJECTS)
	@echo -e "$(GREEN)Creating static library...$(NC)"
	ar rc tetris.a $(FSM_OBJECTS)
	ranlib tetris.a
	@echo -e "$(GREEN)Static library created!$(NC)"
	
%.o: brick_game/tetris/%.c
	@echo -e "$(GREEN)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

%.o: gui/cli/%.c
	@echo -e "$(GREEN)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

%.o: %.c
	@echo -e "$(GREEN)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

test: clean compile_tests
	@echo -e "$(GREEN)Running tests...$(NC)"
	chmod +x unit_test
	./unit_test

compile_tests: clean
	@echo -e "$(GREEN)Compiling tests...$(NC)"
	$(CC) $(CFLAGS) $(POSIX) $(TEST_FILES) -c 
	$(CC) $(CFLAGS) $(POSIX) -o unit_test *.o ./brick_game/tetris/*.c --coverage -lcheck -lsubunit -lm
	@echo -e "$(GREEN)Tests compiled successfully!$(NC)"

gcov_report: run_tests_with_coverage
	@echo -e "$(GREEN)Generating coverage report...$(NC)"
	gcov *.gcda
	gcovr
	gcovr --html-details -o report.html -g
	@echo -e "$(GREEN)Coverage report generated!$(NC)"

run_tests_with_coverage: clean test

check_style:
	@echo -e "$(GREEN)Checking code formatting...$(NC)"
	clang-format -n $(shell find $(SOURCE_DIRS) ./tests . -name '*.h' -o -name '*.c')
	@echo -e "$(GREEN)Formatting check complete!$(NC)"

format_style:
	@echo -e "$(YELLOW)Formatting code...$(NC)"
	clang-format -i $(shell find $(SOURCE_DIRS) ./tests . -name '*.h' -o -name '*.c')
	@echo -e "$(GREEN)Code formatting complete!$(NC)"

cppcheck:
	@echo -e "$(GREEN)Running static analysis...$(NC)"
	cppcheck --enable=all --suppress=missingIncludeSystem --std=c11 $(shell find $(SOURCE_DIRS) ./tests . -name '*.h' -o -name '*.c')
	@echo -e "$(GREEN)Static analysis complete!$(NC)"

valgrind: compile_tests
	@echo -e "$(YELLOW)Running memory analysis...$(NC)"
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./unit_test

generate_documentation: clean
	@echo -e "$(GREEN)Generating documentation...$(NC)"
	sudo doxygen
	@echo -e "$(GREEN)Documentation generated!$(NC)"

help:
	@echo -e "$(BOLD)Available targets:$(NC)"
	@echo -e "  $(GREEN)all$(NC)          - Build and run project"
	@echo -e "  $(GREEN)clean$(NC)        - Clean build files"
	@echo -e "  $(GREEN)install$(NC)      - Install executable"
	@echo -e "  $(GREEN)uninstall$(NC)    - Remove installed files"
	@echo -e "  $(GREEN)dist$(NC)         - Create distribution"
	@echo -e "  $(GREEN)test$(NC)         - Run tests"
	@echo -e "  $(GREEN)gcov_report$(NC)  - Generate coverage report"
	@echo -e "  $(GREEN)check_style$(NC)  - Check code formatting"
	@echo -e "  $(GREEN)format_style$(NC) - Format code"
	@echo -e "  $(GREEN)cppcheck$(NC)     - Run static analysis"
	@echo -e "  $(GREEN)valgrind$(NC)     - Run memory analysis"
	@echo -e "  $(GREEN)help$(NC)         - Show this help"
	@echo ""
	@echo -e "$(BOLD)Created by V01D-4-M3; Check my github:$(NC)"
	@echo -e "$(GREEN)https://github.com/V01D-4-M3         ^-^  $(NC)"