#include "tokens.h"

#include <stdbool.h>

// skip space in the line
void skipSpaces(const char **line) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION
}

// check if the current character is the end of the token
static bool isEnd(char c, char end) {
    
    bool res = false;
    
    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION

    return res;
}

// get the end character of the token (if quoted)
static char getEnd(char c) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION

    return c;
}

// copy a single token from line to token
// (move the line pointer forward until after the token)
static int parseToken(const char **line, char *token) {

    int si = 0, di = 0; // line and token index

    // BEGIN STUDENT IMPLEMENTATION

    // skip the quote character if the token is quoted

    // while the end of the token was not reached
    {
        // unescape characters as needed

        // copy the character to the destination token
    }

    // terminate the destination token string

    // skip the end quote character if the token is quoted

    // move line forward as needed

    // END STUDENT IMPLEMENTATION

    return di;
}

// get the next token from the string
void getToken(const char **line, char **token) {

    // BEGIN STUDENT IMPLEMENTATION

    // END STUDENT IMPLEMENTATION
}