#include "../header/ft_ls.h"

int cal;

size_t  Permission_check(char *dir, t_flags flags){
    char *str;
    DIR *ds;
    struct stat buf;
    size_t result;

    result = 0;
    ds = opendir(dir);
    if(ds == NULL){
        return result;
    }
    while(1){
        struct dirent *obj = readdir(ds);
        if(obj == NULL)
            break;
        str = ft_pathjoin(dir, obj->d_name);
        if (stat(str, &buf) == 0 || lstat(str, &buf) == 0){
            if(flags.a == 0 && obj->d_name[0] == '.'){
                result++;  
                free(str);
                continue ;
            }         
        }
        result++;  
        free(str);
    }
    closedir(ds);
    return (result);
}

size_t size_check(char *dir, t_flags flags){
    char *str;
    DIR *ds;
    struct stat buf;
    size_t result;

    result = 0;
    ds = opendir(dir);
    if(ds == NULL){
        return result;
    }
    while(1){
        struct dirent *obj = readdir(ds);
        if(obj == NULL)
            break;
        str = ft_pathjoin(dir, obj->d_name);
        if (stat(str, &buf) == 0 || lstat(str, &buf) == 0){
            if(flags.a == 0 && obj->d_name[0] == '.'){
                free(str);
                continue ;
            }         
        }
        result++;  
        free(str);
    }
    closedir(ds);
    return (result);
}

