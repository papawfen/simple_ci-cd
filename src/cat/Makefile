CFLAGS = -Wall -Werror -Wextra
SOURCE = $(wildcard s21_*.c)

all: s21_cat

s21_cat:
	gcc $(CFLAGS) s21_cat.c -o s21_cat
	
test:
	cat -b Makefile > t1.txt && ./s21_cat -b Makefile > t2.txt && diff t1.txt t2.txt
	cat -e Makefile > t1.txt && ./s21_cat -e Makefile > t2.txt && diff t1.txt t2.txt
	cat -n Makefile > t1.txt && ./s21_cat -n Makefile > t2.txt && diff t1.txt t2.txt
	cat -s Makefile > t1.txt && ./s21_cat -s Makefile > t2.txt && diff t1.txt t2.txt
	cat -t Makefile > t1.txt && ./s21_cat -t Makefile > t2.txt && diff t1.txt t2.txt
	cat -v Makefile > t1.txt && ./s21_cat -v Makefile > t2.txt && diff t1.txt t2.txt

check: ${SOURCE}
ifeq ("","$(wildcard ./CPPLINT.cfg)")
	cp -f ../../materials/linters/CPPLINT.cfg ./CPPLINT.cfg
endif
	-python3 ../../materials/linters/cpplint.py --extensions=c $^

clean:
	rm -rf  *.txt
	rm -rf s21_cat CPPLINT.cfg
