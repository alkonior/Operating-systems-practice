#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
int main(int argv, const char** argc)
{
    if (argv<3)
    {
        printf("Errror, expected files.");
    }
    const char *in_file_name = argc[1];
    const char *out_file_name = argc[2];
    FILE *in = fopen(in_file_name, "w");
    if (!in) {
        printf("In file not found.");
        return -1;
    }
    fprintf(in,"DAcasva vadsjnca\nndsjcnalsjc jkabcjkhaerljha\nr bvljkhavkjjbsfkjbvsjkd\nbvkjbasjkvbakjhs\n");
    fclose(in);
    int linkRet = link ( argc[2] , argc[3] ) ;
    if (linkRet==0)
    {
        printf("Cannot create link");
    }
    in = fopen(in_file_name, "r");
    char c;
    while (1) {
        fseek(in, 0, SEEK_SET);
        while ((c = fgetc(in)) !=
               EOF) {
            printf("%c", c);
        }
    }
    fclose(in);

    return 0;
}
