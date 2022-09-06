#include "images.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int getGrayScaleFromRgb(int red, int green, int blue) {
    double v = 49 * (0.3 * red + 0.59 * green + 0.11 * blue) / 255;
    return (int)v;
}

void readPpmImg(PpmImg *ppm) {
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
            }
        }

        // fecha o ifstream
        in.close();
    }
}

void convertPpmToPgm(PpmImg *ppm, PgmImg *pgm) {
    pgm->width = ppm->width;
    pgm->height = ppm->height;

    // aloca a matriz gray dinamicamente
    pgm->gray = new int *[pgm->width];
    for (int i = 0; i < pgm->width; i++)
        pgm->gray[i] = new int[pgm->height];

    // converte de rgb para escala de cinza
    for (int i = 0; i < ppm->height; i++) {
        for (int j = 0; j < ppm->width; j++) {
            pgm->gray[i][j] = getGrayScaleFromRgb(
                ppm->red[i][j], ppm->green[i][j], ppm->blue[i][j]);
        }
    }
}

void writePgmImg(PgmImg *pgm) {
    std::ofstream out(pgm->path);

    // escreve as linhas iniciais padrão de um arquivo .pgm
    out << "P2" << std::endl;
    out << pgm->width << " " << pgm->height << std::endl;
    out << 49 << std::endl;

    for (int i = 0; i < pgm->height; i++) {
        for (int j = 0; j < pgm->width; j++) {
            out << pgm->gray[i][j];
            if (j != pgm->width - 1)
                out << " ";
        }
        out << std::endl;
    }
}

// Desaloca a memória usada por uma variável PpmImg
void killPpmImg(PpmImg *ppm) {
    for (int i = 0; i < ppm->width; i++) {
        delete[] ppm->red[i];
        delete[] ppm->green[i];
        delete[] ppm->blue[i];
    }

    delete[] ppm->red;
    delete[] ppm->green;
    delete[] ppm->blue;

    ppm->width = ppm->height = -1;
}

// Desaloca a memória usada por uma variável PgmImg
void killPgmImg(PgmImg *pgm) {
    for (int i = 0; i < pgm->width; i++) {
        delete[] pgm->gray[i];
    }

    delete[] pgm->gray;
    pgm->width = pgm->height = -1;
}