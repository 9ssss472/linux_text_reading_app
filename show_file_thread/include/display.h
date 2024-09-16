#ifndef _DISP_MANAGER_H
#define _DISP_MANAGER_H

#include <stdio.h>

typedef struct dispOpr{
    char *name;
    int xres;
    int yres;
    int bpp;
    int (*dispInit)(void);
    int (*drawOnePixel)(int x, int y, int color);
    int (*cleanScreen)(unsigned int color);
    struct dispOpr *pNext;
}T_dispOpr, *PT_dispOpr; 

int registerDisOpr(PT_dispOpr dispOpr);
int FbInit(void);
int DisplayInit(void);
PT_dispOpr getDispOpr(char * name);
int showDispOpr(void);
int getResolution(int *xRes, int *yRes);


#endif 

