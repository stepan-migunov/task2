#include <stdlib.h>
//#include <string.h>
#include <stdio.h>
#include "bmpDrawing.h"

///File we are working on
FILE* file;

///Width of the image
size_t x_size;

/// Height of the image
size_t y_size;

///Name of the image
char* imageName;

///The main goal of this code
colour** bitmap;

double sqrt_d(double arg)
{
    double left = 0, right = arg, temp = (left + right) / 2;
    while(abs_d(sqr_d(temp) - arg) > 0.00000001)
    {
        if (sqr_d(temp) > arg)
            right = temp;
        else
            left = temp;
        temp = (left + right) / 2;
    }
    return temp;
}
double abs_d(double arg)
{
    return arg > 0 ? arg : -arg;
}
double sqr_d(double arg)
{
    return arg * arg;
}
size_t sqr_t(size_t arg)
{
    return arg*arg;
}
size_t min_t(size_t a, size_t b)
{
    return a < b ? a : b;
}
size_t max_t(size_t a, size_t b)
{
    return a > b ? a : b;
}
size_t abs_t(long arg)
{
    return arg >= 0 ? arg : -arg;
}

struct fileHeader
{
    ///This two bytes are used to storage type of file
    DWORD fileDescription;

    ///This four bytes are storaging file's size
    QuadWORD fileSize;

    ///This two times of two bytes are ????????
    DWORD Reserved1, Reserved2;

    ///This four bytes describe where the bitmap starts
    QuadWORD distanceToData;
}FileHeader;

struct BMPHeader
{
    ///This four bytes describe size of BMP Header (Usually 40 bytes)
    QuadWORD hatSize;

    ///The width of the image
    QuadWORD image_width;

    ///The height of the image
    QuadWORD image_height;

    ///??????????????
    DWORD Planes;

    ///Number of bytes every color is described by
    DWORD bitsPerPixel;

    ///?????????????? filled wit zeros
    WORD* idunnotheirmeanings;
}BMPHeader;

int openImage(char* fileName)
{
    file = fopen(fileName, "r");
    if(file == NULL)
        return -1;
    unsigned b0,b1,b2,b3;
    b0 = fgetc(file);
    b1 = fgetc(file);
    if(b0 != (char)66 || b1 != (char)77)
        return -2;
    int fileNameLen = 0;
    char* c = fileName;
    while(*c != '\0')
        ++c,++fileNameLen;

    imageName = (char*)malloc(fileNameLen+1);
    for(int i = 0; i < fileNameLen+1;++i)
        imageName[i]=fileName[i];

    FileHeader.fileDescription = b0 | (b1 << 8u);
    b0 = fgetc(file), b1 = fgetc(file), b2 = fgetc(file), b3 = fgetc(file);
    FileHeader.fileSize = b0 | (b1 << 8u) | (b2 << 16u) | (b3 << 24u);
    b0 = fgetc(file), b1 = fgetc(file), b2 = fgetc(file), b3 = fgetc(file);
    FileHeader.Reserved1 = b0 | (b1 << 8u), FileHeader.Reserved2 = b2 | (b3 << 8u);
    b0 = fgetc(file), b1 = fgetc(file), b2 = fgetc(file), b3 = fgetc(file);
    FileHeader.distanceToData = b0 | (b1 << 8u) | (b2 << 16u) | (b3 << 24u);

    b0 = fgetc(file), b1 = fgetc(file), b2 = fgetc(file), b3 = fgetc(file);
    BMPHeader.hatSize = b0 | (b1<<8u) | (b2<<16u) | (b3<<24u);
    b0 = fgetc(file), b1 = fgetc(file), b2 = fgetc(file), b3 = fgetc(file);
    BMPHeader.image_width= b0 | (b1<<8u) | (b2<<16u) | (b3<<24u);
    b0 = fgetc(file), b1 = fgetc(file), b2 = fgetc(file), b3 = fgetc(file);
    BMPHeader.image_height= b0 | (b1<<8u) | (b2<<16u) | (b3<<24u);
    x_size = BMPHeader.image_width;
    y_size = BMPHeader.image_height;
    b0 = fgetc(file), b1 = fgetc(file);
    BMPHeader.Planes = b0 | (b1<<8u);

    bitmap = (colour**)(malloc(x_size * sizeof(struct ColorBit*)));
    for(size_t i = 0; i < x_size; ++i)
        bitmap[i] = (colour*)malloc(y_size * sizeof(struct ColorBit));

    b0 = fgetc(file), b1 = fgetc(file);
    BMPHeader.bitsPerPixel = b0 | (b1<<8u);

    BMPHeader.idunnotheirmeanings = (WORD*)malloc(BMPHeader.hatSize - 16);
    for(int i = 0; i < BMPHeader.hatSize - 16; ++i)
        BMPHeader.idunnotheirmeanings[i] = fgetc(file);
    for(int y = 0; y < y_size; ++y)
    {
        for(int x = 0; x < x_size; ++x)
            if (BMPHeader.bitsPerPixel > 24)
                bitmap[x][y].blue_byte = (char) fgetc(file),
                bitmap[x][y].green_byte = (char) fgetc(file),
                bitmap[x][y].red_byte = (char) fgetc(file),
                bitmap[x][y].reserved_byte = (char) fgetc(file);
            else
                bitmap[x][y].blue_byte = (char) fgetc(file),
                bitmap[x][y].green_byte = (char) fgetc(file),
                bitmap[x][y].red_byte = (char) fgetc(file),
                bitmap[x][y].reserved_byte = (char) 0xFF;
        for(int i = 0; i < (4 - ((y_size * BMPHeader.bitsPerPixel/8) % 4))%4;++i)
            fgetc(file);
    }
    return 0;
}

