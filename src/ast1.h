 #include<bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/IR/Verifier.h>
//#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/IR/IRBuilder.h>
//#include <llvm/ModuleProvider.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Support/raw_ostream.h>
using namespace llvm;
class AST;
class Astprogram;
class declarlist;
class decl;
class idlist;
class id;
class statlist;
class stat;
class ass;
class ifs;
class fors;
class whiles;
class lab;
class gotos;
class read;
class println;
class print;
class bl;
class loc;
class expr;
class numb;
class lf;
class ab;
class id1;
class unexp;
class binexp;
class nu;
class Visitor;
Astprogram *start;
map <string,int> stored;
std::map<string, BasicBlock *> labe1;

//static LLVMContext Context=;
static Module *TheModule = new Module("Decaf compiler jit",llvm::getGlobalContext());
static LLVMContext &Context = getGlobalContext();
static IRBuilder<> Builder(Context);
vector<string> FunArgs;

static std::map<std::string, llvm::AllocaInst *> NamedValues;
Value* err(string s1)
{
  //<<s1<<endl;
  return 0;
}
Function *createFunc(IRBuilder<> &Builder,string name)
{
    std::vector<Type *> Integers(FunArgs.size(),Type::getInt32Ty(Context));
    FunctionType *funcType = llvm::FunctionType::get(Builder.getInt32Ty(),Integers,false);
    Function* fooFunc = llvm::Function::Create(
      funcType, llvm::Function::ExternalLinkage,name,TheModule);
    return fooFunc;
}
BasicBlock *createBB(Function *foofunc,string name)
{
  return BasicBlock::Create(Context,name,foofunc);
}
void setFuncArgs(Function* fooFunc,vector<string> FunArgs)
{
  unsigned Idx = 0;
  Function::arg_iterator AI,AE;
  for(AI = fooFunc->arg_begin(),AE = fooFunc->arg_end(); AI!=AE; ++AI,++Idx)
  {
    AI->setName(FunArgs[Idx]);
  }
}
Function *fooFunc;
BasicBlock *entry;
void fun(Module * TheModule)
{
  fooFunc = createFunc(Builder,"main");
  entry = createBB(fooFunc,"entry");
  Builder.SetInsertPoint(entry);

}

Value* Code(string name,int typ,int len)
{
//  int len=stoi(c);

      if(typ==0)
      {
        TheModule->getOrInsertGlobal(name,Builder.getInt32Ty());
        GlobalVariable *gvar=TheModule->getNamedGlobal(name);
        gvar->setLinkage(GlobalValue::CommonLinkage);
        gvar->setAlignment(4);
        ConstantInt* const_int_val = ConstantInt::get(Context, APInt(32,0));
        gvar->setInitializer(const_int_val);

      }
      else{
        Type *ty;
        ty = Type::getInt32Ty(Context);
        ArrayType* arrType = ArrayType::get(ty,(unsigned int)len);
          PointerType* PointerTy_1 = PointerType::get(ArrayType::get(ty,(unsigned int)len),0);
          GlobalVariable* gv = new GlobalVariable(*TheModule,arrType,false,GlobalValue::ExternalLinkage,0,name);
    gv->setInitializer(ConstantAggregateZero::get(arrType));
      }
      Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
return v;


}
class Visitor
{
  public:
    virtual int visit(AST *sta){}
    virtual int visit(Astprogram *sta){}
    virtual int visit(statlist *sta){}
    virtual int visit(stat *sta){}
    virtual int visit(bl *sta){}
    virtual int visit(expr *sta){}
    virtual int visit(binexp *sta){}
    virtual int visit(unexp *sta){}
    virtual int visit(loc *sta){}
    virtual int visit(nu *sta){}
    virtual int visit(ab *sta){}
    virtual int visit(lf *sta){}
    virtual int visit(fors *sta){}
    virtual int visit(gotos *sta){}
    virtual int visit(lab *sta){}
    virtual int visit(ifs *sta){}
    virtual int visit(whiles *sta){}
    virtual int visit(print *sta){}
    virtual int visit(read *sta){}
    virtual int visit(ass *sta){}
};
BasicBlock *Ea=entry;

