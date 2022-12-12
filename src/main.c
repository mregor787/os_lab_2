#include "fcntl.h"
#include "unistd.h"
#include "string.h"
#include "stdio.h"

int main() {
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    if (pipe(fd1) == -1) {
        perror("Pipe1 error\n");
        return -1;
    }
    if (pipe(fd2) == -1) {
        perror("Pipe2 error\n");
        return -1;
    }
    
    char str[1000] = {};
    char *msg = "Enter the string (use ~ as end of input):\n";
    write(1, msg, sizeof(char) * strlen(msg));
    for (int i = 0; i < 1000; ++i) {
        read(0, &str[i], sizeof(char));
        if (str[i] == '~') {
            char c;
            read(0, &c, sizeof(char));
            break;
        }
    }
    int len = strlen(str);
    write(fd1[1], str, sizeof(char) * len);
    
    int ch1 = fork();
    if (ch1 == -1) {
        perror("Child1 error\n");
        return -1;
    }
    else if (ch1 == 0) {
        char str_ch1[len];
        read(fd1[0], str_ch1, sizeof(char) * len);
        char *args[] = {str_ch1, NULL};
        dup2(fd1[1], 1);
        execv("./child1", args);
    }
    else {
        int ch2 = fork();
        if (ch2 == -1) {
            perror("Child2 error\n");
            return -1;
        }
        else if (ch2 == 0) {
            char str_ch2[len];
            read(fd1[0], str_ch2, sizeof(char) * len);
            char *args[] = {str_ch2, NULL};
            dup2(fd2[1], 1);
            execv("./child2", args);
        }
        else {
            char str_res[len];
            read(fd2[0], str_res, sizeof(char) * len);
            char *msg = "Result string:\n";
            write(1, msg, sizeof(char) * strlen(msg));
            int i = 0;
            while (str_res[i] != '~') {
                write(1, &str_res[i], sizeof(char));
                ++i;
            }
            write(1, "\n", sizeof(char));
        }
    }
    return 0;
}