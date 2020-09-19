CC=gcc 
CFLAGS=-Wall -Werror=vla -Wextra -Wshadow -Wswitch-default -std=gnu11 -fsanitize=address 
TARGET=map

.PHONY: clean
.PHONY: test1

all: $(TARGET)

clean:
	rm -f $(TARGET) 
	rm -f *.o
	rm -f ./src/*.o
	rm -f ./test/*.o

#This will test constructing the map and destroying it.
test1:
	./map 1

#This will test putting and getting the value from the map.
test2:
	./map 2

#This will test remove function.
test3:
	./map 3

#This will test size function.
test4:
	./map 4

#compiling

./src/helper.o: ./src/helper.c
	$(CC) -c $(CFLAGS) $^ -o $@

./src/linkedlist.o: ./src/linked_list.c
	$(CC) -c $(CFLAGS) $^ -o $@

./test/test.o: ./test/test.c
	$(CC) -c $(CFLAGS) $^ -o $@

map: ./src/linkedlist.o ./src/helper.o ./test/test.o
	$(CC) $(CFLAGS) $^ -o $@	