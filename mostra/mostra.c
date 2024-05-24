#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

int main(int argc, char* argv[]) {
    char* err;
    if (argc < 2) {
        err = "Uso correto: mostra <ficheiro>\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }

    char* ficheiro = argv[1];

    // Abre o ficheiro

    int fd = open(ficheiro, O_RDONLY);

    if (fd == -1) {
        err = "Ficheiro nao existe\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }

    char buffer[MAX_SIZE]; // Buffer para ler o ficheiro

    // Lê o ficheiro
    size_t sz = read(fd, buffer, MAX_SIZE);
    
    // Verifica se houve erro
    if (sz == -1) {
        err = "Erro ao ler ficheiro\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }

    if (close(fd) < 0) {
        err = "Erro ao fechar arquivo\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }

    // Escreve o conteúdo do ficheiro no stdout e verifica se houve erro
    if (write(STDOUT_FILENO, buffer, sz) == -1) {
        err = "Erro ao escrever no stdout\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }

    return 0;

}