#include <stdio.h>

int FletcherSumm(const char *file_name) {
    FILE *f = fopen(file_name, "r"); // открыли файл
    if (!f) { // проверили успешность открытия
        printf("File not found.");
        return 0;
    }

    unsigned short sum1 = 0, sum2 = 0; // обнулили сумммы
    unsigned char c;
    while ((char)(c = (unsigned char)fgetc(f)) !=
           EOF) { // считали символ, и проверили
        // что он не конечный
        sum1 = (sum1 + c) % 255; // обнавляем суммы
        sum2 = (sum2 + sum1) % 255;
    }

    fclose(f);
    unsigned short ans = (sum2 << 8) | sum1; // получаем итоговоую чек сумму
    return ans;
}