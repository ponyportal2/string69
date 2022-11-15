UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LFLAGS=-lcheck -lsubunit -lrt -lm -lpthread
endif
ifeq ($(UNAME),Darwin)
	LFLAGS=-lcheck -lm
endif
CFLAGS=-Wall -Werror -Wextra
GFLAGS=-fprofile-arcs -ftest-coverage
SOURCES=

all: gcov_report

main:
	gcc main_test.c s21_string.c -o main_exec

shark:
	gcc -Wextra -Wall -Werror shark_test.c s21_string.c -o shark_exec

s21_string.a:
	gcc -c s21_string.c
	ar rc libs21_string.a s21_string.o
	ranlib libs21_string.a
	rm *.o

gcov_report: s21_string.a
	gcc $(GFLAGS) test.c -L. -ls21_string $(LFLAGS) -o test
	./test
	gcov test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	
test: s21_string.a
	gcc test_string.c -L. -ls21_string $(LFLAGS) -o test

rebuild: clean gcov_report

clean:
	rm test libs21_string.a *.gc* test.info
	rm -rf report
