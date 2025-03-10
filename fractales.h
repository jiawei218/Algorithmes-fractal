#ifndef _FRACTALES_H_
#define _FRACTALES_H_


#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif /* _MSC_VER */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <complex.h>
#include "qdbmp.h"


// Definition de la taille de l'image
#define WIDTH 600
#define HEIGHT 380

#define LENGTH 50

#define PI 3.1415926
#define START_POS1   -0.5
#define START_POS2   1.125-0.17592I
#define START_ZOOM  (WIDTH * 0.25296875f)
#define BAIL_OUT        2.0
#define ZOOM_FACTOR     4

extern float offsetAngle ; // 左右枝干和父枝干偏离的角度
//extern float shortenRate ;  // 子枝干比父枝干变短的倍数

BMP* imagemandelbrot;
BMP* imagegraymandelbrot;
BMP* filtrebefman;
BMP* filtremandelbrot;
BMP* flouterbefmandel;
BMP* floutermandel;

BMP* filtrebefjulia;
BMP* imagejulia;
BMP* imagegrayjulia;
BMP* filtrejulia;
BMP* flouterbefjulia;
BMP* flouterjulia;



void sdl_draw_mandelbrot(SDL_Window *window, SDL_Surface *surface,  double complex center, double zoom);

void sdl_draw_julia(SDL_Window *window, SDL_Surface *surface,  double complex center,double zoom, double complex c);

void sdl_draw_tree(SDL_Window *window,SDL_Renderer *renderer, float x_start,float y_start,float length,float angle,int generation, int maxgene, float shortenRate);

#endif
