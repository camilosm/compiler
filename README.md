# Compilador

Esse projeto contém um compilador para uma linguagem fictícia, criado como um trabalho para a disciplina de Compiladores do curso de Engenharia de Computação do CEFET-MG.

## Características da linguagem

* As palavras-chave da linguagem são reservadas;
* Toda variável deve ser declarada antes do seu uso;
* A entrada e a saída da linguagem estão limitadas ao teclado e à tela do computador;
* A linguagem possui comentário de uma linha que começam com **//**;
* A linguagem possui comentário de mais de uma linha que começam com **/\*** e termina com **\*/**;
* O operador **+**, quando aplicado a um dado do tipo string, representa concatenação;
* Os demais operadores aritméticos são aplicáveis somente aos tipos numéricos;
* O resultado da divisão entre dois números inteiros é um número real;
* Somente tipos iguais são compatíveis nesta linguagem;
* As operações de comparação resultam em valor lógico (verdadeiro ou falso);
* Nos testes (dos comandos condicionais e de repetição) a expressão a ser validada deve ser um valor lógico;
* A semântica dos demais comandos e expressões é a tradicional de linguagens como Java e C;
* A linguagem é case-sensitive;

Um exemplo é dado a seguir (basic.cefet):

```
class Basic
	int a,b,r;

init
	read(a);
	read(b);
	r = a + b;
	write(r);
stop
```
Esse programa lê dois inteiros, e imprime sua soma.

## Implementação do compilador

A implementação do interpretador pode ser dividida em (N) fases):
[analisador léxico](#analisador-léxico),
[analisador sintático](#analisador-sintático),
[compilador](#interpretador).
Cada uma dessas fases será detalhada a seguir.

### Analisador léxico

O analisador léxico é responsável por separar os *tokens* da linguagem.
*Tokens* são os menores elementos que podem ser formados por um programa.
Note que, nessa linguagem, espaços, novas linhas, tabulações e comentários não são elementos léxicos, ou seja, não formam *tokens*.

#### Lexema

O lexema é uma estrutura que carrega um *token* e o tipo desse *token*. Opcionalmente, um lexema pode carregar informações adicionais, porém essas não serão utilizadas no escopo da implementação dessa linguagem.

```cpp
struct Lexeme{
	std::string token;
	enum TokenType type;
}
```

O lexema possui seus membros públicos para facilitar sua utilização pelo analisador léxico.
O *token* é uma string com o elemento formado, e *type* é o tipo do *token*.
Os tipos possíveis são listados pela enumeração *TokenType* que inclui símbolos da linguagem (ex.: **+**, **;**, ...), palavras-reservadas (ex.: **if**, **while**, ...), além de alguns tipos especiais (ex.: *token* inválido, constante númerica, ...).

```cpp
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
```

Os três primeiros são tipos especiais usados para identificar as seguintes situações:
* fim de arquivo inesperado (`TKN_UNEXPECTED_EOF`);
* *token* inválido (`TKN_INVALID_TOKEN`);
* fim de arquivo normal/esperado (`TKN_END_OF_FILE`).
Já os últimos tipos são usados para representar os tipos:
* números inteiros (`TKN_NUMBER_INT`);
* números reais (`TKN_NUMBER_FLOAT`);
* strings (`TKN_LITERAL_STRING`);
* identificadores (`TKN_VAR`).
Todos os outros são designados para palavras-reservadas ou símbolos da linguagem.
Para o programa de exemplo, os lexemas obtidos podem ser vistos na seção de [resultado](#resultado).

#### Tabela de Símbolos

A tabela de símbolos (`SymbolTable`) é uma estrutura auxiliar utilizada para facilitar o casamento de um *token* com seu tipo.
A tabela de símbolos é um dicionário que mapeia uma chave (**token**) com seu valor (**TokenType**).
Essa tabela é pré-populada para todas as palavras-reservadas e símbolos da linguagem.

| *Token* | *TokenType*  |
| ------- | -----------  |
| "="     | TKN_ASSIGN   |
| "=="    | TKN_EQUAL    |
| "!="    | TKN_NOT_EQUAL|
| "<"     | TKN_LOWER    |
| ...     | ...          |

Note que não é possível preencher essa tabela com todos os números existentes, nem com todos os possíveis identificadores que possam vir a ser criados por um programa.
Também não deve ser preenchida com os três tipos especiais (`TKN_UNEXPECTED_EOF`, `TKN_INVALID_TOKEN`, `TKN_END_OF_FILE`).
Como a linguagem possui escopo global, uma vez populada essa tabela não será modificada.
Além disso, qualquer consulta a esse mapa cujo *token* não seja encontrado deve retornar o tipo identificador (`TKN_VAR`).

#### Autômato Finito Determinístico

Existem várias estratégias para formação de lexemas.
Na implementação desse interpretador será utilizado um autômato finito determinístico, também conhecido como máquina de estados, conforme diagrama a seguir.

![AFD](images/lexical.png)

O autômato possui estados (nomeados de 1 a 20) e arestas (rotuladas com símbolos, caracteres do programa).
Existe um único estado inicial - estado 1 - representado pelo estado com uma aresta entrante sem origem, e dois estados finais - estados 19 e 20 - representados pelo círculo duplo.
A transição é dada de um estado x (*e<sub>x</sub>*) para um estado y (*e<sub>y</sub>*) sob um caracter do programa (*'s'*):
*T(e<sub>x</sub>, 's') = e<sub>y</sub>*.
O rótulo `ungetc` é um marcador especial que permite que um símbolo lido seja devolvido ao buffer para que seja lido novamente posteriormente.
O analisador léxico implementa esse autômato.


```cpp
class LexicalAnalysis{
	...
	private:
		int m_line;
		SymbolTable m_st;
		FILE* m_file;
};
```

# Agradecimentos:

Doutor @rimsa, professor e inspiração.
Esse trabalho foi desenvolvido usando como base a documentação disponível em https://github.com/rimsa/tiny.