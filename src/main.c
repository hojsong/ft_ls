#include "../header/ft_ls.h"

int cal = 1;

char    **opendirChecker(char **dir, t_flags flags){
    size_t  item_size, idx, dir_resize, iidx, didx;
    t_item  *items;
    DIR     *ds;
    char    **redir;
    struct  stat buf;
    char    *str;
    size_t si[5];

    redir = NULL;
    items = NULL;
    dir_resize = 0;
    item_size = 0;
    idx = 0;
    while(dir[idx]){
        ds = opendir(dir[idx]);
        if(ds == NULL){
            if(stat(dir[idx], &buf) == 0){
                if(S_ISDIR(buf.st_mode))
                    dir_resize++;
                else
                    item_size++;
            }
            else if(lstat(dir[idx], &buf) == 0){
                if(S_ISDIR(buf.st_mode))
                    dir_resize++;
                else
                    item_size++;
            }
            else{
                put_str_fd(2,"ls: ");
                put_str_fd(2, dir[idx]);
                put_str_fd(2,": No such file or directory\n");
            }
        }
        else {
            dir_resize++;
            closedir(ds);
        }
        idx++;
    }
    if(dir_resize == 0 && item_size == 0){
        return NULL;
    }
    else if(dir_resize != 0){
        redir = malloc(sizeof(char *) * (dir_resize + 1));
    }
    if(item_size > 0){
        items = malloc(sizeof(t_item) * (item_size));
    }
    idx = 0;
    iidx = 0;
    didx = 0;
    si[0] = 0;
    si[1] = 0;
    si[2] = 0;
    si[3] = 0;
    si[4] = 0;
    while (dir[idx]){
        ds = opendir(dir[idx]);
        if(ds == NULL){
            str = ft_pathjoin(".", dir[idx]);
            if(stat(str, &buf) == 0 || lstat(str, &buf) == 0){
                if(S_ISDIR(buf.st_mode)){
                    redir[didx] = ft_strdup(dir[idx]);
                    didx++;
                }
                else {
                    if (lstat(str, &buf) == 0){
                        if (S_ISLNK(buf.st_mode)){   
                            items[iidx].type = 1;
                        }
                        else {
                            items[iidx].type = 0;
                        }
                    }
                    items[iidx] = set_StatAndName(buf, dir[idx]);
                    if (si[0] < num_size(buf.st_nlink))
                        si[0] = num_size(buf.st_nlink);
                    struct passwd *pw = getpwuid(buf.st_uid);
                    items[iidx].str1 = pw->pw_name;
                    struct group  *gr = getgrgid(buf.st_gid);
                    items[iidx].str2 = gr->gr_name;
                    if (si[1] < ft_strlen(pw->pw_name))
                        si[1] = ft_strlen(pw->pw_name);
                    if (si[2] < ft_strlen(gr->gr_name))
                        si[2] = ft_strlen(gr->gr_name);
                    if (si[3] < num_size(buf.st_size))
                        si[3] = num_size(buf.st_size);
                    if (si[4] < ft_strlen(dir[idx]))
                        si[4] = ft_strlen(dir[idx]);
                    iidx++;
                }
            }
            free(str);
        }
        else {
            redir[didx] = ft_strdup(dir[idx]);
            didx++;
            closedir(ds);
        }
        idx++;
    }
    if(dir_resize != 0)
        redir[didx] = NULL;
    if (items){
        sort_item(items, item_size, flags);
        if(flags.x == 1){
            items_revers(items, item_size);
        }
        item_execve(items, flags, item_size, si);
        // if (dir_resize != 0)
        //     write(1, "\n", 1);
        free(items);
    }
    if(dir_size(dir) != dir_resize && dir_resize != 0)
        write(1, "\n", 1);
    return redir;
}

void process_directory(char *dir_path, t_flags flags, size_t idx, size_t size) {
    char **dir2;
    size_t i;

    i = idx;
    dir2 = Rdircheck(dir_path, flags);
    dir_sort(dir2, flags, 1);
    while (dir2 && dir2[i]){
        if (i != 0){
            put_str_fd(1, dir2[i]);
            put_str_fd(1,":\n");
        }
        ls_execute(dir2[i], flags);
        if((size == 0 || dir2[i + 1]))
            write(1,"\n",1);
        if(i != 0)
            process_directory(dir2[i], flags, 1, 0);
        i++;
        
    }
    strAllfree(dir2);
}

void    f()
{
    system("leaks ft_ls");
}

int main(int argc, char **argv) {
    char **dir, **dir2;
    t_flags flags;
    size_t idx;

    // atexit(f);
    idx = 0;
    dir = flag_checker(argc, argv, &flags);
    dir2 = opendirChecker(dir, flags);
    if(dir2 == NULL){
        strAllfree(dir);
        return(0);
    }
    dir_sort(dir2, flags, 0);
    while (dir2[idx] && dir2) {
        if(dir_size(dir) != dir_size(dir2) || dir_size(dir) != 1){
            put_str_fd(1,dir2[idx]);
            put_str_fd(1,":\n");
        }
        process_directory(dir2[idx], flags, 0, dir_size(dir2));
        if (dir2[idx + 1])
            write(1, "\n", 1);
        idx++;
    }
    if(dir)
        strAllfree(dir);
    if(dir2)
        strAllfree(dir2);
    return (0);
}


// int main(int argc, char **argv)
// {
//     // DIR *ds;
//     char **dir, **dir2;
//     t_flags flags;
//     size_t idx;
//     size_t i; //total;

//     idx = 0;
//     dir = flag_checker(argc, argv, &flags);
//     dir_sort(dir, flags);
//     while (dir[idx] && dir){
//         i = 0;
//         dir2 = Rdircheck(dir[idx], flags);
//         dir_sort(dir2, flags);
//         while (dir2 && dir2[i]){
//             if(dir_size(dir) != 1 || dir_size(dir2) != 1){
//                 put_str_fd(1, dir2[i]);
//                 put_str_fd(1,":\n");
//             }
//             ls_execute(dir2[i], flags);
//             if(dir[idx + 1] || dir2[i + 1])
//                 write(1,"\n",1);
//             i++;
//         }
//         strAllfree(dir2);
//         idx++;
//     }
//     strAllfree(dir);
// }