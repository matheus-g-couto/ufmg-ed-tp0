#include "images.h"
#include "memlog.h"
#include "msgassert.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int getGrayScaleFromRgb(int red, int green, int blue) {
    double v = 49 * (0.3 * red + 0.59 * green + 0.11 * blue) / 255;
    return (int)v;
}

// https://stackoverflow.com/questions/51949/how-to-get-file-extension-from-string-in-c
bool checkFileExtension(std::string path, std::string extension) {
    if (path.substr(path.find_last_of('.') + 1) == extension)
        return true;
    else
        return false;
}

void readPpmImg(PpmImg *ppm) {
    erroAssert(checkFileExtension(ppm->path, "ppm"),
               "Arquivo de entrada não é formato .ppm");

    std::ifstream in(ppm->path);

    if (in.is_open()) {
        std::string line;
        std::stringstream ss;

        // primeira linha de um arquivo .ppm é sempre "P3"
        std::getline(in, line);

        // segunda linha de um arquivo .ppm é o tamanho da imagem
        std::getline(in, line);
        ss << line;
        ss >> ppm->width >> ppm->height;
        ESCREVEMEMLOG((long int)(&(ppm->width)), sizeof(int), 0);
        ESCREVEMEMLOG((long int)(&(ppm->height)), sizeof(int), 0);

        erroAssert(ppm->width > 0, "Imagem de entrada tem largura negativa");
        erroAssert(ppm->height > 0, "Imagem de entrada tem altura negativa");

        // terceira linha de um arquivo .ppm é "255"
        std::getline(in, line);

        // aloca as matrizes red, green e blue dinamicamente
        ppm->red = new int *[ppm->height];
        ppm->green = new int *[ppm->height];
        ppm->blue = new int *[ppm->height];
        for (int i = 0; i < ppm->height; i++) {
            ppm->red[i] = new int[ppm->width];
            ppm->green[i] = new int[ppm->width];
            ppm->blue[i] = new int[ppm->width];
        }

        // lê as linhas referentes às cores da imagem
        for (int i = 0; i < ppm->height; i++) {
            ss = std::stringstream();
            std::getline(in, line);
            ss << line;

            for (int j = 0; j < ppm->width; j++) {
                ss >> ppm->red[i][j];
                ss >> ppm->green[i][j];
                ss >> ppm->blue[i][j];

                ESCREVEMEMLOG((long int)(&(ppm->red[i][j])), sizeof(int), 0);
                ESCREVEMEMLOG((long int)(&(ppm->green[i][j])), sizeof(int), 0);
                ESCREVEMEMLOG((long int)(&(ppm->blue[i][j])), sizeof(int), 0);
            }
        }

        // fecha o ifstream
        in.close();
    }
}

void convertPpmToPgm(PpmImg *ppm, PgmImg *pgm) {
    pgm->width = ppm->width;
    pgm->height = ppm->height;
    LEMEMLOG((long int)(&(ppm->width)), sizeof(int), 0);
    LEMEMLOG((long int)(&(ppm->height)), sizeof(int), 0);
    ESCREVEMEMLOG((long int)(&(pgm->width)), sizeof(int), 1);
    ESCREVEMEMLOG((long int)(&(pgm->height)), sizeof(int), 1);

    // aloca a matriz gray dinamicamente
    pgm->gray = new int *[pgm->height];
    for (int i = 0; i < pgm->height; i++)
        pgm->gray[i] = new int[pgm->width];

    // converte de rgb para escala de cinza
    for (int i = 0; i < ppm->height; i++) {
        for (int j = 0; j < ppm->width; j++) {
            pgm->gray[i][j] = getGrayScaleFromRgb(
                ppm->red[i][j], ppm->green[i][j], ppm->blue[i][j]);

            LEMEMLOG((long int)(&(ppm->red[i][j])), sizeof(int), 0);
            LEMEMLOG((long int)(&(ppm->green[i][j])), sizeof(int), 0);
            LEMEMLOG((long int)(&(ppm->blue[i][j])), sizeof(int), 0);

            ESCREVEMEMLOG((long int)(&(pgm->gray[i][j])), sizeof(int), 1);
        }
    }
}

void writePgmImg(PgmImg *pgm) {
    erroAssert(checkFileExtension(pgm->path, "pgm"),
               "Arquivo de saida não é formato .pgm");

    std::ofstream out(pgm->path);

    // escreve as linhas iniciais padrão de um arquivo .pgm
    out << "P2" << std::endl;
    out << pgm->width << " " << pgm->height << std::endl;
    out << 49 << std::endl;

    LEMEMLOG((long int)(&(pgm->width)), sizeof(int), 1);
    LEMEMLOG((long int)(&(pgm->height)), sizeof(int), 1);

    for (int i = 0; i < pgm->height; i++) {
        for (int j = 0; j < pgm->width; j++) {
            out << pgm->gray[i][j];
            LEMEMLOG((long int)(&(pgm->gray[i][j])), sizeof(int), 1);

            if (j != pgm->width - 1)
                out << " ";
        }
        out << std::endl;
    }
}
