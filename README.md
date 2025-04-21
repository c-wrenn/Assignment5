# Assignment5

## Learning Outcome: 
### - How to create a child process
### - How to use stdin and stdout
### - How to use pipes

## Part 1
### In this part1, you will extend the same concept, and modify the code to execute this time a double pipe
### command: “ls -ltr | grep 3377 | wc –l”, instead of a single pipe command

## Part 2
### In part1, a double pipe is used to execute the command “ls -ltr | grep 3377 | wc –l”.
### However, our program is static: it means that code need to be modified and rebuilt if we want to
### change the commands to execute. In this part, we make our program dynamic instead of static.