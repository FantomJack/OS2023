//
// Created by belan on 9/29/2023.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int fds[2];
    char buf[2];
    int ret = pipe(fds);
    if (ret != 0){
        fprintf(2, "pipe error\n");
    }

    int pid = fork();
    if( pid > 0){
        write(fds[1], ".", 1);
        wait( (int *) 0);
        read(fds[0], buf, 1);
        fprintf(1, "%d: received pong\n", getpid());
        close(fds[0]);
        close(fds[1]);
        exit(0);
    } else if(pid == 0){
        read(fds[0], buf, 1);
        fprintf(1, "%d: received ping\n", getpid());
        write(fds[1], buf, 1);
        close(fds[0]);
        close(fds[1]);
        exit(0);
    }
    else{
        fprintf(2, "fork error\n");
    }

    exit(0);
}
