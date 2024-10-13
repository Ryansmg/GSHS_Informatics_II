#include <stdio.h>
#include <math.h>

//�ִ�����(max amplitude) ����, 16��Ʈ�ִ밪/8�� ���� ������
#define MAX 65536/8

#define PI 3.1415926535

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

//��� ������ �о� ����
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

int pcm[44100000][4]; //������ ����� �迭, �ִ�1000��

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
    
  int duration;
  float frequency;
  printf("frequency(hz) : ");
  scanf("%f", &frequency);

  printf("duration(msec) : ");
  scanf("%d", &duration);
    
  headt.Subchunk2Size = headt.ByteRate*duration/1000.0; //Subchunk2Size�� �ݿ� 
  headt.ChunkSize = headt.Subchunk2Size+36;             //ChunkSize�� �ݿ� 
  
  char filename[20];
  sprintf(filename, "%.fHz.wav", frequency);  
  FILE *fp1=fopen(filename,"wb");
      
  head=writeheader(headt);             //����� ����� ���� ����� �����ͷ� ��ȯ
  fwrite(&head, sizeof(head), 1, fp1); //��� ��� 
    
  //���� �������� ó���� ���⿡��!!
  int n=(headt.Subchunk2Size)/headt.BlockAlign; //���ø� ������ ��� ���� ���
  int ch=headt.NumChannels;                     //ä�� ����
  int size=headt.BlockAlign/ch;                 //�� ä�δ� ��� ũ��(����Ʈ) ���
  byte buffer[4];                               //�����͸� �о���� �ӽ� ����
    
  //�Էµ� �ð�/�������� sin�� ������ ����
  double phase=0;
  double freqrps=frequency*2*PI/headt.SampleRate; //frequency radians per sample

  //�� ����� �� ä�ξ� sin�� ������ ����
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<ch; j++)
      pcm[i][j]=MAX*sin(phase);        
    phase+=freqrps;
  }

  //�� ����� �� ä�ξ� ���
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<ch; j++)
    {
      lew(buffer, pcm[i][j], size);
      fwrite(buffer, size, 1, fp1);
    }
  }

  printf("%.2fHz, %.2fsec wav file generated!!\n", frequency, duration/1000.0);    
  return 0;
}


