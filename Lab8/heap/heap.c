
#include "heap.h"
#include "array_list/array_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

Heap* heap_initialize(int dataSize, char* dataName, int (*compare)(void*, void*), void (*print)(void*)){
    
    Heap* heap = malloc(sizeof(Heap));
    ArrayList* list = alist_initialize(15, dataSize, dataName);

    heap->list = list;
    heap->compare = compare;
    heap->print = print;
    
    return heap;
}

bool heap_insert(Heap* heap, void* element){
     
     if (heap->list->size == 0){
        alist_add(heap->list,element);
        return true;    
     }
     else {
     
     //okay so        
     alist_add_at(heap->list, (heap->list->size), element);

     //then we heapify up
     return _heapify_up(heap, (heap->list->size-1));
     }
}

void* heap_remove(Heap* heap){
    
    //swapping the root node with the last node
    swap(heap->list, heap->list->size -1, 0);
    
    //removing the last node

    void* removed = alist_remove(heap->list, heap->list->size -1);
    
   //  printf("before going to heapify:  ");    

   // for (int i = 0; i < heap->list->size ; i++ ){
        
   //     heap->print(alist_get(heap->list, i));    
   // }

  //  printf("\n\n");
    
    //then we heapify down

 //   printf("hi");
    _heapify(heap, 0);

  //  printf("After going to heapify:  ");

  //   for (int i = 0; i < heap->list->size ; i++ ){

//         heap->print(alist_get(heap->list, i));
//     }
    
  //   printf("\n\n");
    return removed;
}

void* heap_peek(Heap* heap){
    
    return alist_get(heap->list, 0);
}

int heap_size(Heap* heap){
    
    return heap->list->size;
}

bool heap_contains(Heap* heap, void* element){
    
    int isFound = alist_index_of(heap->list, element);

    if (isFound == -1){
        
        return false;    
    }
    else {
        
        return true;
    }    
}

//will be used in the above function, and then this contract should be complete

bool _heapify(Heap* heap, int index){
    
  //  printf("hello ");
        
    int topi = index;
    int leftChildi = (2*index)+1;
    int rightChildi = (2*index)+2;

  //  printf("hello ");

    void* top = alist_get(heap->list, topi);
    void* leftChild = alist_get(heap->list, leftChildi);
    void* rightChild = alist_get(heap->list, rightChildi);
  //  heap->print(top);

    if (heap->compare(leftChild, top) > 0){ 
           
        topi = leftChildi;    
    }

    //just in case the topi value was changed 
    top =  alist_get(heap->list, topi);

   // heap->print(top);

    if (heap->compare(rightChild, top) > 0){
        
        topi = rightChildi;
    }

     //just in case the topi value was changed
     top = alist_get(heap->list, topi);

    //  heap->print(top);

   if (topi != index){
      // heap->print(top);
       swap(heap->list, topi, index);
       return _heapify(heap, topi);
   }
   else {
        return true;   
    }
}

bool _heapify_up(Heap* heap, int index){
    
    int pindex = (index-1)/2;

    //so first we get the elements at these indexes and then we compare them using the
    //the compare function in the heap
    
    void* pelement = alist_get(heap->list, pindex);
    void* element = alist_get(heap->list, index);

    while (index > 0 && heap->compare(pelement, element) < 0){

        swap(heap->list, index, pindex);  
        index = pindex;
        pindex = (index -1)/2;
        pelement = alist_get(heap->list, pindex);   
    }
         
    return true;
}



