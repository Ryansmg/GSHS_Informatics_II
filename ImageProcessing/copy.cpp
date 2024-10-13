#include <stdio.h>
#define WIDTH 1024
#define HEIGHT 768
#define HEADER 54

unsigned char R[HEIGHT][WIDTH],G[HEIGHT][WIDTH],B[HEIGHT][WIDTH];
int main( )
{
  FILE *fp1 = fopen("sample.bmp","rb");
  FILE *fp2 = fopen("copy.bmp","wb");
  int i, j;
  for(i=0; i<HEADER; i++)   //1024*768 24bit 헤더데이터 복사해넣기
    putc(getc(fp1), fp2);

  for(i=0; i<HEIGHT; i++)   //색 데이터 메모리로 읽기
    for(j=0; j<WIDTH; j++)
    {
      B[i][j]=getc(fp1);
      G[i][j]=getc(fp1);
      R[i][j]=getc(fp1);
    }

  //여기 쯤에서 읽어온 색 데이터 배열 가지고 다양하게 작업해 보자.!!


  for(i=0; i<HEIGHT; i++)   //색 데이터 파일로 쓰기
    for(j=0; j<WIDTH; j++)
    {
      putc(B[i][j],fp2);
      putc(G[i][j],fp2);
      putc(R[i][j],fp2);
    }
  return 0;
}
