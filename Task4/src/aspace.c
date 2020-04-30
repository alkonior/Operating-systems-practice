#include <stdio.h>
#include <stdlib.h>

char global;
char new_global;

int main ()
{
    char local = 5; //стековая переменная
    void *pointer = malloc(200); //указатель на выделенную память
    void *new_pointer = malloc(200);// указатель на новую выделенную память
    char new_local = 10;//новая стековая переменная

    printf ("main:                   %li\n", main);// адрес функции
    printf ("global:                 %li\n", &global);// адрес глобальной переменной
    printf ("new_global:             %li\n", &new_global);// адрес глобальной переменной
    printf ("local:                  %li\n", &local);/// адрес локальной переменной
    printf ("pointer to pointer      %li\n", &pointer); // адрес, по котором хранится значение адреса выделенной памяти
    printf ("pointer to new_pointer  %li\n", &new_pointer);// адрес выделенной памяти
    printf ("new_local:              %li\n", &new_local);//адрес новой локальной переменной
    printf ("pointer                 %li\n", pointer);//адрес новой выделенной памяти
    printf ("new_pointer             %li\n", new_pointer);//адрес новой выделенной памяти




    return 0;
}