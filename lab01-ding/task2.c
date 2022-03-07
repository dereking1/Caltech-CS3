#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **string_blanks(char *s) {
    char **blanks = malloc(strlen(s)* sizeof(char *));
    for (int i = 0; i < strlen(s); i++) {
        blanks[i] = malloc(strlen(s) + 1);
        for (int j = 0; j < strlen(s); j++) {
            if (i == j) {
                blanks[i][j] = '_';
            }
            else {
                blanks[i][j] = s[j];
            }
        }
        blanks[i][strlen(s)] = '\0';
    }
    return blanks;
}

int main(int argc, char *argv[]) {
    char **blanks = string_blanks("Adam");
    for (int i = 0; i < strlen("Adam"); i++) {
        printf("%s ", blanks[i]);
        free(blanks[i]);
    }
    printf("\n");
    free(blanks);
}