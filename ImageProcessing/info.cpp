#include <stdio.h>
typedef unsigned char byte;
struct BMP
{
  //*:little endian
  byte id[2];         //windows BM, "BM"
  byte filesize[4];   //*, file size bytes
  byte reserved1[2];  //reserved, 00 00
  byte reserved2[2];  //reserved, 00 00
  byte offset[4];     //*, offset to color data, windows 54, bytes

  byte DIBsize[4];        //*, DIB head size bytes, windows bmp 40, 28 00 00 00
  byte imagewidth[4];     //*, pixel width left to right
  byte imageheight[4];    //*, pixel height bottom to top
  byte imageplanes[2];    //*, number of plane, must be 1, 01 00
  byte bitsperpixel[2];   //*, bits per pixel, 24bit: 18 00
  byte compression[4];    //*, BI_RGB, no compression: 00 00 00 00
  byte imagedatasize[4];  //*, size of raw bitmap data with padding
  byte hresolution[4];    //*, horizontal print resolution, pixel/meter, 72dpi/39.3701
  byte vresolution[4];    //*, vertical print resolution, pixel/meter,
  byte colorpalette[4];   //*, Number of colors in the palette
  byte importantcolors[4];//*, important color, generally 0, all important
  //four byte modulo padding~ for row~
};

struct BMPt
{
  byte id[2];         //windows BM, "BM"
  int filesize;       //file size bytes
  byte reserved1[2];  //reserved, 00 00
  byte reserved2[2];  //reserved, 00 00
  int offset;         //offset to color data, windows 54, bytes
  
  int DIBsize;        //DIB head size bytes, windows bmp 40, 28 00 00 00
  int imagewidth;     //pixel width left to right
  int imageheight;    //pixel height bottom to top
  int imageplanes;    //number of plane, must be 1, 01 00
  int bitsperpixel;   //bits per pixel, 24, 18 00
  int compression;    //no compression: 00 00 00 00
  int imagedatasize;  //size of raw bitmap data with padding
  int hresolution;    //horizontal print resolution, pixel/meter, 72dpi/39.3701
  int vresolution;    //vertical print resolution, pixel/meter
  int colorpalette;   //Number of colors in the palette
  int importantcolors;//important color, generally 0, all important
};

//little endian read
int ler(byte x[], int n)
{
  int t=0;
  for(int i=0; i<n; i++)
    t |= x[i]<<8*i;
  return t;
}

BMPt readheader(BMP x)
{
  BMPt t;
  for(int i=0; i<2; i++) t.id[i]=x.id[i];
  t.filesize=ler(x.filesize, 4);
  for(int i=0; i<2; i++) t.reserved1[i]=x.reserved1[i];
  for(int i=0; i<2; i++) t.reserved2[i]=x.reserved2[i];
  t.offset=ler(x.offset, 4);
  
  t.DIBsize=ler(x.DIBsize, 4);
  t.imagewidth=ler(x.imagewidth, 4);
  t.imageheight=ler(x.imageheight, 4);
  t.imageplanes=ler(x.imageplanes, 2);
  t.bitsperpixel=ler(x.bitsperpixel, 2);
  t.compression=ler(x.compression, 4);
  t.imagedatasize=ler(x.imagedatasize, 4);
  t.hresolution=ler(x.hresolution, 4);
  t.vresolution=ler(x.vresolution, 4);
  t.colorpalette=ler(x.colorpalette, 4);
  t.importantcolors=ler(x.importantcolors, 4);
  return t;
}

void viewheader(BMPt x)
{
  printf("id : \""); for(int i=0; i<2; i++) putchar(x.id[i]); puts("\"");
  printf("filesize : %d bytes\n", x.filesize);
  printf("offset : %d bytes\n\n", x.offset);
  printf("DIBsize : %d bytes\n", x.DIBsize);
  printf("imagewidth : %d pixels\n", x.imagewidth);
  printf("imageheight : %d pixels", x.imageheight);
  printf("%s\n", x.imageheight<0?", row flipped(top to bottom)":"");
  
  printf("bitsperpixel : %d bits/pixel\n", x.bitsperpixel);
  printf("compression : %d\n", x.compression);
  printf("imagedatasize : %d bytes\n", x.imagedatasize);
  printf("hresolution : %d pixels/meter\n", x.hresolution);
  printf("vresolution : %d pixels/meter\n", x.vresolution);
  printf("colorpalette : %d\n", x.colorpalette);
  printf("importantcolors : %d\n", x.importantcolors);
}

int main()
{
  FILE *f1=fopen("sample.bmp","rb");
  //freopen("info.txt","w", stdout);
  
  BMP head;
  BMPt headt;
  
  fread(&head, sizeof(head), 1, f1);
  headt=readheader(head);
  
  viewheader(headt);
  return 0;
}
