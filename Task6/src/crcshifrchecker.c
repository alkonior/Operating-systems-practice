//
// Created by alkonior on 14.05.2020.
//

#include "crc16.c"

int *read_res(const char *file) {
    int k, i;
    FILE *ptrfile;
    k = 0;
    int s;
    ptrfile = fopen(file, "r+");

    while ((fscanf(ptrfile, "%d", &s) != EOF)) {
        if (!ptrfile) break;
        k += 1;
    }
    int *ex_res = malloc(k * sizeof(int) + 1);

    rewind(ptrfile);
    for (i = 0; i < k; i++) {
        fscanf(ptrfile, "%i\n", &ex_res[i + 1]);
    }
    fclose(ptrfile);
    ex_res[0] = k;
    return ex_res;
}

int main(int argv, const char **argc) {
    if (argv < 3) {
        printf("Errror, expected files.");
    }
    const char *in_file_name = argc[1];
    const char *out_file_name = argc[2];
    FILE *in = fopen(in_file_name, "r");
    if (!in) {
        printf("In file not found.");
        return -1;
    }


    unsigned char buff[4096];
    unsigned int size;

    const int *crc_res = read_res(out_file_name);     //Читаем файл для зашифрованных значений
    int i = 1;
    int max_res = crc_res[0];

    while ((size = fread(buff, 1, 4096, in)) != 0) {
        if (i < max_res + 1) {
            if (crc_16(buff, size) != crc_res[i]) {         //Сверяем поблочно
                printf("Error!!! Wrong file.");
                exit(0);
            }
        }
        else {
                printf("Error!!! Wrong file.");
                exit(0);
            }
        i++;
    }
    if (i != max_res+1)
        printf("Error!!! Wrong file.");
    else
        printf("Good file.");
    fclose(in);
    return 0;
}
