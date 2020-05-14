#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


int main(int argv, const char** argc) {

    if (argv < 2)
    {
        printf("Error: expecting file name and number");
        exit(0);
    }
    const char* name_dir=argc[argv-1];
    int l_flag = argv==3;

    DIR *dir; // Lbhhtrnjhbz
    struct dirent *entry; //Элемент
    dir = opendir(name_dir);

    if (!dir) {
        printf("Error with opening dirr");
        exit(0);
    }

    while ((entry = readdir(dir)) != NULL) { //Читаем элементы

        if (entry->d_type != 4) {       //Tсли это не директория
            printf("-%s", entry->d_name); //Bvz

            if (l_flag) { // при пресутсвии флага, выводим дополнительные данные
                char full_file_name[1024];
                snprintf(full_file_name, sizeof full_file_name, "%s%s", name_dir,
                         entry->d_name); //Полный путь к файлу

                struct stat file_stat; //Описание файла
                if (stat(full_file_name,
                         &file_stat)) {
                    printf("\nError!\n");
                    exit(0);
                }

                /*Инфомация о файле*/
                printf("\n(\n Size: %li,\n Number link: %lu,\n Number block: %li,\n UID: %u,\n GID: %u,\n Mode: %u\n)",
                       file_stat.st_size, file_stat.st_nlink, file_stat.st_blocks,
                       file_stat.st_uid, file_stat.st_gid, file_stat.st_mode);
            }
            printf("\n\n");
        }
    };

    closedir(dir); // закрываем директорию
    return 0;
}

