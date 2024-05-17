#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_SIZE 1000

int main(int argc, char* argv[]) {

    if (argc < 3) {
        printf("Uso correto: %s <arquivo1> <arquivo2>\n", argv[0]);
        return -1;
    }
    char buffer[MAX_SIZE]; // Buffer para ler o ficheiro

    char* ficheiro1 = argv[1];
    char* ficheiro2 = argv[2];

    // Abre o ficheiro
    size_t t1 = open(ficheiro1, O_RDONLY);
    if (t1 == -1) {
        perror("open");
        return -1;
    }

    size_t r1 = read(t1, buffer, MAX_SIZE);
    if (r1 == -1) {
        perror("read");
        return -1;
    }
    
    size_t t2 = open(ficheiro2, O_WRONLY | O_APPEND);
    if (t2 == -1) {
        perror("open");
        return -1;
    }

    if (write(t2, buffer, r1) == -1) {
        perror("write");
        return -1;
    }

    if (close(t2) < 0) {
        perror("Erro ao fechar arquivo");
        return -1;
    }

    return 0;
}