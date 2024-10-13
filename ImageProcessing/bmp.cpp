#include <bits/stdc++.h>
using byte = unsigned char;
using v = std::vector<byte>;
using v2 = std::vector<v>;

class BMP {
public:
    //*:little endian
    byte id[2] = {66, 77};                   //windows BM, "BM"
    byte filesize[4] = {56, 0, 36, 0};       //*, file size bytes
    byte reserved1[2] = {0, 0};              //reserved, 00 00
    byte reserved2[2] = {0, 0};              //reserved, 00 00
    byte offset[4] = {54, 0, 0, 0};          //*, offset to color data, windows 54, bytes
    
    byte DIBsize[4] = {40, 0, 0, 0};         //*, DIB head size bytes, windows bmp 40, 28 00 00 00
    byte imageWidth[4] = {0, 4, 0, 0};       //*, pixel width left to right
    byte imageHeight[4] = {0, 3, 0, 0};      //*, pixel height bottom to top
    byte imagePlanes[2] = {1, 0};            //*, number of plane, must be 1, 01 00
    byte bitsPerPixel[2] = {24, 0};          //*, bits per pixel, 24bit: 18 00
    byte compression[4] = {0, 0, 0, 0};      //*, BI_RGB, no compression: 00 00 00 00
    byte imageDataSize[4] = {2, 0, 36, 0};   //*, size of raw bitmap data with padding
    byte hreSolution[4] = {18, 11, 0, 0};    //*, horizontal print resolution, pixel/meter, 72dpi/39.3701
    byte vreSolution[4] = {18, 11, 0, 0};    //*, vertical print resolution, pixel/meter,
    byte colorpalette[4] = {0, 0, 0, 0};     //*, Number of colors in the palette
    byte importantColors[4] = {0, 0, 0, 0};  //*, important color, generally 0, all important
    
    //four byte modulo padding~ for row~
    
    v getHeaderBytes() {
        v r;
        for(byte &b : id) r.push_back(b);
        for(byte &b : filesize) r.push_back(b);
        for(byte &b : reserved1) r.push_back(b);
        for(byte &b : reserved2) r.push_back(b);
        for(byte &b : offset) r.push_back(b);
        for(byte &b : DIBsize) r.push_back(b);
        for(byte &b : imageWidth) r.push_back(b);
        for(byte &b : imageHeight) r.push_back(b);
        for(byte &b : imagePlanes) r.push_back(b);
        for(byte &b : bitsPerPixel) r.push_back(b);
        for(byte &b : compression) r.push_back(b);
        for(byte &b : imageDataSize) r.push_back(b);
        for(byte &b : hreSolution) r.push_back(b);
        for(byte &b : vreSolution) r.push_back(b);
        for(byte &b : colorpalette) r.push_back(b);
        for(byte &b : importantColors) r.push_back(b);
        return r;
    }

private:
    struct BMPt {
        byte id[2];         //windows BM, "BM"
        int filesize;       //file size bytes
        byte reserved1[2];  //reserved, 00 00
        byte reserved2[2];  //reserved, 00 00
        int offset;         //offset to color data, windows 54, bytes
        
        int DIBsize;        //DIB head size bytes, windows bmp 40, 28 00 00 00
        int imageWidth;     //pixel width left to right
        int imageHeight;    //pixel height bottom to top
        int imagePlanes;    //number of plane, must be 1, 01 00
        int bitsPerPixel;   //bits per pixel, 24, 18 00
        int compression;    //no compression: 00 00 00 00
        int imageDataSize;  //size of raw bitmap data with padding
        int hreSolution;    //horizontal print resolution, pixel/meter, 72dpi/39.3701
        int vreSolution;    //vertical print resolution, pixel/meter
        int colorpalette;   //Number of colors in the palette
        int importantColors;//important color, generally 0, all important
        
        BMPt()=default;
    };

    //little endian read
    static int ler(const byte x[], int n) {
        int tt = 0;
        for(int i=0; i<n; i++) tt |= x[i] << (8 * i);
        return tt;
    }

