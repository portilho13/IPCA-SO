#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

void execute_command(char* command) {
pid_t pid;
int status;

// Fork a child process
pid = fork();

if (pid < 0) {
    perror("Fork failed");
exit(1);
}
else if (pid == 0) {
// Child process
char* args[MAX_COMMAND_LENGTH / 2 + 1]; // Max arguments
char* token;
int arg_index = 0;

// Tokenize the command
token = strtok(command, " \t\n");
while (token != NULL) {
args[arg_index++] = token;
token = strtok(NULL, " \t\n");
}
args[arg_index] = NULL; // Null-terminate the argument list

// Execute the command
if (execvp(args[0], args) < 0) {
perror("Execution failed");
exit(1);
}
}
else {
// Parent process
// Wait for the child process to finish
waitpid(pid, &status, 0);

if (WIFEXITED(status)) {
int exit_status = WEXITSTATUS(status);
 printf("Terminou comando %s com código %d\n", command, exit_status);
 }
else {
printf("Comando %s terminou de forma anormal\n", command);
}
}
}

int main() {
char command[MAX_COMMAND_LENGTH];
while (1) {
 printf("%% "); // Prompt symbol

 // Read the command from standard input
if (fgets(command, sizeof(command), stdin) == NULL) {
perror("Failed to read command");
 exit(1);
}

// Remove the newline character at the end of the command
 size_t len = strlen(command);
if (command[len - 1] == '\n') {
 command[len - 1] = '\0';
 }

// Check for the "termina" command
 if (strcmp(command, "termina") == 0) {
 break;
 }

// Execute the command
 execute_command(command);
}

return 0;
}
