#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
typedef struct dirrectory
{
    const char* name;
    const char** files;
    struct dirrectory** dirrs;
    int num_files;
    int num_dirrs;

} dirrectory;

dirrectory* create_dirrectory(const char* name_dir) {

    dirrectory* tree = malloc(sizeof(dirrectory));
    tree->num_files = 0;
    tree->num_dirrs = 0;
    tree->dirrs = NULL;
    tree->files = NULL;
    tree->name = malloc(strlen(name_dir));
    snprintf(tree->name,strlen(name_dir)+1,"%s",name_dir);

    DIR *dir;               // Дирректория
    struct dirent *entry;   //Элемент
    dir = opendir(name_dir);

    if (!dir) {
        printf("Error with opening dirr");
        exit(0);
    }
    while ((entry = readdir(dir)) != NULL) { //Читаем элементы
        if (entry->d_type == DT_DIR) {
            if(entry->d_name[0]!='.') {

                tree->dirrs = realloc(tree->dirrs, sizeof(dirrectory *) * (tree->num_dirrs + 1));
                tree->num_dirrs++;

                char full_dirr_name[1024];
                snprintf(full_dirr_name, sizeof full_dirr_name, "%s%s/", name_dir,
                         entry->d_name); //Путь к дирректории
                tree->dirrs[tree->num_dirrs - 1] = create_dirrectory(full_dirr_name);
            }
        }else      //Tсли это не директория
        {
            tree->files = realloc(tree->files,sizeof(char*)*(tree->num_files+1));
            tree->num_files++;
            tree->files[tree->num_files-1] = malloc(strlen(entry->d_name));
            snprintf(tree->files[tree->num_files-1],strlen(entry->d_name)+1,"%s",entry->d_name);
        }
    }

    closedir(dir);
    return tree;
}

void print_dirr(dirrectory* dirr)
{
    printf("(\n");
    printf("Name:\n %s\n",dirr->name);
    if (dirr->num_files>0) {
        printf("Files:\n");
        for (int i = 0; i < dirr->num_files; ++i) {
            printf(" %s'\n",dirr->files[i]);
        }
    }
    if (dirr->num_dirrs>0) {
        printf("Dirrs:\n");
        for (int i = 0; i < dirr->num_dirrs; ++i) {
            print_dirr(dirr->dirrs[i]);
        }
    }
    printf(")\n");
}

void find_file(dirrectory* dirr, const char* file)
{
    if (dirr->num_files>0) {
        for (int i = 0; i < dirr->num_files; ++i) {
            if (strcmp(file,dirr->files[i]) == 0)
                printf(" %s%s\n",dirr->name,dirr->files[i]);
        }
    }
    if (dirr->num_dirrs>0) {
        for (int i = 0; i < dirr->num_dirrs; ++i) {
            find_file(dirr->dirrs[i],file);
        }
    }
}

void depth_find_file(dirrectory* dirr, const char* file)
{
    if (dirr->num_dirrs>0) {
        for (int i = 0; i < dirr->num_dirrs; ++i) {
            find_file(dirr->dirrs[i],file);
        }
    }
    if (dirr->num_files>0) {
        for (int i = 0; i < dirr->num_files; ++i) {
            if (strcmp(file,dirr->files[i]) == 0)
                printf(" %s%s\n",dirr->name,dirr->files[i]);
        }
    }
}

int main(int argv, const char** argc) {

    if (argv < 2)
    {
        printf("Error: expecting file name and number");
        exit(0);
    }
    const char* name_dir;
    const char* find_f;
    int f_flag = 0;
    if (argv == 1)
    {
        name_dir = "./";
    }
    if (argv == 2)
    {
        name_dir = argc[1];
    }
    if (argv == 3)
    {
        printf("Error: expecting file name");
    }
    if (argv == 4)
    {
        name_dir = argc[2];
        find_f = argc[3];
        if (argc[1][1]=='f')
            f_flag=1;
        else
            f_flag=2;
    }
    dirrectory* dir = create_dirrectory(name_dir);

    if (f_flag==0)
    {
        printf("Name:\n %s\n",dir->name);
        if (dir->num_files>0) {
            printf("Files:\n");
            for (int i = 0; i < dir->num_files; ++i) {
                printf(" %s'\n",dir->files[i]);
            }
        }
        if (dir->num_dirrs>0) {
            printf("Dirrs:\n");
            for (int i = 0; i < dir->num_dirrs; ++i) {
                print_dirr(dir->dirrs[i]);
            }
        }
    } else
    {
        if (f_flag=1)
            find_file(dir, find_f);
        else
            depth_find_file(dir,find_f);
    }
    return 0;
}

