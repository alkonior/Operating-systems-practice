#include <stdlib.h>
int main(){
    int *a = malloc(100);
    a[0] = 1;
    free(a);
    printf ("value: %li\n", (long)a[0]);
    return 0;
}