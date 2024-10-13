#include <bits/stdc++.h>

constexpr int WIDTH = 1024, HEIGHT = 768, HEADER = 54;
unsigned char R[HEIGHT][WIDTH], G[HEIGHT][WIDTH], B[HEIGHT][WIDTH];
unsigned char zero = 0, mask = 0b01011001;

int main() {
    FILE *fp1 = fopen("C:/Users/ryans/CLionProjects/School/ImageProcessing/sample.bmp", "rb");
    FILE *fp2 = fopen("C:/Users/ryans/CLionProjects/School/ImageProcessing/sample2.bmp", "rb");
    FILE *tar = fopen("C:/Users/ryans/CLionProjects/School/ImageProcessing/compare.bmp", "wb");
    int i, j;
    for(i = 0; i < HEADER; i++) {
        putc(getc(fp1), tar); // 한 바이트 읽기
        getc(fp2);
    }
    
    for(i = 0; i < HEIGHT; i++)
        for(j = 0; j < WIDTH; j++) {
            B[i][j] = getc(fp1) == getc(fp2) ? 255 : 0;
            G[i][j] = getc(fp1) == getc(fp2) ? 255 : 0;
            R[i][j] = getc(fp1) == getc(fp2) ? 255 : 0;
        }
    
    for(i = 0; i < HEIGHT; i++)
        for(j = 0; j < WIDTH; j++) {
            putc(B[i][j], tar);
            putc(G[i][j], tar);
            putc(R[i][j], tar);
        }
}
