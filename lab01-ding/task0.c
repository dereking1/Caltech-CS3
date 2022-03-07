#include <stdio.h>
#include <string.h>

void string_print(char *s) {
    int i = 0;
    for (i = 0; i < strlen(s); i++) {
        if (i < 10) {
            printf("0%d: %c\n", i, s[i]);
        }
        else {
            printf("%d: %c\n", i, s[i]);
        }
    }
}


int main(int argc, char *argv[]) {
    string_print("Adam");
}