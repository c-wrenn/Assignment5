// DynPipe.cpp
#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_CMDS 5

std::vector<char*> parseCommand(const std::string &cmd) {
    std::istringstream iss(cmd);
    std::vector<std::string> parts;
    std::string part;
    while (iss >> part) parts.push_back(part);

    std::vector<char*> args;
    for (auto &s : parts)
        args.push_back(strdup(s.c_str()));
    args.push_back(nullptr);
    return args;
}

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > MAX_CMDS + 1) {
        std::cerr << "Error: Must provide between 2 and 5 piped commands.\n";
        return 1;
    }

    int num_cmds = argc - 1;
    int pipes[MAX_CMDS - 1][2];

    for (int i = 0; i < num_cmds - 1; i++)
        pipe(pipes[i]);

    for (int i = 0; i < num_cmds; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Set up input pipe if not first command
            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }
            // Set up output pipe if not last command
            if (i < num_cmds - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            // Close all pipe fds in child
            for (int j = 0; j < num_cmds - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            std::vector<char*> args = parseCommand(argv[i + 1]);
            execvp(args[0], args.data());
            perror("execvp failed");
            exit(1);
        }
    }

    // Close all pipe fds in parent
    for (int i = 0; i < num_cmds - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int i = 0; i < num_cmds; i++) wait(NULL);
    return 0;
}