class AST
{
public:
  AST()
  {
  }
  virtual int accept(Visitor *v){v->visit(this);}

};

class Astprogram:public AST
{public:
  ///declarlist *de;
  statlist *se;
  Astprogram(){}
  Astprogram(class statlist *s)
  {
  //  this->de=d;
    this->se=s;

  }
  virtual int accept(Visitor *v){v->visit(this);}
  virtual Value *codegen(){

  }
};
class stat:public AST
{
  public:
    virtual int re1(string label){};
    virtual int accept(Visitor *v){v->visit(this);}
    virtual Value *codegen(){}
};
class statlist:public Astprogram
{public:
  vector<stat *>a;
  statlist(){

  }
  void push2(stat *r)
  {
    this->a.push_back(r);
  }
  virtual int accept(Visitor *v){v->visit(this);}
  virtual Value *codegen(){
    for (size_t i = 0; i < a.size(); i++) {
      a[i]->codegen();
    }
  }
};
class declarlist:public Astprogram
{public:
  declarlist()
  {

  }
};



class bl:public AST
{
public:
      statlist * stli;
      bl(statlist *sa)
      {
        this->stli=sa;
      }
      virtual int accept(Visitor *v){v->visit(this);}
      virtual Value *codegen(){
        Value *v=stli->codegen();
        return v;
      }
};
class expr:public AST
{
  public:
    int type;
    expr()
    {
    }
    virtual int accept(Visitor *v){v->visit(this);}
    virtual Value *codegen(){}
    virtual void re1(){}
    virtual int getType() {};
};
class ab:public AST
{
public:
  string label;
  expr *if1;
  int type;
  ab(string la,int t,expr *e)
  {
    if(t==0)
    {
      this->label=la;
      this->if1=e;
      this->type=t;
    }
    else
    {
      this->label=la;
      this->type=t;
    }
  }
  virtual int accept(Visitor *v){int x=v->visit(this);return x;}
  virtual Value *codegen(){
    if(type==0)
    {
      Value *v1=if1->codegen();
      Value *ifcon=Builder.CreateICmpNE(v1,Builder.getInt1(0),"ifcond");
      BasicBlock *aftergoto = createBB(fooFunc,"got");
      Builder.CreateCondBr(v1,labe1[label],aftergoto);
    Builder.SetInsertPoint(aftergoto);

    }
    if(type==1)
    {
        BasicBlock *aftergoto = createBB(fooFunc,"got");
      Builder.CreateBr(labe1[label]);
      Builder.SetInsertPoint(aftergoto);
    }

  }
};

