#include <stdio.h>
#include <unistd.h>

int main(int argv, const char** argc)
{
    if (argv<2)
    {
        printf("Errror, expected files.");
    }
    if (unlink(argc[1]) != 0) {
        printf("Unlink error.");
        return -1;
    } else
        printf("Unlink");
    return 0;
}