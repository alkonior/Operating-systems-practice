#Задание 5
##1 
Вывод программы:
```
Create: 42

Write: 222

Fflush: 5306

Close: 22

Fflush: 60;
```
Как можно увидеть, именно сброс буфера занимает больше всего вреемени, так как в этот момент буквально идет запись в файл.
```
Write: 107
FWrite: 233
Num: 3

Write: 73
FWrite: 41
Num: 30

Write: 405
FWrite: 39
Num: 300

Write: 3626
FWrite: 86
Num: 3000

Write: 33396
FWrite: 498
Num: 30000
```
Можно сказать, что FWrite работает существенно быстрее чем, Write, но это будет ошибкой, так как идет запись в буфер, а сброс буфера мы не делаем. Если его сделать то картина меняется:
```
Write: 124
FWrite: 219
Num: 3

Write: 157
FWrite: 74
Num: 30

Write: 856
FWrite: 79
Num: 300

Write: 8356
FWrite: 176
Num: 3000

Write: 36902
FWrite: 500
Num: 30000
```
Нам уже требуется чуть больше ввремени, но разнится не критична. Что же будет если делать сброс после каждой записи:
```
Write: 118
FWrite: 156
Num: 3

Write: 71
FWrite: 93
Num: 30

Write: 405
FWrite: 434
Num: 300

Write: 3791
FWrite: 4396
Num: 3000

Write: 34703
FWrite: 35016
Num: 30000
```
FWrite оказывается хуче чем Write.

##3
Программа ```src/mytail.c ```. 

Принимает число и файл для чтения в формате: 
```mytail 5 file.txt```.
##4
Программа ```src/mystat.c ```. 

Принимает число и файл для чтения в формате: 
```mystat file```.
##5
Программа ```src/myls.c ```. 

Принимает число и файл для чтения в формате: 

```myls -l dirrectory/``` или ```myls -l dirrectory/```.
##6
Программа ```src/myfind.c ```. 

Принимает число и файл для чтения в формате: 

```myfind -f dirrectory/ file```  ```myfind dirrectory/```.

    