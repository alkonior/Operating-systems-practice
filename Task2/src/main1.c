#include <stdio.h>
#include <zconf.h>

int main() {
    int x = 100;                    //Переменная x

    fork();                         //Создаем дочерний процесс

    printf("%i\n",x);       //Выводим
    return 0;
}
