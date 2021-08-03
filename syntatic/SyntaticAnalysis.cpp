#include "SyntaticAnalysis.h"

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex):
	m_lex(lex), m_current(lex.nextToken()){
}

SyntaticAnalysis::~SyntaticAnalysis(){
}

void SyntaticAnalysis::start(){

}

void SyntaticAnalysis::matchToken(enum TokenType type) {
    // printf("Match token: %d -> %d (\"%s\")\n", m_current.type, type, m_current.token.c_str());
	if(type == m_current.type)
        m_current = m_lex.nextToken();
	else
    	showError();
}

void SyntaticAnalysis::showError() {
    printf("%02d: ", m_lex.line());
    switch (m_current.type) {
        case TKN_INVALID_TOKEN:
            printf("Lexema inválido [%s]\n", m_current.token.c_str());
            break;
        case TKN_UNEXPECTED_EOF:
        case TKN_END_OF_FILE:
            printf("Fim de arquivo inesperado\n");
            break;
        default:
            printf("Lexema não esperado [%s]\n", m_current.token.c_str());
            break;
    }
    exit(1);
}