#include <fstream>
#include <images.h>
#include <iostream>
#include <string>

int main() {
    PpmImg *input_img = new PpmImg();
    std::string input_file_name = "../sample/lagoa.ppm";

    readPpmImg(input_img, input_file_name);

    std::cout << "dimensoes da imagem: " << input_img->width << " "
              << input_img->height << std::endl;

    PgmImg *output_img = new PgmImg();
    convertPpmToPgm(input_img, output_img);

    std::string output_file_name = "vasco.pgm";
    writePgmImg(output_img, output_file_name);

    killPpmImg(input_img);
    killPgmImg(output_img);

    return 0;
}
