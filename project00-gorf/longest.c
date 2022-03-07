#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *find_next_word(FILE *f) {
    int len = 0;
    char *word = malloc(100 * sizeof(char));
    char c = fgetc(f);
    while (c != EOF) {
        if (c == '\n' || c == ' ') {
            break;
        }
        else {
            word[len] = c;
            len++;
        }
        c = fgetc(f);
    }
    return word;
}

char *longest_word(char *word1, char *word2) {
    if (strlen(word1) > strlen(word2)) {
        return word1;
    }
    return word2;
}

char *allocate(int size) {
    char *string = malloc(size * sizeof(char));
    string[0] = '\0';
    return string;
}

int check_usage(int argc, char *arg1, char *arg2) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", arg1);
        return 1;
    }
    if (fopen(arg2, "r") == NULL) {
        printf("longest: %s: No such file or directory\n", arg2);
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (check_usage(argc, argv[0], argv[1]) == 1) {
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    // helpers: finding next word, longest word
    char *longest = allocate(101);
    char *temp = allocate(101);
    int temp_len = 0;
    char c = fgetc(f);
    while (c != EOF) {
        if (c == '\n' || c == ' ') {
            temp[temp_len] = '\0';
            if (strlen(temp) > strlen(longest)) {
                strcpy(longest, temp);
            }
            temp[0] = '\0';
            temp_len = 0;
        }
        else {
            temp[temp_len] = c;
            temp_len++;
        }
        c = fgetc(f);
    }
    if (strlen(longest) > 0) {
        printf("%s\n", longest);
    }
    free(longest);
    free(temp);
    return fclose(f);
}
