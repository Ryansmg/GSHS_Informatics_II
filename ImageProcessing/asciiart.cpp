#include <cstdio>
constexpr int WIDTH = 1024, HEIGHT = 768, HEADER = 54;

unsigned char R[HEIGHT][WIDTH], G[HEIGHT][WIDTH], B[HEIGHT][WIDTH];
int main() {
    FILE *fp1 = fopen("sample.bmp", "rb");
    FILE *fp2 = fopen("asciiart.txt", "wt"); // 텍스트 쓰기 모드
    char t[20] = " .,^;17opnmgWKQ&";
    int i, j;
    for(i=0; i<HEADER; i++) getc(fp1); // 헤더부분 지나가기
    for(i=0; i<HEIGHT; i++)
        for(j=0; j<WIDTH; j++) {
            B[i][j] = getc(fp1);
            G[i][j] = getc(fp1);
            R[i][j] = getc(fp1);
        }
    
    // 색 데이터 배열 가지고 작업!!
    int g; // 새로운 색 값을 만들기 위한 변수
    for(i=448; i>256; i--) {
        for(j=64; j<256; j++) {
            // 보통 사람의 밝기 민감도에 따른 회색변환
            // ITU-R BT.601 표준
            g = (int) (B[i][j] * 0.299 + G[i][j] * 0.587 + R[i][j] * 0.114);
            fprintf(fp2, "%c", t[(15-g/16)]);
        }
        fprintf(fp2, "\n");
    }
}