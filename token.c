#include "tokens.h"

#include <stdbool.h>

// skip space in the line
void skipSpaces(const char **line) {

    // BEGIN STUDENT IMPLEMENTATION
    while (**line == ' ')
        (*line)++;
    // END STUDENT IMPLEMENTATION
}

// check if the current character is the end of the token
static bool isEnd(char c, char end) {
    
    bool res = false;
    
    // BEGIN STUDENT IMPLEMENTATION
    if (c == end || c == '\0' || c == ' ')
        res = true;
    // END STUDENT IMPLEMENTATION

    return res;
}

// get the end character of the token (if quoted)
static char getEnd(char c) {

    // BEGIN STUDENT IMPLEMENTATION
    if (c == '\'')
        return '\'';
    else if (c == '\"')
        return '\"';
    else
        return ' ';
    // END STUDENT IMPLEMENTATION

    return c;
}

// copy a single token from line to token
// (move the line pointer forward until after the token)
static int parseToken(const char **line, char *token) {

    int si = 0, di = 0; // line and token index

    // BEGIN STUDENT IMPLEMENTATION

    // skip the quote character if the token is quoted
    char end = getEnd(**line);
    if (**line == '\'' || **line == '\"')
        (*line)++;

    // while the end of the token was not reached
    while (!isEnd((*line)[si], end)) {
        // unescape characters as needed
        if ((*line)[si] == '\\') {
            si++;
            if ((*line)[si] != '\0')
                token[di++] = (*line)[si++];
        } else {
            // copy the character to the destination token
            token[di++] = (*line)[si++];
        }
    }

    // terminate the destination token string
    token[di] = '\0';

    // skip the end quote character if the token is quoted
    if (**line == '\'' || **line == '\"')
        (*line)++;

    // move line forward as needed
    while (!isEnd((*line)[si], end))
        si++;

    (*line) += si;
    // END STUDENT IMPLEMENTATION

    return di;
}

// get the next token from the string
void getToken(const char **line, char **token) {

    // BEGIN STUDENT IMPLEMENTATION
    skipSpaces(line);

    int tokenSize = 0;
    while (!isEnd((*line)[tokenSize], ' ')) {
        tokenSize++;
    }

    if (tokenSize == 0) {
        *token = 0;
        return;
    }

    // Define a fixed-size buffer for the token within the function scope
    char tokenBuffer[tokenSize + 1];
    // Copy the characters from line to tokenBuffer
    for (int i = 0; i < tokenSize; i++) {
        tokenBuffer[i] = (*line)[i];
    }
    // Null-terminate the token buffer
    tokenBuffer[tokenSize] = '\0';
    // Assign the token buffer to the output token
    *token = tokenBuffer;

    *line += tokenSize;
    // END STUDENT IMPLEMENTATION
}
