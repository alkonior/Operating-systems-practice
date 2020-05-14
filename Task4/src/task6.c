#include <stdlib.h>
int main(){
    void *a = malloc(55);
    a = malloc(100);
    free(a);
    return 0;
}