class lf:public AST
{
public:
    expr *mai;
    string a;
    int type2;
    lf(string b,int t,expr * e)
    {
      if(t==0)
      {
        this->type2=0;
        this->a=b;
      }
      else{
        this->a=b;
        this->type2=1;
        this->mai=e;
      }

    }
    virtual int accept(Visitor *v){v->visit(this);}
    int getType()
    {
      return type2;
    }
    void re1(/* arguments */) {
      int i=1;
      //cout<<a<<endl;
    }
    virtual Value *codegen(){
      Value *v = TheModule->getGlobalVariable(a);
      // cout<<v<<endl;
      if(v==0){return err("Unknown Variable name " + a);}
      if(type2==0){//cout<<"ko\n";
      return v;}
      else
      {
        Value *v1=mai->codegen();
        if(mai->getType()==0)
        {
          v1=Builder.CreateLoad(v1);
        }
        vector<Value*> array_index;
        array_index.push_back(Builder.getInt32(0));
      array_index.push_back(v1);
      v = Builder.CreateGEP(v, array_index, a+"_Index");
      return v;

      }
    }

};
class fors:public stat
{
  public:
      string id;
      expr *start;
      expr *dif;
      expr *finish ;
      bl *forblock;
  fors(string id,expr *start,expr  *finish,expr *diff,bl *bld)
  {
    this->id=id;
    this->start=start;
    this->dif=diff;
    this->finish=finish;
    this->forblock=bld;
  }
  int re1(string label)
  {
    return 1;
  }
  virtual int accept(Visitor *v){v->visit(this);}
  virtual Value *codegen(){
        Value *val=start->codegen();
        if(start->getType()==0){val=Builder.CreateLoad(val);}
        BasicBlock *loop=createBB(fooFunc,"loop");
        BasicBlock *after=createBB(fooFunc,"afterloop");
        Value *a=TheModule->getNamedGlobal(id);
        Value *v3=finish->codegen();
        Value *v34=Builder.CreateStore(val,a);
        Value *v45=Builder.CreateLoad(a);
        Value *end1=Builder.CreateICmpULE(val,v3,"condi");
        Builder.CreateCondBr(end1, loop, after);
        //BasicBlock *pre=Builder.GetInsertBlock();
        //Builder.CreateBr(loop);
        Builder.SetInsertPoint(loop);
        Value *v=forblock->codegen();
        Value  *inc;
        if(dif==NULL){
        inc=Builder.getInt32(1);}
        else{inc=dif->codegen();}
        Value *ty=Builder.CreateLoad(a);
        // Value* cur = Builder.CreateLoad(Alloca, id);
        Value *re=Builder.CreateAdd(ty,inc,"next");
        Builder.CreateStore(re,a);
        // Value *b=TheModule->getNamedGlobal(id);
        // Value *v12=  Builder.CreateStore(re,b);
        Value *end=Builder.CreateICmpULE(re,v3,"loopcond");
        Builder.CreateCondBr(end, loop, after);
        Builder.SetInsertPoint(after);
        Ea=after;

  }
};
class gotos:public stat{
public:
  int contype;
  ab * labe;
  gotos(ab * label)
  {
      this->labe=label;
      this->contype=this->labe->type;
  }
  int re1(string label)
  {
    return 0;
  }
  virtual int accept(Visitor *v){int x=v->visit(this);return x;}
  virtual Value *codegen(){
    labe->codegen();
  }
};
class lab :public stat
{
public:
  string labelname;
  stat *a12;
  lab(string a,stat *ass1)
  {
    this->labelname=a;
    this->a12=ass1;
  }
  int re1(string label)
  {
    if(this->labelname==label)
    {
      return 1;
    }
    return 0;
  }
  virtual int accept(Visitor *v){v->visit(this);}
  virtual Value *codegen(){
      Builder.CreateBr(labe1[labelname]);
      Builder.SetInsertPoint(labe1[labelname]);
      a12->codegen();


  }
};
class ifs:public stat
{
public:
  bl *ifblock;
  bl *elblck;
  expr *ifexpr;
  ifs(expr *ifexpr,bl *ifblock,bl *elseblock)
  {
    this->ifexpr=ifexpr;
    this->ifblock=ifblock;
    this->elblck=elseblock;
  }
  int re1(string label)
  {
    return 0;
  }
  virtual int accept(Visitor *v){v->visit(this);}
  virtual Value *codegen(){
    Value *condi=ifexpr->codegen();
    BasicBlock *thenbb=createBB(fooFunc,"thenbb");
    BasicBlock *elsebb=createBB(fooFunc,"elsebb");
    BasicBlock *contbb=createBB(fooFunc,"contbb");
    Value *ifcon=Builder.CreateICmpNE(condi,Builder.getInt1(0),"ifcond");
    Builder.CreateCondBr(ifcon,thenbb,elsebb);
    Builder.SetInsertPoint(thenbb);
    Value *thenval=ifblock->codegen();
    Builder.CreateBr(contbb);
    Value *val;
    Builder.SetInsertPoint(elsebb);
    if(elblck!=NULL)
    {
      val=elblck->codegen();
    }
    Builder.CreateBr(contbb);

   Builder.SetInsertPoint(contbb);
   Ea=contbb;
  }
};

