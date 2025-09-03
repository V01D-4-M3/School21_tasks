TARGET = s21_matrix.a
SRCS_DIR = s21_matrix
TESTS_DIR = tests
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname)

SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(SRCS:$(SRCS_DIR)/%.c=build/$(SRCS_DIR)/%.o)

TEST_SRC = $(wildcard $(TESTS_DIR)/*.c)
TEST_TARGET = build/test

LIBS = -lcheck -lsubunit -lm
ifneq ($(OS), Linux)
	LIBS += -lrt -lpthread
endif
GCOV_LIB = -lgcov

COVERAGE_DIR = coverage
COVERAGE_INFO = $(COVERAGE_DIR)/coverage.info
HTML_REPORT = $(COVERAGE_DIR)/html/index.html

.PHONY: all build rebuild clean test gcov_report valgrind_check style_check format_style help

all: $(TARGET)

build: $(TARGET)
	@echo "\033[107mCreated by V01D-4-M3; Check my github:\033[0m"
	@echo "\033[106mhttps://github.com/V01D-4-M3     ^-^  \033[0m"
	@mkdir -p build build/$(SRCS_DIR)

.dir_build .dir_build_$(SRCS_DIR):
	@mkdir -p build build/$(SRCS_DIR)

$(TARGET): $(OBJS)
	@ar rcs $@ $^
	@ranlib $@
	@echo "\033[32mLibrary compiled: $(TARGET)\033[0m"

build/$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c | .dir_build .dir_build_$(SRCS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

rebuild: clean all

test: CFLAGS += $(GCOV_FLAGS)
test: clean $(OBJS)
	@echo "\033[34mBuilding test executable with coverage...\033[0m"
	@$(CC) $(CFLAGS) $(TEST_SRC) -I. -I$(SRCS_DIR) -o $(TEST_TARGET) $(OBJS) $(LIBS) $(GCOV_LIB)
	@echo "\033[32mRunning tests...\033[0m"
	@echo "----------------------------------------------------"
	@./$(TEST_TARGET) || (echo "\033[31mTests failed!\033[0m" && exit 1)
	@echo "----------------------------------------------------"
	@echo "\033[32m✅ Tests passed. Coverage data generated (.gcda/.gcno).\033[0m"

gcov_report: test
	@echo "\033[34mGenerating coverage report...\033[0m"
	@gcov -a -b -o build/$(SRCS_DIR) $(SRCS_DIR)/*.c
	@mkdir -p $(COVERAGE_DIR)/html
	@lcov --capture --directory build/$(SRCS_DIR) --output-file $(COVERAGE_INFO) || (echo "\033[33mInstall lcov: sudo apt install lcov\033[0m" && exit 1)
	@genhtml $(COVERAGE_INFO) --output-directory $(COVERAGE_DIR)/html || (echo "\033[33mInstall genhtml\033[0m" && exit 1)
	@echo "\033[32mCoverage report: $(HTML_REPORT)\033[0m"
	@xdg-open "$(HTML_REPORT)" 2>/dev/null || open "$(HTML_REPORT)" 2>/dev/null || echo "\033[33mOpen manually: $(HTML_REPORT)\033[0m"

valgrind_check: CFLAGS += $(GCOV_FLAGS)
valgrind_check: clean $(OBJS)
	@echo "\033[33mBuilding for Valgrind...\033[0m"
	@$(CC) $(CFLAGS) $(TEST_SRC) -I. -I$(SRCS_DIR) -o $(TEST_TARGET) $(OBJS) $(LIBS) $(GCOV_LIB)
	@echo "\033[33mRunning Valgrind...\033[0m"
	@CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="build/valgrind.log" ./$(TEST_TARGET)
	@echo "\033[32mValgrind log saved to build/valgrind.log\033[0m"

format_style:
	@cp ../materials/linters/.clang-format . 2>/dev/null || true
	@clang-format -i $(SRCS_DIR)/*.c $(SRCS_DIR)/*.h tests/*.c tests/*.h *.h
	@rm -f ./.clang-format

style_check:
	@cp ../materials/linters/.clang-format . 2>/dev/null || true
	@clang-format -n $(SRCS_DIR)/*.c $(SRCS_DIR)/*.h tests/*.c tests/*.h *.h || exit 1
	@rm -f ./.clang-format
	@echo "\033[32mStyle check passed.\033[0m"

clean:
	@rm -rf build coverage
	@rm -f $(TARGET) $(TEST_TARGET) *.gcno *.gcda *.gcov
	@echo "\033[32mClean completed.\033[0m"

help:
	@echo "\033[34mAvailable commands:\033[0m"
	@echo "\033[32mall\033[0m             - build library"
	@echo "\033[32mbuild\033[0m           - same as all"
	@echo "\033[32mrebuild\033[0m         - clean + all"
	@echo "\033[32mclean\033[0m           - remove all generated files"
	@echo "\033[32mtest\033[0m            - build & run tests, collect coverage data"
	@echo "\033[32mgcov_report\033[0m     - generate HTML coverage report (runs test first)"
	@echo "\033[32mvalgrind_check\033[0m  - run tests under Valgrind"
	@echo "\033[32mstyle_check\033[0m     - check code style"
	@echo "\033[32mformat_style\033[0m    - auto-format code"
	@echo "\033[32mhelp\033[0m            - show this help"