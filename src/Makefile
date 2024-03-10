SHELL = /bin/sh 

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
TEST_FLAGS = $(shell pkg-config --cflags --libs check)

SRC = *.c
OBJ = calc
C_FILES = s21_calc_back.c

all: uninstall clean install test gcov_report dist dvi

install:
	@mkdir ../smartcalc_v1
	@$(CC) $(CFLAGS) -o ../smartcalc_v1/calc $(SRC) $(LIBS) -lm
	@cp doc.texi ../smartcalc_v1

uninstall:
	@rm -rf ../smartcalc_v1

dist:
	@mkdir ../smartcalc
	@cp -R ./ ../smartcalc
	@tar -cf smartcalc.tar ../smartcalc
	@gzip smartcalc.tar
	@rm -rf ../smartcalc

dvi:
	@cat doc.texi

test:
	@checkmk clean_mode=1 include.file *.check > test.c
	@clang-format -i --style=Google test.c
	@$(CC) $(CFLAGS) -o test $(C_FILES) test.c $(LIBS) $(TEST_FLAGS)
	@./test

gcov_report: 
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(C_FILES) test.c -o gcov_report $(LIBS) $(TEST_FLAGS)
	./gcov_report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

leak:
ifeq ($(OS),Darwin)
	CK_FORK=no leaks -atExit -- ./test
else
	CK_FORK=no valgrind --leak-check=full -s --track-origins=yes --log-file=leak.log ./test
endif

check_style:
	cppcheck --enable=all --suppress=missingIncludeSystem *.h *.c
	clang-format -n -style=google *.h *.c

correct_style:
	clang-format -i -style=google *.h *.c

clean:
	@rm -rf *.o *.a *.out *.info *.html *.gc* test test.c gcov_report report *.log *.tar.gz