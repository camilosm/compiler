#include <string>
#include <cctype>

#include "LexicalAnalysis.h"

LexicalAnalysis::LexicalAnalysis(const char* filename):m_line(1){
	m_file = fopen(filename, "r");
}

LexicalAnalysis::~LexicalAnalysis(){
	if(m_file != nullptr)
		fclose(m_file);
}

Lexeme LexicalAnalysis::nextToken(){
	int state;
	Lexeme lex;

	state = 1;
	while (state != 19 && state != 20){
		int c = fgetc(m_file);
		if(c=='\n')
			m_line++;
		switch(state){
			case 1:
				if(c==' ' || c=='\t' || c=='\r' || c=='\n')
					state = 1;
				else if(c=='/')
					state = 2;
				else if(c=='<' || c=='>' || c=='!' || c=='='){
					lex.token += (char)c;
					state = 6;
				}
				else if(c=='&'){
					lex.token += (char)c;
					state = 7;
				}
				else if(c=='|'){
					lex.token += (char)c;
					state = 8;
				}
				else if(c=='+' || c=='-' || c=='*' || c=='(' || c==')' || c=='{' || c=='}' || c==';' || c==','){
					lex.token += (char)c;
					state = 19;
				}
				else if(isalpha(c)){
					lex.token += (char)c;
					state = 9;
				}
				else if(c=='0'){
					lex.token += (char)c;
					state = 11;
				}
				else if(isdigit(c)){
					lex.token += (char)c;
					state = 14;
				}
				else if(c=='\"')
					state = 17;
				else if(c==-1){
					lex.type = TKN_END_OF_FILE;
					state = 20;
				}
				else{
					lex.token += (char) c;
					lex.type = TKN_INVALID_TOKEN;
					state = 20;
				}
				break;

			case 2:
				if(c=='/')
					state = 3;
				else{
					if(c=='*')
						state=4;
					else{
						lex.token += '/';
						if(c!=-1)
							ungetc(c, m_file);
						state = 19;
					}
				}
				break;

			case 3:
				if(c=='\n'){
					state = 1;
				}
				else if(c==-1){
					lex.type = TKN_END_OF_FILE;
					state = 20;
				}
				else
					state = 3;
				break;

			case 4:
				if(c=='*')
					state = 5;
				else if(c==-1){
					lex.type = TKN_END_OF_FILE;
					state = 20;
				}
				else
					state = 4;
				break;

			case 5:
				if(c=='/')
					state = 1;
				else if(c==-1){
					lex.type = TKN_END_OF_FILE;
					state = 20;
				}
				else if(c=='*')
					state = 5;
				else
					state = 4;				
				break;

			case 6:
				if(c=='='){
					lex.token += (char)c;
					state = 19;
				}
				else{
					if(c!=-1)
						ungetc(c, m_file);
					state = 19;
				}
				break;
			case 7:
				if(c=='&'){
					lex.token+=(char)c;
					state = 19;
				}
				else{
					if(c!=-1)
						ungetc(c, m_file);
					state = 19;
				}
				break;

			case 8:
				if(c=='|'){
					lex.token+=(char)c;
					state = 19;
				}
				else{
					if(c!=-1)
						ungetc(c, m_file);
					state = 19;
				}
				break;

			case 9:
				if(isalpha(c)){
					lex.token += (char)c;
					state = 9;
				}
				else if(c=='_' || isdigit(c)){
					lex.token += (char)c;
					state = 10;
				}
				else{
					if(c!=-1)
						ungetc(c, m_file);
					state = 19;
				}
				break;
			// done up to here, needs testing
			case 10:

				break;
			case 11:

				break;
			case 12:

				break;
			case 13:

				break;
			case 14:

				break;
			case 15:

				break;
			case 16:

				break;
			case 17:

				break;
			case 18:

				break;
			default:
				throw std::string("invalid state");
				break;
		}
	}

	if(state==19){
		lex.type=m_st.find(lex.token);
	}

	return lex;
}