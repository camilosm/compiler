#if !defined(SYNTATIC_ANALYSIS_H)
#define SYNTATIC_ANALYSIS_H

#include "../lexical/LexicalAnalysis.h"

class SyntaticAnalysis{
	private:
		LexicalAnalysis& m_lex;
		Lexeme m_current;
	
	public:
		SyntaticAnalysis(LexicalAnalysis& lex);
		virtual ~SyntaticAnalysis();

		void start();
		void matchToken(enum TokenType type);
		void showError();
};

#endif // SYNTATIC_ANALYSIS_H
