#include <iostream>
#include <cstdlib>

#include "lexical/LexicalAnalysis.h"

int main(int argc, char* argv[]){
    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " [program]" << std::endl;
        exit(1);
    }

    try{
        LexicalAnalysis l(argv[1]);
        std::cout << l.nextToken().str() << std::endl;
    } catch(const std::string& error){
        std::cerr << error << std::endl;
    }

    return 0;
}