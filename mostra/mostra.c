
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_SIZE 1000


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso correto: %s <arquivo>\n", argv[0]);
        return -1;
    }

    char* ficheiro = argv[1];

    // Abre o ficheiro

    int fd = open(ficheiro, O_RDONLY);

    if (fd == -1) {
        perror("open");
        return -1;
    }

    char buffer[MAX_SIZE]; // Buffer para ler o ficheiro

    // Lê o ficheiro
    size_t sz = read(fd, buffer, MAX_SIZE);
    
    // Verifica se houve erro
    if (sz == -1) {
        perror("read");
        return -1;
    }

    // Escreve o conteúdo do ficheiro no stdout
    size_t wr = write(STDOUT_FILENO, buffer, sz);

    // Verifica se houve erro
    if (wr == -1) {
        perror("write");
        return -1;
    }

    return 0;

}