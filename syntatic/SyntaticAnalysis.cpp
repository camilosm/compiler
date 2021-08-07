#include <cstdarg>
#include <iostream>

#include "SyntaticAnalysis.h"

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex):
	m_lex(lex), m_current(lex.nextToken()){
}

SyntaticAnalysis::~SyntaticAnalysis(){
}

void SyntaticAnalysis::start(){
	proc_program();
	matchToken(TKN_END_OF_FILE);
}

void SyntaticAnalysis::matchToken(enum TokenType type){
	// std::cout << "Expected: " << tt2str(type) << ", found: " << tt2str(m_current.type) << "(\"" << m_current.token << "\")" << std::endl;
	if(type == m_current.type)
		m_current = m_lex.nextToken();
	else
		showError(1, type);
}

int SyntaticAnalysis::checkToken(int qt_tokens, ...){
	va_list valist_tokens;
	enum TokenType type;
	va_start(valist_tokens, qt_tokens);
	for(int i=0; i<qt_tokens; i++){
		type = (enum TokenType)va_arg(valist_tokens, int);
		if(m_current.type==type){
			va_end(valist_tokens);
			return 1;
		}
	}
	return 0;
}

void SyntaticAnalysis::showError(int qt_tokens, ...){
	printf("Line %02d: expected one of: [", m_lex.line());
	va_list valist_tokens;
	enum TokenType type;
	va_start(valist_tokens, qt_tokens);
	type = (enum TokenType)va_arg(valist_tokens, int);
	std::cout << tt2str(type);
	for(int i = 1; i<qt_tokens; i++){
		type = (enum TokenType)va_arg(valist_tokens, int);
		std::cout << ", " << tt2str(type);
	}
	std::cout << "], found: ";
	switch (m_current.type){
		case TKN_INVALID_TOKEN:
			std::cout << "invalid token [" << m_current.token << "]" << std::endl;
			break;
		case TKN_UNEXPECTED_EOF:
		case TKN_END_OF_FILE:
			std::cout << "unexpected end of file!" << std::endl;
			exit(1);
			break;
		default:
			std::cout << "unexpected token [(\"" << m_current.token << "\", "<< tt2str(m_current.type) << ")]" << std::endl;
			break;
	}
	m_current = m_lex.nextToken();
}


// <program> ::= class identifier [ <decl_list> ] <body>
void SyntaticAnalysis::proc_program(){
	matchToken(TKN_CLASS);
	matchToken(TKN_ID);
	switch(m_current.type){
		case TKN_INT:
		case TKN_FLOAT:
		case TKN_STRING:
			proc_decl_list();
			break;
		default:
			break;
	}
	proc_body();
}

// <decl_list> ::= <decl> ';' { <decl> ';' }
void SyntaticAnalysis::proc_decl_list(){
	proc_decl();
	matchToken(TKN_SEMICOLON);
	while(checkToken(3, TKN_INT, TKN_FLOAT, TKN_STRING)){
		proc_decl();
		matchToken(TKN_SEMICOLON);
	}
}

// <decl> ::= <type> <ident_list>
void SyntaticAnalysis::proc_decl(){
	proc_type();
	proc_ident_list();
}

// <type> ::= int | float | string
void SyntaticAnalysis::proc_type(){
	switch(m_current.type){
		case TKN_INT:
			matchToken(TKN_INT);
			break;
		case TKN_FLOAT:
			matchToken(TKN_FLOAT);
			break;
		case TKN_STRING:
			matchToken(TKN_STRING);
			break;
		default:
			showError(3, TKN_INT, TKN_FLOAT, TKN_STRING);
			break;
	}
}

// <ident_list> ::= identifier { ',' identifier }
void SyntaticAnalysis::proc_ident_list(){
	matchToken(TKN_ID);
	while(m_current.type==TKN_COMMA){
		matchToken(TKN_COMMA);
		matchToken(TKN_ID);
	}
}

// <body> ::= init <stmt_list> stop
void SyntaticAnalysis::proc_body(){
	matchToken(TKN_INIT);
	proc_stmt_list();
	matchToken(TKN_STOP);
}

// <stmt_list> ::= <stmt> ';' { <stmt> ';' }
void SyntaticAnalysis::proc_stmt_list(){
	proc_stmt();
	matchToken(TKN_SEMICOLON);
	while(checkToken(5, TKN_ID, TKN_IF, TKN_DO, TKN_READ, TKN_WRITE)){
		proc_stmt();
		matchToken(TKN_SEMICOLON);
	}
}

// <stmt> ::= <assign_stmt> | <if_stmt> | <do_stmt> | <read_stmt> | <write_stmt>
void SyntaticAnalysis::proc_stmt(){
	switch(m_current.type){
		case TKN_ID:
			proc_assign_stmt();
			break;
		case TKN_IF:
			proc_if_stmt();
			break;
		case TKN_DO:
			proc_do_stmt();
			break;
		case TKN_READ:
			proc_read_stmt();
			break;
		case TKN_WRITE:
			proc_write_stmt();
			break;
		default:
			showError(5, TKN_ID, TKN_IF, TKN_DO, TKN_READ, TKN_WRITE);
			break;
	}
}

// <assign_stmt> ::= identifier '=' <simple_expr>
void SyntaticAnalysis::proc_assign_stmt(){
	matchToken(TKN_ID);
	matchToken(TKN_ASSIGN);
	proc_simple_expr();
}

