
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso correto: %s <arquivo>\n", argv[0]);
        return -1;
    }

    char* ficheiro = argv[1];

    int fd = open(ficheiro, O_RDONLY);

    if (fd == -1) {
        perror("open");
        return -1;
    }

    return 0;

}