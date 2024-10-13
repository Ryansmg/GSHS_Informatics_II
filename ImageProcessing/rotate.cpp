#include <bits/stdc++.h>

constexpr int WIDTH = 1024, HEIGHT = 768, HEADER = 54;
unsigned char R[HEIGHT][WIDTH], G[HEIGHT][WIDTH], B[HEIGHT][WIDTH];
unsigned char zero = 0, mask = 0b01011001;

int main() {
    FILE *fp1 = fopen("C:/Users/ryans/CLionProjects/School/ImageProcessing/sample.bmp", "rb");
    FILE *fp2 = fopen("C:/Users/ryans/CLionProjects/School/ImageProcessing/rotate.bmp", "wb");
    int i, j;
    for(i = 0; i < HEADER; i++) // 헤더 데이터 복사
        putc(getc(fp1), fp2); // 한 바이트 읽기
    
    for(i = 0; i < HEIGHT; i++)
        for(j = 0; j < WIDTH; j++) {
            B[i][j] = getc(fp1);
            G[i][j] = getc(fp1);
            R[i][j] = getc(fp1);
        }
    
    for(i = 0; i < HEIGHT; i++)
        for(j = 0; j < WIDTH; j++) {
            putc(B[HEIGHT-i-1][WIDTH-j-1], fp2);
            putc(G[HEIGHT-i-1][WIDTH-j-1], fp2);
            putc(R[HEIGHT-i-1][WIDTH-j-1], fp2);
        }
}
