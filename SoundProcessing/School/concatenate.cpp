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

int pcm[44100000][4]; //데이터 저장용 배열, 최대1000초

int main()
{
  WAV head;
  WAVt headt={
    //*:little endian
    'R','I','F','F', //byte ChunkID[4];//"RIFF"
    0,               //ChunkSize;      //*
    'W','A','V','E', //Format[4];      //"WAVE"
    'f','m','t',' ', //Subchunk1ID[4]; //"fmt "
    16,              //Subchunk1Size;  //*
    1,               //AudioFormat;    //*, 1:pcm(pulse code modulation)
    2,               //NumChannels;    //*, 1:mono, 2:stereo
    44100,           //SampleRate;     //*
    176400,          //ByteRate;       //*
    4,               //BlockAlign;     //*
    16,              //BitsPerSample;  //*
    'd','a','t','a', //Subchunk2ID[4]; //"data"
    0                //Subchunk2Size;  //*
  };
    
  //파일 크기나 속성을 바꾸고 싶다면 여기서 처리!!!
  
  FILE *fp1=fopen("C4.wav","rb");
  FILE *fp2=fopen("E4.wav","rb");
  FILE *fp3=fopen("G4.wav","rb");
  FILE *fp4=fopen("concatenate.wav","wb");
    
  WAV head1, head2, head3;
  WAVt headt1, headt2, headt3;
    
  fread(&head1, sizeof(head1), 1, fp1); //헤더 읽기
  headt1=readheader(head1);             //값 변환
  fread(&head2, sizeof(head2), 1, fp2);
  headt2=readheader(head2);
  fread(&head3, sizeof(head3), 1, fp3);
  headt3=readheader(head3);

  headt.Subchunk2Size = headt1.Subchunk2Size+headt2.Subchunk2Size+headt3.Subchunk2Size; //Subchunk2Size에 반영
  headt.ChunkSize = headt.Subchunk2Size+36; //ChunkSize에 반영
    
  head=writeheader(headt);             //헤더에 저장될 값을 헤더용 데이터로 변환
  fwrite(&head, sizeof(head), 1, fp4); //헤더 기록

  int n;
  int ch=headt.NumChannels;                     //채널 개수
  int size=headt.BlockAlign/ch;                 //한 채널당 블록 크기(바이트) 계산
  byte buffer[4];                               //데이터를 읽어들일 임시 버퍼

  n=(headt1.Subchunk2Size)/headt1.BlockAlign;   //파일1 데이터 블록 개수
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<ch; j++)
    {
      fread(buffer, size, 1, fp1);
      fwrite(buffer, size, 1, fp4);
    }
  }

  n=(headt2.Subchunk2Size)/headt2.BlockAlign;   //파일2 데이터 블록 개수
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<ch; j++)
    {
      fread(buffer, size, 1, fp2);
      fwrite(buffer, size, 1, fp4);
    }
  }

  n=(headt3.Subchunk2Size)/headt3.BlockAlign;   //파일3 데이터 블록 개수
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<ch; j++)
    {
      fread(buffer, size, 1, fp3);
      fwrite(buffer, size, 1, fp4);
    }
  }

  printf("file generated!!\n");
  return 0;
}


