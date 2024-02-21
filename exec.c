#include "exec.h"
#include "colors.h"

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h> // Added for isgraph

// Print an error message in red color to stderr
void error(const char *cmd, int err) {
    fprintf(stderr, "%s%s: %s\n%s", RED, cmd, strerror(err), RESET);
}

static const char *colors[] = {BLUE, YELLOW, MAGENTA, CYAN};
static const int numColors = sizeof(colors) / sizeof(char *);

// Return a string containing a random color
// The color must be different from the last one that was returned
static const char *randomColor() {
    static int prevColorIndex = -1; // Initialize to an invalid index

    int color;
    do {
        color = rand() % numColors;
    } while (color == prevColorIndex);

    prevColorIndex = color;
    return colors[color];
}

// Execute the process with execvp and exit with exit code errno if failed
static void child(char **argv, const int *pipefd) {
    close(pipefd[0]); // Close the read end of the pipe

    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(errno);
    }

    close(pipefd[1]); // Close the write end of the pipe

    execvp(argv[0], argv);
    // If execvp returns, it means an error occurred
    perror("execvp");
    exit(errno);
}

// Read the input from the pipe and print it to stdout
// Each *graphic* character must be in a different color than the last
// Note: see `isgraph()` in ctype.h
static void readPipe(const int *pipefd) {
    char ch;

    const char *currentColor = NULL;
    ssize_t bytesRead;

    while ((bytesRead = read(pipefd[0], &ch, 1)) > 0) {
        if (isgraph(ch)) { // Check if the character is printable
            const char *nextColor = randomColor();
            if (currentColor != nextColor) {
                currentColor = nextColor;
                printf("%s", currentColor);
            }
        }
        printf("%c", ch);
        fflush(stdout);
    }

    if (bytesRead == -1) {
        perror("read");
    }

    close(pipefd[0]); // Close the read end of the pipe
}

// Handle the input from the pipe until closed
// and then wait for the child process to terminate
static void parent(char *cmd, pid_t pid, const int *pipefd) {
    close(pipefd[1]); // Close the write end of the pipe
    readPipe(pipefd);
    close(pipefd[0]); // Close the read end of the pipe
}

// Create a pipe, fork the process and call the child or parent function accordingly
void exec(char **argv) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(errno);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(errno);
    }

    if (pid == 0) {
        // Child process
        child(argv, pipefd);
    } else {
        // Parent process
        parent(argv[0], pid, pipefd);
    }
}
