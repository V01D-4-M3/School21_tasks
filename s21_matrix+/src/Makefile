CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LIBS = -lgtest -lgtest_main -pthread

SRCS_DIR = .
TESTS_DIR = ./tests
BUILD_DIR = build
OBJECTS_DIR = $(BUILD_DIR)/objects
COVERAGE_DIR = $(BUILD_DIR)/coverage

TARGET = $(BUILD_DIR)/s21_matrix_oop.a
TEST_TARGET = $(BUILD_DIR)/s21_test
GCOV_TARGET = $(BUILD_DIR)/s21_test_gcov

SRCS = $(SRCS_DIR)/s21_matrix.cpp
OBJS = $(OBJECTS_DIR)/s21_matrix.o
TEST_SRC = $(TESTS_DIR)/s21_test_matrix.cpp

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	@ar rcs $(TARGET) $(OBJS)
	@echo "\033[32mStatic library created: $(TARGET)\033[0m"
	@echo "\033[42mCreated by V01D-4-M3; Check my github:\033[0m"
	@echo "\033[42mhttps://github.com/V01D-4-M3           ^-^  \033[0m"

$(OBJECTS_DIR)/s21_matrix.o: $(SRCS_DIR)/s21_matrix.cpp
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(SRCS_DIR)

test: $(TARGET)
	@echo "\033[34mBuilding test executable...\033[0m"
	@$(CC) $(CFLAGS) $(TEST_SRC) -I$(SRCS_DIR) -o $(TEST_TARGET) $(TARGET) $(LIBS)
	@echo "\033[32mRunning tests...\033[0m"
	@echo "----------------------------------------------------"
	@./$(TEST_TARGET) || (echo "\033[31mTests failed!\033[0m" && exit 1)
	@echo "----------------------------------------------------"
	@echo "\033[32mAll tests passed!\033[0m"

gcov: CFLAGS += $(GCOV_FLAGS)
gcov: $(OBJS)
	@echo "\033[34mBuilding test executable with coverage...\033[0m"
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(TEST_SRC) -I$(SRCS_DIR) -o $(GCOV_TARGET) $(OBJS) $(LIBS)
	@echo "\033[32mRunning tests with coverage...\033[0m"
	@echo "----------------------------------------------------"
	@./$(GCOV_TARGET)
	@echo "----------------------------------------------------"
	@echo "\033[34mGenerating coverage data...\033[0m"
	@mkdir -p $(COVERAGE_DIR)
	@lcov --capture --directory $(OBJECTS_DIR) --output-file $(COVERAGE_DIR)/coverage.info
	@echo "\033[34mFiltering out system headers...\033[0m"
	@lcov --remove $(COVERAGE_DIR)/coverage.info '/usr/*' --output-file $(COVERAGE_DIR)/coverage_filtered.info
	@genhtml $(COVERAGE_DIR)/coverage_filtered.info --output-directory $(COVERAGE_DIR)/html
	@echo "\033[32mCoverage report generated at $(COVERAGE_DIR)/html/index.html\033[0m"
	@echo "\033[33mOpening coverage report in browser...\033[0m"
	@xdg-open $(COVERAGE_DIR)/html/index.html 2>/dev/null || open $(COVERAGE_DIR)/html/index.html 2>/dev/null || echo "\033[31mCould not open browser automatically\033[0m"

valgrind_check: $(TARGET)
	@echo "\033[34mBuilding test executable for valgrind...\033[0m"
	@$(CC) $(CFLAGS) $(TEST_SRC) -I$(SRCS_DIR) -o $(TEST_TARGET) $(TARGET) $(LIBS)
	@echo "\033[32mRunning tests with valgrind...\033[0m"
	@echo "----------------------------------------------------"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(TEST_TARGET)
	@echo "----------------------------------------------------"
	@echo "\033[32mValgrind check completed. See valgrind-out.txt for details.\033[0m"

format_style:
	@echo "\033[34mFormatting code style...\033[0m"
	@cp ../materials/linters/.clang-format .
	@clang-format -i *.cpp *.h tests/*.cpp
	@rm ./.clang-format
	@echo "\033[32mCode formatting completed!\033[0m"

style_check:
	@echo "\033[34mChecking code style...\033[0m"
	@cp ../materials/linters/.clang-format .
	@clang-format -n *.cpp *.h tests/*.cpp || (echo "\033[31mStyle check failed!\033[0m" && rm ./.clang-format && exit 1)
	@rm ./.clang-format
	@echo "\033[32mStyle check passed!\033[0m"

clean:
	@rm -rf $(BUILD_DIR) *.gcda *.gcno *.gcov valgrind-out.txt
	@echo "\033[33mClean completed!\033[0m"

rebuild: clean all

help:
	@echo "\033[36mAvailable commands:\033[0m"
	@echo "  \033[32mmake\033[0m       - Build static library"
	@echo "  \033[32mmake test\033[0m   - Build and run tests"
	@echo "  \033[32mmake gcov\033[0m   - Build with coverage and generate report"
	@echo "  \033[32mmake valgrind_check\033[0m - Run tests with valgrind memory check"
	@echo "  \033[32mmake format_style\033[0m - Format code using clang-format"
	@echo "  \033[32mmake style_check\033[0m - Check code style"
	@echo "  \033[32mmake clean\033[0m   - Remove build artifacts"
	@echo "  \033[32mmake rebuild\033[0m - Clean and rebuild everything"
	@echo "  \033[32mmake help\033[0m    - Show this help message"
	@echo ""
	@echo "\033[42m@V01D-4-M3\033[0m"

.PHONY: all test gcov valgrind_check format_style style_check clean rebuild help