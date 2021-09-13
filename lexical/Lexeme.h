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
	// enum var_type data_type;
	union {
		int int_value;
		float float_value;
		char string_value[255];
	} data_value;

	Lexeme(): token(""), type(TKN_INVALID_TOKEN){
		memset(&data_value,0,sizeof(data_value));
	}
	Lexeme(std::string token, enum TokenType type):token(token), type(type){
		memset(&data_value,0,sizeof(data_value));
	}
	virtual ~Lexeme(){}

	const std::string str(){
		std::stringstream ss;
		ss << "(\"" << token << "\", " << tt2str(type) << ")";
		return ss.str();
	}
};

#endif // LEXEME_H
