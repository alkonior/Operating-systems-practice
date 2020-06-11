#Task6
#2
Результат ```valgrind --tool=helgrind ./main-race```

```
==41724== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==41724== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==41724== Command: ./main-race
==41724== 
==41724== ---Thread-Announcement------------------------------------------
==41724== 
==41724== Thread #1 is the program's root thread
==41724== 
==41724== ---Thread-Announcement------------------------------------------
==41724== 
==41724== Thread #2 was created
==41724==    at 0x49DA0F2: clone (clone.S:71)
==41724==    by 0x489D2EB: create_thread (createthread.c:101)
==41724==    by 0x489EE0F: pthread_create@@GLIBC_2.2.5 (pthread_create.c:817)
==41724==    by 0x4842917: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==41724==    by 0x109513: Pthread_create (mythreads.h:51)
==41724==    by 0x1095F1: main (main-race.c:14)
==41724== 
==41724== ----------------------------------------------------------------
==41724== 
==41724== Possible data race during read of size 4 at 0x10C014 by thread #1
==41724== Locks held: none
==41724==    at 0x1095F2: main (main-race.c:15)
==41724== 
==41724== This conflicts with a previous write of size 4 by thread #2
==41724== Locks held: none
==41724==    at 0x1095A6: worker (main-race.c:8)
==41724==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==41724==    by 0x489E608: start_thread (pthread_create.c:477)
==41724==    by 0x49DA102: clone (clone.S:95)
==41724==  Address 0x10c014 is 0 bytes inside data symbol "balance"
==41724== 
==41724== ----------------------------------------------------------------
==41724== 
==41724== Possible data race during write of size 4 at 0x10C014 by thread #1
==41724== Locks held: none
==41724==    at 0x1095FB: main (main-race.c:15)
==41724== 
==41724== This conflicts with a previous write of size 4 by thread #2
==41724== Locks held: none
==41724==    at 0x1095A6: worker (main-race.c:8)
==41724==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==41724==    by 0x489E608: start_thread (pthread_create.c:477)
==41724==    by 0x49DA102: clone (clone.S:95)
==41724==  Address 0x10c014 is 0 bytes inside data symbol "balance"
==41724== 
==41724== 
==41724== Use --history-level=approx or =none to gain increased speed, at
==41724== the cost of reduced accuracy of conflicting-access information
==41724== For lists of detected and suppressed errors, rerun with: -s
==41724== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

Проблема в том, что два потока пытаются изменить одни и те же данные одновременно. Для решения нужно воспользоваться атомиками или мьютексом, заблокировав им проблемное место.

#3
Результат ```valgrind --tool=helgrind ./main-deadlock```
```
==42359== Helgrind, a thread error detector
==42359== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==42359== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==42359== Command: ./main-deadlock
==42359== 
==42359== ---Thread-Announcement------------------------------------------
==42359== 
==42359== Thread #3 was created
==42359==    at 0x49DA0F2: clone (clone.S:71)
==42359==    by 0x489D2EB: create_thread (createthread.c:101)
==42359==    by 0x489EE0F: pthread_create@@GLIBC_2.2.5 (pthread_create.c:817)
==42359==    by 0x4842917: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42359==    by 0x109513: Pthread_create (mythreads.h:51)
==42359==    by 0x109654: main (main-deadlock.c:24)
==42359== 
==42359== ----------------------------------------------------------------
==42359== 
==42359== Thread #3: lock order "0x10C040 before 0x10C080" violated
==42359== 
==42359== Observed (incorrect) order is: acquisition of lock at 0x10C080
==42359==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42359==    by 0x109382: Pthread_mutex_lock (mythreads.h:23)
==42359==    by 0x1095CD: worker (main-deadlock.c:13)
==42359==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42359==    by 0x489E608: start_thread (pthread_create.c:477)
==42359==    by 0x49DA102: clone (clone.S:95)
==42359== 
==42359==  followed by a later acquisition of lock at 0x10C040
==42359==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42359==    by 0x109382: Pthread_mutex_lock (mythreads.h:23)
==42359==    by 0x1095D9: worker (main-deadlock.c:14)
==42359==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42359==    by 0x489E608: start_thread (pthread_create.c:477)
==42359==    by 0x49DA102: clone (clone.S:95)
==42359== 
==42359== Required order was established by acquisition of lock at 0x10C040
==42359==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42359==    by 0x109382: Pthread_mutex_lock (mythreads.h:23)
==42359==    by 0x1095B3: worker (main-deadlock.c:10)
==42359==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42359==    by 0x489E608: start_thread (pthread_create.c:477)
==42359==    by 0x49DA102: clone (clone.S:95)
==42359== 
==42359==  followed by a later acquisition of lock at 0x10C080
==42359==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42359==    by 0x109382: Pthread_mutex_lock (mythreads.h:23)
==42359==    by 0x1095BF: worker (main-deadlock.c:11)
==42359==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42359==    by 0x489E608: start_thread (pthread_create.c:477)
==42359==    by 0x49DA102: clone (clone.S:95)
==42359== 
==42359==  Lock at 0x10C040 was first observed
==42359==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42359==    by 0x109382: Pthread_mutex_lock (mythreads.h:23)
==42359==    by 0x1095B3: worker (main-deadlock.c:10)
==42359==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42359==    by 0x489E608: start_thread (pthread_create.c:477)
==42359==    by 0x49DA102: clone (clone.S:95)
==42359==  Address 0x10c040 is 0 bytes inside data symbol "m1"
==42359== 
==42359==  Lock at 0x10C080 was first observed
==42359==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42359==    by 0x109382: Pthread_mutex_lock (mythreads.h:23)
==42359==    by 0x1095BF: worker (main-deadlock.c:11)
==42359==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42359==    by 0x489E608: start_thread (pthread_create.c:477)
==42359==    by 0x49DA102: clone (clone.S:95)
==42359==  Address 0x10c080 is 0 bytes inside data symbol "m2"
==42359== 
==42359== 
==42359== 
==42359== Use --history-level=approx or =none to gain increased speed, at
==42359== the cost of reduced accuracy of conflicting-access information
==42359== For lists of detected and suppressed errors, rerun with: -s
==42359== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)
```
Типичная проблема взаимной блокировки. Простого решения обычно нет, только поиск проблемы и ее устранение.

#4
Результат ```valgrind --tool=helgrind ./main-deadlock-global```
```
==42427== Helgrind, a thread error detector
==42427== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==42427== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==42427== Command: ./main-deadlock-global
==42427== 
==42427== ---Thread-Announcement------------------------------------------
==42427== 
==42427== Thread #3 was created
==42427==    at 0x49DA0F2: clone (clone.S:71)
==42427==    by 0x489D2EB: create_thread (createthread.c:101)
==42427==    by 0x489EE0F: pthread_create@@GLIBC_2.2.5 (pthread_create.c:817)
==42427==    by 0x4842917: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42427==    by 0x109513: Pthread_create (mythreads.h:51)
==42427==    by 0x10966C: main (main-deadlock-global.c:27)
==42427== 
==42427== ----------------------------------------------------------------
==42427== 
==42427== Thread #3: lock order "0x10C080 before 0x10C0C0" violated
==42427== 
==42427== Observed (incorrect) order is: acquisition of lock at 0x10C0C0
==42427==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42427==    by 0x109382: Pthread_mutex_lock (mythreads.h:23)
==42427==    by 0x1095D9: worker (main-deadlock-global.c:15)
==42427==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42427==    by 0x489E608: start_thread (pthread_create.c:477)
==42427==    by 0x49DA102: clone (clone.S:95)
==42427== 
==42427==  followed by a later acquisition of lock at 0x10C080
==42427==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42427==    by 0x109382: Pthread_mutex_lock (mythreads.h:23)
==42427==    by 0x1095E5: worker (main-deadlock-global.c:16)
==42427==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42427==    by 0x489E608: start_thread (pthread_create.c:477)
==42427==    by 0x49DA102: clone (clone.S:95)
==42427== 
==42427== Required order was established by acquisition of lock at 0x10C080
==42427==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42427==    by 0x109382: Pthread_mutex_lock (mythreads.h:23)
==42427==    by 0x1095BF: worker (main-deadlock-global.c:12)
==42427==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42427==    by 0x489E608: start_thread (pthread_create.c:477)
==42427==    by 0x49DA102: clone (clone.S:95)
==42427== 
==42427==  followed by a later acquisition of lock at 0x10C0C0
==42427==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42427==    by 0x109382: Pthread_mutex_lock (mythreads.h:23)
==42427==    by 0x1095CB: worker (main-deadlock-global.c:13)
==42427==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42427==    by 0x489E608: start_thread (pthread_create.c:477)
==42427==    by 0x49DA102: clone (clone.S:95)
==42427== 
==42427==  Lock at 0x10C080 was first observed
==42427==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42427==    by 0x109382: Pthread_mutex_lock (mythreads.h:23)
==42427==    by 0x1095BF: worker (main-deadlock-global.c:12)
==42427==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42427==    by 0x489E608: start_thread (pthread_create.c:477)
==42427==    by 0x49DA102: clone (clone.S:95)
==42427==  Address 0x10c080 is 0 bytes inside data symbol "m1"
==42427== 
==42427==  Lock at 0x10C0C0 was first observed
==42427==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42427==    by 0x109382: Pthread_mutex_lock (mythreads.h:23)
==42427==    by 0x1095CB: worker (main-deadlock-global.c:13)
==42427==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42427==    by 0x489E608: start_thread (pthread_create.c:477)
==42427==    by 0x49DA102: clone (clone.S:95)
==42427==  Address 0x10c0c0 is 0 bytes inside data symbol "m2"
==42427== 
==42427== 
==42427== 
==42427== Use --history-level=approx or =none to gain increased speed, at
==42427== the cost of reduced accuracy of conflicting-access information
==42427== For lists of detected and suppressed errors, rerun with: -s
==42427== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)
```
Отчет helgrind не отличается от предыдущего, хотя и добавление нового мьютекса рашает проблему взаимной блокировки.

#5
Результат ```valgrind --tool=helgrind ./main-signal```
```
==42624== Helgrind, a thread error detector
==42624== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==42624== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==42624== Command: ./main-signal
==42624== 

