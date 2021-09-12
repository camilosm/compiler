#if !defined(SYMBOL_TABLE_H)
#define SYMBOL_TABLE_H

#include <map>
#include <string>

#include "TokenType.h"
#include "Lexeme.h"

class SymbolTable{
	public:
		SymbolTable();
		virtual ~SymbolTable();

		bool contains(std::string token);
		Lexeme get(std::string token);
		// bool put(std::string token, enum var_type type);
		bool put(Lexeme lex);
	private:
		std::map<std::string, Lexeme> m_st;
};

#endif // SYMBOL_TABLE_H
