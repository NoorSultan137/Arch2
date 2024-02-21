#include "tokens.h"

#define MAX_TOKENS 50
#define MAX_TOKEN_LEN 100

// Parse the given line into tokens and return the number of tokens
static int parseTokens(const char **line, char **tokens) {
    int cnt = 0;
    const char *start = *line;

    // Skip leading spaces
    while (**line == ' ')
        (*line)++;

    // Extract tokens
    while (**line != '\0' && cnt < MAX_TOKENS - 1) {
        const char *tokenStart = *line;

        // Find token end
        while (**line != '\0' && **line != ' ')
            (*line)++;

        // Copy token to tokens array
        int tokenLen = *line - tokenStart;
        for (int i = 0; i < tokenLen && i < MAX_TOKEN_LEN; i++)
            tokens[cnt][i] = tokenStart[i];
        tokens[cnt][tokenLen] = '\0';

        cnt++;

        // Skip spaces until next token
        while (**line == ' ')
            (*line)++;
    }

    // Null-terminate tokens array
    tokens[cnt] = 0;

    // Restore line pointer
    *line = start;

    return cnt;
}

// Break the line into tokens
int getTokens(const char *line, char ***tokens) {
    int cnt = 0;
    char *tokenArray[MAX_TOKENS];

    // Parse tokens
    cnt = parseTokens(&line, tokenArray);

    // Copy tokens to output parameter
    for (int i = 0; i < cnt; i++)
        (*tokens)[i] = tokenArray[i];
    (*tokens)[cnt] = 0;

    return cnt;
}

// Free the memory allocated for the tokens
void freeTokens(char ***tokens) {
    // Loop through the token array and set each element to NULL
    for (int i = 0; (*tokens)[i] != 0 && i < MAX_TOKENS; i++) {
        // Loop through each character in the token and set it to '\0'
        for (int j = 0; (*tokens)[i][j] != '\0' && j < MAX_TOKEN_LEN; j++) {
            (*tokens)[i][j] = '\0';
        }
        // Set the pointer to NULL
        (*tokens)[i] = 0;
    }
}

