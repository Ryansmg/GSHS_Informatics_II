#include <stdio.h>

//데이터형 재정의
typedef unsigned char byte;

//WAV 파일 헤더(44바이트)의 의미 
struct WAV {
  //*:little endian
  byte ChunkID[4];      //"RIFF"
  byte ChunkSize[4];    //*
  byte Format[4];       //"WAVE"
  byte Subchunk1ID[4];  //"fmt "
  byte Subchunk1Size[4];//*
  byte AudioFormat[2];  //*, 1:pcm(pulse code modulation)
  byte NumChannels[2];  //*
  byte SampleRate[4];   //*
  byte ByteRate[4];     //*
  byte BlockAlign[2];   //*
  byte BitsPerSample[2];//*
  byte Subchunk2ID[4];  //"data"
  byte Subchunk2Size[4];//*
};

int main()
{
  FILE *fp1=fopen("sample.wav","rb");
  FILE *fp2=fopen("copy1.wav","wb");
    
  WAV head;
  fread(&head, sizeof(head), 1, fp1);   //헤더 읽기
  fwrite(&head, sizeof(head), 1, fp2);  //헤더 붙여넣기
    
  //소리 데이터 복사
  //샘플 데이터의 개수를 모르기 때문에 파일 끝까지 복사 붙여넣기
  int t; 
  while((t=getc(fp1)) != EOF) //EOF(-1, 파일 끝)이 아니면 데이터 복사, 잠재적 오류 가능성 있음
    putc(t, fp2);             //데이터 붙여넣기
    
  return 0;
}

