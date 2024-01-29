#ifndef LIST_H
#define LIST_H

typedef struct node node_t;

node_t **newList();
void freeList(node_t **head, void (*freeData)(void *));
void printList(node_t *head, void (*printData)(void *));
void insertFront(node_t **head, void *data);
void insertBack(node_t **head, void *data);
void *deleteFront(node_t **head);
void *deleteBack(node_t **head);
void moveNodeToFront(node_t **list, node_t **at);
void moveToBack(node_t **list, node_t **at);

void movePrev(node_t **head);
node_t *getNext(node_t *node);
node_t *getPrev(node_t *node);
void *getData(node_t *node);
void *setData(node_t *node, void *data);

#endif // LIST_H