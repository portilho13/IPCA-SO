#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

int main(int argc, char* argv[]) {

    char buffer[MAX_SIZE]; // Buffer para ler o ficheiro
    char* err;
    if (argc < 2) {
        err = "Uso correto: copia <origem> <destino>\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }

    char* ficheiro = argv[1];

    int fd = open(ficheiro, O_RDONLY);
    if (fd == -1) {
        perror("Ficheiro nao existe");
        return -1;
    }

    // Lê o ficheiro
    int sz = read(fd, buffer, MAX_SIZE);
    
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

    int fc = creat("ficheiro.copia", O_RDWR);
    if (fc == -1) {
        err = "Erro ao criar ficheiro\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }

    if (write(fc, buffer, sz) == -1) {
        err = "Erro ao escrever no ficheiro\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }

    if (close(fd) < 0) {
        err = "Erro ao fechar arquivo\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }

    return 0;
}