// <if_stmt> ::= if '(' <expression> ')' '{' <stmt_list> '}' [ else '{' <stmt_list> '}' ]
void SyntaticAnalysis::proc_if_stmt(){
	matchToken(TKN_IF);
	matchToken(TKN_OPEN_PAR);
	proc_expression();
	matchToken(TKN_CLOSE_PAR);
	matchToken(TKN_OPEN_CUR);
	proc_stmt_list();
	matchToken(TKN_CLOSE_CUR);
	if(m_current.type==TKN_ELSE){
		matchToken(TKN_ELSE);
		matchToken(TKN_OPEN_CUR);
		proc_stmt_list();
		matchToken(TKN_CLOSE_CUR);
	}
}

// <do_stmt> ::= do '{' <stmt_list> '}' <do_suffix>
void SyntaticAnalysis::proc_do_stmt(){
	matchToken(TKN_DO);
	matchToken(TKN_OPEN_CUR);
	proc_stmt_list();
	matchToken(TKN_CLOSE_CUR);
	proc_do_suffix();
}

// <do_suffix> ::= while '(' <expression> ')'
void SyntaticAnalysis::proc_do_suffix(){
	matchToken(TKN_WHILE);
	matchToken(TKN_OPEN_PAR);
	proc_expression();
	matchToken(TKN_CLOSE_PAR);
}

// <read_stmt> ::= read '(' identifier ')'
void SyntaticAnalysis::proc_read_stmt(){
	matchToken(TKN_READ);
	matchToken(TKN_OPEN_PAR);
	matchToken(TKN_ID);
	matchToken(TKN_CLOSE_PAR);
}

// <write_stmt> ::= write '(' <simple_expr> ')'
void SyntaticAnalysis::proc_write_stmt(){
	matchToken(TKN_WRITE);
	matchToken(TKN_OPEN_PAR);
	proc_simple_expr();
	matchToken(TKN_CLOSE_PAR);
}

// <expression> ::= <simple_expr> [ <relop> <simple_expr> ]
void SyntaticAnalysis::proc_expression(){
	proc_simple_expr();
	if(checkToken(6, TKN_GREATER, TKN_GREATER_EQ, TKN_LOWER, TKN_LOWER_EQ, TKN_NOT_EQUAL, TKN_EQUAL)){
		proc_relop();
		proc_simple_expr();
	}
}

// <simple_expr> ::= <term> { <addop> <term> }
void SyntaticAnalysis::proc_simple_expr(){
	proc_term();
	while(checkToken(3, TKN_ADD, TKN_SUB, TKN_OR)){
		proc_addop();
		proc_term();
	}
}

// <term> ::= <factor_a> { <mulop> <factor_a> }
void SyntaticAnalysis::proc_term(){
	proc_factor_a();
	while(checkToken(3, TKN_MUL, TKN_DIV, TKN_AND)){
		proc_mulop();
		proc_factor_a();
	}
}

// <factor_a> ::= [ ( '!' | '-' ) ] <factor>
void SyntaticAnalysis::proc_factor_a(){
	switch(m_current.type){
		case TKN_NOT:
			matchToken(TKN_NOT);
			break;
		case TKN_SUB:
			matchToken(TKN_SUB);
			break;
		default:
			break;
	}
	proc_factor();
}

// <factor> ::= identifier | constant | '(' <expression> ')'
void SyntaticAnalysis::proc_factor(){
	switch(m_current.type){
		case TKN_ID:
			matchToken(TKN_ID);
			break;
		case TKN_NUMBER_INT:
			matchToken(TKN_NUMBER_INT);
			break;
		case TKN_NUMBER_FLOAT:
			matchToken(TKN_NUMBER_FLOAT);
			break;
		case TKN_LITERAL_STRING:
			matchToken(TKN_LITERAL_STRING);
			break;
		case TKN_OPEN_PAR:
			matchToken(TKN_OPEN_PAR);
			proc_expression();
			matchToken(TKN_CLOSE_PAR);
			break;
		default:
			showError(5, TKN_ID, TKN_NUMBER_INT, TKN_NUMBER_FLOAT, TKN_LITERAL_STRING, TKN_OPEN_PAR);
			break;
	}
}

// <relop> ::= '>' | '>=' | '<' | '<=' | '!=' | '=='
void SyntaticAnalysis::proc_relop(){
	switch(m_current.type){
		case TKN_GREATER:
			matchToken(TKN_GREATER);
			break;
		case TKN_GREATER_EQ:
			matchToken(TKN_GREATER_EQ);
			break;
		case TKN_LOWER:
			matchToken(TKN_LOWER);
			break;
		case TKN_LOWER_EQ:
			matchToken(TKN_LOWER_EQ);
			break;
		case TKN_NOT_EQUAL:
			matchToken(TKN_NOT_EQUAL);
			break;
		case TKN_EQUAL:
			matchToken(TKN_EQUAL);
			break;
		default:
			showError(6, TKN_GREATER, TKN_GREATER_EQ, TKN_LOWER, TKN_LOWER_EQ, TKN_NOT_EQUAL, TKN_EQUAL);
			break;
	}
}

// <addop> ::= '+' | '-' | '||'
void SyntaticAnalysis::proc_addop(){
	switch(m_current.type){
		case TKN_ADD:
			matchToken(TKN_ADD);
			break;
		case TKN_SUB:
			matchToken(TKN_SUB);
			break;
		case TKN_OR:
			matchToken(TKN_OR);
			break;
		default:
			showError(3, TKN_ADD, TKN_SUB, TKN_OR);
			break;
	}
}

// <mulop> ::= '*' | '/' | '&&'
void SyntaticAnalysis::proc_mulop(){
	switch(m_current.type){
		case TKN_MUL:
			matchToken(TKN_MUL);
			break;
		case TKN_DIV:
			matchToken(TKN_DIV);
			break;
		case TKN_AND:
			matchToken(TKN_AND);
			break;
		default:
			showError(3, TKN_MUL, TKN_DIV, TKN_AND);
			break;
	}
}