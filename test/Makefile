

all : test

test: test.c max.o
	g++ max.o test.c -I../../gtest/gtest-1.7.0/include -I. -lgtest_main -L. -lpthread -g -Wall -o test -fprofile-arcs -ftest-coverage

max.o : max.c
	g++ -c max.c -fprofile-arcs -ftest-coverage

clean: 
	rm -f *.o test *.gcda *.gcno *.gcov
