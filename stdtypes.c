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

void string_destroy(string* str_obj) {
    free(str_obj->str);
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

void color_init(color* color_obj, char r, char g, char b) {
    color_obj->red = r;
    color_obj->green = g;
    color_obj->blue = b;
}

char color_get_red(color* color_obj) {
    return color_obj->red;
}

char color_get_green(color* color_obj) {
    return color_obj->green;
}

char color_get_blue(color* color_obj) {
    return color_obj->blue;
}

void color_set_red(color* color_obj, char red) {
    color_obj->red = red;
}

void color_set_green(color* color_obj, char green) {
    color_obj->green = green;
}

void color_set_blue(color* color_obj, char blue) {
    color_obj->blue = blue;
}