    static BMPt readheader(BMP x) {
        BMPt t{};
        for(int i=0; i<2; i++) t.id[i]=x.id[i];
        t.filesize=ler(x.filesize, 4);
        for(int i=0; i<2; i++) t.reserved1[i]=x.reserved1[i];
        for(int i=0; i<2; i++) t.reserved2[i]=x.reserved2[i];
        t.offset=ler(x.offset, 4);
        t.DIBsize=ler(x.DIBsize, 4);
        t.imageWidth=ler(x.imageWidth, 4);
        t.imageHeight=ler(x.imageHeight, 4);
        t.imagePlanes=ler(x.imagePlanes, 2);
        t.bitsPerPixel=ler(x.bitsPerPixel, 2);
        t.compression=ler(x.compression, 4);
        t.imageDataSize=ler(x.imageDataSize, 4);
        t.hreSolution=ler(x.hreSolution, 4);
        t.vreSolution=ler(x.vreSolution, 4);
        t.colorpalette=ler(x.colorpalette, 4);
        t.importantColors=ler(x.importantColors, 4);
        return t;
    }
    static void viewHeader(BMPt x) {
        printf("id : \""); for(byte i : x.id) putchar(i); puts("\"");
        printf("filesize : %d bytes\n", x.filesize);
        printf("offset : %d bytes\n\n", x.offset);
        printf("DIBsize : %d bytes\n", x.DIBsize);
        printf("imagewidth : %d pixels\n", x.imageWidth);
        printf("imageheight : %d pixels", x.imageHeight);
        printf("%s\n", x.imageHeight < 0 ? ", row flipped(top to bottom)" : "");
        
        printf("bitsperpixel : %d bits/pixel\n", x.bitsPerPixel);
        printf("compression : %d\n", x.compression);
        printf("imagedatasize : %d bytes\n", x.imageDataSize);
        printf("hresolution : %d pixels/meter\n", x.hreSolution);
        printf("vresolution : %d pixels/meter\n", x.vreSolution);
        printf("colorpalette : %d\n", x.colorpalette);
        printf("importantcolors : %d\n", x.importantColors);
    }
    BMPt t{};
    BMP()=default;
public:
    const char *fileName = nullptr;
    v2 R, G, B; int height = 768, width = 1024;
    explicit BMP(const char *Filename) {
        fileName = Filename;
        FILE *f1 = fopen(Filename,"rb");
        fread(this, 54, 1, f1);
        t = readheader(*this);
        height = t.imageHeight; width = t.imageWidth;
        R = G = B = v2(height, v(width));
        for(int i=0; i<height; i++)
            for(int j=0; j<width; j++) {
                B[i][j] = getc(f1);
                G[i][j] = getc(f1);
                R[i][j] = getc(f1);
            }
    }
    static BMP createBlack(int width = 1024, int height = 768) {
        BMP t{};
        t.width = width; t.height = height;
        t.R = t.G = t.B = v2(height, v(width, 0));
        return t;
    }
    void viewHeader() { viewHeader(t); }
    void saveAt(const char *Filename) {
        FILE *f = fopen(Filename, "wb");
        v byteVector = getHeaderBytes();
        assert(byteVector.size() == 54);
        for(int i=0; i<54; i++) putc(byteVector[i], f);
        for(int i=0; i<height; i++)
            for(int j=0; j<width; j++) {
                putc(B[i][j], f);
                putc(G[i][j], f);
                putc(R[i][j], f);
            }
        fclose(f);
    }
};

int main() {
    BMP bmp = BMP::createBlack();
    for(int i=0; i<50000000; i++) {
        bmp.R[rand()%bmp.height][rand()%bmp.width] += 1;
//        bmp.G[rand()%bmp.height][rand()%bmp.width] += 1;
//        bmp.B[rand()%bmp.height][rand()%bmp.width] += 1;
    }
    bmp.saveAt("C:/Users/ryans/CLionProjects/School/ImageProcessing/test.bmp");
}
