#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "match.h"

void check(bool actual, char *pattern, char *text) {
    size_t buffer_size = (22 + strlen(pattern) + strlen(text) + 1);
    char *buffer = malloc(buffer_size * sizeof(char));
    strcpy(buffer, "echo ");
    strcat(buffer, "\"");
    strcat(buffer, text);
    strcat(buffer, "\"");
    strcat(buffer, " | grep -c \"^");
    strcat(buffer, pattern);
    strcat(buffer, "$\"\0");
    FILE *f = popen(buffer, "r");
    char acc;
    if (actual == true) {acc = '1';}
    else {acc = '0';}
    assert(fgetc(f) == acc);
    pclose(f);
    free(buffer);
}

bool is_valid(char *string, size_t length) {
    for (size_t i = 0; i < length; i++) {
        char c = string[i];
        if (isalpha(c) == 0) {
            if (c != '*') {
                return false;
            }
            if (i < length - 1) {
                if (string[i + 1] == '*') {
                    return false;
                }
            }
        }
    }
    return true;
}

int LLVMFuzzerTestOneInput(uint8_t *data, size_t size) {
    size_t intsize = size / sizeof(int8_t);
    uint8_t *intdata = (uint8_t *)data;
    if (intsize >= 2) {
        size_t len1 = intdata[0];
        if (size >= sizeof(uint8_t) + len1) {
            size_t len2 = size - sizeof(uint8_t) - len1;
            char *str = ( (char *)intdata ) + 1;
            char *str1 = calloc(len1 + 1, sizeof(char));
            char *str2 = calloc(len2 + 1, sizeof(char));
            strncpy(str1, str, len1);
            strncpy(str2, str + len1, len2);
            if (is_valid(str1, len1) && is_valid(str2, len2))  {
                printf("s1=%s, s2=%s\n", str1, str2);
                bool result = match(str1, str2);
                check(result, str1, str2);
                free(str1);
                free(str2);
                return result;
            }
            free(str1);
            free(str2);
        }
    }
    return 0;
}