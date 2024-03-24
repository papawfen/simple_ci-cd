CFLAGS = -Wall -Werror -Wextra
SOURCE = $(wildcard s21_*.c)

all: s21_grep test

s21_grep:
	gcc $(CFLAGS) s21_grep.c -o s21_grep

test:
	grep -e asd makefile > t1.txt && ./s21_grep -e asd makefile > t2.txt && diff t1.txt t2.txt
	grep -i asd makefile > t1.txt && ./s21_grep -i asd makefile > t2.txt && diff t1.txt t2.txt
	grep -v asd makefile > t1.txt && ./s21_grep -v asd makefile > t2.txt && diff t1.txt t2.txt
	grep -c asd makefile > t1.txt && ./s21_grep -c asd makefile > t2.txt && diff t1.txt t2.txt
	grep -l asd makefile > t1.txt && ./s21_grep -l asd makefile > t2.txt && diff t1.txt t2.txt
	grep -n asd makefile > t1.txt && ./s21_grep -n asd makefile > t2.txt && diff t1.txt t2.txt
	grep -h asd makefile > t1.txt && ./s21_grep -h asd makefile > t2.txt && diff t1.txt t2.txt
	grep -s asd makefile > t1.txt && ./s21_grep -s asd makefile > t2.txt && diff t1.txt t2.txt
	grep -f makefile s21_grep.c > t1.txt && ./s21_grep -f makefile s21_grep.c > t2.txt && diff t1.txt t2.txt
	grep -o asd makefile > t1.txt && ./s21_grep -o asd makefile > t2.txt && diff t1.txt t2.txt

check: ${SOURCE}
ifeq ("","$(wildcard ./CPPLINT.cfg)")
	cp -f ../../materials/linters/CPPLINT.cfg ./CPPLINT.cfg
endif
	-python3 ../../materials/linters/cpplint.py --extensions=c $^

clean:
	rm -rf *.txt s21_grep CPPLINT.cfg
