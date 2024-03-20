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

char **flag_checker(int argc, char **argv, t_flags *flags);
size_t ft_strlen(const char* str);
void ft_invalid_option();
void    strAllfree(char **str);