#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    pid_t pid;
    pid_t pid2;
    int pipefd[2] = {
        0,
    };

    if (pipe(pipefd) == -1) {
        perror("pipe() error!");
        return -1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork() error!");
    } else if (pid == 0) {
        close(pipefd[0]);

        dup2(pipefd[1], STDOUT_FILENO);
        execl("/bin/cat", "cat", "/etc/passwd", NULL);
    } else {
        close(pipefd[1]);

        wait(&pid);

        dup2(pipefd[0], STDIN_FILENO);

        int fd = open("userlist.txt", O_CREAT | O_WRONLY, 0777);
        dup2(fd, STDOUT_FILENO);

        execl("/usr/bin/cut", "cut", "-d", ":", "-f", "1", NULL);
    }

    return 0;
}
