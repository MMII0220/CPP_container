CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++20 -lstdc++ # -fsanitize=address
TEST_FLAGS = -lgtest -pthread
TEST_TARGET = test

all: test

clean:
	@echo "Deleting unnecessary files..."
	@rm -rf *.o *.a *.out *.log $(TEST_TARGET)
	rm -rf *.o *.out s21_container.a unit_test
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report *.info

test: clean
	@$(CC) $(CFLAGS) ./all_test.cpp  $(TEST_FLAGS) -o $(TEST_TARGET)
	./$(TEST_TARGET)

gcov_report: clean test
	@g++ --coverage $(CFLAGS) all_test.cpp ./s21_containers/s21_container.hpp ./s21_containersplus/s21_containersplus.hpp -o test -lstdc++ -lm -lgtest
	@./test
	@geninfo --ignore-errors mismatch --output-filename test.info --test-name test --memory 0 all_test.gcda
	@genhtml --ignore-errors mismatch -o report test.info
	@open report/index.html
