#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

void execute_command(char* command) {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("Fork falhou");
        exit(1);
    }
    else if (pid == 0) {

        char* args[MAX_COMMAND_LENGTH / 2 + 1];
        char* token;
        int arg_index = 0;

        token = strtok(command, " \t\n");

        while (token != NULL) {
            args[arg_index++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[arg_index] = NULL;

        if (execvp(args[0], args) < 0) {
            perror("Execução falhou");
            exit(1);
        }
    }
    else {

        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            char msg[128];
            snprintf(msg, sizeof(msg), "O comando %s terminou com o código %d\n", command, exit_status);
            write(STDOUT_FILENO, msg, strlen(msg));
        }
        else {
            char msg[128] = "Comando não funcionou\n";
            write(STDOUT_FILENO, msg, strlen(msg));
        }
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    while (1) {
        const char* prompt = "% ";
        write(STDOUT_FILENO, prompt, strlen(prompt));

        if (fgets(command, sizeof(command), stdin) == NULL) {
            perror("Comando lido sem sucesso");
            exit(1);
        }

        size_t len = strlen(command);
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        if (strcmp(command, "termina") == 0) {
            break;
        }

        if (strncmp(command, "cd ", 3) == 0) {
            char* path = command + 3;
            if (chdir(path) != 0) {
                perror("cd falhou");
            }
            continue;
        }

        execute_command(command);
    }

    return 0;
}