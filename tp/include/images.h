#ifndef IMAGES_H
#define IMAGES_H
#include <string>

struct PpmImg {
    int width;
    int height;
    int **red;
    int **green;
    int **blue;
};

struct PgmImg {
    int width;
    int height;
    int **gray;
};

void readPpmImg(PpmImg *ppm, std::string file_name);
void convertPpmToPgm(PpmImg *ppm, PgmImg *pgm);
void writePgmImg(PgmImg *pgm, std::string file_name);

// int getGrayScaleFromRgb(int red, int green, int blue);

void killPpmImg(PpmImg *ppm);
void killPgmImg(PgmImg *pgm);

#endif