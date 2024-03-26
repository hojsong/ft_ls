#include "../header/ft_ls.h"

size_t si[4];

size_t size_check(char *dir, t_flags flags){
    char *str;
    DIR *ds;
    struct stat buf;
    size_t result;

    result = 0;
    ds = opendir(dir);
    if(ds == NULL)
        return result;
    while(1){
        struct dirent *obj = readdir(ds);
        if(obj == NULL)
            break;
        str = ft_strjoin(dir, obj->d_name);
        if (stat(str, &buf) == 0){
            if(flags.a == 0 && obj->d_name[0] == '.'){
                continue ;
            }         
            result++;    
        }
        free(str);
    }
    closedir(ds);
    return (result);
}

t_item set_StatAndName(struct stat buf, char *name){
    t_item result;

    result.name = name;
    result.status = buf;
    return result;
}

void    sort_item(t_item *items, size_t size, t_flags flags){
    t_item swapitem;
    int idx, i;

    idx = 0;
    while (++idx < (int)size){
        i = idx - 1;
        while (i >= 0){
            if(flags.t == 1){
                if(items[i].status.st_mtime < items[i + 1].status.st_mtime){
                    swapitem = items[i];
                    items[i] = items[i + 1];
                    items[i + 1] = swapitem;
                }
                else if(items[i].status.st_mtime > items[i + 1].status.st_mtime){
                }
                else if(items[i].status.st_mtime == items[i + 1].status.st_mtime && ft_strcmp(items[i].name, items[i + 1].name) > 0){
                    swapitem = items[i];
                    items[i] = items[i + 1];
                    items[i + 1] = swapitem;
                }
            }
            else {
                if(ft_strcmp(items[i].name, items[i + 1].name) > 0){
                    swapitem = items[i];
                    items[i] = items[i + 1];
                    items[i + 1] = swapitem;
                }
            }
            i--;        
        }
    }

}

t_item *stat_List(char *dir, t_flags flags, size_t size, size_t *total){
    t_item *result;
    char *str;
    DIR *ds;
    struct stat buf;
    size_t idx;

    idx = 0;
    si[0] = 0;
    si[1] = 0;
    si[2] = 0;
    si[3] = 0;
    result = malloc(sizeof(t_item) * (size));
    ds = opendir(dir);
    if(ds == NULL)
        return NULL;
    while(1){
        struct dirent *obj = readdir(ds);
        if(obj == NULL)
            break;
        str = ft_strjoin(dir, obj->d_name);
        if (stat(str, &buf) == 0){
            *total += buf.st_blocks;
            if(flags.a == 0 && obj->d_name[0] == '.'){
                continue ;
            }    
            result[idx] = set_StatAndName(buf,obj->d_name);
            struct passwd *pw = getpwuid(result[idx].status.st_uid);
            struct group  *gr = getgrgid(result[idx].status.st_gid);
            if (si[0] < num_size(result[idx].status.st_nlink))
                si[0] = num_size(result[idx].status.st_nlink);
            if (si[1] < ft_strlen(pw->pw_name))
                si[1] = ft_strlen(pw->pw_name);
            if (si[2] < ft_strlen(gr->gr_name))
                si[2] = ft_strlen(gr->gr_name);
            if (si[3] < num_size(result[idx].status.st_size))
                si[3] = num_size(result[idx].status.st_size);

            idx++;
        }
        free(str);
    }
    closedir(ds);
    sort_item(result, size, flags);
    return (result);
}

void    items_revers(t_item *items, size_t size){
    size_t i, x;
    t_item swap;

    if (size <= 1)
        return ;
    x = size / 2;
    i = 0;
    while (i < x){
        swap = items[i];
        items[i] = items[size - i - 1];
        items[size - i - 1] = swap;
        i++;
    }
}

void ls_execute(char *dir, t_flags flags){
    size_t size, idx, total, x, al;
    t_item *items;
    char *str;
    
    total = 0;
    size = size_check(dir, flags);
    if (size == 0){
        put_str_fd(1,"ls: ");
        put_str_fd(1, dir);
        put_str_fd(1,": No such file or directory\n");
        return ;
    }
    items = stat_List(dir, flags, size, &total);
    if (items == NULL){
        put_str_fd(1,"ls: ");
        put_str_fd(1, dir);
        put_str_fd(1,": No such file or directory\n");
        return ;
    }
    idx = 0;
    if(flags.l == 1){
        put_str_fd(1,"total ");
        put_num_fd(1, total);
        write(1, "\n", 1);
    }
    if(flags.r == 1){
        items_revers(items, size);
    }
    while(idx < size){
        if(flags.l == 1){
            printPermissions(items[idx].status.st_mode);
            write(1, " ", 1);
            al = 0;
            while (num_size(items[idx].status.st_nlink) + al++ < si[0])
                write(1, " ", 1);
            put_num_fd(1, items[idx].status.st_nlink);
            write(1, " ", 1);
            struct passwd *pw = getpwuid(items[idx].status.st_uid);
            struct group  *gr = getgrgid(items[idx].status.st_gid);
            al = 0;
            while (ft_strlen(pw->pw_name) + al++ < si[1])
                write(1, " ", 1);
            put_str_fd(1, pw->pw_name);
            put_str_fd(1, "  ");
            al = 0;
            while (ft_strlen(gr->gr_name) + al++ < si[2])
                write(1, " ", 1);
            put_str_fd(1, gr->gr_name);
            put_str_fd(1, "  ");
            al = 0;
            while (num_size(items[idx].status.st_size) + al++ < si[3])
                write(1, " ", 1);
            put_num_fd(1, items[idx].status.st_size);
            put_str_fd(1, "  ");
            printTime(items[idx].status.st_mtime);
            put_str_fd(1, items[idx].name);
            str = ft_strjoin(dir, items[idx].name);
            if (lstat(str, &items[idx].status) == 0) {
                if (S_ISLNK(items[idx].status.st_mode)) {
                    char link_target[1024];
                    ssize_t len = readlink(str, link_target, sizeof(link_target)-1);
                    if (len != -1) {
                        link_target[len] = '\0';
                        put_str_fd(1, " -> ");
                        put_str_fd(1, link_target);
                    } 
                }
            }
            free(str);
            put_str_fd(1, "\n");
        }
        else if(flags.l == 0){
            put_str_fd(1, items[idx].name);
            x = ft_strlen(items[idx].name);
            while(x++ < 15){
                write(1, " ", 1);
            }
            write(1, " ", 1);
            if ((idx + 1 )% 4 == 0)
                write(1, "\n", 1);
        }
        idx++;
    }
    if(flags.l == 0 && idx % 4 != 0)
        write(1, "\n", 1);
}