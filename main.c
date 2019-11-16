#include "types.h"
#include "stdtypes.h"
#include "utils.h"
#include "graphics.h"

#include <stdio.h>
#include <unistd.h>

extern char* optarg;

int main(int argc, char* argv[]) {
    int horizontal_res = DEFAULT_HORIZONTAL_RES;
    int vertical_res = DEFAULT_VERTICAL_RES;
    string dialogue_fn;
    string graphic_fn;
    string map_fn;
    string_init(&dialogue_fn, DIALOGUE_FN);
    string_init(&graphic_fn, GRAPHICS_FN);
    string_init(&map_fn, MAP_FN);

    printf("%d arguments passed in\n", argc - 1);

    int opt;

    // -x xres -y yres -d dialoguefile -g graphicfile -m mapfile 
    while((opt = getopt(argc, argv, "x:y:d:g:m:")) != -1) {
        switch (opt) {
            case 'x':
                if(is_number(optarg)) {
                    horizontal_res = atoi(optarg);
                } else {
                    printf("Invalid horizontal res, exiting\n");
                    return -1;
                }
                break;
            case 'y':
                if(is_number(optarg)) {
                    vertical_res = atoi(optarg);
                } else {
                    printf("Invalid vertical res, exiting\n");
                    return -1;
                }
                break;
            case 'd':
                string_set_cstr(&dialogue_fn, optarg);
                break;
            case 'g':
                string_set_cstr(&graphic_fn, optarg);
                break;
            case 'm':
                string_set_cstr(&map_fn, optarg);
                break;
            default:
                break;
        }
    }

    printf("Done arg parsing, launching\n");

    int graphic_ret = 0;
    
    if((graphic_ret = init_graphics_mode())) {
        printf("Failed launching graphics with code %d\n", graphic_ret);
        return -1;
    }

    

    string_destroy(&map_fn);
    string_destroy(&graphic_fn);
    string_destroy(&dialogue_fn);
}