#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <string.h>
#include <grp.h>

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


void writeString(int fd, const char* str) {
    write(fd, str, strlen(str));
}

void writeNumber(int fd, unsigned long number) {
    char numStr[20]; // 충분히 큰 배열을 선언
    int i = 19;

    numStr[i--] = '\0'; // 널 문자로 종료
    if (number == 0) {
        numStr[i--] = '0';
    } else {
        while (number != 0 && i) {
            numStr[i--] = (number % 10) + '0';
            number /= 10;
        }
    }

    write(fd, &numStr[i + 1], strlen(&numStr[i + 1]));
}

void printTime(time_t modTime) {
    // ctime() 함수를 사용하여 time_t 값을 문자열로 변환
    char *timeString = ctime(&modTime);
    
    // ctime()에서 반환된 문자열은 개행 문자를 포함하므로 이를 제거
    size_t len = ft_strlen(timeString);
    if (len > 0 && timeString[len - 1] == '\n') {
        timeString[len - 1] = ' ';
    }

    // STDOUT_FILENO를 사용하여 표준 출력에 시간 문자열을 출력
    write(1, timeString, strlen(timeString));
}

int main() {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            struct stat fileInfo;
            if (stat(dir->d_name, &fileInfo) == 0) {
                printPermissions(fileInfo.st_mode);
                writeNumber(STDOUT_FILENO, fileInfo.st_nlink);
                writeString(STDOUT_FILENO, " ");

                // 사용자 이름과 그룹 이름 출력
                struct passwd *pw = getpwuid(fileInfo.st_uid);
                struct group  *gr = getgrgid(fileInfo.st_gid);
                writeString(STDOUT_FILENO, pw->pw_name);
                writeString(STDOUT_FILENO, " ");
                writeString(STDOUT_FILENO, gr->gr_name);
                writeString(STDOUT_FILENO, " ");

                // 파일 크기 출력
                writeNumber(STDOUT_FILENO, fileInfo.st_size);
                writeString(STDOUT_FILENO, " ");

                // 수정 시간 출력
                printTime(fileInfo.st_mtime);

                // 디렉토리 이름 출력
                writeString(STDOUT_FILENO, dir->d_name);
                writeString(STDOUT_FILENO, "\n");
            }
        }
        closedir(d);
    }
    return 0;
}
