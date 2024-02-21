#include "history.h"
#include "list.h"

#include <stddef.h>

static node_t **history = NULL; // head of the history list
static node_t *at; // current position in the history (for the up/down keys)

// handle the up/down keys. key is 'A' for up arrow and 'B' for down arrow
int handleHistoryKeys(int count, int key) {

    // BEGIN STUDENT IMPLEMENTATION
    if (history == NULL)
        return 0;

    if (key == 'A') {
        if (at == NULL)
            at = *history;
        else if (getPrev(at) != NULL)
            at = getPrev(at);
    } else if (key == 'B') {
        if (at != NULL && getNext(at) != NULL)
            at = getNext(at);
    }
    // END STUDENT IMPLEMENTATION

    return 0; // always returns 0
}

// add a line to the history
void addToHistory(const char *line) {

    // BEGIN STUDENT IMPLEMENTATION
    if (history == NULL)
        return;

    char *newLine = strdup(line);
    insertBack(history, newLine);
    // END STUDENT IMPLEMENTATION
}

// initialize the history
void initHistory() {

    // BEGIN STUDENT IMPLEMENTATION
    if (history == NULL)
        history = newList();
    resetHistory();
    // END STUDENT IMPLEMENTATION
}

// free the history
void freeHistory() {

    // BEGIN STUDENT IMPLEMENTATION
    if (history == NULL)
        return;

    freeList(history, NULL);
    history = NULL;
    // END STUDENT IMPLEMENTATION
}

// reset the current position in the history
void resetHistory() {

    // BEGIN STUDENT IMPLEMENTATION
 at = NULL;
    // END STUDENT IMPLEMENTATION
}

// print a line to the console
static void printLine(void *line) {

    // BEGIN STUDENT IMPLEMENTATION
printf("%s\n", (char *)line);
    // END STUDENT IMPLEMENTATION
}

// print the full history to the console
void printHistory() {

    // BEGIN STUDENT IMPLEMENTATION
    if (history == NULL)
        return;

    printList(*history, printLine);
    // END STUDENT IMPLEMENTATION
}
