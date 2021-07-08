#include "SymbolTable.h"

SymbolTable::SymbolTable(){
	// SYMBOLS
    m_st["("] = Lexeme("(", TKN_OPEN_PAR);
    m_st[")"] = Lexeme(")", TKN_CLOSE_PAR);
    m_st["{"] = Lexeme("{", TKN_OPEN_CUR);
    m_st["}"] = Lexeme("}", TKN_CLOSE_CUR);
    m_st[","] = Lexeme(",", TKN_COMMA);
    m_st[";"] = Lexeme(";", TKN_SEMICOLON);

    // OPERATORS
    m_st["="] = Lexeme("=", TKN_ASSIGN);
    m_st["!"] = Lexeme("!", TKN_NOT);
    m_st["=="] = Lexeme("==", TKN_EQUAL);
    m_st["!="] = Lexeme("!=", TKN_NOT_EQUAL);
    m_st["<"] = Lexeme("<", TKN_LOWER);
    m_st[">"] = Lexeme(">", TKN_GREATER);
    m_st["<="] = Lexeme("<=", TKN_LOWER_EQ);
    m_st[">="] = Lexeme(">=", TKN_GREATER_EQ);
    m_st["+"] = Lexeme("+", TKN_ADD);
    m_st["-"] = Lexeme("-", TKN_SUB);
    m_st["*"] = Lexeme("*", TKN_MUL);
    m_st["/"] = Lexeme("/", TKN_DIV);
    m_st["||"] = Lexeme("||", TKN_OR);
    m_st["&&"] = Lexeme("&&", TKN_AND);


    // KEYWORDS
    m_st["if"] = Lexeme("if", TKN_IF);
    m_st["else"] = Lexeme("else", TKN_ELSE);
    m_st["do"] = Lexeme("do", TKN_DO);
    m_st["while"] = Lexeme("while", TKN_WHILE);
    m_st["read"] = Lexeme("read", TKN_READ);
    m_st["write"] = Lexeme("write", TKN_WRITE);
    m_st["class"] = Lexeme("class", TKN_CLASS);
    m_st["int"] = Lexeme("int", TKN_INT);
    m_st["float"] = Lexeme("float", TKN_FLOAT);
    m_st["string"] = Lexeme("string", TKN_STRING);
    m_st["init"] = Lexeme("init", TKN_INIT);
    m_st["stop"] = Lexeme("stop", TKN_STOP);
}

SymbolTable::~SymbolTable(){
}

bool SymbolTable::contains(std::string token){
	return m_st.find(token) != m_st.end();
}

Lexeme SymbolTable::get(std::string token) {
	return this->contains(token) ? m_st[token]:Lexeme(token, TKN_INVALID_TOKEN);
}

bool SymbolTable::put(std::string token, enum var_type type){
    if(this->contains(token))
        return false;
    Lexeme lex(token, TKN_ID);
    lex.data.type = type;
    m_st[token] = lex;
    return true;
}