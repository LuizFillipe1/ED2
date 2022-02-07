CFLAGS=-O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow
LIBS=-lm
EXECUTAVEL=ED2

all: $(EXECUTAVEL)

$(EXECUTAVEL): main.o Rubro.o
	gcc main.o Rubro.o $(LIBS) -o $(EXECUTAVEL)

Rubro.o: Rubro.c
	gcc $(CFLAGS) -c Rubro.c

main.o: main.c
	gcc $(CFLAGS) -c main.c

clean:
	rm -rs *.o *~ Rubro

run: $(EXECUTAVEL)
	./$(EXECUTAVEL)

all: $(EXECUTAVEL)
	./$(EXECUTAVEL) <arq.in