#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PERMS 0644
#define DIRP 0755
#define MAX_NAME_SIZE 32

struct __User {
    char name[MAX_NAME_SIZE + 1];
    int age;
    int hakbun;
    int phone;
};
typedef struct __User User;

int main() {
    int fd = 0;
    char *pathname = "./2019203102/testfile.dat";

    if (mkdir("./2019203102", DIRP) == -1) {
        perror("mkdir() error!");
        exit(-1);
    }

    ssize_t wSize = 0;

    char userName[MAX_NAME_SIZE + 1] = "Jisung Yu";
    int userAge = 21;
    int userHakbun = 2019203102;
    int userPhone = 52909380;

    User *user = (User *)malloc(sizeof(User));
    memset(user->name, '\0', MAX_NAME_SIZE + 1);
    strcpy(user->name, userName);
    user->age = userAge;
    user->hakbun = userHakbun;
    user->phone = userPhone;

    fd = open(pathname, O_CREAT | O_TRUNC | O_RDWR, PERMS);
    if (fd == -1) {
        perror("open() error!");
        exit(-2);
    }

    wSize = write(fd, (User *)user, sizeof(User));
    if (wSize == -1) {
        perror("write() error!");
        exit(-3);
    }

    //    printf("fd: %d, size: %ld \n", fd, wSize);
    close(fd);
    free(user);

    fd = 0;
    ssize_t rSize = 0;

    User *rUser = (User *)malloc(sizeof(User));
    memset(rUser->name, '\0', MAX_NAME_SIZE + 1);
    rUser->age = 0;
    rUser->hakbun = 0;
    rUser->phone = 0;

    fd = open(pathname, O_RDONLY, PERMS);
    if (fd == -1) {
        perror("open() error!");
        exit(-4);
    }

    rSize = read(fd, (User *)rUser, sizeof(User));
    if (rSize == -1) {
        perror("read() error!");
        exit(-5);
    }
    printf("User Name: %s\nAge: %d\nStudent ID: %d\nPhone: %d\n", rUser->name,
           rUser->age, rUser->hakbun, rUser->phone);

    close(fd);
    free(rUser);

    return 0;
}
