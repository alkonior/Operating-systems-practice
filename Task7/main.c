#include <stdio.h>
#include <stdint.h>

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
    unsigned char buff[1001];
    buff[1000]=0;
    unsigned int size;
    while ((size = fread(buff, 1, 1000, in)) != 0) {
        int n = 0;
        for (int i = 0; i < size; ++i) {
            if (('a' <= buff[i] && buff[i] <= 'z') || ('A' <= buff[i] && buff[i] <= 'Z'))
            {
                n++;
            }
            else
            {
                for (int j = 0; j < n; j+=4) {
                    if (j+4<n+1)
                    {
                        *((uint32_t *)&buff[i-n+j]) ^= 0b00100000001000000010000000100000;
                    } else
                    {
                        for (int k = j; k < n; ++k) {
                            (buff[i-n+k]) ^= 0b00100000;
                        }
                    }
                }
                n=0;
            }
        }
        for (int j = 0; j < n; j+=4) {
            if (j+4<n+1)
            {
                *((uint32_t *)&buff[size-j]) ^= 0b00100000001000000010000000100000;
            } else
            {
                for (int k = j; k < n; ++k) {
                    (buff[size-k-1]) ^= 0b00100000;
                }
            }
        }
        fprintf(out, "%s", buff);
    }

    return 0;
}
