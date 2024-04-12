/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojsong <hojsong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:39:22 by hojsong           #+#    #+#             */
/*   Updated: 2024/04/12 15:59:05 by hojsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

struct dirent **reObj(struct dirent **re,  struct dirent *obj){
    struct dirent **result;
    size_t i;
    
    i = 0;
    if(re != NULL){
        while (re[i])
            i++;
    }
    result = malloc(sizeof(struct dirent *) * (i + 2));
    i = 0;
    while (re && re[i]){
        result[i] = re[i];
        i++;
    }
    result[i] = obj;
    result[i + 1] = NULL;
    if(re)
        free(re);
    return (result);
}

void    strAllfree(char **str){
    int i;

    if (str == NULL)
        return ;
    i = 0;
    while (str[i]){
        free(str[i]);
        str[i] = NULL;
        i++;
    }
    free(str);
    str = NULL;
}

void    put_str_fd(int fd, char *str){
    size_t i;

    i = 0;
    while(str && str[i]){
        write(fd, &str[i], 1);
        i++;
    }
}

void    put_num_fd(int fd, int num){
    char s;
    
    if(num <= 9 && num >= -9){
        if (num < 0){
            write(fd, "-", 1);
            num *= -1;
        }
        s = '0' + num;
        write(fd, &s, 1);
    }
    else {
        s = num % 10 + '0';
        put_num_fd(fd, num / 10);
        write(fd, &s, 1);
    }
}

size_t    num_size(int num){
    size_t i;
    
    i = 0;
    if(num <= 9 && num >= -9){
        if (num < 0){
            num *= -1;
            i++;
        }
        i++;
    }
    else {
        i += num_size(num / 10);
        i++;
    }
    return i;
}


void printTime(time_t modTime) {
    char *timeString = ctime(&modTime);
    char *dest;
    size_t len = ft_strlen(timeString);
    size_t x;

    x = 0;
    while (x < 9){
        timeString[len - x - 1] = '\0';
        x++;
    }

    dest = ft_replace(timeString, 4);

    if(dest){
        write(1, dest, ft_strlen(dest));
        free(dest);
    }
    else
        write(1, timeString, ft_strlen(timeString));
}

char    **addDir(char **dir, char *nowdir, char *d_name, size_t idx){
    size_t i;
    char **result;

    i = 0;
    while(dir && dir[i])
        i++;
    result = malloc((sizeof(char *)) * (i + 2));
    i = 0;
    while(i < idx){
        result[i] = ft_strdup(dir[i]);
        i++;
    }
    result[i] = ft_pathjoin(nowdir, d_name);
    i++;
    while(i < idx){ 
        result[i] = ft_strdup(dir[i]);
        i++;
    }
    result[i] = NULL;
    strAllfree(dir);
    return (result);
}

void printPermissions(mode_t mode, char *str, struct stat *buf) {
    char permissions[11] = "---------- ";
    permissions[10] = ' ';

    if (lstat(str, buf) == 0){
        if (S_ISLNK(buf->st_mode)){   
            permissions[0] = 'l';
            char link_target[1024];
            ssize_t len = readlink(str, link_target, sizeof(link_target)-1);
            if (len != -1) {
                buf->st_size = len;
                buf->st_nlink = 1;
            }
        }
        else if (S_ISDIR(mode))
            permissions[0] = 'd';
    }
    if (mode & S_IRUSR) permissions[1] = 'r';
    if (mode & S_IWUSR) permissions[2] = 'w';
    if (mode & S_IXUSR && mode & S_ISUID) permissions[3] = 's';
    else if (mode & S_ISUID) permissions[3] = 'S';
    else if (mode & S_IXUSR) permissions[3] = 'x';

    if (mode & S_IRGRP) permissions[4] = 'r';
    if (mode & S_IWGRP) permissions[5] = 'w';
    if (mode & S_IXGRP && mode & S_ISGID) permissions[6] = 's';
    else if (mode & S_ISGID) permissions[6] = 'S';
    else if (mode & S_IXGRP) permissions[6] = 'x';

    if (mode & S_IROTH) permissions[7] = 'r';
    if (mode & S_IWOTH) permissions[8] = 'w';
    if (mode & S_IXOTH && mode & S_ISVTX) permissions[9] = 't';
    else if (mode & S_ISVTX) permissions[9] = 'T';
    else if (mode & S_IXOTH) permissions[9] = 'x';

    write(1, permissions, sizeof(permissions));
}