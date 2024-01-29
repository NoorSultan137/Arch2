#ifndef HISTORY_H
#define HISTORY_H

void initHistory();
void freeHistory();
void resetHistory();
void addToHistory(const char *line);
void printHistory();
int handleHistoryKeys(int count, int key);

#endif // HISTORY_H