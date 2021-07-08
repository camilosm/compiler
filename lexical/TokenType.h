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
	TKN_VAR				// variable
};

inline std::string tt2str(enum TokenType type){
	switch(type){
		// SPECIALS
		case TKN_UNEXPECTED_EOF:
			return "UNEXPECTED_EOF";
		case TKN_INVALID_TOKEN:
			return "INVALID_TOKEN";
		case TKN_END_OF_FILE:
			return "END_OF_FILE";

		// SYMBOLS
		case TKN_OPEN_PAR:
			return "OPEN_PAR";
		case TKN_CLOSE_PAR:
			return "CLOSE_PAR";
		case TKN_OPEN_CUR:
			return "OPEN_CUR";
		case TKN_CLOSE_CUR:
			return "CLOSE_CUR";
		case TKN_COMMA:
			return "COMMA";
		case TKN_SEMICOLON:
			return "SEMICOLON";
		
		// OPERATORS
		case TKN_ASSIGN:
			return "ASSIGN";
		case TKN_NOT:
			return "NOT";
		case TKN_EQUAL:
			return "EQUAL";
		case TKN_NOT_EQUAL:
			return "NOT_EQUAL";
		case TKN_LOWER:
			return "LOWER";
		case TKN_GREATER:
			return "GREATER";
		case TKN_LOWER_EQ:
			return "LOWER_EQ";
		case TKN_GREATER_EQ:
			return "GREATER_EQ";
		case TKN_ADD:
			return "ADD";
		case TKN_SUB:
			return "SUB";
		case TKN_MUL:
			return "MUL";
		case TKN_DIV:
			return "DIV";
		case TKN_OR:
			return "OR";
		case TKN_AND:
			return "AND";
		
		// KEYWORDS
		case TKN_IF:
			return "IF";
		case TKN_ELSE:
			return "ELSE";
		case TKN_DO:
			return "DO";
		case TKN_WHILE:
			return "WHILE";
		case TKN_READ:
			return "READ";
		case TKN_WRITE:
			return	"WRITE";
		case TKN_CLASS:
			return	"CLASS";
		case TKN_INT:
			return	"INT";
		case TKN_FLOAT:
			return	"FLOAT";
		case TKN_STRING:
			return	"STRING";
		case TKN_INIT:
			return	"INIT";
		case TKN_STOP:
			return	"STOP";

		// OTHERS
		
		case TKN_NUMBER_INT:
			return "NUMBER_INT";
		case TKN_NUMBER_FLOAT:
			return "NUMBER_FLOAT";
		case TKN_LITERAL_STRING:
			return "LITERAL_STRING";
		case TKN_VAR:
			return "VAR";

		default:
			throw std::string("Invalid token type");
	}
}

#endif // TOKEN_TYPE_H
