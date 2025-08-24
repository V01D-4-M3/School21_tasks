TARGET = s21_matrix.a
SRCS_DIR = s21_matrix
TESTS_DIR = tests
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
GCOV = -fprofile-arcs -ftest-coverage
OS = $(shell uname)

SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(SRCS:$(SRCS_DIR)/%.c=build/$(SRCS_DIR)/%.o)

TEST_SRC = $(wildcard $(TESTS_DIR)/*.c)
TEST_TARGET = build/test
LIBS = -lcheck -lsubunit -lm

ifneq ($(OS), Linux)
	LIBS += -lrt -lpthread
endif

all: $(TARGET)

build: $(TARGET)

$(OBJS): | build build/$(SRCS_DIR)

build:
	@mkdir -p build build/$(SRCS_DIR)

$(TARGET): $(OBJS)
	@ar rcs $@ $^
	@ranlib $@
	@echo "\033[32mLibrary compiled: $(TARGET)\033[0m"

build/$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c | build build/$(SRCS_DIR)
	@$(CC) $(CFLAGS) $(GCOV) -c $< -o $@

rebuild: clean all

test: CFLAGS += $(GCOV)
test: $(TARGET)
	@echo "\033[34mBuilding test executable...\033[0m"
	@$(CC) $(CFLAGS) $(TEST_SRC) -I$(SRCS_DIR) -o $(TEST_TARGET) $(TARGET) $(LIBS)
	@echo "\033[32mRunning tests...\033[0m"
	@echo "----------------------------------------------------"
	@./$(TEST_TARGET)
	@gcov -a -b -o build/$(SRCS_DIR) $(SRCS_DIR)/*.c
	@mkdir -p coverage
	@mv *.gcov coverage/ 2>/dev/null || echo "\033[33mNo gcov reports generated\033[0m"
	@echo "\033[32mTests completed with coverage\033[0m"

format_style:
	@cp ../materials/linters/.clang-format .
	@clang-format -i **/*.c **/*.h *.h
	@rm ./.clang-format

style_check:
	@cp ../materials/linters/.clang-format .
	@clang-format -n **/*.c **/*.h *.h
	@rm ./.clang-format

valgrind_check: test
	@echo "\033[33mRunning Valgrind...\033[0m"
	@CK_FORK=no valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--log-file="build/valgrind.log" \
		./$(TEST_TARGET)
	@echo "\033[32mValgrind log saved to build/valgrind.log\033[0m"

help:
	@echo "\033[34mMakefile commands:\033[0m"
	@echo "\033[32mall\033[0m           - build the library"
	@echo "\033[32mbuild\033[0m         - build the library"
	@echo "\033[32mrebuild\033[0m       - clean and rebuild"
	@echo "\033[32mclean\033[0m         - remove generated files"
	@echo "\033[32mtest\033[0m          - build and run unit tests with coverage"
	@echo "\033[32mvalgrind_check\033[0m - run tests under Valgrind"
	@echo "\033[32mstyle_check\033[0m   - check code style"
	@echo "\033[32mformat_style\033[0m  - format code with clang-format"
	@echo "\033[32mhelp\033[0m          - show this help"

clean:
	@rm -rf build coverage 
	@rm -f $(TARGET) $(TEST_TARGET) *.gcov
	@echo "\033[32mClean completed: build/ and coverage/ removed\033[0m"

.PHONY: all build rebuild clean test valgrind_check style_check format_style help