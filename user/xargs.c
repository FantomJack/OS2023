//
// Created by belan on 10/1/2023.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user.h"


char* strcat(char* destination, const char* source){
    char* ptr = destination + strlen(destination);

    while (*source != '\0') {
        *ptr++ = *source++;
    }
    *ptr = '\0';

    return destination;
}



int main (int argc, char * argv[]){

    char * argv_new[10];
    for (int i = 0; i < 10; ++i) {
        argv_new[i] = (char *) malloc(50);
        argv_new[i][0] = '\0';
    }
    char buf;
    int argc_new = 0;
    while ( read(0, &buf, 1) != 0){
        if(buf != ' '){
            argv_new[argc_new] = strcat(argv_new[argc_new], &buf);
        }else{
            argc_new++;
        }
    }

    for (int i = 0; i < 10; ++i) {
        char * ptr = argv_new[i];
        while ( *ptr != '\0') {
            fprintf(1, "%d ", *ptr);
            ptr++;
        }
        fprintf(1, "\n %d\n", strlen(argv_new[i]));
        free(argv_new[i]);
    }

//    wait( (int *) 0);
    exit(0);
}