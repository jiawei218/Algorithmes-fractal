#include "fractales.h"

float offsetAngle = PI/6;
//float shortenRate = 0.75;

void sdl_draw_mandelbrot(SDL_Window *window, SDL_Surface *surface,  double complex center, double zoom)
{
//BMP
  imagemandelbrot = BMP_Create(WIDTH, HEIGHT, 32);

    int f,x,y,n;
    int maxiter =  60; //(WIDTH/2) * 0.049715909 * log10(zoom); 

    complex double z, c;
    float C;

    fprintf(stderr, "zoom: %f\n", zoom);
    fprintf(stderr, "center point: %f %+fi\n", creal(center), 
                                              cimag(center) );
    fprintf(stderr, "iterations: %d\n", maxiter);

        for  (y = 0; y < HEIGHT; y ++)
        {
            for (x = 0; x < WIDTH; x++)
            {
                /* Get the complex poing on gauss space to be calculate */
                z = c = creal(center) + ((x - (WIDTH/2))/zoom) + 
                    ((cimag(center) + ((y - (HEIGHT/2))/zoom))*_Complex_I);

                #define X creal(z) // on prend la partie réel de Z
                #define Y cimag(z) // on prend la partie immaginaire de Z

                /* Check if point lies within the main cardiod or 
                   in the period-2 buld */
                if ( (pow(X-.25,2) + pow(Y,2))*(pow(X,2) + (X/2) + pow(Y,2) - .1875) < pow(Y,2)/4 ||
                     pow(X+1,2) + pow(Y,2) < .0625 )
                    n = maxiter;
                else
                    for (n = 0; n <= maxiter && cabs(z) < BAIL_OUT; n ++)
                        z = cpow(z, 2) + c; 

                C = n - log2f(logf(cabs(z)) / M_LN2 );
                //M_LN2:ln(2)

                /* Paint the pixel calculated depending on the number 
                   of iterations found */
                   if(n >=maxiter)
                   {
                      ((Uint32*)surface->pixels)[(y*surface->w) + x] = 0;
                      BMP_SetPixelRGB(imagemandelbrot, x, y, 0, 0, 0);
                       //BMP_CHECK_ERROR( stderr, -2 );
                   }               
                    else
                    {
                      ((Uint32*)surface->pixels)[(y*surface->w) + x] = SDL_MapRGB(surface->format,(1+sin(C*0.27 + 5))*127., (1+cos(C*0.85))*127., (1+sin(C*0.15))*127. );

                      BMP_SetPixelRGB(imagemandelbrot, x, y, (1+sin(C*0.27 + 5))*127., (1+cos(C*0.85))*127., (1+sin(C*0.15))*127.);
                    }
                    
                     
                    // ((Uint32*)surface->pixels)[(y*surface->w) + x] = SDL_MapRGB(surface->format,100+n*10, 155+n*20, 100  );

            }
        }
        SDL_UpdateWindowSurface(window);
}


void sdl_draw_julia(SDL_Window *window, SDL_Surface *surface,  double complex center,double zoom, double complex c)
{

  imagejulia = BMP_Create(WIDTH, HEIGHT, 32);
  int f,x,y,n;
  int maxiter =40;//(WIDTH/2) * 0.049715909 * log10(zoom); 

  complex double z, z_o;
    
  float C;

    //int num=0;

    fprintf(stderr, "zoom: %f\n", zoom);
    fprintf(stderr, "center point: %f %+fi\n", creal(center), 
                                              cimag(center) );
    fprintf(stderr, "C défini: %f %+fi\n", creal(c),
                  cimag(c));                 
    fprintf(stderr, "iterations: %d\n", maxiter);

    for  (y = 0; y < HEIGHT; y ++)
        {
            for (x = 0; x < WIDTH; x++)
            {
                /* Get the complex poing on gauss space to be calculate */
                z_o = creal(center) + ((x - (WIDTH/2))/zoom) + 
                    ((cimag(center) + ((y - (HEIGHT/2)))/zoom)*_Complex_I);

                z=z_o+c;

                #define X creal(z) // on prend la partie réel de Z
                #define Y cimag(z) // on prend la partie immaginaire de Z

                /* Check if point lies within the main cardiod or 
                   in the period-2 buld */
               
                for (n = 0; n <= maxiter && cabs(z) < BAIL_OUT; n ++)        
                  z = cpow(z, 2) + c; 
                

                C = n - log2f(logf(cabs(z)) / M_LN2 );

                /* Paint the pixel calculated depending on the number 
                   of iterations found */
                   if(n >=maxiter)                   
                    {
                      ((Uint32*)surface->pixels)[(y*surface->w) + x] = 0;
                    BMP_SetPixelRGB(imagejulia, x, y, 0, 0, 0);
                    }
                    else
                    {
                      ((Uint32*)surface->pixels)[(y*surface->w) + x] = SDL_MapRGB(surface->format,(1+sin(C*0.27 + 5))*127., (1+cos(C*0.85))*127., (1+sin(C*0.15))*127. );
                      BMP_SetPixelRGB(imagejulia, x, y, (1+sin(C*0.27 + 5))*127., (1+cos(C*0.85))*127., (1+sin(C*0.15))*127.);
                    }


            }
        }
        SDL_UpdateWindowSurface(window);

}


void sdl_draw_tree(SDL_Window *window,SDL_Renderer *renderer, float x_start,float y_start,float length,float angle,int generation,int maxgene,float shortenRate)
{
  //bmp
  //imagetree = BMP_Create(WIDTH, HEIGHT, 32);

	// 利用三角函数求出当前枝干的终点x,y坐标
	int x_end, y_end;
	x_end = x_start + length * cos(angle);
	y_end = y_start + length * sin(angle);
	
	//画线
	SDL_RenderDrawLine(renderer, x_start, y_start, x_end, y_end);

	int Childgeneation = generation + 1;
	float Childlength = length * shortenRate;

	if (Childlength >= 2 && Childgeneation <= maxgene)
	{
		//for left
		sdl_draw_tree(window, renderer, x_end, y_end, Childlength, angle + offsetAngle, Childgeneation,maxgene,shortenRate);
		
	}

  Childgeneation = generation + 1;
  Childlength = length * shortenRate;
	x_end = x_start + length * cos(angle);
	y_end = y_start + length * sin(angle);
	if (Childlength >= 2 && Childgeneation <= maxgene)
	{
		sdl_draw_tree(window, renderer, x_end, y_end, Childlength, angle - offsetAngle, Childgeneation,maxgene,shortenRate);
	}

	SDL_RenderPresent(renderer); // Show render on window
 
}
