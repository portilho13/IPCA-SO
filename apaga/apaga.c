#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char* err;
    if (argc < 2) {
        err = "Uso correto: apaga <ficheiro>\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }
    char* ficheiro = argv[1];

    if (unlink(ficheiro) == -1) {
        err = "Erro ao apagar ficheiro\n";
        write(STDERR_FILENO, err, strlen(err));
        return -1;
    }
    return 0;
}