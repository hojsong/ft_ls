#include "../header/ft_ls.h"

void ft_invalid_option(){
    printf("ls: invalid options\n");
    exit (0);
}

char **flag_checker(int argc, char **argv, t_flags *flags){
    char **result;
    int i;
    int x;
    int y;

    flags->a = 0;
    flags->l = 0;
    flags->R = 0;
    flags->r = 0;
    flags->t = 0;
    i = 1;
    while(i < argc){
        x = (int)ft_strlen(argv[i]);
        if(x > 1 && argv[i][0] == '-'){
            y = 1;
            while(y < x){
                if(argv[i][y] == 'a')
                    flags->a = 1;
                else if(argv[i][y] == 'l')
                    flags->l = 1;
                else if(argv[i][y] == 'R')
                    flags->R = 1;
                else if(argv[i][y] == 'r')
                    flags->r = 1;
                else if(argv[i][y] == 't')
                    flags->t = 1;
                else
                    ft_invalid_option();
                y++;
            }
        }
        else
            break;
        i++;
    }
    if (argc == i){
        result = malloc((sizeof(char *) * (2)));
        result[0] = ft_strdup(".");
        result[1] = NULL;
    }
    else {    
        result = malloc((sizeof(char *) * (argc - i + 1)));
        int idx = 0;
        while (i + idx < argc){
            result[idx] = ft_strdup(argv[i + idx]);
            idx++;
        }
        result[idx]= NULL;
    }
    return result;
}

size_t  dir_size(char **dir){
    size_t idx;

    idx = 0;
    while(dir && dir[idx]){
        idx++;
    }
    return idx;
}

char **Rdircheck(char *dir, t_flags flags){
    char **result;
    DIR *ds;
    struct stat buf;
    size_t i; //total;
    char *str;

    result = malloc(sizeof(char *) * 2);
    if(ft_strcmp(dir, ".") == 0)
        result[0] = ft_strdup(dir);
    else 
        result[0] = ft_strjoin(".", dir);
    result[1] = NULL;
    if (flags.R == 0){
        return result;
    }
    ds = opendir(result[0]);
    i = 1;
    while(1){
        struct dirent *obj = readdir(ds);
        if(obj == NULL)
            break;
        str = ft_strjoin(result[0], obj->d_name);
        if (stat(str, &buf) == 0){
            if (lstat(str, &buf) == 0) {
                if (S_ISLNK(buf.st_mode)) {    
                }
                else
                {
                    if(flags.a == 0 && obj->d_name[0] == '.'){
                        continue ;
                    }                
                    else if(S_ISDIR(buf.st_mode) && \
                        ft_strcmp(obj->d_name, ".") && ft_strcmp(obj->d_name, "..")){
                        result = addDir(result, dir, obj->d_name, i);
                        i++;
                    }
                }
            }
        }
        free(str);
        str = NULL;
    }
    closedir(ds);
    return result;
}

void dir_sort(char **dir, t_flags flags){
    int  idx;
    int  size;
    DIR     *ds;
    long  *maxtime;
    struct stat buf;
    struct stat buf2[3];
    char    *swapdir;
    char    *str;
    long  swaptime;


    size = (int)dir_size(dir);
    if (size < 2)
        return ;
    idx = 0;
    if(flags.t == 1){
        maxtime = malloc(sizeof(long) * (size + 1));
        while (dir && dir[idx]){
            ds = opendir(dir[idx]);
            if(ds == NULL){
                idx++;
                continue;
            }
            while(1){
                struct dirent *obj = readdir(ds);
                if(obj == NULL)
                    break;
                str = ft_strjoin(dir[idx],obj->d_name);
                if (stat(str, &buf) == 0){
                    if(ft_strcmp(obj->d_name, ".") == 0){
                        maxtime[idx] = buf.st_mtime;
                        buf2[idx] = buf;
                    }
                }
                free(str);
                str = NULL;
            }
            closedir(ds);
            idx++;
        }
        idx = 0;
        while (++idx < size){
            int i = idx - 1;
            while (i >= 0){
                if(maxtime[i] < maxtime[i + 1]){
                    swapdir = dir[i];
                    swaptime = maxtime[i];
                    dir[i] = dir[i + 1];
                    maxtime[i] = maxtime[i + 1];
                    dir[i + 1] = swapdir;
                    maxtime[i + 1] = swaptime;
                }
                else if(maxtime[i] > maxtime[i + 1]){
                }
                else if(maxtime[i] == maxtime[i + 1] && ft_strcmp(dir[i], dir[i + 1]) > 0){
                    swapdir = dir[i];
                    dir[i] = dir[i + 1];
                    dir[i + 1] = swapdir;
                }
            }
            i--;        
        }
        free(maxtime);
    }
    while (++idx < size){
        int i = idx - 1;
        while (i >= 0){
            if(ft_strcmp(dir[i], dir[i + 1]) > 0){
                swapdir = dir[i];
                dir[i] = dir[i + 1];
                dir[i + 1] = swapdir;
                }
            i--;
        }
    }
}