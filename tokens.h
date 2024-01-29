#ifndef TOKENS_H
#define TOKENS_H

int getTokens(const char *line, char ***tokens);
void freeTokens(char ***tokens);
void skipSpaces(const char **line);
void getToken(const char **line, char **token);

#endif // TOKENS_H