#include <iostream>
#include <cstdlib>

#include "lexical/LexicalAnalysis.h"

int main(int argc, char* argv[]){
    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " [program]" << std::endl;
        exit(1);
    }
    
    try{
        LexicalAnalysis lexer(argv[1]);

        // O código a seguir é usado apenas para testar o analisador léxico.
        // TODO: depois de pronto, comentar o código abaixo.
        Lexeme lex;
        while((lex = lexer.nextToken()).type > 0) {
            printf("(\"%s\", %s)\n", lex.token.c_str(), tt2str(lex.type).c_str());
        }
        switch (lex.type) {
            case TKN_INVALID_TOKEN:
                printf("%02d: Lexema inválido [%s]\n", lexer.line(), lex.token.c_str());
                break;
            case TKN_UNEXPECTED_EOF:
                printf("%02d: Fim de arquivo inesperado\n", lexer.line());
                break;
            default:
                printf("(\"%s\", %s)\n", lex.token.c_str(), tt2str(lex.type).c_str());
                break;
        }
        // Comentar até aqui
    } catch(const std::string& error){
        std::cerr << error << std::endl;
    }

    return 0;
}