#ifndef _TRAITEMENTS_H_
#define _TRAITEMENTS_H_

#include "fractales.h"

int choix();

int chooses();

int imagegrey(BMP *bmp1, const char* filename1,const char* filename2);

int imagefiltre(BMP *bmp1,  BMP* bmp2, const char* filename1,const char* filename2);

int flouter(BMP *bmp1,BMP* bmp2,const char* filename1,const char* filename2);

#endif
