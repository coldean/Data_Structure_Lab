#define _GNU_SOURCE ;

#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_PATH_LEN 1024

void myError(const char *msg);
void fileType(const struct stat *fileInfo);
void fileMode(const struct stat *fileInfo);

int main(int argc, char const *argv[]) {
    struct stat fileInfo;
    struct passwd *userInfo;

    DIR *dirp;
    struct dirent *dirInfo;
    char cwd[MAX_PATH_LEN + 1] = {'\0'};

    // const char path[MAX_PATH_LEN] = "./first";

    // argv가 인식이 안됨. ./제거하고 폴더명만 적으면 작동
    if (chdir(argv[1]) == -1) {
        perror("chdir() error!");
        exit(-1);
    }

    if (getcwd(cwd, MAX_PATH_LEN) == NULL) {
        perror("getcwd() error!");
        exit(-1);
    }

    if (argc != 2) {
        printf("Usage: %s [pathname]\n", argv[0]);
        exit(-1);
    }

    dirp = opendir(argv[1]);
    while ((dirInfo = readdir(dirp)) != NULL) {
        // printf("File name or path: %s\n", argv[1]);
        if (stat((cwd, argv[1], dirInfo->d_name), &fileInfo) == -1) {
            myError("stat() error!");
        }

        // file permission
        fileMode(&fileInfo);

        // owner name
        userInfo = getpwuid(fileInfo.st_uid);
        printf("%s  ", userInfo->pw_name);

        // file size
        printf("%7ld  ", fileInfo.st_size);

        // modified time
        printf("%ld  ", fileInfo.st_mtime);

        // file name
        printf("%s\n", dirInfo->d_name);
        // fileType(&fileInfo);
    }

    closedir(dirp);

    return 0;
}

void myError(const char *msg) {
    perror(msg);
    exit(-1);
}

void fileType(const struct stat *fileInfo) {

    //디렉토리 읽으면서 받아온 파일 이름 출력하게 변경하기
    if (S_ISREG(fileInfo->st_mode)) {
        printf("Regular file");
    }
    //
    else if (S_ISDIR(fileInfo->st_mode)) {
        printf("Directory");
    } else if (S_ISLNK(fileInfo->st_mode)) {
        printf("Symbolic link");
    } else if (S_ISSOCK(fileInfo->st_mode)) {
        printf("Socket");
    } else if (S_ISFIFO(fileInfo->st_mode)) {
        printf("FIFO");
    } else if (S_ISCHR(fileInfo->st_mode)) {
        printf("Character device");
    } else if (S_ISBLK(fileInfo->st_mode)) {
        printf("Block device");
    } else if (S_TYPEISMQ(fileInfo)) {
        printf("Message queue");
    } else if (S_TYPEISSEM(fileInfo)) {
        printf("Semaphore");
    } else if (S_TYPEISSHM(fileInfo)) {
        printf("Shared memory");
    }
    puts("");
}

void fileMode(const struct stat *fileInfo) {
    // User

    if (S_ISDIR(fileInfo->st_mode)) {
        printf("d");
    } else if (S_ISLNK(fileInfo->st_mode)) {
        printf("l");
    } else {
        printf("-");
    }

    if (S_IRUSR & fileInfo->st_mode) {
        printf("r");
    } else {
        printf("-");
    }

    if (S_IWUSR & fileInfo->st_mode) {
        printf("w");
    } else {
        printf("-");
    }

    if (S_IXUSR & fileInfo->st_mode) {
        printf("x");
    } else {
        printf("-");
    }

    // Group
    if (S_IRGRP & fileInfo->st_mode) {
        printf("r");
    } else {
        printf("-");
    }

    if (S_IWGRP & fileInfo->st_mode) {
        printf("w");
    } else {
        printf("-");
    }

    if (S_IXGRP & fileInfo->st_mode) {
        printf("x");
    } else {
        printf("-");
    }

    // Others
    if (S_IROTH & fileInfo->st_mode) {
        printf("r");
    } else {
        printf("-");
    }

    if (S_IWOTH & fileInfo->st_mode) {
        printf("w");
    } else {
        printf("-");
    }

    if (S_IXOTH & fileInfo->st_mode) {
        printf("x");
    } else {
        printf("-");
    }

    //    puts("");
    printf("  ");
}
