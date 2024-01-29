#include "history.h"
#include "list.h"

#include <stddef.h>

static node_t **history = NULL; // head of the history list
static node_t *at; // current position in the history (for the up/down keys)

// handle the up/down keys. key is 'A' for up arrow and 'B' for down arrow
int handleHistoryKeys(int count, int key) {

    // BEGIN STUDENT IMPLEMENTATION

    if (!history) {
        return 0; // if the history is empty, do nothing
    }

    // add the current line to the history if it is not already there
    addToHistory(getData(at));

    // go to the next or previous line in the history
    if (key == 'A') {
        movePrev(&at);
    } else if (key == 'B') {
        moveNext(&at);
    }

    // replace the current line with the line from the history
    replaceLine(getData(at));

    // END STUDENT IMPLEMENTATION

    return 0; // always returns 0
}

// add a line to the history
void addToHistory(const char *line) {

    // BEGIN STUDENT IMPLEMENTATION

    if (!history) {
        history = newList(); // if history is empty, create a new list
    }

    // add a new node if the line at the head is not empty and different from the new line
    if (getData(*history) != NULL && strcmp(line, getData(*history)) != 0) {
        insertFront(history, strdup(line));
    } else if (getData(*history) == NULL) {
        // replace the line at the head if it is empty and the next line is different from the new line
        node_t *next = getNext(*history);
        if (next != NULL && strcmp(line, getData(next)) != 0) {
            setData(*history, strdup(line));
        }
    }
    // END STUDENT IMPLEMENTATION
}

// initialize the history
void initHistory() {

    // BEGIN STUDENT IMPLEMENTATION
    history = NULL;
    at = NULL;
    // END STUDENT IMPLEMENTATION
}

// free the history
void freeHistory() {

    // BEGIN STUDENT IMPLEMENTATION
freeList(&history, free);
    // END STUDENT IMPLEMENTATION
}

// reset the current position in the history
void resetHistory() {

    // BEGIN STUDENT IMPLEMENTATION
at = history ? *history : NULL;
    // END STUDENT IMPLEMENTATION
}

// print a line to the console
static void printLine(void *line) {

    // BEGIN STUDENT IMPLEMENTATION
 if (line) {
        printf("%s\n", (char *)line);
    }
    // END STUDENT IMPLEMENTATION
}

// print the full history to the console
void printHistory() {

    // BEGIN STUDENT IMPLEMENTATION
printList(*history, printLine);
    // END STUDENT IMPLEMENTATION
}
