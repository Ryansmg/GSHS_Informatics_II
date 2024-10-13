#include <stdio.h>
#define WIDTH 1024
#define HEIGHT 768
#define HEADER 54

unsigned char R[HEIGHT][WIDTH],G[HEIGHT][WIDTH],B[HEIGHT][WIDTH];
int main( )
{
  FILE *fp1 = fopen("sample.bmp","rb");
  FILE *fp2 = fopen("greyplus.bmp","wb");
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
  int g;  //새로운 색 값을 만들기 위한 변수
  for(i=0; i<HEIGHT; i++)
    for(j=0; j<WIDTH; j++)
    {
      //보통 사람의 밝기 민감도에 따른 회색변환
      //ITU-R BT.601 표준?
      g = B[i][j]*0.299+G[i][j]*0.587+R[i][j]*0.114;
      B[i][j]=g;  //변환값을 파랑 데이터 영역에 기록
      G[i][j]=g;  //변환값을 녹색 데이터 영역에 기록
      R[i][j]=g;  //변환값을 빨강 데이터 영역에 기록
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
