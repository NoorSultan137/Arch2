#include "line.h"
#include "history.h"
#include "colors.h"
#include "tokens.h"
#include "exec.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// change the current directory as specified by tokens and return a new prompt if needed
const char *cd(char **tokens, const char *prompt) {

    // BEGIN STUDENT IMPLEMENTATION


    // END STUDENT IMPLEMENTATION

    tokens = NULL; // suppress unused parameter warning

    return prompt;
}

int main() {
    const char *line;
    char **tokens = NULL;

    // initialize the line and history modules
    initLine(GREEN, BOLD_WHITE, BOLD_BLUE, CYAN, BOLD_RED);
    initHistory();

    const char *prompt = getPrompt(); // get the initial prompt
    while ((line = getLine(prompt)) != NULL && strcmp(line, "exit") != 0) {
        addToHistory(line); // add the line to the history if needed
        if (getTokens(line, &tokens) > 0) {
            if (strcmp((*&tokens)[0], "ls") == 0 && (*&tokens)[1] == NULL)
                // make ls output look like it does on a normal terminal
                exec((char *[]) {"ls", "-C", NULL});
            else if (strcmp((*&tokens)[0], "cd") == 0)
                prompt = cd(tokens, prompt); // handle change directory
            else if (strcmp((*&tokens)[0], "history") == 0)
                printHistory(); // print all lines in history
            else
                exec((*&tokens)); // execute the given command
            freeTokens(&tokens);
        }
    }
    printf("exit\n");

    // free the line and history modules resources
    freeHistory();
    freeLine();

    return EXIT_SUCCESS;
}
