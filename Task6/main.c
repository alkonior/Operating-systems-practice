#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/time.h>
#include "src/xor.c"
#include "src/fletcher.c"
#include "src/crc16.c"

unsigned long long current_time() {
    struct timeval t;
    gettimeofday(&t, NULL); // получаем текущее время
    return t.tv_sec * 1e6 + t.tv_usec;  // пересчитываем всё в usec
}


int * read_res(const char *file )
{
    int k,i;
    FILE *ptrfile;
    k=0;
    int s;
    ptrfile=fopen(file,"r+");

    while ((fscanf(ptrfile, "%d",&s)!=EOF))
    {    if(!ptrfile) break;
        k+=1;
    }
    int *ex_res = malloc(k*sizeof(int));

    rewind(ptrfile);
    for(i=0;i<k;i++)
    {
        fscanf(ptrfile, "%i\n",&ex_res[i]);
    }
    fclose(ptrfile);
    return ex_res;
}

int main() {
    const char *file;
    unsigned long long res = 0;


    unsigned long long test_start = 0;
    unsigned long long test_end = 0;

    const int* xor_res=read_res("../Tests/xor.out");
    file = "../Tests/1.txt";
    test_start = current_time();//Начали отсчет XOR
    res = XorSumm(file);
    test_end = current_time();//Закончили отсчет XOR
    printf("Xor %i:\n Get:      %i \n Expected: %i\n Time: %i\n\n",1,res,xor_res[0],test_end-test_start);

    file = "../Tests/2.txt";
    test_start = current_time();//Начали отсчет XOR
    res = XorSumm(file);
    test_end = current_time();//Закончили отсчет XOR
    printf("Xor %i:\n Get:      %i \n Expected: %i\n Time: %i\n\n",2,res,xor_res[1],test_end-test_start);

    file = "../Tests/3.txt";
    test_start = current_time();//Начали отсчет XOR
    res = XorSumm(file);
    test_end = current_time();//Закончили отсчет XOR
    printf("Xor %i:\n Get:      %i \n Expected: %i\n Time: %i\n\n",3,res,xor_res[2],test_end-test_start);
    free(xor_res);



    const int* fletcher_res=read_res("../Tests/fletcher.out");
    file = "../Tests/1.txt";
    test_start = current_time();//Начали отсчет Fletcher
    res = FletcherSumm(file);
    test_end = current_time();//Закончили отсчет Fletcher
    printf("Fletcher %i:\n Get:      %i \n Expected: %i\n Time: %i\n\n",1,res,fletcher_res[0],test_end-test_start);

    file = "../Tests/2.txt";
    test_start = current_time();//Начали отсчет Fletcher
    res = FletcherSumm(file);
    test_end = current_time();//Закончили отсчет Fletcher
    printf("Fletcher %i:\n Get:      %i \n Expected: %i\n Time: %i\n\n",2,res,fletcher_res[1],test_end-test_start);

    file = "../Tests/3.txt";
    test_start = current_time();//Начали отсчет Fletcher
    res = FletcherSumm(file);
    test_end = current_time();//Закончили отсчет Fletcher
    printf("Fletcher %i:\n Get:      %i \n Expected: %i\n Time: %i\n\n",3,res,fletcher_res[2],test_end-test_start);
    free(fletcher_res);




    const int* crc16_res=read_res("../Tests/crc16.out");
    file = "../Tests/1.txt";
    test_start = current_time();//Начали отсчет CRC16
    res = CRC16Summ(file);
    test_end = current_time();//Закончили отсчет CRC16
    printf("CRC16 %i:\n Get:      %li \n Expected: %li\n Time: %i\n\n",1,res,crc16_res[0],test_end-test_start);

    file = "../Tests/2.txt";
    test_start = current_time();//Начали отсчет CRC16
    res = CRC16Summ(file);
    test_end = current_time();//Закончили отсчет CRC16
    printf("CRC16 %i:\n Get:      %li \n Expected: %li\n Time: %i\n\n",2,res,crc16_res[1],test_end-test_start);

    file = "../Tests/3.txt";
    test_start = current_time();//Начали отсчет CRC16
    res = CRC16Summ(file);
    test_end = current_time();//Закончили отсчет CRC16
    printf("CRC16 %i:\n Get:      %li \n Expected: %li\n Time: %i\n\n",3,res,crc16_res[2],test_end-test_start);
    free(crc16_res);




}