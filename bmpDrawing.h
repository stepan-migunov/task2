#ifndef LIBRARY_H
#define LIBRARY_H


///This type, storing size of something, has descriptive name
typedef unsigned long   size_t;

///This is one-byte long built-in type
typedef unsigned char   WORD;

///This is two-byte long built-in type
typedef unsigned short  DWORD;

///This is four-byte long built-in type
typedef unsigned int    QuadWORD;

///Color is described by three bytes
typedef struct ColorBit
{
    char red_byte;
    char green_byte;
    char blue_byte;
    char reserved_byte;
} colour;

///Each point is described by two integer coordinates
typedef struct point
{
    long x;
    long y;
} point;

///This struct is used to storage file's meta information
struct fileHeader;

///This struct is used to storage bitmap's meta information
struct BMPHeader;

///File we are working on
extern FILE* file;

///Width of the image
extern size_t x_size;

/// Height of the image
extern size_t y_size;

///Name of the image
extern char* imageName;

///The main goal of this code
extern colour** bitmap;


///WORKING WITH FILE:
///Opens image. Returning 0 if opening was successful.
///Returns -1 if file does not exist.
///Returns -2 if file has not BMP type
int openImage(char* fileName);


///WORKING WITH FILE:
///Creates image with corresponding size.
///Returns 0 if bitmap was successfully opened.
///Returns -1 if current bitmap isn't empty. Maybe you should close previous file
///Returns -2 if cannot create a bitmap
int create(const char* fileName, size_t size_x, size_t size_y);


///WORKING WITH FILE:
///Writes file to the disk. Returns 0 if file was successfully written. Returns -1 otherwise
int writeFile();


///WORKING WITH FILE:
///Closes file, stops working with it
void close();


///DRAWING:
///Paints pixel at x,y coordinates with chosen color, does nothing if it is outside borders
void paintPixel(long x, long y, colour color);
void paintPixel_point(struct point dot, struct ColorBit color);


///DRAWING:
///Draws Circle with given center, radius and color
void drawCircle(long center_x, long center_y, int radius, colour color);
void drawCircle_point(struct point center, int radius, struct ColorBit color);


///DRAWING:
///Draws Line with given start&end points, depth and color
void drawLine(long begin_x, long begin_y, long end_x, long end_y, int depth, colour color);
void drawLine_point(struct point begin, struct point end, int depth, struct ColorBit color);


///DRAWING:
///Draws rectangle starting from UpperLeftCorner and going width pixels right and height pixels down.
///(border == 0)border is used when you want it be filled with color,
///(border < 0)be filled white with with white filling and colored border with thickness -border
///(border > 0)or be filled with nothing but with colored border with thickness border
void drawRectangle(long Vertex_x, long Vertex_y, size_t width, size_t height, colour color, int border);
void drawRectangle_point(point UpperLeftCorner, size_t width, size_t height, colour color, int border);


///MATH:
///Square of a double
double sqr_d(double arg);

///MATH:
///Absolute value of a double
double abs_d(double arg);

///MATH:
///Square root of a double
double sqrt_d(double arg);

///MATH:
///Square of a size_t
size_t sqr_t(size_t arg);

///MATH:
///Minimum between two size_t
size_t min_t(size_t a, size_t b);

///MATH:
///Maximum between two size_t
size_t max_t(size_t a, size_t b);

///MATH:
///Absilute value of a long
size_t abs_t(long arg);


///Some default colors are given by defines:
#define BLACK ((struct ColorBit){(char)0,(char)0,(char)0})
#define WHITE ((struct ColorBit){(char)255,(char)255,(char)255})

#define RED ((struct ColorBit){(char)255,(char)0,(char)0})
#define GREEN ((struct ColorBit){(char)0,(char)255,(char)0})
#define BLUE ((struct ColorBit){(char)0,(char)0,(char)255})

#define YELLOW ((struct ColorBit){(char)255,(char)255,(char)0})
#define AZURE ((struct ColorBit){(char)0,(char)255,(char)255})
#define MAGENTA ((struct ColorBit){(char)255,(char)0,(char)255})


#endif //LIBRARY_H