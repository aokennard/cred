#include "utils.h"

int is_number(char* str) {
    int length = strlen(str);
    for(int i = 0; i < length; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int is_number_s(string str) {
    for(int i = 0; i < str.strlen; i++) {
        if (!isdigit(str.str[i])) {
            return 0;
        }
    }
    return 1;
}