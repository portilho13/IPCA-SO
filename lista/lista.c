#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#define MSG 256
#define PATH 1024

void listar_diretorio(const char* path) {
    struct dirent* entry;
    struct stat statbuf;
    char* err;
    char mensagem[MSG];
    DIR* dp;

    dp = opendir(path);
    if (dp == NULL) {
        err = "Erro ao abrir diretorio\n";
        write(STDERR_FILENO, err, strlen(err));
        return;
    }
    snprintf(mensagem, sizeof(mensagem), "Listagem do diretorio: %s >\n", path);

    write(STDOUT_FILENO, mensagem, strlen(mensagem));


    while ((entry = readdir(dp)) != NULL) {
        char fullpath[PATH];

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (stat(fullpath, &statbuf) == -1) {
            err = "Erro ao obter informacoes do arquivo\n";
            write(STDERR_FILENO, err, strlen(err));
            continue;
        }
        printf("|\n");
        if (S_ISDIR(statbuf.st_mode)) {
            snprintf(mensagem, sizeof(mensagem), " -> [DIR]  %s\n", entry->d_name);
            write(STDOUT_FILENO, mensagem, strlen(mensagem));

        }
        else {
            snprintf(mensagem, sizeof(mensagem), " -> [FILE] %s\n", entry->d_name);
            write(STDOUT_FILENO, mensagem, strlen(mensagem));

        }
    }

    closedir(dp);
}

int main(int argc, char* argv[]) {
    const char* path;

    if (argc < 2) {
        path = ".";
    }
    else {
        path = argv[1];
    }

    listar_diretorio(path);

    return 0;
}
