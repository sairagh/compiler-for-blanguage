  %{
  #include <bits/stdc++.h>
  #include <stdlib.h>

  #include<string.h>
  #include"ast1.h"
  using namespace std;
  vector<lab *>labe;
  vector<statlist *>sa;
  const char *a[1000];
  const char *b[1000];
  int k=0;
  int i=0;
  int fla=0;
   extern "C" FILE *yyin;
  extern char* yytext;
  int yylex (void);
  void yyerror (char const *s);
  void addvar(char *a);
  void chvar(char *a);
  void addla(char *a);
  void chla(char *a);
  Astprogram *sta;
  ass *a1;
  ifs *a3;
  read *a4;
  print *a5;
  fors *a6;
  whiles *a7;
  statlist *s12;
  map<string,int>a23;
  vector<string>a11;
 %}

%union{
  int num;
  char *an;
	char *identifier_val;
  char *rel;
	char *con;
	char *ari;

  class Astprogram *pno;
  class declarlist *decllis;
  class decl *decla;
  class idlist *idlino;
  class id *idno;
  class statlist *stlino;
  class stat *stno;
  class ass *assno;
  class ifs *ifsno;
  class fors *forsno;
  class whiles *whileno;
  class lab *labno;
  class gotos *gono;
  class read *readno;
  class print *printno;
  class bl *blno;
  class expr *exprno;
  class numb *numno;
  class lf *lfno;
  class ab *abno;
  class id1 *id1no;
  }

%token <num> NUMBER
%token <identifier_val> IDENTIFIER
%token ETOK
%token<an> AD
%token SEMI
%token INT
%token DEC
%token COD
%token PRI
%token IF
%token ELSE
%token<ari> EQ
%token<ari> NEQ
%token FOR
%token WHILE
%token PR1
%token READ
%token <ari>NO
%token <ari>AND
%token <ari>OR
%token <rel> REL
%token <con> CON
%token <ari> ARI
%token GOTO
%left EQ NEQ
%left AND OR
%left REL
%left '+' '-'
%left ARI
%left CON
%nonassoc NO
%type <pno> program
  %type <stlino> statement_list
%type <stno> statement
%type <assno> ass
%type <ifsno> if
%type <forsno> for
%type <whileno> while
%type <labno> lab
%type <gono> goto
%type <readno> read
%type <printno> println
%type <printno> print
%type <exprno> expr
%type <lfno> lf
%type <abno> ab
%type <blno>bl

%%
program:	DEC '{' declaration_list '}' COD '{' statement_list '}' {$$=new Astprogram($7);sta=$$;s12=$7;sa.push_back($7);}

declaration_list: decl declaration_list |decl

decl:INT LL SEMI

LL: id ',' LL|id

id:IDENTIFIER {addvar($1);Code(string($1),0,0);}
|IDENTIFIER '[' NUMBER ']' {addvar($1);Code(string($1),1,$3);}

statement_list: statement_list statement{$1->push2($2);$$=$1;}
|statement{$$=new statlist();$$->push2($1);}

statement:ass{$$=$1;}|if{$$=$1;}|for{$$=$1;}|while{$$=$1;}|lab{$$=$1;}|goto{$$=$1;}|read{$$=$1;}|print{$$=$1;}|println{$$=$1;}

println:PR1 AD ',' lf SEMI {$$=new print(string($2),$4,1);}
| PR1 lf SEMI {string s;s=" ";$$=new print(s,$2,3);}
| PR1 AD SEMI {$$=new print(string($2),NULL,4);}

goto: GOTO ab SEMI{$$=new gotos($2);}

ab:IDENTIFIER IF expr  {a11.push_back(string($1));$$=new ab(string($1),0,$3);}
|IDENTIFIER {a11.push_back(string($1));$$=new ab(string($1),1,NULL);}

read:READ lf SEMI{$$=new read($2);a4=$$;}

print:PRI AD ',' lf SEMI {char a[1000];strcpy(a,$4->a.c_str());chvar(a);$$=new print(string($2),$4,0);a5=$$;}

