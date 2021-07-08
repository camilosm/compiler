#if !defined(LEXICAL_ANALYSIS_H)
#define LEXICAL_ANALYSIS_H

#include "Lexeme.h"
#include "SymbolTable.h"

class LexicalAnalysis{
	public:
		LexicalAnalysis(const char* filename);
		virtual ~LexicalAnalysis();
		int line() const;
		Lexeme nextToken();
	private:
		int m_line;
		SymbolTable m_st;
		FILE* m_file;
};

#endif // LEXICAL_ANALYSIS_H