#include <string>

#include "LexicalAnalysis.h"

LexicalAnalysis::LexicalAnalysis(const char* filename):m_line(1){
	m_file = fopen(filename, "r");
}

LexicalAnalysis::~LexicalAnalysis(){
	if(m_file != nullptr)
		fclose(m_file);
}

int LexicalAnalysis::line() const {
    return m_line;
}

Lexeme LexicalAnalysis::nextToken(){
	Lexeme lex;
	int state = 1;
	
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
				else if(c==EOF){
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
						if(c!=EOF){
							ungetc(c, m_file);
							if(c=='\n')
								m_line--;
						}
						state = 19;
					}
				}
				break;

			case 3:
				if(c=='\n'){
					state = 1;
				}
				else if(c==EOF){
					lex.type = TKN_END_OF_FILE;
					state = 20;
				}
				else
					state = 3;
				break;

			case 4:
				if(c=='*')
					state = 5;
				else if(c==EOF){
					lex.type = TKN_UNEXPECTED_EOF;
					state = 20;
				}
				else
					state = 4;
				break;

			case 5:
				if(c=='/')
					state = 1;
				else if(c==EOF){
					lex.type = TKN_UNEXPECTED_EOF;
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
					if(c!=EOF){
						ungetc(c, m_file);
						if(c=='\n')
							m_line--;
					}						
					state = 19;
				}
				break;
			case 7:
				if(c=='&'){
					lex.token+=(char)c;
					state = 19;
				}
				else{
					if(c!=EOF)
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
					if(c!=EOF){
						ungetc(c, m_file);
						if(c=='\n')
							m_line--;
					}
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
					if(c!=EOF){
						ungetc(c, m_file);
						if(c=='\n')
							m_line--;
					}
					state = 19;
				}
				break;
			
			case 10:
				if(c=='_' || isdigit(c) || isalpha(c)){
					lex.token += (char)c;
					state = 10;
				}
				else{
					if(c!=EOF){
						ungetc(c, m_file);
						if(c=='\n')
							m_line--;
					}
					lex.type = TKN_ID;
					state = 20;
				}
				break;

			case 11:
				if(c=='.'){
					lex.token += (char)c;
					state = 12;
				}
				else{
					lex.type = TKN_NUMBER_INT;
					lex.data.int_value = 0;
					if(c!=EOF){
						ungetc(c, m_file);
						if(c=='\n')
							m_line--;
					}
					state = 20;
				}
				break;

			case 12:
				if(isdigit(c)){
					lex.token += (char)c;
					state = 13;
				}
				else if(c==EOF){
					lex.type = TKN_UNEXPECTED_EOF;
					state = 20;
				}
				else{
					lex.type = TKN_INVALID_TOKEN;
					ungetc(c, m_file);
					if(c=='\n')
						m_line--;
					state = 20;
				}
				break;

			case 13:
				if(isdigit(c)){
					lex.token += (char)c;
					state = 13;
				}
				else{
					if(c!=EOF){
						ungetc(c, m_file);
						if(c=='\n')
							m_line--;
					}
					lex.type = TKN_NUMBER_FLOAT;
					lex.data.float_value = std::stof(lex.token);
					state = 20;
				}
				break;

			case 14:
				if(isdigit(c)){
					lex.token += (char)c;
					state = 14;
				}
				else if(c=='.'){
					lex.token += (char)c;
					state = 15;
				}
				else{
					if(c!=EOF){
						ungetc(c, m_file);
						if(c=='\n')
							m_line--;
					}
					lex.type = TKN_NUMBER_INT;
					lex.data.int_value = std::stoi(lex.token);
					state = 20;
				}
				break;

			case 15:
				if(isdigit(c)){
					lex.token += (char)c;
					state = 16;
				}
				else if(c==EOF){
					lex.type = TKN_UNEXPECTED_EOF;
					state = 20;
				}
				else{
					if(c=='\n')
						m_line--;
					lex.type = TKN_INVALID_TOKEN;
				}
				break;

			case 16:
				if(isdigit(c)){
					lex.token += (char)c;
					state = 16;
				}
				else{
					if(c!=EOF){
						ungetc(c, m_file);
						if(c=='\n')
							m_line--;
					}
					lex.type = TKN_NUMBER_FLOAT;
					lex.data.float_value = std::stof(lex.token);
					state = 20;
				}
				break;

			case 17:
				if(c=='\\')
					state = 18;
				else if(c=='\"'){
					lex.type = TKN_LITERAL_STRING;
					state = 20;
				}
				else if(c==EOF){
					lex.type = TKN_UNEXPECTED_EOF;
					state = 20;
				}
				else{
					lex.token += (char)c;
					state = 17;
				}
				break;

			case 18:
				state = 17;
				if(c=='b')
					lex.token += '\b';
				else if(c=='f')
					lex.token += '\f';
				else if(c=='n')
					lex.token += '\n';
				else if(c=='r')
					lex.token += '\r';
				else if(c=='t')
					lex.token += '\t';
				else if(c=='\\')
					lex.token += '\\';
				else if(c=='"')
					lex.token += '\"';
				else{
					if(c==EOF)
						lex.type = TKN_UNEXPECTED_EOF;
					else{
						lex.token += '\\'+(char)c;
						lex.type = TKN_INVALID_TOKEN;
					}
					state = 20;
				}
				break;
			default:
				throw std::string("invalid state");
				break;
		}
	}

	if(state==19){
		if(!m_st.contains(lex.token))
			m_st.put(lex.token, lex.data.type);
		lex=m_st.get(lex.token);
	}

	return lex;
}