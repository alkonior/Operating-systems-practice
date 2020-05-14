#Task6
#1,2,3,4
Файл ```main.c```.

Вывод тестов:
```
Xor 1:
 Get:      96 
 Expected: 96
 Time: 4

Xor 2:
 Get:      17 
 Expected: 17
 Time: 13

Xor 3:
 Get:      19 
 Expected: 19
 Time: 31604

Fletcher 1:
 Get:      19495 
 Expected: 19495
 Time: 4

Fletcher 2:
 Get:      61990 
 Expected: 61990
 Time: 22

Fletcher 3:
 Get:      11874 
 Expected: 11874
 Time: 48962

CRC16 1:
 Get:      38712 
 Expected: 38712
 Time: 26

CRC16 2:
 Get:      34752 
 Expected: 34752
 Time: 20

CRC16 3:
 Get:      20396 
 Expected: 20396
 Time: 49080
```
Как можно заметить, время не особо различается, но стабильно

CRC16 > Fletcher > Xor,
причем Fletcher и CRC16 не особо различаются по времени, что забавно.
#5
```shifr.c ``` шифрует блочно и записывает в файл.

```crcshifrchecker.c ``` сверяет файл с зашифрованной версией.
