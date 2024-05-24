#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

// Definindo constantes para os tipos de ficheiros
#define FILE_TYPE_UNKNOWN 0
#define FILE_TYPE_REGULAR 1
#define FILE_TYPE_DIRECTORY 2
#define FILE_TYPE_SYMLINK 3
#define FILE_TYPE_CHAR 4
#define FILE_TYPE_BLOCK 5
#define FILE_TYPE_FIFO 6
#define FILE_TYPE_SOCKET 7

int get_file_type(mode_t mode) {
    if (S_ISREG(mode)) return FILE_TYPE_REGULAR;
    if (S_ISDIR(mode)) return FILE_TYPE_DIRECTORY;
    if (S_ISLNK(mode)) return FILE_TYPE_SYMLINK;
    if (S_ISCHR(mode)) return FILE_TYPE_CHAR;
    if (S_ISBLK(mode)) return FILE_TYPE_BLOCK;
    if (S_ISFIFO(mode)) return FILE_TYPE_FIFO;
    if (S_ISSOCK(mode)) return FILE_TYPE_SOCKET;
    return FILE_TYPE_UNKNOWN;
}

void print_file_info(const char *path) {
    struct stat statbuf;
    struct passwd *pwd;
    struct group *grp;
    char timebuf[80];

    if (stat(path, &statbuf) == -1) {
        perror("stat");
        return;
    }

    // Tipo de ficheiro
    const char *tipo;
    switch (get_file_type(statbuf.st_mode)) {
        case FILE_TYPE_REGULAR:
            tipo = "Ficheiro normal\n";
            break;
        case FILE_TYPE_DIRECTORY:
            tipo = "Diretoria\n";
            break;
        case FILE_TYPE_SYMLINK:
            tipo = "Link simbólico\n";
            break;
        case FILE_TYPE_CHAR:
            tipo = "Ficheiro de dispositivo de caractere\n";
            break;
        case FILE_TYPE_BLOCK:
            tipo = "Ficheiro de dispositivo de bloco\n";
            break;
        case FILE_TYPE_FIFO:
            tipo = "FIFO (pipe)\n";
            break;
        case FILE_TYPE_SOCKET:
            tipo = "Socket\n";
            break;
        default:
            tipo = "Desconhecido\n";
            break;
    }
    write(STDOUT_FILENO, tipo, strlen(tipo));

    // i-node
    printf("i-node: %ld\n", (long) statbuf.st_ino);

    // Utilizador dono
    pwd = getpwuid(statbuf.st_uid);
    grp = getgrgid(statbuf.st_gid);
    printf("Dono: %s (UID: %d, GID: %d, Grupo: %s)\n", pwd ? pwd->pw_name : "Desconhecido", statbuf.st_uid, statbuf.st_gid, grp ? grp->gr_name : "Desconhecido");

    // Datas
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", localtime(&statbuf.st_ctime));
    printf("Data de criação: %s\n", timebuf);

    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", localtime(&statbuf.st_atime));
    printf("Data de último acesso: %s\n", timebuf);

    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", localtime(&statbuf.st_mtime));
    printf("Data de última modificação: %s\n", timebuf);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        char *err = "Uso: informa <ficheiro>\n";
        write(STDERR_FILENO, err, strlen(err));
        return EXIT_FAILURE;
    }

    print_file_info(argv[1]);

    return EXIT_SUCCESS;
}
