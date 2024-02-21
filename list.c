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
    node = (node_t *)malloc(sizeof(node_t));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
        node->prev = NULL;
    }
    // END STUDENT IMPLEMENTATION

    return node;
}

// insert the node at the given position
static void insertNode(node_t *node, node_t **at) {

    // BEGIN STUDENT IMPLEMENTATION
    if (*at == NULL) {
        *at = node;
        return;
    }
    node->next = *at;
    node->prev = (*at)->prev;
    if ((*at)->prev != NULL)
        (*at)->prev->next = node;
    (*at)->prev = node;
    *at = node;
    // END STUDENT IMPLEMENTATION
}

// detach the given node from the list and return it
static node_t *detachNode(node_t **at) {

    // BEGIN STUDENT IMPLEMENTATION
    node_t *node = *at;
    if (node != NULL) {
        if (node->prev != NULL)
            node->prev->next = node->next;
        if (node->next != NULL)
            node->next->prev = node->prev;
    }
    *at = NULL;
    return node;
    // END STUDENT IMPLEMENTATION

    return *at;
}

// delete the given node from the list and return its data
static void *deleteNode(node_t **at) {

    void *data = NULL;

    // BEGIN STUDENT IMPLEMENTATION
    node_t *node = detachNode(at);
    if (node != NULL) {
        data = node->data;
        free(node);
    }
    return data;
    // END STUDENT IMPLEMENTATION

    return data;
}

// move the given node to the given to given position using the given insert function
static void moveNode(node_t **to, node_t **from, void (*insert)(node_t **, void *)) {

    // BEGIN STUDENT IMPLEMENTATION
    node_t *node = detachNode(from);
    if (node != NULL)
        insert(to, node->data);
    // END STUDENT IMPLEMENTATION
}

// create a new empty list and return its head
node_t **newList() {

    node_t **head = NULL;

    // BEGIN STUDENT IMPLEMENTATION
    head = (node_t **)malloc(sizeof(node_t *));
    if (head != NULL)
        *head = NULL;
    // END STUDENT IMPLEMENTATION

    return head;
}

// free the given list and nullify the head
// note: freeData should not be null
void freeList(node_t **head, void (*freeData)(void *)) {

    // BEGIN STUDENT IMPLEMENTATION
    if (*head == NULL)
        return;

    node_t *current = *head;
    while (current != NULL) {
        node_t *next = current->next;
        if (freeData != NULL)
            freeData(current->data);
        free(current);
        current = next;
    }
    *head = NULL;
    // END STUDENT IMPLEMENTATION
}

// move the head of the list to the next node
void moveNext(node_t **head) {

    // BEGIN STUDENT IMPLEMENTATION
    if (*head != NULL)
        *head = (*head)->next;
    // END STUDENT IMPLEMENTATION
}

// move the head of the head to the previous node
void movePrev(node_t **head) {

    // BEGIN STUDENT IMPLEMENTATION
    if (*head != NULL)
        *head = (*head)->prev;
    // END STUDENT IMPLEMENTATION
}

// return the node after the given node
node_t *getNext(node_t *node) {

    // BEGIN STUDENT IMPLEMENTATION
    if (node != NULL)
        return node->next;
    return NULL;
    // END STUDENT IMPLEMENTATION

    return NULL;
}

// return the node before the given node
node_t *getPrev(node_t *node) {

    // BEGIN STUDENT IMPLEMENTATION
    if (node != NULL)
        return node->prev;
    return NULL;
    // END STUDENT IMPLEMENTATION

    return NULL;
}

// return the data at the given node
void *getData(node_t *node) {

    void *data = NULL;

    // BEGIN STUDENT IMPLEMENTATION
    if (node != NULL)
        return node->data;
    return NULL;
    // END STUDENT IMPLEMENTATION

    return data;
}

// set the data at the given node and return the old data
void *setData(node_t *node, void *data) {

    void *oldData = NULL;

    // BEGIN STUDENT IMPLEMENTATION
    if (node != NULL) {
        oldData = node->data;
        node->data = data;
    }
    return oldData;
    // END STUDENT IMPLEMENTATION

    return oldData;
}

// insert a new node with the given data at the front of the list
void insertFront(node_t **head, void *data) {

    // BEGIN STUDENT IMPLEMENTATION
    node_t *new_node = newNode(data);
    if (new_node != NULL) {
        insertNode(new_node, head);
    }
    // END STUDENT IMPLEMENTATION
}

// insert a new node with the given data at the back of the list
void insertBack(node_t **head, void *data) {

    // BEGIN STUDENT IMPLEMENTATION
    node_t *new_node = newNode(data);
    if (new_node != NULL) {
        if (*head == NULL) {
            *head = new_node;
        } else {
            node_t *last = *head;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = new_node;
            new_node->prev = last;
        }
    }
    // END STUDENT IMPLEMENTATION
}

// delete the node at the front of the list and return its data
void *deleteFront(node_t **head) {

    void *data = NULL;

    // BEGIN STUDENT IMPLEMENTATION
    if (*head != NULL) {
        node_t *temp = *head;
        *head = (*head)->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        data = temp->data;
        free(temp);
    }
    return data;
    // END STUDENT IMPLEMENTATION

    return data;
}

// delete the node at the back of the list and return its data
void *deleteBack(node_t **head) {

    void *data = NULL;

    // BEGIN STUDENT IMPLEMENTATION
    if (*head != NULL) {
        node_t *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        if (temp->prev != NULL) {
            temp->prev->next = NULL;
        }
        data = temp->data;
        free(temp);
    }
    return data;
    // END STUDENT IMPLEMENTATION

    return data;
}

// move a node to the front of the list
void moveNodeToFront(node_t **list, node_t **at) {

    // BEGIN STUDENT IMPLEMENTATION
    if (*at == NULL || *at == *list)
        return;

    detachNode(at);
    insertNode(*at, list);
    // END STUDENT IMPLEMENTATION
}

// move a node to the back of the list
void moveNodeToBack(node_t **list, node_t **at) {

    // BEGIN STUDENT IMPLEMENTATION
    if (*at == NULL || *at == *list)
        return;

    detachNode(at);
    if (*list == NULL) {
        *list = *at;
        return;
    }

    node_t *temp = *list;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = *at;
    (*at)->prev = temp;
    *at = NULL;
    // END STUDENT IMPLEMENTATION
}

// print the list using the given print function
void printList(node_t *head, void (*printData)(void *)) {

    // BEGIN STUDENT IMPLEMENTATION
    if (head == NULL)
        return;

    node_t *current = head;
    while (current != NULL) {
        printData(current->data);
        current = current->next;
    }
    // END STUDENT IMPLEMENTATION
}
