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
    
    //�� ������ �迭 ������ �۾�!!
  int g;  //���ο� �� ���� ����� ���� ����
  for(i=0; i<HEIGHT; i++)
    for(j=0; j<WIDTH; j++)
    {
      //���� ����� ��� �ΰ����� ���� ȸ����ȯ
      //ITU-R BT.601 ǥ��?
      g = B[i][j]*0.299+G[i][j]*0.587+R[i][j]*0.114;
      B[i][j]=g;  //��ȯ���� �Ķ� ������ ������ ���
      G[i][j]=g;  //��ȯ���� ��� ������ ������ ���
      R[i][j]=g;  //��ȯ���� ���� ������ ������ ���
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
