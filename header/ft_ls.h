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
    int r;
    int R;
    int t;
} t_flags;

typedef struct item{
    char        *name;
    struct stat status;
} t_item;


char    *ft_replace(char *str, size_t n);
void process_directory(char *dir_path, t_flags flags, size_t idx, size_t size);
char    **flag_checker(int argc, char **argv, t_flags *flags);
size_t ft_strlen(const char* str);
size_t  dir_size(char **dir);
void    ft_invalid_option();
char    **addDir(char **dir, char *nowdir, char *d_name, size_t idx);
char    **Rdircheck(char *dir, t_flags flags);
void    ls_execute(char *dir, t_flags flags);
void printPermissions(mode_t mode, char *str, struct stat *buf);
void    strAllfree(char **str);
void    printTime(time_t modTime);
size_t    num_size(int num);
void    put_num_fd(int fd, int num);
void    put_str_fd(int fd, char *str);
int     ft_strcmp(char *str1, char *str2);
char    *ft_pathjoin(char *str1, char *str2);
char    *ft_strdup(char *str);
void    dir_sort(char **dir, t_flags flags);
struct dirent **reObj(struct dirent **re,  struct dirent *obj);