this should print first
==42624== ---Thread-Announcement------------------------------------------
==42624== 
==42624== Thread #2 was created
==42624==    at 0x49DA0F2: clone (clone.S:71)
==42624==    by 0x489D2EB: create_thread (createthread.c:101)
==42624==    by 0x489EE0F: pthread_create@@GLIBC_2.2.5 (pthread_create.c:817)
==42624==    by 0x4842917: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42624==    by 0x109533: Pthread_create (mythreads.h:51)
==42624==    by 0x10961C: main (main-signal.c:15)
==42624== 
==42624== ---Thread-Announcement------------------------------------------
==42624== 
==42624== Thread #1 is the program's root thread
==42624== 
==42624== ----------------------------------------------------------------
==42624== 
==42624== Possible data race during write of size 4 at 0x10C014 by thread #2
==42624== Locks held: none
==42624==    at 0x1095CD: worker (main-signal.c:9)
==42624==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42624==    by 0x489E608: start_thread (pthread_create.c:477)
==42624==    by 0x49DA102: clone (clone.S:95)
==42624== 
==42624== This conflicts with a previous read of size 4 by thread #1
==42624== Locks held: none
==42624==    at 0x10961E: main (main-signal.c:16)
==42624==  Address 0x10c014 is 0 bytes inside data symbol "done"
==42624== 
==42624== ----------------------------------------------------------------
==42624== 
==42624== Possible data race during read of size 4 at 0x10C014 by thread #1
==42624== Locks held: none
==42624==    at 0x10961E: main (main-signal.c:16)
==42624== 
==42624== This conflicts with a previous write of size 4 by thread #2
==42624== Locks held: none
==42624==    at 0x1095CD: worker (main-signal.c:9)
==42624==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42624==    by 0x489E608: start_thread (pthread_create.c:477)
==42624==    by 0x49DA102: clone (clone.S:95)
==42624==  Address 0x10c014 is 0 bytes inside data symbol "done"
==42624== 
==42624== ----------------------------------------------------------------
==42624== 
==42624== Possible data race during write of size 1 at 0x52AE1A5 by thread #1
==42624== Locks held: none
==42624==    at 0x48488A6: mempcpy (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42624==    by 0x494A7B1: _IO_new_file_xsputn (fileops.c:1236)
==42624==    by 0x494A7B1: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1197)
==42624==    by 0x493F677: puts (ioputs.c:40)
==42624==    by 0x109633: main (main-signal.c:18)
==42624==  Address 0x52ae1a5 is 21 bytes inside a block of size 1,024 alloc'd
==42624==    at 0x483C893: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42624==    by 0x493CE83: _IO_file_doallocate (filedoalloc.c:101)
==42624==    by 0x494D04F: _IO_doallocbuf (genops.c:347)
==42624==    by 0x494C0AF: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:745)
==42624==    by 0x494A834: _IO_new_file_xsputn (fileops.c:1244)
==42624==    by 0x494A834: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1197)
==42624==    by 0x493F677: puts (ioputs.c:40)
==42624==    by 0x1095CC: worker (main-signal.c:8)
==42624==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==42624==    by 0x489E608: start_thread (pthread_create.c:477)
==42624==    by 0x49DA102: clone (clone.S:95)
==42624==  Block was alloc'd by thread #2
==42624== 
this should print last
==42624== 
==42624== Use --history-level=approx or =none to gain increased speed, at
==42624== the cost of reduced accuracy of conflicting-access information
==42624== For lists of detected and suppressed errors, rerun with: -s
==42624== ERROR SUMMARY: 24 errors from 3 contexts (suppressed: 46 from 42)
```
Проблема та же что и в первом случе. Но это не вызывает проблем, так как мы не перезаписываем переменную в основном потоке.
Проблема однако в том, что основной поток продалжает работать и постояннно запрашивать данные о переменной, напрасно татя свой ресурс.
#5
Результат ```valgrind --tool=helgrind ./main-signal-cv```
```
==42822== Helgrind, a thread error detector
==42822== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==42822== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==42822== Command: ./main-signal-cv
==42822== 
this should print first
this should print last
==42822== 
==42822== Use --history-level=approx or =none to gain increased speed, at
==42822== the cost of reduced accuracy of conflicting-access information
==42822== For lists of detected and suppressed errors, rerun with: -s
==42822== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 12 from 12)
```
Проблем не обнаруженно. Причина в том, что мы блокируем основной поток, до тех пор пока на cv не придет сигнал. В случае сигнала поток просыпается и продолжает свое выполнение.