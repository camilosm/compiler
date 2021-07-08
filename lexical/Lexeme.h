#if !defined(LEXEME_H)
#define LEXEME_H

#include <string>
#include <sstream>
#include <cstring>

#include "TokenType.h"

enum var_type {
	UNKNOWN_TYPE,
	NUMBER_INTEGER,
	NUMBER_FLOAT,
	LITERAL_STRING
};
//classe?

struct Lexeme{
	std::string token;
	enum TokenType type;
	union {
		enum var_type type;
		int int_value;
		float float_value;
	} data;

	Lexeme(): token(""), type(TKN_END_OF_FILE){
		memset(&data,0,sizeof(data));
	}
	Lexeme(std::string token, enum TokenType type):token(token), type(type){
		memset(&data,0,sizeof(data));
	}
	virtual ~Lexeme(){}

	const std::string str(){
		std::stringstream ss;

		ss << "(\"" << token << "\", " << tt2str(type) << ")";
		return ss.str();
	}
};

#endif // LEXEME_H
