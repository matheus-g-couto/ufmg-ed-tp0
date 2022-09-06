#include <fstream>
#include <getopt.h>
#include <images.h>
#include <iostream>
#include <string>

struct Flags {
    std::string input_file;
    std::string output_file;
    bool save_logs;
    std::string log_file;
    bool save_mem_acc;

    Flags()
        : input_file("../sample/mineirao.ppm"), output_file("bin/out.pgm"),
          save_logs(false), save_mem_acc(false) {}
};

void parse_args(int argc, char **argv, Flags *f) {
    int opt;
    while ((opt = getopt(argc, argv, "i:o:p:l")) != -1) {
        switch (opt) {
        case 'i':
            f->input_file = optarg;
            break;
        case 'o':
            f->output_file = optarg;
            break;
        case 'p':
            f->save_logs = true;
            f->log_file = optarg;
            break;
        case 'l':
            f->save_mem_acc = true;
            break;
        case '?':
            std::cout << "opcao desconhecida ou invalida" << std::endl;
            abort();
            break;
        default:
            std::cout << "vascao" << std::endl;
        }
    }
}

int main(int argc, char **argv) {
    Flags *f = new Flags();
    parse_args(argc, argv, f);

    PpmImg *input_img = new PpmImg(f->input_file);

    readPpmImg(input_img);

    std::cout << "dimensoes da imagem: " << input_img->width << " "
              << input_img->height << std::endl;

    PgmImg *output_img = new PgmImg(f->output_file);
    convertPpmToPgm(input_img, output_img);

    writePgmImg(output_img);

    delete input_img;
    delete output_img;

    return 0;
}