t_item set_StatAndName(struct stat buf, char *name){
    t_item result;

    result.name = ft_strdup(name);
    result.status = buf;
    result.str1 = NULL;
    result.str2 = NULL;
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
                    ;
                }
                else if(items[i].status.st_mtime == items[i + 1].status.st_mtime 
                    && ft_strcmp(items[i].name , items[i+1].name) > 0){
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

t_item *stat_List(char *dir, t_flags flags, size_t size, size_t *total, size_t *si){
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
    si[4] = 0;
    result = malloc(sizeof(t_item) * (size));
    if (result == NULL)
        return NULL;
    ds = opendir(dir);
    if(ds == NULL)
    {
        free (result);
        return NULL;
    }
    while(1){
        struct dirent *obj = readdir(ds);
        if(obj == NULL)
            break;
        str = ft_pathjoin(dir, obj->d_name);
        if (stat(str, &buf) == 0 || lstat(str, &buf) == 0){
            if (lstat(str, &buf) == 0){
               if (S_ISLNK(buf.st_mode)){   
                    *total += 8;
                    result[idx].type = 1;
               }
                else {
                    result[idx].type = 0;
                    *total += buf.st_blocks;
                }
            }
            if(flags.a == 0 && obj->d_name[0] == '.'){
                free(str);
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
            if (si[4] < ft_strlen(result[idx].name))
                si[4] = ft_strlen(result[idx].name);
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

void item_execve(t_item *items, t_flags flags, size_t item_size, size_t *si){
    size_t lc, size, ll, al, idx, x;
    char *str;

    size = item_size;
    if (flags.l == 0)
    {
        lc = (size / cal);
        if (size % cal)
            lc ++;
        lc *= cal;
    }
    else
        lc = size;
    idx = 0;
    while(idx < lc){
        if(flags.l == 1){
            ll = idx;
            str = items[ll].name;
            printPermissions(items[ll].status.st_mode, str, &items[ll].status);
            write(1, " ", 1);
            al = 0;
            while (num_size(items[ll].status.st_nlink) + al++ < si[0])
                write(1, " ", 1);
            put_num_fd(1, items[ll].status.st_nlink);
            write(1, " ", 1);
            al = 0;
            if (items[ll].str1){
                while (ft_strlen(items[ll].str1) + al++ < si[1])
                    write(1, " ", 1);
                put_str_fd(1, items[ll].str1);
            }
            else {
                struct passwd *pw = getpwuid(items[ll].status.st_uid);
                while (ft_strlen(pw->pw_name) + al++ < si[1])
                    write(1, " ", 1);
                put_str_fd(1, pw->pw_name);
            }
            put_str_fd(1, "  ");
            al = 0;
            if (items[ll].str2){
                while (ft_strlen(items[ll].str2) + al++ < si[1])
                    write(1, " ", 1);
                put_str_fd(1, items[ll].str2);
            }
            else {
                struct group  *gr = getgrgid(items[ll].status.st_gid);
                while (ft_strlen(gr->gr_name) + al++ < si[2])
                    write(1, " ", 1);
                put_str_fd(1, gr->gr_name);
            }
            put_str_fd(1, "  ");
            al = 0;
            while (num_size(items[ll].status.st_size) + al++ < si[3])
                write(1, " ", 1);
            put_num_fd(1, items[ll].status.st_size);
            put_str_fd(1, " ");
            printTime(items[ll].status.st_mtime);
            put_str_fd(1, " ");
            put_str_fd(1, items[ll].name);
            if (lstat(str, &items[ll].status) == 0) {
                if (S_ISLNK(items[ll].status.st_mode)) {
                    char link_target[1024];
                    ssize_t len = readlink(str, link_target, sizeof(link_target)-1);
                    if (len != -1) {
                        link_target[len] = '\0';
                        put_str_fd(1, " -> ");
                        put_str_fd(1, link_target);
                    } 
                }
            }
            free(items[ll].name);
            put_str_fd(1, "\n");
        }
        else if(flags.l == 0){
            ll = (idx / cal) + ((idx % cal) * (lc / cal));
            if (ll < size)
            {
                put_str_fd(1, items[ll].name);
                x = ft_strlen(items[ll].name);
                while(x++ < si[4] + 6){
                    write(1, " ", 1);
                }
                write(1, " ", 1);
                free(items[ll].name);
            }
            if ((idx + 1) % (cal) == 0)
                write(1, "\n", 1);
        }
        idx++;
    }
}

int ls_execute(char *dir, t_flags flags){
    size_t size, total;
    size_t si[5], idx, lc, x, al, ll;
    t_item *items;
    char *str;

    total = 0;
    if (Permission_check(dir, flags) == 0)
    {
        if (ft_strlen(dir) > 2 && dir[0] == '.' && dir[1] == '/')
            str = ft_replace(dir, 2);
        else
            str = ft_strdup(dir);
        put_str_fd(2,"ls: ");
        put_str_fd(2, str);
        put_str_fd(2,": Permission denied\n");
        free(str);
        return (0);
    }
    size = size_check(dir, flags);
    if (size == 0)
        return (0);
    items = stat_List(dir, flags, size, &total, si);
    if (items == NULL)
        return (0);
    if(flags.l == 1){
        put_str_fd(1,"total ");
        put_num_fd(1, total);
        write(1, "\n", 1);
    }
    if(flags.x == 1){
        items_revers(items, size);
    }
    // item_execve(items, flags, size, si);

    if (flags.l == 0)
    {
        lc = (size / cal);
        if (size % cal)
            lc ++;
        lc *= cal;
    }
    else
        lc = size;
    // size--;
    idx = 0;
    while(idx < lc){
        if(flags.l == 1){
            ll = idx;
            str = ft_pathjoin(dir, items[ll].name);
            printPermissions(items[ll].status.st_mode, str, &items[ll].status);
            write(1, " ", 1);
            al = 0;
            while (num_size(items[ll].status.st_nlink) + al++ < si[0])
                write(1, " ", 1);
            put_num_fd(1, items[ll].status.st_nlink);
            write(1, " ", 1);
            struct passwd *pw = getpwuid(items[ll].status.st_uid);
            struct group  *gr = getgrgid(items[ll].status.st_gid);
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
            while (num_size(items[ll].status.st_size) + al++ < si[3])
                write(1, " ", 1);
            put_num_fd(1, items[ll].status.st_size);
            put_str_fd(1, " ");
            printTime(items[ll].status.st_mtime);
            put_str_fd(1, " ");
            put_str_fd(1, items[ll].name);
            if (lstat(str, &items[ll].status) == 0) {
                if (S_ISLNK(items[ll].status.st_mode)) {
                    char link_target[1024];
                    ssize_t len = readlink(str, link_target, sizeof(link_target)-1);
                    if (len != -1) {
                        link_target[len] = '\0';
                        put_str_fd(1, " -> ");
                        put_str_fd(1, link_target);
                    } 
                }
            }
            free(items[ll].name);
            free(str);
            put_str_fd(1, "\n");
        }
        else if(flags.l == 0){
            ll = (idx / cal) + ((idx % cal) * (lc / cal));
            if (ll < size)
            {
                put_str_fd(1, items[ll].name);
                x = ft_strlen(items[ll].name);
                while(x++ < si[4] + 6){
                    write(1, " ", 1);
                }
                write(1, " ", 1);
                free(items[ll].name);
            }
            if ((idx + 1) % (cal) == 0)
                write(1, "\n", 1);
        }
        idx++;
    }
    free(items);
    return (1);
}