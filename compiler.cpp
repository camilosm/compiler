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
        Lexeme lex = lexer.nextToken();
        while(lex.type != TKN_END_OF_FILE && lex.type != TKN_UNEXPECTED_EOF){
            if(lex.type==TKN_INVALID_TOKEN)
                printf("Linha %02d: Lexema inválido [%s]\n", lexer.line(), lex.token.c_str());
            printf("(\"%s\", %s)\n", lex.token.c_str(), tt2str(lex.type).c_str());
            lex = lexer.nextToken();
        }
        printf("(\"%s\", %s)\n", lex.token.c_str(), tt2str(lex.type).c_str());
        if(lex.type==TKN_UNEXPECTED_EOF)
            printf("Linha %02d: Fim de arquivo inesperado\n", lexer.line());
        printf("Linhas: %d\n", lexer.line());
        // Comentar até aqui
    }
    catch(const std::string& error){
        std::cerr << error << std::endl;
    }

    return 0;
}