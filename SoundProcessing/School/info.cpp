#include <stdio.h>

typedef unsigned char byte;

struct WAV
{
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

//wav 파일 헤더 데이터 저장 처리용 임시 구조체 
struct WAVt
{
  byte ChunkID[4];    //"RIFF"
  int ChunkSize;      //*
  byte Format[4];     //"WAVE"
  byte Subchunk1ID[4];//"fmt "
  int Subchunk1Size;  //*
  short AudioFormat;  //*, 1:pcm(pulse code modulation)
  short NumChannels;  //*
  int SampleRate;     //*
  int ByteRate;       //*
  short BlockAlign;   //*
  short BitsPerSample;//*
  byte Subchunk2ID[4];//"data"
  int Subchunk2Size;  //*
};

//little endian read
int ler(byte x[], int n)
{
  int t=0, s=4-n;
  for(int i=0; i<n; i++)
    t |= (x[i]<<((i+s)*8));
  return t>>(s*8);
}

//헤더 데이터 읽어 오기
WAVt readheader(WAV x)
{
  WAVt t;
  for(int i=0; i<4; i++) t.ChunkID[i]=x.ChunkID[i];
  t.ChunkSize=ler(x.ChunkSize, 4);
  for(int i=0; i<4; i++) t.Format[i]=x.Format[i];
  for(int i=0; i<4; i++) t.Subchunk1ID[i]=x.Subchunk1ID[i];
  t.Subchunk1Size=ler(x.Subchunk1Size, 4);
  t.AudioFormat=ler(x.AudioFormat, 2);
  t.NumChannels=ler(x.NumChannels, 2);
  t.SampleRate=ler(x.SampleRate, 4);
  t.ByteRate=ler(x.ByteRate, 4);
  t.BlockAlign=ler(x.BlockAlign, 2);
  t.BitsPerSample=ler(x.BitsPerSample, 2);
  for(int i=0; i<4; i++) t.Subchunk2ID[i]=x.Subchunk2ID[i];
  t.Subchunk2Size=ler(x.Subchunk2Size, 4);
  return t;
}

//헤더 정보 출력 하기
void viewheader(WAVt x)
{
  printf("ChunkID : \""); for(int i=0; i<4; i++) putchar(x.ChunkID[i]); puts("\"");
  printf("ChunkSize : %d bytes\n", x.ChunkSize);
  printf("Format : \""); for(int i=0; i<4; i++) putchar(x.Format[i]); puts("\"");
  printf("Subchunk1ID : \"");for(int i=0; i<4; i++) putchar(x.Subchunk1ID[i]);puts("\"");
  printf("Subchunk1Size : %d bytes\n", x.Subchunk1Size);
  printf("AudioFormat : %d%s\n", x.AudioFormat, x.AudioFormat==1?", PCM":"");
  printf("NumChannels : %d%s\n",x.NumChannels,x.NumChannels==2?", stereo":(x.NumChannels==1?", mono":""));
  printf("SampleRate : %.1f Khz\n", (float)(x.SampleRate)/1000);
  printf("ByteRate : %d Bps\n", x.ByteRate);
  printf("BlockAlign : %d bytes\n", x.BlockAlign);
  printf("BitsPerSample : %d bits\n", x.BitsPerSample);
  printf("Subchunk2ID : \"");for(int i=0; i<4; i++) putchar(x.Subchunk2ID[i]);puts("\"");
  printf("Subchunk2Size : %d bytes\n\n", x.Subchunk2Size);
  printf("wav file size: %.2f KB(%d bytes)\n", (float)(x.ChunkSize+8)/1000, x.ChunkSize+8);
  printf("wav header size : %d bytes\n", (unsigned int)sizeof(x));
  printf("pcm data size: %d bytes\n", x.Subchunk2Size);
  printf("pcm duration : %.3f sec\n\n", (float)((x.Subchunk2Size))/x.ByteRate);
}

int main()
{
  FILE *fp1=fopen("WindowsExclamation.wav","rb");
  //freopen("info.txt","w", stdout);
    
  WAV head;
  WAVt headt;
    
  fread(&head, sizeof(head), 1, fp1);  //헤더 읽기
  headt=readheader(head);              //헤더 데이터 변환
    
  viewheader(headt);                   //헤더 데이터 보기
  return 0;
}
