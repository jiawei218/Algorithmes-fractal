#include "traitements_simples.h"


int imagegrey(BMP *bmp1, const char* filename1,const char* filename2)
{
  bmp1 = BMP_ReadFile(filename1);
  BMP_CHECK_ERROR( stderr, -1 ); 
  UINT width,height;
  UINT x,y;
  UCHAR   r, g, b;
  width = BMP_GetWidth( bmp1 );
  height = BMP_GetHeight( bmp1 );
  
  for( x=0;x<width;++x)
  {
    for(y=0;y<height;++y)
    {
      BMP_GetPixelRGB(bmp1, x,y, &r, &g, &b);
      UCHAR gris=(r+b+g)/3;
      BMP_SetPixelRGB(bmp1, x, y,  gris, gris, gris);
    }
  }
  BMP_WriteFile(bmp1, filename2);
  BMP_CHECK_ERROR( stderr, -2 );
}



int imagefiltre(BMP *bmp1,  BMP* bmp2, const char* filename1,const char* filename2)
{
  bmp1 = BMP_ReadFile(filename1);
  BMP_CHECK_ERROR( stderr, -1 ); 
  UINT width,height;
  UINT x,y;
  int k;
  UCHAR   val,vall,valll,val1,val2,val3,val4,val5,val6,val7,val8,val9;
  UCHAR r,r1,r2,r3,r4,r5,r6,r7,r8,r9;
  UCHAR g,g1,g2,g3,g4,g5,g6,g7,g8,g9;
  UCHAR b,b1,b2,b3,b4,b5,b6,b7,b8,b9;
  width = BMP_GetWidth( bmp1 );
  height = BMP_GetHeight( bmp1 );
  bmp2 = BMP_Create(width, height, 32);
  k=choix();
  //if(k==1)
  
  for( x=0;x<width;++x)
  {
    for(y=0;y<height;++y)
   {
      if(x==0||x==(width-1)||y==0||(y==height-1))
      {
        BMP_SetPixelRGB(bmp2, x,  y, 0, 0, 0);
        continue;
      }

        BMP_GetPixelRGB(bmp1,  x, y, &r1, &g1, &b1);
        val1=0.299*r1+0.578*g1+0.114*b1;
        BMP_GetPixelRGB(bmp1,  x-1,  y, &r2, &g2, &b2);
        val2=0.299*r2+0.578*g2+0.114*b2;
        BMP_GetPixelRGB(bmp1,  x+1,  y, &r3, &g3, &b3);
        val3=0.299*r3+0.578*g3+0.114*b3;
        BMP_GetPixelRGB(bmp1,  x-1,  y-1, &r4, &g4, &b4);
        val4=(0.299*r4+0.578*g4+0.114*b4);
        BMP_GetPixelRGB(bmp1,  x,  y-1, &r5, &g5, &b5);
        val5=(0.299*r5+0.578*g5+0.114*b5);
        BMP_GetPixelRGB(bmp1,  x+1,  y-1, &r6, &g6, &b6);
        val6=(0.299*r6+0.578*g6+0.114*b6);
        BMP_GetPixelRGB(bmp1,   x-1,  y+1, &r7, &g7, &b7);
        val7=(0.299*r7+0.578*g7+0.114*b7);
        BMP_GetPixelRGB(bmp1,  x,  y+1, &r8, &g8, &b8);
        val8=(0.299*r8+0.578*g8+0.114*b8);
        BMP_GetPixelRGB(bmp1,  x+1,  y+1, &r9, &g9, &b9);
        val9=(0.299*r9+0.578*g9+0.114*b9);
        
        if(k==1)
          // rehausseur de contrastes
          val=9*val1-val2-val3-val4-val5-val6-val7-val8-val9;
        else if(k==2)
          // détection de contours
          val=(8*val1-val2-val3-val4-val5-val6-val7-val8-val9)+128;
          // Pour flouter : 
          //val=(val1+val2+val3+val4+val5+val6+val7+val8+val9)/9;
        else if(k==3)
          val=0*val1-val2+val3-2*val4-val5-0*val6+0*val7+val8+2*val9;

        BMP_SetPixelRGB(bmp2, x, y, val,val,val);     
    }
  }
  BMP_WriteFile(bmp2, filename2);
  BMP_CHECK_ERROR( stderr, -2 );
}

int chooses()
{
  printf("choisissez le moyen que vous voulez utiliser pour flouter l'image:(1 ou 2 ou 3) \n");
  printf("1: matrice\n");
  printf("2: le bruit sel\n");//poivre et 
 // printf("3: le bruit gaussien\n ");
  int num=0;
  int k=0;
  printf("votre choix: ");
  scanf("%d",&num);
    switch(num)
    {
      case 1:
        k=1;  
        break;
      case 2:          
        k=2;
        break;
      default:
        printf("un faux nombre \n");
        break;
    }   
     return k;
}

