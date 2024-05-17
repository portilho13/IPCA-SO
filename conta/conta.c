
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
    char ch;
    int num = 0;

    // Abre o ficheiro

    int fd = open(ficheiro, O_RDONLY);
    while (read(fd, &ch, 1) != 0) { // Enquanto houver caracteres para ler (read retorna 0 quando chega ao fim do arquivo)
        if (ch == '\n') {
            num++;
        }
    }
    printf("Número de linhas: %d\n", num);
    return 0;
}