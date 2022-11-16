UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LFLAGS=-lcheck -lsubunit -lrt -lm -lpthread
	SYSFLAG=-D LINUX
endif
ifeq ($(UNAME),Darwin)
	LFLAGS=-lcheck -lm
	SYSFLAG=-D APPLE
endif
CFLAGS=-Wall -Werror -Wextra
GFLAGS=-fprofile-arcs -ftest-coverage
SOURCES=

all: s21_string.a

main:
	gcc $(SYSFLAG) main_test.c s21_string.c -o main_exec

shark:
	gcc -Wextra -Wall -Werror shark_test.c s21_string.c -o shark_exec

sharkss:
	gcc -Wextra -Wall -Werror s21_string.c s21_sscanf.c shark_sscanf_test.c -o shark_exec

git_sharkss:
	git add s21_sscanf.c s21_sscanf.h shark_sscanf_test.c
	git commit -m "sharkmer: sscanf update"
	git push origin develop

style:
	clang-format -n style=Google *.c *.h

s21_string.a:
	gcc -c s21_string.c
	ar rc libs21_string.a s21_string.o
	ranlib libs21_string.a
	rm -f *.o

gcov_report:
	gcc $(GFLAGS) test.c s21_string.c $(LFLAGS) -o test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	
test: s21_string.a
	gcc test.c -L. -ls21_string $(LFLAGS) -o test
	./test

rebuild: clean gcov_report

clean:
	rm -f test libs21_string.a *.gc* test.info
	rm -f -rf report
