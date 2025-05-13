.PHONY: tests build
all: gcov_report

create: 
	mkdir -p build
	cmake -S ./ -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS_DEBUG="-g -std=c++17 --coverage "
	cmake --build build

s21_matrix_oop.a: create
	cmake --build build --target s21_matrix_oop

test: clean create
	./build/test/test_matrix

gcov_report: test
	mkdir -p report
	gcovr -r . --html-details -o ./report/gcov_report.html -f s21_matrix_oop.cpp
	open ./report/gcov_report.html

style: clean
	find . -type f -name "*.cpp" -o -name "*.h" | xargs clang-format --Werror --style=Google -n

clean:
	rm -rf build/ *.o *.a *.gcno *.gcda *.info report/

leaks: test
ifeq ($(shell uname -s), Linux)
	valgrind --leak-check=full --track-origins=yes --quiet --log-file=text.txt ./build/test/test_matrix
else
	CK_FORK=no leaks --atExit -- ./build/test/test_matrix
endif
