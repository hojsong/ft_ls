#include "../header/ft_ls.h"

void ft_invalid_option(){
    printf("ls: invalid options\n");
    exit (0);
}

char **flag_checker(int argc, char **argv, t_flags *flags){
    char **result;
    int i = 0;
    int x;

    while(argv[++i]){
        x = (int)ft_strlen(argv[i]);
        if(x > 1 && argv[i][0] == '-'){
            x = 0;
            while(argv[i][++x]){
                if(argv[i][x] == 'a')
                    flags->a = 1;
                else if(argv[i][x] == 'l')
                    flags->l = 1;
                else if(argv[i][x] == 'R')
                    flags->R = 1;
                else if(argv[i][x] == 'r')
                    flags->r = 1;
                else
                    ft_invalid_option();
            }
        }
        else
            break;
    }
    if (argc == i){
        result = malloc((sizeof(char *) * (2)));
        result[0] = ".";
        result[1] = NULL;
    }
    else {    
        result = malloc((sizeof(char *) * (argc - i + 2)));
        int idx = 0;
        while (argv[i + idx]){
            result[idx] = argv[i + idx];
            idx++;
        }
        result[idx]= NULL;
    }
    return result;
}
