#include "list.h"

#include <stdio.h>

// tip: you can change data to be (char*) for easier debugging

typedef struct node {
    void *data;
    struct node *next, *prev;
} node_t;

// create a new node with the given data
static node_t *newNode(void *data) {

    node_t *node = NULL;

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION

    return node;
}

// insert the node at the given position
static void insertNode(node_t *node, node_t **at) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION
}

// detach the given node from the list and return it
static node_t *detachNode(node_t **at) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION

    return *at;
}

// delete the given node from the list and return its data
static void *deleteNode(node_t **at) {

    void *data = NULL;

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION

    return data;
}

// move the given node to the given to given position using the given insert function
static void moveNode(node_t **to, node_t **from, void (*insert)(node_t **, void *)) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION
}

// create a new empty list and return its head
node_t **newList() {

    node_t **head = NULL;

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION

    return head;
}

// free the given list and nullify the head
// note: freeData should not be null
void freeList(node_t **head, void (*freeData)(void *)) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION
}

// move the head of the list to the next node
void moveNext(node_t **head) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION
}

// move the head of the head to the previous node
void movePrev(node_t **head) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION
}

// return the node after the given node
node_t *getNext(node_t *node) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION

    return NULL;
}

// return the node before the given node
node_t *getPrev(node_t *node) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION

    return NULL;
}

// return the data at the given node
void *getData(node_t *node) {

    void *data = NULL;

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION

    return data;
}

// set the data at the given node and return the old data
void *setData(node_t *node, void *data) {

    void *oldData = NULL;

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION

    return oldData;
}

// insert a new node with the given data at the front of the list
void insertFront(node_t **head, void *data) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION
}

// insert a new node with the given data at the back of the list
void insertBack(node_t **head, void *data) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION
}

// delete the node at the front of the list and return its data
void *deleteFront(node_t **head) {

    void *data = NULL;

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION

    return data;
}

// delete the node at the back of the list and return its data
void *deleteBack(node_t **head) {

    void *data = NULL;

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION

    return data;
}

// move a node to the front of the list
void moveNodeToFront(node_t **list, node_t **at) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION
}

// move a node to the back of the list
void moveNodeToBack(node_t **list, node_t **at) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION
}

// print the list using the given print function
void printList(node_t *head, void (*printData)(void *)) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION
}