int create(const char* fileName, size_t width, size_t height)
{
    if(bitmap != NULL)
        return -1;

    int fileNameLen = 0;
    const char* c = fileName;
    while(*c != '\0')
        ++c,++fileNameLen;

    imageName = (char*)malloc(fileNameLen+1);
    for(int i = 0; i < fileNameLen+1;++i)
        imageName[i]=fileName[i];

    x_size = width;
    y_size = height;

    FileHeader.fileDescription = (66u) | (77u<<8u);
    FileHeader.fileSize = (54 + height*(width*3 + ((4 - ((width * 3) % 4))%4)));
    FileHeader.Reserved1 = 0;
    FileHeader.Reserved2 = 0;
    FileHeader.distanceToData = 54;

    BMPHeader.hatSize = 40;
    BMPHeader.image_width = width;
    BMPHeader.image_height = height;
    BMPHeader.Planes = 1;
    BMPHeader.bitsPerPixel = 24;
    free(BMPHeader.idunnotheirmeanings);
    BMPHeader.idunnotheirmeanings = (WORD*)malloc(24);
    for(int i = 0; i < 24; ++i)
        BMPHeader.idunnotheirmeanings[i] = 0;

    bitmap = (colour**)malloc(x_size * sizeof(struct ColorBit*));
    if(bitmap == NULL)
        return -2;
    for(size_t i = 0; i < x_size; ++i)
        bitmap[i] = (colour*)malloc(y_size * sizeof(struct ColorBit));
    for(int x = 0; x < x_size; ++x)
        for(int y = 0; y < y_size; ++y)
            bitmap[x][y] = WHITE;

    return 0;
}

int writeFile()
{
    file = fopen(imageName, "w");
    if(file == NULL)
        return -1;

    fputc((char)(FileHeader.fileDescription & 255u), file);
    fputc((char)(FileHeader.fileDescription >> 8u), file);

    fputc((char)(FileHeader.fileSize & 255u), file);
    fputc((char)((FileHeader.fileSize >> 8u) & 255u), file);
    fputc((char)((FileHeader.fileSize >> 16u) & 255u), file);
    fputc((char)((FileHeader.fileSize >> 24u) & 255u), file);

    fputc((char)(FileHeader.Reserved1 & 255u), file);
    fputc((char)(FileHeader.Reserved1 >> 8u), file);

    fputc((char)(FileHeader.Reserved2 & 255u), file);
    fputc((char)(FileHeader.Reserved2 >> 8u), file);

    fputc((char)((FileHeader.distanceToData >>  0u) & 255u), file);
    fputc((char)((FileHeader.distanceToData >>  8u) & 255u), file);
    fputc((char)((FileHeader.distanceToData >> 16u) & 255u), file);
    fputc((char)((FileHeader.distanceToData >> 24u) & 255u), file);

    fputc((char)((BMPHeader.hatSize >>  0u) & 255u), file);
    fputc((char)((BMPHeader.hatSize >>  8u) & 255u), file);
    fputc((char)((BMPHeader.hatSize >> 16u) & 255u), file);
    fputc((char)((BMPHeader.hatSize >> 24u) & 255u), file);

    fputc((char)((BMPHeader.image_width >>  0u) & 255u), file);
    fputc((char)((BMPHeader.image_width >>  8u) & 255u), file);
    fputc((char)((BMPHeader.image_width >> 16u) & 255u), file);
    fputc((char)((BMPHeader.image_width >> 24u) & 255u), file);

    fputc((char)((BMPHeader.image_height >>  0u) & 255u), file);
    fputc((char)((BMPHeader.image_height >>  8u) & 255u), file);
    fputc((char)((BMPHeader.image_height >> 16u) & 255u), file);
    fputc((char)((BMPHeader.image_height >> 24u) & 255u), file);

    fputc((char)(BMPHeader.Planes  & 255u), file);
    fputc((char)(BMPHeader.Planes >> 8u), file);

    fputc((char)(BMPHeader.bitsPerPixel  & 255u), file);
    fputc((char)(BMPHeader.bitsPerPixel >> 8u), file);

    for(int i = 0; i < BMPHeader.hatSize - 16; ++i)
        fputc((char)(BMPHeader.idunnotheirmeanings[i]), file);

    for(int y = 0; y < y_size; ++y)
    {
        for(int x = 0; x < x_size; ++x)
            if (BMPHeader.bitsPerPixel > 24)
                fputc((char)(bitmap[x][y].blue_byte), file),
                        fputc((char)(bitmap[x][y].green_byte), file),
                        fputc((char)(bitmap[x][y].red_byte), file),
                        fputc((char)(bitmap[x][y].reserved_byte), file);
            else
                fputc((char)(bitmap[x][y].blue_byte), file),
                        fputc((char)(bitmap[x][y].green_byte), file),
                        fputc((char)(bitmap[x][y].red_byte), file);
        for(int i = 0; i < (4 - ((y_size * BMPHeader.bitsPerPixel/8) % 4))%4;++i)
            fputc((char)0xFF, file);
    }
    return 0;
}

