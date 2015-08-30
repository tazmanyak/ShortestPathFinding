#ifndef SVG_H_  
#define SVG_H_  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definitions
#define MAX_FILE_NAME 100
#define OUTPUT_FILE_NAME "svg_output.svg"



typedef struct
{
    int x;
    int y;
}Coord;

typedef struct
{
  char xy[20];        
        
}SVG;



void generate_svg(char *input, char *output);
//storage for coordinates

#endif
