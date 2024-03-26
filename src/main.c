#include "../header/ft_ls.h"

void process_directory(char *dir_path, t_flags flags, size_t idx, size_t size) {
    char **dir2;
    size_t i;

    i = idx;
    dir2 = Rdircheck(dir_path, flags);
    dir_sort(dir2, flags);
    while (dir2 && dir2[i]){
        if (size != 1 || i != 0){
            put_str_fd(1, dir2[i]);
            put_str_fd(1,":\n");
        }
        ls_execute(dir2[i], flags);
        if(dir2[i + 1])
            write(1,"\n",1);
        if(i != 0)
            process_directory(dir2[i], flags, 1, 0);
        i++;
    }
    strAllfree(dir2);
}

int main(int argc, char **argv) {
    char **dir;
    t_flags flags;
    size_t idx;

    idx = 0;
    dir = flag_checker(argc, argv, &flags);
    dir_sort(dir, flags);
    while (dir[idx] && dir) {
        process_directory(dir[idx], flags, 0, dir_size(dir));
        idx++;
    }
    strAllfree(dir);
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
//     // system("leaks ft_ls");
// }