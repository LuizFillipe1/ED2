CFLAGS=-O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow
LIBS=-lm
EXECUTAVEL=ED2

all: $(EXECUTAVEL)

$(EXECUTAVEL): main.o bmais.o
	gcc main.o bmais.o $(LIBS) -o $(EXECUTAVEL)

bmais.o: bmais.c
	gcc $(CFLAGS) -c bmais.c

main.o: main.c
	gcc $(CFLAGS) -c main.c

clean:
	rm -rs *.o *~ bmais

run: $(EXECUTAVEL)
	./$(EXECUTAVEL)
