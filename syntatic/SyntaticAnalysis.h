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
		int checkToken(int qt_tokens, ...);
		void showError(int qt_tokens, ...);

		void proc_program();
		void proc_decl_list();
		void proc_decl();
		void proc_type();
		void proc_ident_list();
		void proc_body();
		void proc_stmt_list();
		void proc_stmt();
		void proc_assign_stmt();
		void proc_if_stmt();
		void proc_do_stmt();
		void proc_do_suffix();
		void proc_read_stmt();
		void proc_write_stmt();
		void proc_expression();
		void proc_simple_expr();
		void proc_term();
		void proc_factor_a();
		void proc_factor();
		void proc_relop();
		void proc_addop();
		void proc_mulop();
};

#endif // SYNTATIC_ANALYSIS_H