int flouter(BMP *bmp1,BMP* bmp2,const char* filename1,const char* filename2)
{ 
    bmp1 = BMP_ReadFile(filename1);
    BMP_CHECK_ERROR( stderr, -1 ); 
    UINT width,height;
    width = BMP_GetWidth( bmp1 );
    height = BMP_GetHeight( bmp1 );
    bmp2 = BMP_Create(width, height, 32);  
  int k=chooses();

  if(k==1)  //flouter
  { 
    UINT x,y;  
    UCHAR   val,vall,valll,val1,val2,val3,val4,val5,val6,val7,val8,val9;
    UCHAR r,r1,r2,r3,r4,r5,r6,r7,r8,r9;
    UCHAR g,g1,g2,g3,g4,g5,g6,g7,g8,g9;
    UCHAR b,b1,b2,b3,b4,b5,b6,b7,b8,b9;
    for( x=0;x<width;++x)
    {
      for(y=0;y<height;++y)
      {
        if(x==0||x==(width-1)||y==0||(y==height-1))
        {
          BMP_SetPixelRGB(bmp2, x,  y, 0, 0, 0);
          continue;
        }

          BMP_GetPixelRGB(bmp1,  x, y, &r1, &g1, &b1);
          val1=0.299*r1+0.578*g1+0.114*b1;
          BMP_GetPixelRGB(bmp1,  x-1,  y, &r2, &g2, &b2);
          val2=0.299*r2+0.578*g2+0.114*b2;
          BMP_GetPixelRGB(bmp1,  x+1,  y, &r3, &g3, &b3);
          val3=0.299*r3+0.578*g3+0.114*b3;
          BMP_GetPixelRGB(bmp1,  x-1,  y-1, &r4, &g4, &b4);
          val4=(0.299*r4+0.578*g4+0.114*b4);
          BMP_GetPixelRGB(bmp1,  x,  y-1, &r5, &g5, &b5);
          val5=(0.299*r5+0.578*g5+0.114*b5);
          BMP_GetPixelRGB(bmp1,  x+1,  y-1, &r6, &g6, &b6);
          val6=(0.299*r6+0.578*g6+0.114*b6);
          BMP_GetPixelRGB(bmp1,   x-1,  y+1, &r7, &g7, &b7);
          val7=(0.299*r7+0.578*g7+0.114*b7);
          BMP_GetPixelRGB(bmp1,  x,  y+1, &r8, &g8, &b8);
          val8=(0.299*r8+0.578*g8+0.114*b8);
          BMP_GetPixelRGB(bmp1,  x+1,  y+1, &r9, &g9, &b9); 
          val=(val1+val2+val3+val4+val5+val6+val7+val8+val9)/9;
          BMP_SetPixelRGB(bmp2, x, y, val,val,val);     
      }
    }
    BMP_WriteFile(bmp2, filename2);
    BMP_CHECK_ERROR( stderr, -2 );
  }
  else if(k==2) // bruit sel(blanc) /bruit poivre(noir)
  {
    bmp2 = BMP_ReadFile(filename1);
    //SNR
    srand((unsigned)time(NULL));
    float SNR=rand()/(RAND_MAX+1.0);
    int SP=width*height;
   // printf("%d",SP);
    int NP=SP*(1-SNR);
    //printf("%d",NP);
    for(int i=0;i<NP;i++)
    {
     // srand((unsigned)time(NULL));
      int x=rand()%(width+1);
      int y=rand()%(height+1);
     // printf("%d,%d",x,y);
     // printf("\n");
      BMP_SetPixelRGB(bmp2,  x,  y, 255, 255, 255);
    }
    BMP_WriteFile(bmp2, filename2);
    BMP_CHECK_ERROR( stderr, -2 );
  }
 /* else if(k==3) //gaussien
  {
    int x,y;
    UCHAR R,G,B,R1,G1,B1;
    float R2,G2,B2;
    float r,g,b;
    float Xmean=0.0;
    float sigma=10;
    
    srand((unsigned)time(NULL));
    float d=rand()/(RAND_MAX+1.0);
    float sigma2=sigma*sigma*2;
    float PI2=PI*2;
    float sigmaPI2=sqrt(PI2*sigma);
    float result= exp(-(pow(d,2)/sigma2))/sigmaPI2;

        printf("%f ",result); 
        printf("\n");
        
   
    for( x=0;x<width;++x)
    {
      for(y=0;y<height;++y)
      {
        
        srand((unsigned)time(NULL));
        float d=rand()/(RAND_MAX+1.0);
        float sigma2=sigma*sigma*2;
        float PI2=PI*2;
        float sigmaPI2=sqrt(PI2*sigma);
        float result= exp(-(pow(d,2)/sigma2))/sigmaPI2;
        //printf("%f ",result); 
        //printf("\n"); 

        BMP_GetPixelRGB(bmp1, x,  y, &R, &G, &B);

        R2=((float)R)+Xmean+sigma*result;
        G2=((float)G)+Xmean+sigma*result;
        B2=((float)B)+Xmean+sigma*result;
       //printf("%f,%f,%f ",R2,G2,B2);
        //UCHAR RESULT=(UCHAR)(Xmean+result);
        r=(R2)/255;
        g=(G2)/255;
        b=(B2)/255;
       // printf("%f,%f,%f ",r,g,b);
        //printf("\n");
        R1=(UCHAR)r;
        B1=(UCHAR)b;
        G1=(UCHAR)g;
      //  printf("%u,%u,%u ",R1,G1,B1);
       // printf("\n");

        BMP_SetPixelRGB(bmp2,  x, y, R1,G1, B1);
      }
    }
    BMP_WriteFile(bmp2, filename2);
    BMP_CHECK_ERROR( stderr, -2 );

  }
  */

}

int choix()
{
  printf("choisissez le type de Matrice du Filtre:(1 ou 2 ou 3) \n");
  printf("1: Filtre réhausseur de contraste\n");
  printf("2: Filtre de détection de bord\n");
  printf("3: Filtre d'embossage\n ");
  int num=0;
  int k=0;
  printf("Votre choix: ");
  scanf("%d",&num);
    switch(num)
    {
      case 1:
        k=1;  
        break;
      case 2:          
        k=2;
        break;
      case 3:
        k=3;
        break;
      default:
        printf("un faux nombre \n");
        break;
    }   
     return k;
}