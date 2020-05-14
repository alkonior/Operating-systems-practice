//
// Created by alkonior on 14.05.2020.
//

#include "crc16.c"

int main(int argv, const char** argc)
{
    if (argv<3)
    {
        printf("Errror, expected files.");
    }
    const char *in_file_name = argc[1];
    const char *out_file_name = argc[2];
    FILE *in = fopen(in_file_name, "r");
    if (!in) {
        printf("In file not found.");
        return -1;
    }
    FILE *out = fopen(out_file_name, "w");
    if (!out) {
        printf("Error out file.");
        return -1;
    }

    // читаем, вычисляем сумму, записываем.
    unsigned char buff[4096];
    unsigned int size;
    while ((size = fread(buff, 1, 4096, in)) != 0) {
        fprintf(out, "%u\n", crc_16(buff, size));
    }

    fclose(out);
    fclose(in);
    return 0;
}
