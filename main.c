 #include "fractales.h"
 #include "traitements_simples.h"





double complex choose()
{
  double complex c;
  printf(" coucou le menu de choix\n");
  printf("1: c= 0 \n");
      printf("2: c= -1 \n");
      printf("3: c= 0.28 + 0.5312345 i \n");
      printf("4: c= -0.63 + 0.67 i \n");
      printf("5: c= 0.35 + 0.05 i \n");
      printf("6: c=-0.76 + 0.12 i \n");

     int k=1;
     while(k==1){
      printf("choisissez la value de c: \n");
      int cho=0;
      scanf("%d",&cho);
      switch(cho){
        case 1:
          c=0;
          k=0;
          break;
        case 2:
          c=-1;
          k=0;
          break;
        case 3:
           c= 0.28 + 0.5312345I;
           k=0;
          break;
        case 4:
          c= -0.63 + 0.67I;
          k=0;
          break;
        case 5:
          c= 0.35 + 0.05I;
          k=0;
          break;
        case 6:
          c=-0.76 + 0.12I;
          k=0;
          break;
        default:
          printf("un faux nombre \n");
          break;

      }
      
     }
     return c;
}

int remenu()
{
  int choixx;
  int bre=0;
  printf("* * * * * * * * * * * * * * * * * *\n");
  printf("Voulez-vous revenir au menu principal?: [oui:1 non:0]\n");
  printf("entrez la valeur de choix: ");
  scanf("%d",&choixx);
  if(choixx==0)
  {
    printf("* * * * * * * * * * * * * * * * * *\n");
    printf("merci d'utiliser.\nAU REVOIR!\n");
    exit(0);
  }                        
  else if(choixx==1)                             
    bre=1;

  return bre;
}

