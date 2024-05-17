#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_SIZE 1000

int main(int argc, char* argv[]) {

    char buffer[MAX_SIZE]; // Buffer para ler o ficheiro

    if (argc < 2) {
        perror("Uso correto: copia <origem> <destino>");
        return -1;
    }

    char* ficheiro = argv[1];

    size_t fd = open(ficheiro, O_RDONLY);
    if (fd == -1) {
        perror("Ficheiro nao existe");
        return -1;
    }

    // Lê o ficheiro
    size_t sz = read(fd, buffer, MAX_SIZE);
    
    // Verifica se houve erro
    if (sz == -1) {
        perror("read");
        return -1;
    }

    if (close(fd) < 0) {
        perror("c1");
        return -1;
    }

    int fc = creat("ficheiro.copia", O_RDWR);
    if (fc == -1) {
        perror("Erro ao criar ficheiro");
        return -1;
    }

    if (write(fc, buffer, sz) == -1) {
        perror("Erro ao escrever no ficheiro");
        return -1;
    }

    if (close(fd) < 0) {
        perror("c1");
        return -1;
    }

    return 0;
}