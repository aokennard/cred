#include "stdtypes.h"
#include <string.h>
#include <stdlib.h>

void position_init(position* posn, int x, int y) {
    posn->x = x;
    posn->y = y;
}

int position_get_x(position* posn) {
    return posn->x;
}

int position_get_y(position* posn) {
    return posn->y;
}

void position_set_x(position* posn, int x) {
    posn->x = x;
}

void position_set_y(position* posn, int y) {
    posn->y = y;
}

void string_init(string* str_obj, char* str) {
    str_obj->strlen = strlen(str);
    str_obj->str = malloc(str_obj->strlen + 1);
    strcpy(str_obj->str, str);
}

char* string_get_cstr(string* str) {
    return str->str;
}

int string_get_len(string* str) {
    return str->strlen;
}

void string_set_cstr(string* str, char* cstr) {
    str->strlen = strlen(cstr);
    str->str = realloc(str->str, str->strlen);
    strcpy(str->str, cstr);
}