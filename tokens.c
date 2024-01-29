#include "tokens.h"

#define MAX_TOKENS 50
#define MAX_TOKEN_LEN 100

// parse the given line into tokens and return the number of tokens
static int parseTokens(const char **line, char **tokens) {

    int cnt = 0;

    // BEGIN STUDENT IMPLEMENTATION

    // while the end of the line is not reached
    {
        // skip any spaces before the token

        // if the end of the line was not reached, get the next token

        // skip any spaces after the token
    }

    // terminate the tokens array with an extra null pointer

    // END STUDENT IMPLEMENTATION

    return cnt;
}

// break the line into tokens
int getTokens(const char *line, char ***tokens) {

    int cnt = 0;

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION

    return cnt;
}

// free the memory allocated for the tokens

void freeTokens(char ***tokens) {

    // BEGIN STUDENT IMPLEMENTATION

    // if there is anything to free
    {
        // free each token in the array

        // free the token array
    }

    // END STUDENT IMPLEMENTATION
}