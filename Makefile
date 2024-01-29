CC=gcc
CFLAGS=-g -m32 -Wall -Werror -Wno-error=unused-function -Wno-error=unused-variable \
       -Wno-error=unused-const-variable -Wno-error=uninitialized

.PHONY: all clean

all: vish test

bin/exec.o: exec.c exec.h colors.h
	$(CC) $(CFLAGS) -c exec.c -o bin/exec.o

bin/tokens.o: tokens.c tokens.h
	$(CC) $(CFLAGS) -c tokens.c -o bin/tokens.o

bin/token.o: token.c tokens.h
	$(CC) $(CFLAGS) -c token.c -o bin/token.o

bin/vish.o: vish.c line.h history.h tokens.h exec.h
	$(CC) $(CFLAGS) -c vish.c -o bin/vish.o

bin/list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c -o bin/list.o

bin/history.o: history.c history.h
	$(CC) $(CFLAGS) -c history.c -o bin/history.o

bin/line.o: line.o
	cp line.o bin/line.o

test: test.c
	$(CC) $(CFLAGS) test.c -o test

vish: bin/vish.o bin/tokens.o bin/token.o bin/list.o bin/exec.o bin/history.o bin/line.o
	$(CC) $(CFLAGS) bin/vish.o bin/tokens.o bin/token.o bin/list.o bin/line.o bin/exec.o bin/history.o -o vish -lreadline

clean:
	rm -f bin/*.o vish test
