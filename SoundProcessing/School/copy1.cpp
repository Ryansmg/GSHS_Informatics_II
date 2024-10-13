#include <stdio.h>

//�������� ������
typedef unsigned char byte;

//WAV ���� ���(44����Ʈ)�� �ǹ� 
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
  fread(&head, sizeof(head), 1, fp1);   //��� �б�
  fwrite(&head, sizeof(head), 1, fp2);  //��� �ٿ��ֱ�
    
  //�Ҹ� ������ ����
  //���� �������� ������ �𸣱� ������ ���� ������ ���� �ٿ��ֱ�
  int t; 
  while((t=getc(fp1)) != EOF) //EOF(-1, ���� ��)�� �ƴϸ� ������ ����, ������ ���� ���ɼ� ����
    putc(t, fp2);             //������ �ٿ��ֱ�
    
  return 0;
}

