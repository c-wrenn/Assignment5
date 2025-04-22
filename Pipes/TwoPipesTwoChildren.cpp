// Version 1
// Use one parent and two children to do the work
// TwoPipesTwoChildren.cpp
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    pid_t child1 = fork();

    if (child1 == 0) {
        // First child: executes "ls -ltr"
        dup2(pipe1[1], STDOUT_FILENO); // stdout → pipe1 write end
        close(pipe1[0]); close(pipe1[1]);
        close(pipe2[0]); close(pipe2[1]);
        char *args[] = {(char *)"ls", (char *)"-ltr", NULL};
        execvp(args[0], args);
        perror("exec ls");
        exit(1);
    }

    pid_t child2 = fork();

    if (child2 == 0) {
        // Second child: executes "grep 3377"
        dup2(pipe1[0], STDIN_FILENO);  // stdin ← pipe1 read end
        dup2(pipe2[1], STDOUT_FILENO); // stdout → pipe2 write end
        close(pipe1[1]); close(pipe1[0]);
        close(pipe2[0]); close(pipe2[1]);
        char *args[] = {(char *)"grep", (char *)"3377", NULL};
        execvp(args[0], args);
        perror("exec grep");
        exit(1);
    }

    // Parent: executes "wc -l"
    dup2(pipe2[0], STDIN_FILENO); // stdin ← pipe2 read end
    close(pipe1[0]); close(pipe1[1]);
    close(pipe2[0]); close(pipe2[1]);
    char *args[] = {(char *)"wc", (char *)"-l", NULL};
    execvp(args[0], args);
    perror("exec wc");
    return 1;
}