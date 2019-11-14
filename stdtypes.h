#ifndef STDTYPES_H
#define STDTYPES_H

typedef struct position position;
typedef struct string string;
typedef struct color color;

struct position {
    int x;
    int y;
};

struct string {
    char* str;
    int strlen;
};

struct color {
    char red;
    char green;
    char blue;
};

#endif
