#include "match.h"
#include <string.h>

bool match(char *pattern, char *text) {
    if (*pattern == '\0') {
        return strlen(text) == 0;
    }
    if (*(pattern+1) == '*') {
        // no match: skip
        // match
        //case1: read next character of text (in star)
        //case2: skip star
        // 2 true, 1 false -> true -> 1 or 2
        if (*pattern == *text || (*pattern == '.' && *text != '\0')) {
            bool in_star = match(pattern, text+1);
            bool skip_star = match(pattern+2, text);
            return in_star == true || skip_star == true;
        }
        return match(pattern+2, text);
    }
    if (*text == '\0' || *pattern == '\0') {
        return *text == '\0' && *pattern == '\0';
    }
    if (*pattern == '.' && *text != '\0') {
        return match(pattern+1, text+1);
    }
    if (*pattern == *text) {
        return match(pattern+1, text+1);
    }
    return false;
}