// make the parent create 3 children processes, and the children will
// execute the commands (parent will do nothing
// TwoPipesThreeChildren.cpp
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    pid_t c1 = fork();
    if (c1 == 0) {
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[0]); close(pipe1[1]);
        close(pipe2[0]); close(pipe2[1]);
        char *args[] = {(char *)"ls", (char *)"-ltr", NULL};
        execvp(args[0], args);
        exit(1);
    }

    pid_t c2 = fork();
    if (c2 == 0) {
        dup2(pipe1[0], STDIN_FILENO);
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe1[0]); close(pipe1[1]);
        close(pipe2[0]); close(pipe2[1]);
        char *args[] = {(char *)"grep", (char *)"3377", NULL};
        execvp(args[0], args);
        exit(1);
    }

    pid_t c3 = fork();
    if (c3 == 0) {
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe1[0]); close(pipe1[1]);
        close(pipe2[0]); close(pipe2[1]);
        char *args[] = {(char *)"wc", (char *)"-l", NULL};
        execvp(args[0], args);
        exit(1);
    }
    // Parent does nothing

    close(pipe1[0]); close(pipe1[1]);
    close(pipe2[0]); close(pipe2[1]);
    wait(NULL); wait(NULL); wait(NULL);
    return 0;
}