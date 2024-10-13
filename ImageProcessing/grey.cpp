//#include <stdio.h>
//#define WIDTH 1024
//#define HEIGHT 768
//#define HEADER 54
//
//unsigned char R[HEIGHT][WIDTH],G[HEIGHT][WIDTH],B[HEIGHT][WIDTH];
//int main( )
//{
//  FILE *fp1 = fopen("sample.bmp","rb");
//  FILE *fp2 = fopen("grey.bmp","wb");
//  int i, j;
//  for(i=0; i<HEADER; i++)
//    putc(getc(fp1), fp2);
//
//  for(i=0; i<HEIGHT; i++)
//    for(j=0; j<WIDTH; j++)
//    {
//      B[i][j]=getc(fp1);
//      G[i][j]=getc(fp1);
//      R[i][j]=getc(fp1);
//    }
//
//  //�� ������ �迭 ������ �۾�!!
//  int g;  //���ο� �� ���� ����� ���� ����
//  for(i=0; i<HEIGHT; i++)
//    for(j=0; j<WIDTH; j++)
//    {
//      g = (B[i][j]+G[i][j]+R[i][j])/3; //3���� �� ��ո����
//      B[i][j]=g;  //��հ��� �Ķ� ������ ������ ���
//      G[i][j]=g;  //��հ��� ��� ������ ������ ���
//      R[i][j]=g;  //��հ��� ���� ������ ������ ���
//    }
//
//
//  for(i=0; i<HEIGHT; i++)
//    for(j=0; j<WIDTH; j++)
//    {
//      putc(B[i][j],fp2);
//      putc(G[i][j],fp2);
//      putc(R[i][j],fp2);
//    }
//  return 0;
//}

#include <stdio.h>
#include <windows.h>
#define WIDTH 1024
#define HEIGHT 768
#define HEADER 54

unsigned char R[HEIGHT][WIDTH], G[HEIGHT][WIDTH], B[HEIGHT][WIDTH];
int main()
{
    FILE *fp1 = fopen("sample.bmp", "rb");
    FILE *fp2 = fopen("copy.bmp", "wb");
    int i, j;
    for(i=0;i<HEADER;i++)
    {
        putc(getc(fp1), fp2);
    }
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            B[i][j]=getc(fp1);
            G[i][j]=getc(fp1);
            R[i][j]=getc(fp1);
        }
    }
    int g;
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            g=(B[i][j]+G[i][j]+R[i][j])/3;

        B[i][j]=g;
        G[i][j]=g;
        R[i][j]=g;
        }
    }
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            putc(B[i][j], fp2);
            putc(G[i][j], fp2);
            putc(R[i][j], fp2);
        }
    }
    return 0;
}
