#include <stdio.h>

typedef unsigned char byte;

struct WAV
{
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

//little endian write
void lew(byte *x, int t, int n)
{
  for(int i=0; i<n; i++, t>>=8)
    x[i] = t&0xFF;
}

WAV writeheader(WAVt x)
{
  WAV t;
  for(int i=0; i<4; i++) t.ChunkID[i]=x.ChunkID[i];
  lew(t.ChunkSize, x.ChunkSize, 4);
  for(int i=0; i<4; i++) t.Format[i]=x.Format[i];
  for(int i=0; i<4; i++) t.Subchunk1ID[i]=x.Subchunk1ID[i];
  lew(t.Subchunk1Size, x.Subchunk1Size, 4);
  lew(t.AudioFormat, x.AudioFormat, 2);
  lew(t.NumChannels, x.NumChannels, 2);
  lew(t.SampleRate, x.SampleRate, 4);
  lew(t.ByteRate, x.ByteRate, 4);
  lew(t.BlockAlign, x.BlockAlign, 2);
  lew(t.BitsPerSample, x.BitsPerSample, 2);
  for(int i=0; i<4; i++) t.Subchunk2ID[i]=x.Subchunk2ID[i];
  lew(t.Subchunk2Size, x.Subchunk2Size, 4);
  return t;
}

int main()
{
  FILE *fp1=fopen("sample.wav","rb");
  FILE *fp2=fopen("copy2.wav","wb");
    
  WAV head;
  WAVt headt;
    
  fread(&head, sizeof(head), 1, fp1);  //헤더 읽기
  headt=readheader(head);              //헤더 데이터를 값으로 변환
    
  //파일 크기나 속성을 바꾸고 싶다면 여기서 처리!!!
    
  head=writeheader(headt);             //헤더에 저장될 값을 헤더용 데이터로 변환
  fwrite(&head, sizeof(head), 1, fp2); //헤더 기록 

    
  //사운드 데이터의 처리는 여기에서!!
  int n=(headt.Subchunk2Size)/headt.BlockAlign; //샘플링 데이터 블록 개수 계산 
  
  byte buffer[4];                               //데이터를 읽어들일 임시 버퍼
  for(int i=0; i<n; i++)
  {
    fread(buffer, headt.BlockAlign, 1, fp1); //파일에서 한 블록씩 읽어서 버퍼에 저장
    fwrite(buffer, headt.BlockAlign, 1, fp2);//버퍼에 기록되어있는 데이터를 파일에 저장
  }
    
  return 0;
}
