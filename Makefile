all:
	cc test_ccl.c -o test -Wall -Wextra -pedantic

clean:
	rm ./test
