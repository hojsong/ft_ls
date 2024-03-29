#pragma once

#include <unistd.h>      // write, readdir, closedir, readlink
#include <sys/types.h>   // opendir, stat, lstat, getpwuid, getgrgid, listxattr, getxattr
#include <dirent.h>      // opendir, readdir, closedir
#include <sys/stat.h>    // stat, lstat
#include <sys/xattr.h>   // listxattr, getxattr
#include <pwd.h>         // getpwuid
#include <grp.h>         // getgrgid
#include <time.h>        // time, ctime
#include <stdlib.h>      // malloc, free, exit
#include <stdio.h>       // perror
#include <string.h>      // strerror

typedef struct flags{
    int a;
    int l;
    int x;
    int R;
    int t;
} t_flags;

typedef struct item{
    char        *name;
    int         type;
    struct stat status;
    char        *str1;
    char        *str2;
} t_item;


size_t          size_check(char *dir, t_flags flags);
t_item          set_StatAndName(struct stat buf, char *name);
void            sort_item(t_item *items, size_t size, t_flags flags);
t_item          *stat_List(char *dir, t_flags flags, size_t size, size_t *total, size_t *si);
void            items_revers(t_item *items, size_t size);
void            item_execve(t_item *items, t_flags flags, size_t item_size, size_t *si);
void            ls_execute(char *dir, t_flags flags);

size_t          ft_strlen(const char* str);
int             ft_strcmp(char *str1, char *str2);
char            *ft_replace(char *str, size_t n);
char            *ft_pathjoin(char *str1, char *str2);
char            *ft_strdup(char *str);

char            **opendirChecker(char **dir, t_flags flags);
void            process_directory(char *dir_path, t_flags flags, size_t idx, size_t size) ;

void            ft_invalid_option();
char            **flag_checker(int argc, char **argv, t_flags *flags);
size_t          dir_size(char **dir);
char            **Rdircheck(char *dir, t_flags flags);
void            dir_sort(char **dir, t_flags flags, int its);

struct dirent    **reObj(struct dirent **re,     struct dirent *obj);
void            strAllfree(char **str);
void            put_str_fd(int fd, char *str);
void            put_num_fd(int fd, int num);
size_t          num_size(int num);
void            printTime(time_t modTime) ;
char            **addDir(char **dir, char *nowdir, char *d_name, size_t idx);
void            printPermissions(mode_t mode, char *str, struct stat *buf) ;
