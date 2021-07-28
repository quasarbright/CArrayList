#define INITIAL_CAPACITY 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int count;
    int capacity;
    int* data;
} ArrayList;

// fresh empty list
ArrayList * empty() {
    ArrayList *list = malloc(sizeof(ArrayList));
    int* data = malloc(INITIAL_CAPACITY * sizeof(int));
    if(list == NULL || data == NULL) {
        fprintf(stderr, "unable to create list\n");
        exit(1);
    }
    list->data = data;
    list->count = 0;
    list->capacity = INITIAL_CAPACITY;
    return list;
}

// grow a list (in place)
void grow(ArrayList *list) {
    // allocate an array with twice the size and copy the data over
    list->data = realloc(list->data, 2 * list->capacity * sizeof(int));
    list->capacity *= 2;
    if(list->data == NULL) {
        fprintf(stderr, "unable to grow list\n");
        exit(1);
    }
}

// add an element
void add(ArrayList *list, int element) {
    if(list->count >= list->capacity) {
        grow(list);
    }
    list->data[list->count] = element;
    list->count++;
}

// get an element
int get(ArrayList *list, int index) {
    if(index < 0 || index >= list->count) {
        fprintf(stderr, "index out of bounds\n");
        exit(1);
    } else {
        return list->data[index];
    }
}

// get the list's size
int size(ArrayList *list) {
    return list->count;
}

// print list with trailing commas
void printList(ArrayList *list) {
    printf("[");
    for(int i = 0; i < list->count; i++) {
        printf("%d,", get(list, i));
    }
    printf("]\n");
}

// delete the whole list (free list and internal array)
void del(ArrayList *list) {
    free(list->data);
    free(list);
}

int main() {
    ArrayList *list = empty();
    printList(list);
    for(int i = 0; i < 50; i++) {
        add(list,i);
        printList(list);
    }
    del(list);
    return 0;
}
