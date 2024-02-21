#include "exec.h"
#include "colors.h"

#include <sys/types.h> // I think that this is a missing header, beacause pid_t is not working properly without it
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// print an error message in red color to stderr
void error(const char *cmd, int err) {
    fprintf(stderr, "%s%s: %s\n%s", RED, cmd, strerror(err), RESET);
}

static const char *colors[] = {BLUE, YELLOW, MAGENTA, CYAN};
static const int numColors = sizeof(colors) / sizeof(char *);

// return a string containing a random color
// the color must be different from the last one that was returned
static const char *randomColor() {

    int color;

    // BEGIN STUDENT IMPLEMENTATION
    color = rand() % numColors;

    // END STUDENT IMPLEMENTATION

    return colors[color];
}

// execute the process with execvp and exit with exit code errno if failed
static void child(char **argv, const int *pipefd) {

    // BEGIN STUDENT IMPLEMENTATION
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
    // END STUDENT IMPLEMENTATION

    exit(errno);
}

// read the input from the pipe and print it to stdout
// each *graphic* character must be in a different color than the last
// note: see `isgraph()` in ctype.h
static void readPipe(const int *pipefd) {

    char ch;

    // BEGIN STUDENT IMPLEMENTATION
    const char *currentColor = NULL;
    while (read(pipefd[0], &ch, 1) > 0) {
        if (isgraph(ch)) {
            const char *nextColor = randomColor();
            if (currentColor != nextColor) {
                currentColor = nextColor;
                printf("%s", currentColor);
            }
        }
        printf("%c", ch);
        fflush(stdout);
    }

    close(pipefd[0]); // Close the read end of the pipe
    // END STUDENT IMPLEMENTATION
}

// handle the input from the pipe until closed
// and then wait for the child process to terminate
static void parent(char *cmd, pid_t pid, const int *pipefd) {

    int status = 0; // store the exit status of the child

    // BEGIN STUDENT IMPLEMENTATION
    close(pipefd[1]); // Close the write end of the pipe
    readPipe(pipefd);
    close(pipefd[0]); // Close the read end of the pipe

    int status = 0; // store the exit status of the child
    waitpid(pid, &status, 0);

    // check the exit status of the child and print an error message if needed
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        error(cmd, WEXITSTATUS(status)); // error exit status
    // END STUDENT IMPLEMENTATION

    // check the exit status of the child and print an error message if needed
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        error(cmd, WEXITSTATUS(status)); // error exit status
}

// create a pipe, fork the process and call the child or parent function accordingly
void exec(char **argv) {

    // BEGIN STUDENT IMPLEMENTATION
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
    // END STUDENT IMPLEMENTATION
}
