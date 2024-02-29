#ifndef FILEREADING_H
#define FILEREADING_H

#include <stdio.h>
#include <stdlib.h>

char* readline(FILE* fp) {
    char c;
    int size = 120;
    char* buffer = malloc(sizeof(char) * size);
    int read = 0;  

    while (1) {
        c = fgetc(fp);
        if(c == '\n' || c == EOF || (feof(fp) != 0)) {
            break;
        }
        if(read >= size) {
            size *= 2;
            buffer = realloc(buffer, sizeof(char) * size);
        }
        buffer[read++] = c;
    }

    if(read == 0) {
        free(buffer);
        return NULL;
    }

    char* str = realloc(buffer, sizeof(char) * (read + 1));
    str[read] = '\0';
    return str;
}

#endif