void close()
{
    for(int i = 0; i < x_size; ++i)
        free(bitmap[i]);
    free(bitmap);
    bitmap = NULL;
    free(BMPHeader.idunnotheirmeanings);
    BMPHeader.idunnotheirmeanings = NULL;
    fclose(file);
}

void drawCircle(long center_x, long center_y, int radius, colour color)
{
    drawCircle_point((struct point){center_x, center_y},radius,color);
}
void drawCircle_point(struct point center, int radius, struct ColorBit color)
{
    for(int x = (int)(center.x) - radius; x <= center.x + radius; ++x)
    {
        int y = center.y - radius;
        while(y <= center.y + radius)
        {
            if(sqr_t(x-center.x) + sqr_t(y-center.y) < radius*radius)
            {
                paintPixel_point((struct point) {x, y}, color);
            }
            ++y;
        }
    }
}

void drawLine(long begin_x, long begin_y, long end_x, long end_y,int depth,colour color)
{
    drawLine_point((point){begin_x, begin_y},(struct point){end_x,end_y}, depth, color);
}
void drawLine_point(struct point begin, struct point end, int depth, struct ColorBit color)
{
    if(begin.x == end.x)
    {
        for(size_t y = min_t(begin.y, end.y); y <= max_t(begin.y, end.y); ++y)
            drawCircle(begin.x,y,depth/2,color);
        return;
    }
    if(begin.y == end.y)
    {
        for(size_t x = min_t(begin.x, end.x); x <= max_t(begin.x, end.x); ++x)
            drawCircle(x,begin.y,depth/2,color);
        return;
    }

    double  lambda = (double)((double)end.y - (double)begin.y)/(double)((double)begin.x - (double)end.x),
            muNumerator = (double)((double)begin.x * (double)end.y - (double)begin.y * (double)end.x),
            muDenominator = (double)(end.x - begin.x);

    for(size_t x = min_t(begin.x, end.x); x <= max_t(begin.x, end.x); ++x)
        for(size_t y = min_t(begin.y, end.y); y <= max_t(begin.y, end.y); ++y)
        {
            double temp = abs_d(lambda * (double)x + (double)y + muNumerator/muDenominator) / sqrt_d(1.0 + sqr_d(lambda));
            if (temp < 0.5)
                drawCircle_point((point) {(long)x, (long)y}, depth / 2, color);
        }
}

void paintPixel(long x, long y, colour color)
{
    paintPixel_point((struct point){x,y},color);
}
void paintPixel_point(struct point dot, struct ColorBit color)
{
    if(dot.x<x_size && dot.y<y_size && dot.x>=0 && dot.y>=0)
        bitmap[dot.x][dot.y] = color;
}

void drawRectangle(long Vertex_x, long Vertex_y, size_t width, size_t height, colour color, int border)
{
    drawRectangle_point((struct point){Vertex_x, Vertex_y}, width, height, color, border);
}
void drawRectangle_point(point UpperLeftCorner, size_t width, size_t height, colour color, int border)
{
    if(border == 0)
    {
        for(int x = 0; x < (int)width; ++x)
            for(int y = 0; y > -(int)height; --y)
                paintPixel_point((point){UpperLeftCorner.x + x, UpperLeftCorner.y + y},color);
        return;
    }
    if(border < 0)
    {
        drawRectangle_point(UpperLeftCorner,width,height,color,0);
        drawRectangle_point((struct point){UpperLeftCorner.x - border, UpperLeftCorner.y + border}, width + border, height + border, WHITE, 0);
        return;
    }
    for(int x = 0; x < (int)width; ++x)
        for(int y = 0; y >= -(int)height; --y)
            if(x <= border || x >= width-border || y >= -border || y <= -height+border)
                paintPixel(UpperLeftCorner.x + x,UpperLeftCorner.y + y,color);
}