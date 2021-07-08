CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=compiler
OBJS=compiler.o lexical/SymbolTable.o lexical/LexicalAnalysis.o

all: $(TARGET)
	rm -rf $(OBJS)

clean:
	rm -rf $(TARGET) $(OBJS)

compiler.o:

lexical/SymbolTable.o: lexical/TokenType.h

lexical/LexicalAnalysis.o: lexical/Lexeme.h lexical/SymbolTable.h

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<