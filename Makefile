CC=gcc.exe
RESHCK=Reshack\Reshacker.exe

all:  pjass

pjass: lex.yy.c grammar.tab.c grammar.tab.h misc.o
	$(CC) lex.yy.c grammar.tab.c misc.c -o $@ -O2 -mno-cygwin
	$(RESHCK) -addskip $@.exe, $@.exe, pjass.res ,,,

lex.yy.c: token.l
	flex $<

grammar.tab.c: grammar.y
	bison -o grammar.tab.c $<

grammar.tab.h: grammar.y
	bison -d -o grammar.tab $<

%.o: %.c
	$(CC) $< -c

clean:
	del grammar.tab.h
	del grammar.tab.c
	del lex.yy.c
	del misc.o
	del pjass.exe

t:
	./pjass <t.txt

package:
	tar Ccvfz ../ jass2.tar.gz  jass2/Makefile jass2/grammar.y jass2/token.l jass2/misc.c jass2/misc.h jass2/readme.txt

binpackage:
	rm -f PJASS.zip ; pkzip -a pjass.zip ../doc/readme.txt ./pjass.exe ; mv -f PJASS.zip pjass-bin-091-win32.zip

