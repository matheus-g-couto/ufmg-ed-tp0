#include <fstream>
#include <images.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    PpmImg *input_img = new PpmImg();
    std::string input_file_name = "../sample/bolao.ppm";

    readPpmImg(input_img, input_file_name);

    std::cout << "dimensoes da imagem: " << input_img->width << " "
              << input_img->height << std::endl;

    PgmImg *output_img = new PgmImg();
    convertPpmToPgm(input_img, output_img);

    std::string output_file_name = "vasco.pgm";
    writePgmImg(output_img, output_file_name);

    delete input_img;
    delete output_img;

    return 0;
}
