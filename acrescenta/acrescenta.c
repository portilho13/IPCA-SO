#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

int main(int argc, char* argv[]) {
    char* err;
    if (argc < 3) {
        err = "Uso correto: acrescenta <origem> <destino>\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }
    char buffer[MAX_SIZE]; // Buffer para ler o ficheiro

    char* ficheiro1 = argv[1];
    char* ficheiro2 = argv[2];

    // Abre o ficheiro
    int t1 = open(ficheiro1, O_RDONLY);
    if (t1 == -1) {
        err = "Ficheiro nao existe\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }

    int r1 = read(t1, buffer, MAX_SIZE);
    if (r1 == -1) {
        err = "Erro ao ler ficheiro\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }
    
    int t2 = open(ficheiro2, O_WRONLY | O_APPEND);
    if (t2 == -1) {
        err = "Erro ao abrir arquivo\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }

    if (write(t2, buffer, r1) == -1) {
        err = "Erro ao escrever no ficheiro\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }

    if (close(t2) < 0) {
        err =  "Erro ao fechar arquivo\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }

    return 0;
}