#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int check_usage(int argc, char *arg1, char *arg2) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", arg1);
        return 1;
    }
    if (fopen(arg2, "r") == NULL) {
        printf("wc: %s: No such file or directory\n", arg2);
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (check_usage(argc, argv[0], argv[1]) == 1) {
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    int num_lines = 0;
    char c = fgetc(f);
    while (c != EOF) {
        if (c == '\n') {
            num_lines++;
        }
        c = fgetc(f);
    }
    printf("%d %s\n", num_lines, argv[1]);
    return fclose(f);
}