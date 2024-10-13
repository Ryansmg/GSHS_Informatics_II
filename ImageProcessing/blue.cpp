#include <stdio.h>
#define WIDTH 1024
#define HEIGHT 768
#define HEADER 54

unsigned char R[HEIGHT][WIDTH],G[HEIGHT][WIDTH],B[HEIGHT][WIDTH];
int main( )
{
  FILE *fp1 = fopen("sample.bmp","rb");
  FILE *fp2 = fopen("blue.bmp","wb");
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
  for(i=0; i<HEIGHT; i++)
    for(j=0; j<WIDTH; j++)
    {
      G[i][j]=0;  //녹색 없애기
      R[i][j]=0;  //빨강색 없애기
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
