#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <zconf.h>

typedef unsigned long long ull;


int main(int argv, const char** argc) {

    if (argv < 3)
    {
        printf("Error: expecting file name and number");
        exit(0);
    }
    unsigned int n = atoi(argc[1]);
    const char *name=argc[2];
    int f;                 // afqk
    struct stat file_stat; // Описание файла
    stat(name, &file_stat);
    unsigned int block_size = file_stat.st_blksize; // Находим размер блоков файла

    char *ans = malloc(block_size + 1);     // Ответ
    char *buf = malloc(block_size);              // Буфер для чтения

    if ((f = open(name, O_RDONLY)) < 0) {
        printf("Error opening!");
        exit(0);
    }

    for (unsigned int i = 0;; i++) {
        long int offset = (long)(i + 1) * block_size;   // Смещение блока
        if (offset > file_stat.st_size) {
            offset = file_stat.st_size;                 //Случай, когда блок больше файла
        }

        if (lseek(f, -offset, SEEK_END) == -1L) {       //Смещаемся на offset
            printf("Seek Error\n");
            exit(0);
        }

        int was_read = 0;                                   // Число прочитанного
        if ((was_read = read(f, buf, block_size)) == 0) {
            printf("Read Error\n");
            exit(0);
        }

        for (long int j = 0; j < was_read; j++) { //Ищем строки
            if (buf[was_read - 1 - j] == '\n') { //Нашли конец строки
                n--;
            }

            if ((n == 0) ||
                (((offset == file_stat.st_size)) && (j == (was_read - 1)))) {
                //Если нашли все строки или дошли до начала файла то выводим все что нашли
                if (n != 0) {
                    printf("%c", buf[0]);
                }
                for (long int k = i * block_size + j - 1; k >= 0; k--) {
                    printf("%c", ans[k]);
                }
                free(ans);
                free(buf);
                exit(0);
            }
            ans[i * block_size + j] =
                    buf[was_read - 1 - j]; // добавляем значение в ответ
        }

        if (!(ans = realloc(ans, (i + 2) * block_size))) { //Увеличиваем размер ответа
            printf("Allocation error.");
            exit(1);
        }
    }
    return 0;
}