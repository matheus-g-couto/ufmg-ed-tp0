#include "memlog.h"
#include <fstream>
#include <getopt.h>
#include <images.h>
#include <iostream>
#include <string.h>
#include <string>

struct Flags {
    std::string input_file;
    std::string output_file;
    char log_file[100];
    bool regmem;

    Flags()
        : input_file("assets/in/mineirao.ppm"),
          output_file("assets/out/output.pgm"), log_file("bin/log.out"),
          regmem(false) {}
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
            strcpy(f->log_file, optarg);
            break;
        case 'l':
            f->regmem = true;
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

void printInputTemplate() {
    std::cout << "Exemplo de entrada: run.out -i <input_file> -o <output_file>"
              << std::endl;
}

int main(int argc, char **argv) {
    // verifica se a linha de comando passou argumentos
    Flags *f = new Flags();
    parse_args(argc, argv, f);

    // inicia registro de acesso
    iniciaMemLog(f->log_file);
    if (f->regmem)
        ativaMemLog();
    else
        desativaMemLog();

    // cria o objeto onde será salvo o arquivo .ppm
    defineFaseMemLog(0);
    PpmImg *input_img = new PpmImg(f->input_file);
    readPpmImg(input_img);

    // cria o objeto onde será salvo o arquivo .pgm
    defineFaseMemLog(1);
    PgmImg *output_img = new PgmImg(f->output_file);
    convertPpmToPgm(input_img, output_img);

    // escreve a imagem convertida no arquivo de saída
    defineFaseMemLog(2);
    writePgmImg(output_img);

    // desaloca a memória dos objetos
    defineFaseMemLog(3);
    delete input_img;
    delete output_img;

    return finalizaMemLog();
}
