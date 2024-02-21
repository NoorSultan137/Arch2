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

    const char *newPrompt = prompt;

    if (tokens[1] == NULL) {
        fprintf(stderr, "vish: cd: missing argument\n");
    } else if (tokens[2] != NULL) {
        fprintf(stderr, "vish: cd: too many arguments\n");
    } else {
        newPrompt = tokens[1];
    }

    return newPrompt;
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


//I defined the 4 functions initLine(), freeLine(), getPrompt(), getLine(), since they are not defined anywhere in the program.

// Static variables to store prompt and colors
static const char *prompt = "> ";
static const char *color1 = RED;
static const char *color2 = GREEN;
static const char *color3 = YELLOW;
static const char *color4 = BLUE;
static const char *color5 = BOLD_RED;

void initLine(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5) {
    color1 = c1;
    color2 = c2;
    color3 = c3;
    color4 = c4;
    color5 = c5;
}

void freeLine() {
    // You may add cleanup logic here if needed
}

const char *getPrompt() {
    return prompt;
}

const char *getLine(const char *prompt) {
    char *line = NULL;
    size_t len = 0;

    printf("%s", prompt);
    if (getline(&line, &len, stdin) == -1) {
        free(line);
        return NULL;
    }

    // Remove newline character if present
    if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }

    return line;
}
