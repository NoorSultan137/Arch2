#include "exec.h"
#include "colors.h"

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

    do {
        color = rand() % numColors;
    } while (color == lastColor);

    lastColor = color;
    
    // END STUDENT IMPLEMENTATION

    return colors[color];
}

// execute the process with execvp and exit with exit code errno if failed
static void child(char **argv, const int *pipefd) {

    // BEGIN STUDENT IMPLEMENTATION

    close(pipefd[0]); // close read end of the pipe
    dup2(pipefd[1], STDOUT_FILENO); // redirect stdout to the pipe
    dup2(pipefd[1], STDERR_FILENO); // redirect stderr to the pipe
    close(pipefd[1]); // close the write end of the pipe

    execvp(argv[0], argv); // execute the process

    // if execvp fails, print an error message in red
    fprintf(stderr, "%s%s: %s\n%s", RED, argv[0], strerror(errno), RESET);
    // END STUDENT IMPLEMENTATION

    exit(errno);
}

// read the input from the pipe and print it to stdout
// each *graphic* character must be in a different color than the last
// note: see `isgraph()` in ctype.h
static void readPipe(const int *pipefd) {

    char ch;

    // BEGIN STUDENT IMPLEMENTATION

    const char *currentColor = randomColor();
    while (read(pipefd[0], &ch, 1) > 0) {
        if (isgraph(ch)) {
            printf("%s%c", currentColor, ch);
            fflush(stdout);
            currentColor = randomColor();
        } else {
            printf("%c", ch);
            fflush(stdout);
        }
    }
    printf("%s", RESET); // reset color at the end
}
    // END STUDENT IMPLEMENTATION
}

// handle the input from the pipe until closed
// and then wait for the child process to terminate
static void parent(char *cmd, pid_t pid, const int *pipefd) {

    int status = 0; // store the exit status of the child

    // BEGIN STUDENT IMPLEMENTATION

    close(pipefd[1]); // close write end of the pipe

    // handle input from the pipe
    readPipe(pipefd);

    // wait for the child to terminate
    waitpid(pid, &status, 0);

    // END STUDENT IMPLEMENTATION

    // check the exit status of the child and print an error message if needed
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        error(cmd, WEXITSTATUS(status)); // error exit status
}

// create a pipe, fork the process and call the child or parent function accordingly
void exec(char **argv) {

    // BEGIN STUDENT IMPLEMENTATION

    int pipefd[2];
    pid_t pid;

    // create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    // fork the process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }

    if (pid == 0) {
        // in child process
        child(argv, pipefd);
    } else {
        // in parent process
        parent(argv[0], pid, pipefd);
    }
    // END STUDENT IMPLEMENTATION
}
