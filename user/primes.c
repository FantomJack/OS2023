//
// Created by belan on 9/29/2023.
//

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void child_cycle(int fds[2]){

    int buf;
    close(fds[1]);
    read(fds[0], &buf, sizeof(buf));
    int p = buf;
    if( buf == 0) exit(0);
    fprintf(1, "prime %d\n", p);
    int new_fds[2];
    pipe(new_fds);
    int pid = fork();

    if (pid > 0) {
        close(new_fds[0]);

        while (read(fds[0], &buf, sizeof(buf)) != 0) {
            if (buf % p != 0) {
//                fprintf(1, "%d ", buf);
                write(new_fds[1], &buf, sizeof(buf));
            }
        }
        close(new_fds[1]);
        close(fds[0]);
        wait((int *) 0);
        exit(0);
    } else if ( pid == 0) {
        child_cycle(new_fds);
    } else{
        fprintf(2, "fork error");
    }

    exit(0);
}


int main(int argc, char *argv[]) {

    int fds[2];
    pipe(fds);

    int pid = fork();

    if (pid > 0) {
        close(fds[0]);
        for (int i = 2; i <= 35; ++i) {
            write(fds[1], &i, sizeof(i));
        }
        close(fds[1]);
        wait((int *) 0);
        exit(0);

    } else if (pid == 0) {

        child_cycle(fds);

    } else {
        fprintf(2, "fork error");
    }


    exit(0);
}