class whiles:public stat
{
  public:
    expr *whileexpr;
    bl *whilebl;
    whiles(expr *e1,bl *b1)
    {
      this->whileexpr=e1;
      this->whilebl=b1;
    }
    int re1(string label)
    {
      return 0;
      }
    virtual int accept(Visitor *v){v->visit(this);}
    virtual Value *codegen(){
      // Value *val=Builder.getInt32(start);
      BasicBlock *loop=createBB(fooFunc,"loop");
      BasicBlock *after=createBB(fooFunc,"afterloop");
      Value *v3=whileexpr->codegen();
      Value *ifcon=Builder.CreateICmpNE(v3,Builder.getInt1(0),"whilecon");
      Builder.CreateCondBr(ifcon, loop, after);
      Builder.SetInsertPoint(loop);
      Value *v=whilebl->codegen();
      v3=whileexpr->codegen();
      Value *ifcon1=Builder.CreateICmpNE(v3,Builder.getInt1(0),"whilecon");
      Builder.CreateCondBr(ifcon1, loop, after);
      Builder.SetInsertPoint(after);
      Ea=after;
    }
};
class print:public stat
{
public:
   string s1;
   int ty;
   lf *s2;
   print(string a,lf *b,int t)
   {
     if(t==0)
     {
       this->s1=a;
       this->s2=b;
       this->ty=t;
     }
     else if(t==1){
       this->s1=a;
       this->ty=1;
       this->s2=b;
     }
     else if(t==3)
     {
       this->s2=b;
       this->ty=t;
     }
     else
     {
       this->s1=a;
       this->s2=b;
       this->ty=t;
     }
   }
   int re1(string label)
   {
     return 0;
   }
   virtual int accept(Visitor *v){v->visit(this);}
   virtual Value *codegen(){
           Value* v;
           vector< Value* >args;
           vector< Type* >type;
           string s;
           string s3;
           if(ty!=3){
           int y3=s1.size()-2;
           //s1=s1.substr(1,s1.size()-2);
           s3=s1.substr(1,y3);
            }

           if(ty==1){s=s3+" "+"%d"+"\n";}
           else if(ty==0){s = s3+" "+"%d";}
           else if (ty==3){s="%d\n";}
           Value* x = Builder.CreateGlobalStringPtr(s);
           args.push_back(x);
           type.push_back(x->getType());
           if(ty!=4){
           if(s2->type2==0)
           {      // cout<<s2->a;
                   v = TheModule->getNamedGlobal(s2->a);
                   v =Builder.CreateLoad(v);
           }
           else
           {   // array variable
               //cout << s2->a << endl;
               v = s2->codegen();
               v = Builder.CreateLoad(v);
              // Builder.CreateLoad()
               //<<"hii"<<endl;
           }
           args.push_back(v);
           type.push_back(v->getType());}
           llvm::ArrayRef<Type*> typeargs(type);
           llvm::ArrayRef<Value*> refargs(args);
           llvm::FunctionType *FType = FunctionType::get(Type::getInt32Ty(Context), typeargs, false);
           Constant* printfunc1 = TheModule->getOrInsertFunction("printf", FType);
           return Builder.CreateCall(printfunc1,refargs);
         }


};

