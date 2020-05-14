#include <stdio.h>
#include <stdlib.h>

unsigned char XorSumm(const char *file) {


    FILE *f = fopen(file, "r"); // открыли файл

    if (!f) { // проверили успешность открытия
        printf("File not found.");
        return 0;
    }

    unsigned char sum = 0; // Итоговая сумма
    char c;

    while ((c = fgetc(f)) != EOF) { // считали символ, и проверили
        // что он не конечный
        sum ^= c; // добавили XOR к ответу символа
    }

    fclose(f);
    return sum;
}