lab:IDENTIFIER ':' statement {a23[string($1)]=1;$$=new lab(string($1),$3);labe.push_back($$);BasicBlock *thenbb=createBB(fooFunc,string($1));
labe1[string($1)]=thenbb;}


for:FOR IDENTIFIER '=' expr ',' expr bl {chvar($2);$$=new fors(string($2),$4,$6,NULL,$7);}
|FOR IDENTIFIER '=' expr ',' expr ',' expr bl {chvar($2);$$=new fors(string($2),$4,$6,$8,$9);a6=$$;}

while:WHILE  expr  bl {$$=new whiles($2,$3);a7=$$;}

ass:lf '=' expr SEMI {$$=new ass ($1,$3);a1=$$;}

lf:IDENTIFIER {chvar($1);$$=new lf($1,0,NULL);}
|IDENTIFIER '[' expr ']' {chvar($1);$$=new lf($1,1,$3);}

if:IF  expr  bl {$$=new ifs($2,$3,NULL);a3=$$;}
| IF  expr  bl ELSE bl{$$=new ifs($2,$3,$5);a3=$$;}

bl:'{'  statement_list   '}'{ $$=new bl($2);}


expr	:expr '+' expr {char *s="+";$$=new binexp($1,$3,string(s));}
 	|expr '-' expr {char *s="-";$$=new binexp($1,$3,string(s));}
  |expr ARI expr {$$=new binexp($1,$3,string($2));}
  |expr CON expr{$$=new binexp($1,$3,string($2));}
  |expr REL expr{$$=new binexp($1,$3,string($2));}
  |expr NEQ expr{$$=new binexp($1,$3,string($2));}
  |expr EQ expr{$$=new binexp($1,$3,string($2));}
  |NO expr{$$=new unexp($2,string($1));}
  |expr OR expr{$$=new binexp($1,$3,string($2));}
  |expr AND expr{$$=new binexp($1,$3,string($2));}
  |'(' expr ')' {char *s="(";$$=new unexp($2,string(s));}
	|	NUMBER{$$=new nu($1);}
	|lf{$$=new loc($1);}

%%

void yyerror (char const *s)
{
        fla=1;
        fprintf (stderr, "%s\n", s);
      // printf("undeclared variable %s\n",s);
}
void addvar(char *a1)
{
a[i]=a1;
//printf("%s\n",a[i]);
i++;
}

void chvar(char *a1)
{
int fl=0;
int j=0;
for(j=0;j<i;j++)
{
  if(strcmp(a1,a[j])==0)
  {
  fl=1;
  }
}
if(!fl)
{
printf("undeclared variable %s\n",a1);
yyerror(a1);
}
}


void addla(char *a1)
{
b[k]=a1;
//printf("%s\n",b[k]);
k++;
}

void chla(char *a1)
{
int fl=0;
int j=0;
for(j=0;j<k;j++)
{
  if(strcmp(a1,b[j])==0)
  {
  fl=1;
  }
}
if(!fl)
{
printf("undeclared label %s\n",a1);
yyerror(a1);
}
}
int che()
{
  for(int i=0;i<a11.size();i++)
  {
    if(a23[a11[i]]==0)
    {
      // al1 = labelMap ;
      // a23 =
      return 0;
    }
  }
  return 1;
}
int main(int argc, char *argv[])
{
	if (argc == 1 ) {
		fprintf(stderr, "Correct usage: bcc filename\n");
		exit(1);
	}

	if (argc > 2) {
		fprintf(stderr, "Passing more arguments than necessary.\n");
		fprintf(stderr, "Correct usage: bcc filename\n");
	}

	yyin = fopen(argv[1], "r");

  fun(TheModule);
	yyparse();
  int ty=che();
//  cout<<ty<<" "<<fla<<endl;
  if(ty==1&&fla==0)
  {
  int fl=1;
  interpret* in;
  in=new interpret(sa);
  sta->accept(in);
  s12->codegen();
  Builder.CreateRet(Builder.getInt32(0));
  TheModule->dump();
  }

  else
  {
  printf("the program has errors\n");
  }
}
