#include "tokens.h"

#define MAX_TOKENS 50
#define MAX_TOKEN_LEN 100

// parse the given line into tokens and return the number of tokens
static int parseTokens(const char **line, char **tokens) {

    int cnt = 0;

    // BEGIN STUDENT IMPLEMENTATION

    while (**line != '\0' && cnt < MAX_TOKENS - 1) {
        skipSpaces(line);

        if (**line == '\0') {
            break;
        }

        int tokenSize = parseToken(line, tokens[cnt]);
        if (tokenSize == 0) {
            break;
        }

        cnt++;
    }

    tokens[cnt] = 0;
    // END STUDENT IMPLEMENTATION

    return cnt;
}

// break the line into tokens
int getTokens(const char *line, char ***tokens) {

    int cnt = 0;

    // BEGIN STUDENT IMPLEMENTATION
    *tokens = (char **)malloc(MAX_TOKENS * sizeof(char *));
    if (*tokens == 0) {
        // Handle memory allocation error here
        return 0;
    }

    const char *currentLine = line;
    while (*currentLine != '\0' && cnt < MAX_TOKENS - 1) {
        (*tokens)[cnt] = (char *)malloc((MAX_TOKEN_LEN + 1) * sizeof(char));
        if ((*tokens)[cnt] == 0) {
            // Handle memory allocation error here
            freeTokens(tokens);
            return 0;
        }

        cnt++;
    }

    cnt = parseTokens(&line, *tokens);
    // END STUDENT IMPLEMENTATION

    return cnt;
}

// free the memory allocated for the tokens

void freeTokens(char ***tokens) {

    // BEGIN STUDENT IMPLEMENTATION

    if (*tokens != 0) {
        for (int i = 0; (*tokens)[i] != 0; i++) {
            free((*tokens)[i]);
        }
        free(*tokens);
        *tokens = 0;
    }
    // END STUDENT IMPLEMENTATION
}
