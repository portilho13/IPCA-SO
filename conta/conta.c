
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
        err = "Uso correto: conta <ficheiro>\n";
        write(STDERR_FILENO, err, strlen(err));
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