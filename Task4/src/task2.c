#include <stdio.h>

int main(){
    char name[5]; //Массив на стеке
    puts("Enter name: ");
    scanf("%5s", name);
    printf("Hello,  %s.\n\n\tNice to see you.\n", name);

    puts("Enter name: ");
    scanf("%5s", name);
    printf("Hello,  %s.\n\n\tNice to see you.\n", name);

    const char *name1="Anna"; //указатель на строку на статик сегменте
    char a_letter=name1[0];
   // name1[0]=name1[3]; // access to read only data
   // name1[3]=a_letter; // access to read only data
    puts(name1);
}