#include "../header/ft_ls.h"

void    strAllfree(char **str){
    int i;

    if (str == NULL)
        return ;
    i = 0;
    while (str[i]){
        if(str[i])
            free(str[i]);
        i++;
    }
    if(str)
        free(str);
}

void printPermissions(mode_t mode) {
    char permissions[11] = "---------- "; // 기본 권한 문자열 초기화
    permissions[10] = ' '; // 마지막에 공백 추가

    if (S_ISDIR(mode)) permissions[0] = 'd';
    if (mode & S_IRUSR) permissions[1] = 'r';
    if (mode & S_IWUSR) permissions[2] = 'w';
    if (mode & S_IXUSR) permissions[3] = 'x';
    if (mode & S_IRGRP) permissions[4] = 'r';
    if (mode & S_IWGRP) permissions[5] = 'w';
    if (mode & S_IXGRP) permissions[6] = 'x';
    if (mode & S_IROTH) permissions[7] = 'r';
    if (mode & S_IWOTH) permissions[8] = 'w';
    if (mode & S_IXOTH) permissions[9] = 'x';

    // STDOUT_FILENO는 표준 출력을 나타내는 파일 디스크립터입니다.
    write(STDOUT_FILENO, permissions, sizeof(permissions));
}