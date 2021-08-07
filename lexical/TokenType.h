#if !defined(TOKEN_TYPE_H)
#define TOKEN_TYPE_H

#include <string>

enum TokenType {
	// SPECIALS
	TKN_UNEXPECTED_EOF = -2,
	TKN_INVALID_TOKEN = -1,
	TKN_END_OF_FILE = 0,

	// SYMBOLS
	TKN_OPEN_PAR,		// (
	TKN_CLOSE_PAR,		// )
	TKN_OPEN_CUR,		// {
	TKN_CLOSE_CUR,		// }
	TKN_COMMA,			// ,
	TKN_SEMICOLON,		// ;

	// OPERATORS
	TKN_ASSIGN,			// =
	TKN_NOT,			// !
	TKN_EQUAL,			// ==
	TKN_NOT_EQUAL,		// !=
	TKN_LOWER,			// <
	TKN_GREATER,		// >
	TKN_LOWER_EQ,		// <=
	TKN_GREATER_EQ,		// >=
	TKN_ADD,			// +
	TKN_SUB,			// -
	TKN_MUL,			// *
	TKN_DIV,			// /
	TKN_OR,				// ||
	TKN_AND,			// &&

	// KEYWORDS
	TKN_IF,				// if
	TKN_ELSE,			// else
	TKN_DO,				// do
	TKN_WHILE,			// while
	TKN_READ,			// read
	TKN_WRITE,			// write
	TKN_CLASS,			// class
	TKN_INT,			// int
	TKN_FLOAT,			// float
	TKN_STRING,			// string
	TKN_INIT,			// init
	TKN_STOP,			// stop
	
	// OTHERS
	TKN_NUMBER_INT,		// integers
	TKN_NUMBER_FLOAT,	// reals
	TKN_LITERAL_STRING,	// strings
	TKN_ID				// variable
};

inline std::string tt2str(enum TokenType type){
	switch(type){
		// SPECIALS
		case TKN_UNEXPECTED_EOF:
			return "TKN_UNEXPECTED_EOF";
		case TKN_INVALID_TOKEN:
			return "TKN_INVALID_TOKEN";
		case TKN_END_OF_FILE:
			return "TKN_END_OF_FILE";

		// SYMBOLS
		case TKN_OPEN_PAR:
			return "TKN_OPEN_PAR";
		case TKN_CLOSE_PAR:
			return "TKN_CLOSE_PAR";
		case TKN_OPEN_CUR:
			return "TKN_OPEN_CUR";
		case TKN_CLOSE_CUR:
			return "TKN_CLOSE_CUR";
		case TKN_COMMA:
			return "TKN_COMMA";
		case TKN_SEMICOLON:
			return "TKN_SEMICOLON";
		
		// OPERATORS
		case TKN_ASSIGN:
			return "TKN_ASSIGN";
		case TKN_NOT:
			return "TKN_NOT";
		case TKN_EQUAL:
			return "TKN_EQUAL";
		case TKN_NOT_EQUAL:
			return "TKN_NOT_EQUAL";
		case TKN_LOWER:
			return "TKN_LOWER";
		case TKN_GREATER:
			return "TKN_GREATER";
		case TKN_LOWER_EQ:
			return "TKN_LOWER_EQ";
		case TKN_GREATER_EQ:
			return "TKN_GREATER_EQ";
		case TKN_ADD:
			return "TKN_ADD";
		case TKN_SUB:
			return "TKN_SUB";
		case TKN_MUL:
			return "TKN_MUL";
		case TKN_DIV:
			return "TKN_DIV";
		case TKN_OR:
			return "TKN_OR";
		case TKN_AND:
			return "TKN_AND";
		
		// KEYWORDS
		case TKN_IF:
			return "TKN_IF";
		case TKN_ELSE:
			return "TKN_ELSE";
		case TKN_DO:
			return "TKN_DO";
		case TKN_WHILE:
			return "TKN_WHILE";
		case TKN_READ:
			return "TKN_READ";
		case TKN_WRITE:
			return "TKN_WRITE";
		case TKN_CLASS:
			return "TKN_CLASS";
		case TKN_INT:
			return "TKN_INT";
		case TKN_FLOAT:
			return "TKN_FLOAT";
		case TKN_STRING:
			return "TKN_STRING";
		case TKN_INIT:
			return "TKN_INIT";
		case TKN_STOP:
			return "TKN_STOP";

		// OTHERS
		case TKN_NUMBER_INT:
			return "TKN_NUMBER_INT";
		case TKN_NUMBER_FLOAT:
			return "TKN_NUMBER_FLOAT";
		case TKN_LITERAL_STRING:
			return "TKN_LITERAL_STRING";
		case TKN_ID:
			return "TKN_IDENTIFIER";

		default:
			throw std::string("invalid token type");
	}
}

#endif // TOKEN_TYPE_H
