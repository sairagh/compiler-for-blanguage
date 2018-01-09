CFLAGS = -lfl `llvm-config-3.8 --cppflags mcjit native --ldflags --libs core` -ltinfo -lpthread -ldl
bcc:	parser.tab.c lex.yy.c ast1.h
	g++ -g -w -Wno-deprecated -g -std=c++11 parser.tab.c lex.yy.c -lfl $(CFLAGS) -o bcc
parser.tab.c: parser.y
	bison -d -v parser.y
parser.tab.h: parser.y
	bison -d -v parser.y
lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

.PHONY: clean
clean:
	-@rm -rf parser.tab.c parser.tab.h lex.yy.c bcc 2>/dev/null || true
