#include <iostream>
#include <cstdlib>

#include "lexical/LexicalAnalysis.h"
#include "syntatic/SyntaticAnalysis.h"

int main(int argc, char* argv[]){
    if(argc != 2){
        std::cout << "Uso: " << argv[0] << " [programa]" << std::endl;
        exit(1);
    }

    try{
        Lexeme lex;
        LexicalAnalysis lexical(argv[1]);
        SyntaticAnalysis syntatic(lexical);

        syntatic.start();
    }
    catch(const std::string& error){
        std::cerr << error << std::endl;
    }

    return 0;
}
