#ifndef LINE_H
#define LINE_H

void initLine(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5);
void freeLine();
const char *getPrompt();
const char *getLine(const char *prompt);
void replaceLine(char *line);

#endif // LINE_H