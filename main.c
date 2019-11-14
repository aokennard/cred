#include "types.h"
#include "utils.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int32_t horizontal_res = DEFAULT_HORIZONTAL_RES;
    int32_t vertical_res = DEFAULT_VERTICAL_RES;

    printf("%d arguments passed in", argc - 1);

    int opt;

    // -x xres -y yres -d dialoguefile -s spritefile -m mapfile 
    while((opt = getopt(argc, argv, "x:y:d:s:m:"))) {
        switch (opt) {
            case 'x':
                if(is_number(optarg)) {
                    horizontal_res = atoi(optarg);
                } else {
                    printf("Invalid horizontal res, exiting");
                    return -1;
                }
                break;
            case 'y':
                if(is_number(optarg)) {
                    vertical_res = atoi(optarg);
                } else {
                    printf("Invalid vertical res, exiting");
                    return -1;
                }
                break;
            case 'd':
                
                break;
            case 's':
                
                break;
            case 'm':
                
                break;
            default:
                break;
        }
    }
}