#ifndef STDTYPES_H
#define STDTYPES_H


typedef struct position position;
typedef struct string string;
typedef struct color color;

struct position {
    int x;
    int y;
};

void position_init(position* posn, int x, int y);
int position_get_x(position* posn);
int position_get_y(position* posn);
void position_set_x(position* posn, int x);
void position_set_y(position* posn, int y);

struct string {
    char* str;
    int strlen;
};

void string_init(string* str_obj, char* str);
void string_destroy(string* str_obj);
char* string_get_cstr(string* str);
int string_get_len(string* str);
void string_set_cstr(string* str, char* cstr);

struct color {
    char red;
    char green;
    char blue;
};

void color_init(color* color_obj, char r, char g, char b);
char color_get_red(color* color_obj);
char color_get_green(color* color_obj);
char color_get_blue(color* color_obj);
void color_set_red(color* color_obj, char red);
void color_set_green(color* color_obj, char green);
void color_set_blue(color* color_obj, char blue);


#endif
