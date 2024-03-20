#include "../header/ft_ls.h"

int main(int argc, char **argv)
{
    DIR *ds;
    char **dir;
    // char **dir2;
    struct stat buf;
    t_flags flags;
    int idx = 0;

    dir = flag_checker(argc, argv, &flags);
    while (dir[idx] && dir){
        ds = opendir(dir[idx]);
        idx++;
        if(ds == NULL){
            printf("ls: %s: No such file or directory\n", dir[idx - 1]);
            continue;
        }
        while(1){
            struct dirent *obj = readdir(ds);
            if(obj == NULL)
                break;
            printf("%s\n", obj->d_name);
            stat(obj->d_name, &buf);
            // buf->st_atimespec, buf->st_birthtimespec, buf->st_blksize,
            // buf->st_blocks, buf->st_ctimespec, buf->st_dev
            // buf->st_flags, buf->st_gen, buf->st_gid
            // buf->st_ino, buf->st_lspare, buf->st_mode
            // buf->st_mtimespec,buf->st_nlink,buf->st_qspare
            // buf->st_rdev,buf->st_size,buf->st_uid
        }
    }
    // strAllfree(dir);
}