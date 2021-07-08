#include "SymbolTable.h"

SymbolTable::SymbolTable(){
	// SYMBOLS
    m_st["("] = TKN_OPEN_PAR;
    m_st[")"] = TKN_CLOSE_PAR;
    m_st["{"] = TKN_OPEN_CUR;
    m_st["}"] = TKN_CLOSE_CUR;
    m_st[","] = TKN_COMMA;
    m_st[";"] = TKN_SEMICOLON;

    // OPERATORS
    m_st["="] = TKN_ASSIGN;
    m_st["!"] = TKN_NOT;
    m_st["=="] = TKN_EQUAL;
    m_st["!="] = TKN_NOT_EQUAL;
    m_st["<"] = TKN_LOWER;
    m_st[">"] = TKN_GREATER;
    m_st["<="] = TKN_LOWER_EQ;
    m_st[">="] = TKN_GREATER_EQ;
    m_st["+"] = TKN_ADD;
    m_st["-"] = TKN_SUB;
    m_st["*"] = TKN_MUL;
    m_st["/"] = TKN_DIV;
    m_st["||"] = TKN_OR;
    m_st["&&"] = TKN_AND;


    // KEYWORDS
    m_st["if"] = TKN_IF;
    m_st["else"] = TKN_ELSE;
    m_st["do"] = TKN_DO;
    m_st["while"] = TKN_WHILE;
    m_st["read"] = TKN_READ;
    m_st["write"] = TKN_WRITE;
    m_st["class"] = TKN_CLASS;
    m_st["int"] = TKN_INT;
    m_st["float"] = TKN_FLOAT;
    m_st["string"] = TKN_STRING;
    m_st["init"] = TKN_INIT;
    m_st["stop"] = TKN_STOP;
}

SymbolTable::~SymbolTable(){
}

bool SymbolTable::contains(std::string token){
	return m_st.find(token) != m_st.end();
}

enum TokenType SymbolTable::find(std::string token) {
	return this->contains(token) ? m_st[token]:TKN_VAR;
}