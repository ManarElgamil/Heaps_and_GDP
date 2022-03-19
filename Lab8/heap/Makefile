
COMPILER = gcc

CSTD = --std=c18

PREQ = array_list.o heap.o

MAIN = heapM.o

ARRAY_LIST = array_list/array_list.c array_list/array_list.h

HEAP = heap.c heap.h

INCLUDES = -I/array_list

all: heap rheap

rheap: $(PREQ) rheapM.o
	$(COMPILER) $(CSTD) $(PREQ) rheapM.o -o rheap

heap: $(PREQ) $(MAIN)
	$(COMPILER) $(CSTD) $(PREQ) $(MAIN) -o heap

array_list.o: $(ARRAY_LIST)
	$(COMPILER) $(CSTD) -c array_list/array_list.c -o array_list.o

heap.o: $(HEAP)
	$(COMPILER) $(CSTD) $(INCLUDES) -c heap.c -o heap.o


# the ones I need however are stack.o, queue.o array_list.o and ofcourse bintree.o

#clean:
#   rm -f $(PREQ) bintree










