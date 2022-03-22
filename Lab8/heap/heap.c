
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
     
     if (heap == NULL || element == NULL){
        return false;     
    }
     
             
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
    bool swapped  =  swap(heap->list, heap->list->size -1, 0);

    if (swapped == false){
        return NULL;    
    }
    
    //removing the last node

    void* removed = alist_remove(heap->list, heap->list->size -1);
    bool heapified;  
   //  printf("\nhello\n");
      if (removed == NULL){
           return NULL;
      }
      else {
       //    printf("\nhello\n");
         heapified = _heapify(heap, 0);    
      }

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


bool _heapify(Heap* heap, int index){    
  
    if (heap == NULL){
        return false;    
    }
    
    //it should be heapified by default
    if ( heap->list->size == 0 || heap->list->size == 1){
        
        return true;    
    }

    int topi = index;
    int leftChildi = (2*index)+1;
    int rightChildi = (2*index)+2;
    

    if ( topi < 0 || leftChildi < 0 || leftChildi < 0 || topi > heap->list->size || leftChildi > heap->list->size || rightChildi > heap->list->size){
        return false;
    }
  
    void* top = alist_get(heap->list, topi);
    void* leftChild = alist_get(heap->list, leftChildi);
    void* rightChild = alist_get(heap->list, rightChildi);
  
    if (top == NULL){
        
            return false;
    }
    
   //  printf("\n Left child if statement\n");
    if ( leftChild != NULL && heap->compare(leftChild, top) > 0){ 
           
        topi = leftChildi;    
        top = leftChild;
    }

    // printf("\nRight child if statement\n");

    if (  rightChild != NULL && heap->compare(rightChild, top) > 0){
        
       // printf("\nRight child if statement\n");
        topi = rightChildi;
        top = rightChild;
    }

     //just in case the topi value was changed
   if (topi != index){
       swap(heap->list, index, topi);
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
    
    //we need if statments here in order to progress, because this might cause a seg fault

    void* pelement = alist_get(heap->list, pindex);
    void* element = alist_get(heap->list, index);

    //no need to heapify
    if (heap->list->size == 1){
        return true;    
    }

    if (index < 0 ){
        return false;    
    }

    if (element == NULL || pelement == NULL){
        return false;    
     }

    int c =  heap->compare(pelement, element);

    if (c >= 0){
        
       return true;    
    }

    else {
        
        swap(heap->list, index, pindex);
        return _heapify_up(heap, pindex);
    }
    
}



