#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc!=0) {
        int size = atoi(argv[1]);
        printf("process = %d\n", getpid()); // узнаем индекс текущего процесса
        char *array = (char *) malloc(
                size * 1024 * 1024); // выделяем нужное количество, получаем адрес выделенной памяти
        if (array != NULL)
        while (1) {
            for (int i = 0; i < size * 1024 * 1024; ++i) {
                array[i] = 'c';
            }
        }
        else
        {
            printf("Not enaugth memory");
        }
    } else
        printf("Need memory size");
    return 0;
}