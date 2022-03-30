EXECUTAVEL=ED2

all: $(EXECUTAVEL)

$(EXECUTAVEL): main.o trie.o
	gcc main.o trie.o -o $(EXECUTAVEL)

trie.o: trie.c
	gcc -c trie.c

main.o: main.c
	gcc -c main.c

clean:
	rm -rs *.o *~ trie

run: $(EXECUTAVEL)
	./$(EXECUTAVEL)
