#ifndef IMAGES_H
#define IMAGES_H
#include <string>

struct PpmImg {
    std::string path;
    int width;
    int height;
    int **red;
    int **green;
    int **blue;

    PpmImg() {}
    PpmImg(std::string p) : path(p) {}
};

struct PgmImg {
    std::string path;
    int width;
    int height;
    int **gray;

    PgmImg() {}
    PgmImg(std::string p) : path(p) {}
};

void readPpmImg(PpmImg *ppm);
void convertPpmToPgm(PpmImg *ppm, PgmImg *pgm);
void writePgmImg(PgmImg *pgm);

void killPpmImg(PpmImg *ppm);
void killPgmImg(PgmImg *pgm);

#endif