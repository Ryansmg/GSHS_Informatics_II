#include <stdio.h>
#define WIDTH 1024
#define HEIGHT 768
#define HEADER 54

unsigned char R[HEIGHT][WIDTH],G[HEIGHT][WIDTH],B[HEIGHT][WIDTH];
int main( )
{
  FILE *fp1 = fopen("sample.bmp","rb");
  FILE *fp2 = fopen("vflip.bmp","wb");
  int i, j;
  for(i=0; i<HEADER; i++)
    putc(getc(fp1), fp2);
    
  for(i=0; i<HEIGHT; i++)
    for(j=0; j<WIDTH; j++)
    {
      B[i][j]=getc(fp1);
      G[i][j]=getc(fp1);
      R[i][j]=getc(fp1);
    }
    
  //색 데이터 배열 가지고 작업!!
  int t;
  for(i=0; i<HEIGHT/2; i++)
    for(j=0; j<WIDTH; j++)
    {
      t=B[HEIGHT-1-i][j];
      B[HEIGHT-1-i][j]=B[i][j];
      B[i][j]=t;
      t=G[HEIGHT-1-i][j];
      G[HEIGHT-1-i][j]=G[i][j];
      G[i][j]=t;
      t=R[HEIGHT-1-i][j];
      R[HEIGHT-1-i][j]=R[i][j];
      R[i][j]=t;
    }
    
  for(i=0; i<HEIGHT; i++)
    for(j=0; j<WIDTH; j++)
    {
      putc(B[i][j],fp2);
      putc(G[i][j],fp2);
      putc(R[i][j],fp2);
    } 
  return 0;
}