class read:public stat
{
public:
    lf *va;
    read(lf *ex)
    {
      this->va=ex;
    }
    int re1(string label)
    {
      return 0;
      //cout<<"hi"<<endl;
    }
    virtual int accept(Visitor *v){v->visit(this);}
    virtual Value *codegen(){
      Value* v;
            vector< Value* >args;
            vector< Type* >type;
            string s = "%d";
            Value* x = Builder.CreateGlobalStringPtr(s);
            args.push_back(x);
            type.push_back(x->getType());
            if(va->type2==0)
            {
                    v = TheModule->getNamedGlobal(va->a);

            }
            else
            {   // array variable
                // << va->a << endl;
                v = va->codegen();
            }
            args.push_back(v);
            type.push_back(v->getType());
            llvm::ArrayRef<Type*> typeargs(type);
            llvm::ArrayRef<Value*> refargs(args);
            llvm::FunctionType *FType = FunctionType::get(Type::getInt32Ty(Context), typeargs, false);
            Constant* printfunc = TheModule->getOrInsertFunction("scanf", FType);
            return Builder.CreateCall(printfunc,refargs);
    }
};

class ass:public stat
{
public:
  lf * le;
  expr * re;
  string op;
  ass(lf * lo,expr *re)
  {
    this->le=lo;
    this->re=re;
    this->op.push_back('=');
  }
  int re1(string label)
  {
    return 0;
  }
virtual int accept(Visitor *v){v->visit(this);}
virtual Value *codegen()
{
    if(1)
    {
      Value* cur = TheModule->getGlobalVariable(le->a);
      // Value* lhs = le->codegen();
      if(le->type2==1)
      {
        Value *v1=le->mai->codegen();
        if(le->mai->getType()==0)
        {
          v1=Builder.CreateLoad(v1);
        }
        vector<Value*> array_index;
        array_index.push_back(Builder.getInt32(0));
        array_index.push_back(v1);
        cur = Builder.CreateGEP(cur, array_index, le->a+"_Index");
        //lhs = cur;
      }
      Value *lhs=cur;
      Value* val = re->codegen();
      if(re->getType()==0){val=Builder.CreateLoad(val);}
      return Builder.CreateStore(val, lhs);
    }
}
};

class binexp:public expr
{
  public:

    expr *left;
    expr *right;

    string op;
  binexp(expr *a,expr *b,string op1)

  {
    this->type=0;
    this->left=a;
    this->right=b;
    this->op=op1;
  }
  virtual int accept(Visitor *v){int x=v->visit(this);return x;}
  virtual Value *codegen(){
    Value *v1 = left->codegen();
    if(left->getType()==0)
        v1 = Builder.CreateLoad(v1);
    Value *v2=right->codegen();
    if(right->getType()==0)
      v2 = Builder.CreateLoad(v2);
    if((!v1)||(!v2)){
    return err("error in expression");}
    Type *ty;
    if (op=="+")
    {
        Value *v= Builder.CreateAdd(v1, v2, "addtmp");
        return v;
    }
    if (op=="-")
    {
        Value *v= Builder.CreateSub(v1, v2, "subtmp");
        return v;
    }
    if (op=="*")
    {
        Value *v= Builder.CreateMul(v1, v2, "tmp");
        return v;
    }
    if (op=="/")
    {
        Value *v= Builder.CreateUDiv(v1, v2, "tmp");
        return v;
    }
    if (op=="%")
    {
        Value *v= Builder.CreateURem(v1, v2, "tmp");
        return v;
    }
    if (op=="<")
    {
        Value *v= Builder.CreateICmpULT(v1, v2, "tmp");
        return v;
    }
    if (op==">")
    {
        Value *v= Builder.CreateICmpUGT(v1, v2, "tmp");
        return v;
    }
    if (op=="<=")
    {
        Value *v= Builder.CreateICmpULE(v1, v2, "tmp");
        return v;
    }
    if (op==">=")
    {
        Value *v= Builder.CreateICmpUGE(v1, v2, "tmp");
        return v;
    }
    if (op=="==")
    {
        Value *v= Builder.CreateICmpEQ(v1, v2, "tmp");
        return v;
    }
    else if (op == "!="){
    Value *v = Builder.CreateICmpNE(v1,v2,"notequalcomparetmp");
    return v;
}
else if (op == "||"){
  Value *v = Builder.CreateICmpNE(v1,v2,"notequalcomparetmp");
  return v;
}
else if (op == "&&"){
    Value *v = Builder.CreateICmpNE(v1,v2,"notequalcomparetmp");
    return v;
}

}
};
class unexp:public expr
{
  public:
      expr *mai;
      string op;
  unexp(expr *a,string o1)
  {
    if(o1[0]=='(')
    {
    this->type=1;
    this->mai=a;
    }
    else
    {
      this->type=2;
      this->mai=a;
      this->op=o1;
    }
  }
  virtual int accept(Visitor *v){int x=v->visit(this);return x;}
  virtual Value *codegen(){
    Value * hs=mai->codegen();
    if(mai->getType()==0)
    {
      hs=Builder.CreateLoad(hs);
    }
    if(type==1){
      return hs;
    }
    else{
    if(op=="!"){
       return Builder.CreateNot(hs,"ntmp");
    }
    else
    {
         return Builder.CreateNeg(hs,"negtmp");
    }

    }
  }
}
;
class loc:public expr
{
public:
    lf *lo;