int main(int argc, char **argv)
{
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);

    SDL_Window *window;
    SDL_Renderer *renderer;

    window = SDL_CreateWindow("fractale", 
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WIDTH,  
            HEIGHT, 
            SDL_WINDOW_OPENGL
            );

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);


    int newbre;
    int choix=1;
    
    while(choix==1)
    {
      
      printf("* * * * * * * * * * * * * * * * * *\n");
      printf("Bienvenue dans 'Fractale Generator'\n");
      printf("* * * * * * * * * * * * * * * * * *\n");
      printf("choisissez le type de fractale, SVP: \n");      
      printf("1: mandelbrot\n2: julia \n3:tree\n");
      int num;
      scanf("%d", &num);
      if(num==1)
    {
        double complex center = START_POS1;
      //double complex c = -0.76 + 0.12I;
        double zoom = START_ZOOM;
        printf("* * * * * * * * * * * * * * * * * *\n");
        printf("ATTENTION\n");
        printf("Dans cette partie, \nutiliser le clavier:\n # Barre d'espace(' '): Afficher l'image originale\n # Touche entrée(enter): Enreigistrer l'image actuelle en tant qu'image au format bmp\n # Touche d'échappement(ESC): Revenir au menu principal\nutiliser la souris:\n # Bouton gauche: Afficher la nouvelle image agrandie\n # Bouton droite: Afficher la nouvelle image réduite\n");
        printf("* * * * * * * * * * * * * * * * * *\n");

        sdl_draw_mandelbrot(window, surface, center, zoom);
        SDL_Event event;
        while(1)
        {
            SDL_PollEvent(&event);
            switch (event.type)
            {
              case SDL_QUIT:
                  exit(0);
                  break;
              case SDL_KEYDOWN:
                  if (event.key.keysym.sym == ' ')
                  {
                    printf("* * * * * * * * * * * * * * * * * *\n");
                      printf("l'image originale\n");
                      center = START_POS1;
                      zoom = START_ZOOM;

                      sdl_draw_mandelbrot(window, surface, center, zoom); 
                    
                  }
                  else if(event.key.keysym.sym ==SDLK_RETURN)
                  {
                    printf("* * * * * * * * * * * * * * * * * *\n");
                    BMP_WriteFile(imagemandelbrot,"imagemandelbrot.bmp");
                    BMP_CHECK_ERROR( stderr, -1 );
                    printf("l'image de mandelbrot: succès\n");

                    printf("- - - - - - - - - - - - - - - - - \n");
                    //noir et blanc
                    printf("Voulez-vous transformer l'image d'une fractale en noir et blanc:(0:non; 1:oui)\n");
                    int nbchoix;
                    printf("votre choix: ");
                    scanf("%d",&nbchoix);
                    if(nbchoix==1)
                    {                      
                      imagegrey(imagegraymandelbrot, "imagemandelbrot.bmp", "imagegraymandelbrot.bmp");
                      
                      printf("l'image de gray mandelbrot: succès\n");                      
                    }
                    else 
                      printf("merci!\n");
                      //filtre
                    while(1)
                    {
                      printf("- - - - - - - - - - - - - - - - - \n");
                      printf("Voulez-vous transformer l'image d'une fractale du filtre:(0:non; 1:oui)\n");
                      int nbchoixa;
                      printf("votre choix: ");
                      scanf("%d",&nbchoixa);
                      if(nbchoixa==1)
                      {                      
                        imagefiltre(filtrebefman,filtremandelbrot, "imagemandelbrot.bmp", "filtremandelbrot.bmp");
                      
                        printf("l'image de mandelbrot du filtre: succès\n");                      
                      }
                      else{
                        printf("merci!\n");
                        break;
                      } 
                      
                    }
                    
                    //BMP_Free(imagemandelbrot); le mettre à la fin du programme, avant qu'il se termine
                    while(1)
                    {
                      printf("- - - - - - - - - - - - - - - - - \n");
                      printf("Voulez-vous flouter l'image d'une fractale :(0:non; 1:oui)\n");
                      int nbchoixb;
                      printf("votre choix: ");
                      scanf("%d",&nbchoixb);
                      if(nbchoixb==1)
                      {                      
                        flouter(flouterbefmandel, floutermandel, "imagemandelbrot.bmp", "imafloumandel.bmp");
                      
                        printf("flouter l'image de mandelbrot: succès\n");                      
                      }
                      else {
                        printf("merci!\n");
                        break;
                      }

                    }
                    
                  }
                  else if (event.key.keysym.sym ==SDLK_ESCAPE)
                    {
                      newbre=remenu();
                    }
                    break;
              case SDL_MOUSEBUTTONDOWN:
                  center = creal(center) + ((event.button.x - (WIDTH/2))/zoom) +
                         ((cimag(center) + ((event.button.y - (HEIGHT/2))/zoom))
                          *_Complex_I);

                  if (event.button.button == 1){
                    printf("* * * * * * * * * * * * * * * * * *\n");
                    printf("bouton gauche:\n");
                    zoom *= ZOOM_FACTOR;
                  }                      
                  else if (event.button.button == 3){
                    printf("* * * * * * * * * * * * * * * * * *\n");
                    printf("bouton droite:\n");
                    zoom /= ZOOM_FACTOR;
                  }                 
                  sdl_draw_mandelbrot(window, surface, center, zoom);
                  break;
          }

        if(newbre==1){
          break;
          newbre=0;
        }
        }
     
        //break;  
    }
      else if(num==2)
    {
        double complex center = START_POS2;
        double complex c;
        double zoom = START_ZOOM;

        printf("* * * * * * * * * * * * * * * * * *\n");
        printf("ATTENTION\n");
        printf("Dans cette partie, \nutiliser le clavier:\n # Barre d'espace(' '): Revenir au menu de choix\n # Touche entrée(enter): Enreigistrer l'image actuelle en tant qu'image au format bmp\n # Touche d'échappement(ESC): Revenir au menu principal\nutiliser la souris:\n # Bouton gauche: Mouvement d'image\n ");
        printf("* * * * * * * * * * * * * * * * * *\n");
        c=choose();
        //printf("* * * * * * * * * * * * * * * * * *\n");


        sdl_draw_julia(window, surface,center,zoom,c); 

        SDL_Event event;
        while(1)
        {
            SDL_PollEvent(&event);
            switch (event.type)
            {
                case SDL_QUIT:
                  exit(0);
                  break;
                case SDL_KEYDOWN:
                  if (event.key.keysym.sym == ' ')
                  {
                    printf("* * * * * * * * * * * * * * * * * *\n");
                    
                    c=choose();                  
                    sdl_draw_julia(window, surface, center,zoom,c);
                  } 
                  else if(event.key.keysym.sym ==SDLK_RETURN)
                  {
                    printf("* * * * * * * * * * * * * * * * * *\n");
                    BMP_WriteFile(imagejulia,"imagejulia.bmp");
                    BMP_CHECK_ERROR( stderr, -2 );
                    printf("l'image de julia: succès\n");      printf("- - - - - - - - - - - - - - - - - \n");   
                    //BMP_Free(imagejulia);
                    printf("Voulez-vous transformer l'image d'une fractale en noir et blanc:(0:non; 1:oui)\n");
                    int nbchoix;
                    printf("votre choix: ");
                    scanf("%d",&nbchoix);
                    if(nbchoix==1)
                    {                      
                      imagegrey(imagegrayjulia, "imagejulia.bmp", "imagegrayjulia.bmp");
                      
                      printf("l'image de gray julia: succès\n");                      
                    }
                    else 
                      printf("merci!\n");
                    while(1)
                    {
                      printf("- - - - - - - - - - - - - - - - - \n");
                      printf("Voulez-vous transformer l'image d'une fractale du filtre:(0:non; 1:oui)\n");
                      int nbchoixa;
                      printf("votre choix: ");
                      scanf("%d",&nbchoixa);
                      if(nbchoixa==1)
                      {                      
                        imagefiltre(filtrebefjulia,filtrejulia, "imagejulia.bmp", "filtrejulia.bmp");
                      
                        printf("l'image de julia du filtre: succès\n"); 
                      }
                      else {
                        printf("merci!\n");
                        break;
                      }

                    }
                    while(1)
                    {
                      printf("- - - - - - - - - - - - - - - - - \n");
                      printf("Voulez-vous flouter l'image d'une fractale :(0:non; 1:oui)\n");
                      int nbchoixb;
                      printf("votre choix: ");
                      scanf("%d",&nbchoixb);
                      if(nbchoixb==1)
                      {                      
                        flouter(flouterbefjulia, flouterjulia, "imagejulia.bmp", "imafloujulia.bmp");
                      
                        printf("flouter l'image de julia: succès\n");                      
                      }
                      else {
                        printf("merci!\n");
                        break;
                      }
  
                    }
                                       
                  }
                  else if (event.key.keysym.sym == SDLK_ESCAPE)
                  {
                    newbre=remenu();
                  }
                     
                  break;
                case SDL_MOUSEBUTTONDOWN:
                  printf("* * * * * * * * * * * * * * * * * *\n");
                  center = creal(center) + ((event.button.x - (WIDTH/2))/zoom) +
                         ((cimag(center) + ((event.button.y - (HEIGHT/2)))/zoom)
                          *_Complex_I);

                  sdl_draw_julia(window, surface, center,zoom,c);
                  break;
             }
          if(newbre==1)
          {
            break;
            newbre=0;
          }
        }
    }
      else if(num==3)
      {
        float x_start1=WIDTH/2;
        float y_start1=HEIGHT/2;
        float length1=LENGTH;
        float angle1=-PI/2;
        int generation1=1;

        printf("* * * * * * * * * * * * * * * * * *\n");
        printf("ATTENTION\n");
        printf("Dans cette partie, \nutiliser le clavier:\n # Barre d'espace(' '): Afficher l'image originale\n # Touche entrée(enter): obtenir un arbre plus grand\n # Touche d'échappement(ESC): Revenir au menu principal\nutiliser la souris:\n # Bouton gauche: Mouvement d'image\n ");
        printf("* * * * * * * * * * * * * * * * * *\n");

        sdl_draw_tree(window,renderer, x_start1,  y_start1,  length1, angle1, generation1,9,0.75);

        SDL_Event event;
        while(1)
        {
            SDL_PollEvent(&event);
            switch (event.type)
            {
                case SDL_QUIT:
                  exit(0);
                  break;
                case SDL_KEYDOWN:
                  if (event.key.keysym.sym == ' ')
                  {
                    x_start1=WIDTH/2;
                    y_start1=HEIGHT/2;
                    length1=LENGTH;
                    angle1=-PI/2;
                    generation1=1;
					        	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
						        SDL_RenderClear(renderer);
						        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

						        sdl_draw_tree(window, renderer, x_start1, y_start1, length1, angle1, generation1,9,0.75);

                  } 
                  else if(event.key.keysym.sym ==SDLK_RETURN)
                  {
                    x_start1=WIDTH/2;
                    y_start1=(HEIGHT);
                    length1=75;
					        	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
						        SDL_RenderClear(renderer);
						        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

						        sdl_draw_tree(window, renderer, x_start1, y_start1, length1, angle1, generation1,14,0.85);

                  }
                  else if (event.key.keysym.sym == SDLK_ESCAPE)
                  {
                    newbre=remenu();
                  }
                     
                  break;
                case SDL_MOUSEBUTTONDOWN:
				        	x_start1 = event.button.x ;
				        	y_start1 = event.button.y ;
                  length1=LENGTH;
				        	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					        SDL_RenderClear(renderer);
				        	SDL_SetRenderDrawColor(renderer, 0,255, 0, SDL_ALPHA_OPAQUE);
					        sdl_draw_tree(window, renderer, x_start1, y_start1, length1, angle1, generation1,9,0.75);
                  
                  break;
             }
          if(newbre==1)
          {
            break;
            newbre=0;
          }
        }
      }
      else SDL_Quit();
    }
    
    BMP_Free(filtrebefman);
    BMP_Free(filtremandelbrot);
    BMP_Free(flouterbefmandel);
    BMP_Free(floutermandel);        
    BMP_Free(imagegraymandelbrot);
    BMP_Free(imagemandelbrot);

    BMP_Free(imagegrayjulia);
    BMP_Free(filtrebefjulia);
    BMP_Free(filtrejulia);
    BMP_Free(flouterbefjulia);  
    BMP_Free(flouterjulia);       
   BMP_Free(imagejulia);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