    loc(lf * left)
    {
      this->type=5;
      this->lo=left;
    }
   virtual int accept(Visitor *v){int x=v->visit(this);return x;}
   virtual Value *codegen(){
     return lo->codegen();
   }
   virtual  int getType()
   {
     return 0;
   }

};
class nu:public expr
{
  public:
  int val;
  nu(int a)
  {
    this->val=a;
    this->type=3;
  }
   virtual int accept(Visitor *v){v->visit(this);}
   void re1()
   {
     std::cout << val << '\n';
   }
   virtual Value *codegen(){
     //Value* v =  ConstantInt::get(getGlobalContext(), llvm::APInt(32,val));
    Value* v =  Builder.getInt32(val);
     return v;

   }
};
/*Code for interpreter*/
class interpret:public Visitor
{
public:
    vector<statlist *>sa;
    interpret(vector<statlist *>s){
      this->sa=s;
    }
    int visit(Astprogram *sta)
    {
      sta->se->accept(this);
    }
    int visit(statlist *sta)
    {
      for(int i=0;i<sta->a.size();i++)
        {
          int x=sta->a[i]->accept(this);
          //cout<<x<<endl;
          if(x==1e5)
          {
            return 0;
          }
        }
    }
    int visit(fors *sta)
    {
      string y1=sta->id;
      int x=sta->start->accept(this);
      int y;
      if(sta->dif!=NULL){
      y=sta->dif->accept(this);}
      else{y=1;}
      int z=sta->finish->accept(this);
      while(x<=z)
      {
        stored[y1]=x;
        sta->forblock->accept(this);
        x=x+y;
      }
      stored[y1]=x;
    }
    int visit(whiles *sta)
    {
      int x;
      int i=3;
      while(1)
      {
        x=sta->whileexpr->accept(this);
        if(x<=0)
        {
          break;
        }
        sta->whilebl->accept(this);
      }
    }
    int visit(read *sta)
    {
      int x;
      cin>>x;
      if(sta->va->type2==0)
      {
      stored[sta->va->a]=x;}
      else
      {
        int  m=sta->va->mai->accept(this);
        char a=m+'0';
        string s;
        s.append(sta->va->a);
        s.push_back('[');
        s.push_back(a);
        s.push_back(']');
      stored[s]=x;
      }
      //cout<<x<<endl;
    }
    int visit(ass *sta)
    {
      //cout<<"hello"<<endl;
      int x=sta->re->accept(this);
    // cout<<x<<endl;
     if(sta->le->type2==0)
     {
     stored[sta->le->a]=x;}
     else
     {
       int  m=sta->le->mai->accept(this);
       char a=m+'0';
       string s;
       s.append(sta->le->a);
       s.push_back('[');
       s.push_back(a);
       s.push_back(']');
      // cout<<s<<endl;
     stored[s]=x;
     }
      //  stored[sta->le->a]=x;
      //map[sta->le]=x;
    }
    int visit(ifs *sta)
    {
      int x=sta->ifexpr->accept(this);
    //  cout<<x<<endl;
      if(x>0)
      {
        sta->ifblock->accept(this);
      }
      else
      {
        if(sta->elblck!=NULL)
          sta->elblck->accept(this);
      }
    }
    int visit(bl *sta)
    {
      sta->stli->accept(this);
    }
    int visit(binexp *sta)
    {
      int left=sta->left->accept(this);
      int right=sta->right->accept(this);
      int a=left;
      int b=right;
      if(sta->op.compare("+")==0)
          return left+right;
      if(sta->op.compare("-")==0)
            return left-right;
      if(sta->op.compare("*")==0)
            return left*right;
      if(sta->op.compare("/")==0)
            return left/right;
      if(sta->op.compare("%")==0)
            return left%right;
      if(sta->op.compare("<")==0)
      {int x=a<b;
            return x;}
            if(sta->op.compare("<=")==0)
            {int x=(a<=b);
                  return x;}
      if(sta->op.compare(">")==0)
            return a>b;
      if(sta->op.compare(">=")==0)
            return a>=b;
      if(sta->op.compare("||")==0)
            return a||b;
      if(sta->op.compare("&&")==0)
            return a&&b;
      if(sta->op.compare("==")==0)
            return a==b;
      if(sta->op.compare("!=")==0)
              return a!=b;
    }
    int visit(lab *sta)
    {
      sta->a12->accept(this);
    }
    int visit(print *sta)
    {
    string s3;
    if(sta->ty!=3){
      int x=sta->s1.size()-2;
      s3=sta->s1.substr (1,x);}
      int x1;
      if(sta->ty!=4){
      x1=sta->s2->accept(this);}
      if(sta->ty==1)
      {
        cout<<s3<<" "<<x1<<endl;}
      else if(sta->ty==0){

          cout<<s3<<" "<<x1;}
        else if (sta->ty==3)
        {
          cout<<x1<<endl;
        }
        else
        {
          cout<<s3<<endl;
        }

    }
    int visit(unexp *sta)
    {
      int a;
      int an=sta->mai->accept(this);
      if(sta->op.compare("("))
          return an;
      else{
      //  cout<<an<<endl;

        a=!an;
        //cout<<a<<endl;
        return a;}

    }
    int visit(gotos *sta)
    {
      int x=sta->labe->accept(this);
      return x;
    }
    int visit(ab *sta)
    {
      int fl=0;
      if(sta->type==0)
      {
        int x=sta->if1->accept(this);
        if(x>0)
        {
          fl=1;
        }
      }
      if(sta->type==1)
      {
        fl=1;
      }

      if(fl==1)
      {
        int i1,i2;
        int i,j;
        string s2=sta->label;
        for(i=0;i<sa.size();i++)
        {
          for(j=0;j<sa[i]->a.size();j++)
          {
                if(sa[i]->a[j]->re1(s2)==1)
                {
                  i1=i;
                  i2=j;
                }
          }
        }
        for(j=i2;j<sa[i1]->a.size();j++)
        {
          int x=sa[i1]->a[j]->accept(this);
          if(x==1e5)
          {
            return 1e5;
          }
        }
        return 1e5;
      }
      else
      {
        return 0;
      }
    }
    int visit(loc *sta)
    {
      return sta->lo->accept(this);
    }
    int visit(lf *sta)
    {
      if(sta->type2==0){

      return stored[sta->a];}
      else
      {
        string s1;
        int y=sta->mai->accept(this);
        char z=y+'0';
        s1.append(sta->a);
        s1.push_back('[');
        s1.push_back(z);
        s1.push_back(']');
        return stored[s1];
      }
    }
    int visit(nu *sta)
    {
      int x=sta->val;
      return x;
    }
};
