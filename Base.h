#ifndef _BASE_H_
#define _BASE_H_
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include"Scanner.h"
#include<fstream> 
#define maxsize 104

using namespace std;

	/*非终极符*/
typedef enum 
{
	Program,     ProgramHead,   ProgramName,    DeclarePart, TypeDec, TypeDeclaration,     
	TypeDecList,   TypeDecMore,    TypeId,      TypeName,   BaseType,    
	StructureType, ArrayType,      Low,         Top,	    RecType,     
	FieldDecList,  FieldDecMore,   IdList,      IdMore,     VarDec,  
	VarDeclaration,VarDecList,     VarDecMore,  VarIdList,   VarIdMore,
	ProcDec,       ProcDeclaration,ProcDecMore,    ProcName,    ParamList,   
	ParamDecList,ParamMore,     Param,          FormList,    FidMore,
	ProcDecPart, ProcBody,      ProgramBody,    StmList,     StmMore,     Stm,
	AssCall,     AssignmentRest,ConditionalStm, LoopStm,     InputStm,
	Invar,		 OutputStm,     ReturnStm,      CallStmRest, ActParamList,
	ActParamMore,RelExp,        OtherRelE,      Exp,         OtherTerm,
	Term,        OtherFactor,   Factor,         Variable,    VariMore,    FieldVar,
	FieldVarMore,CmpOp,         AddOp,          MultOp
}NonTerminals;


static struct node
{
	NonTerminals left;
	string right[10];
} productions[104]={
{Program,{"ProgramHead","DeclarePart","ProgramBody","DOT","0"}},
{ProgramHead,{"PROGRAM","ProgramName","0"}},
{ProgramName,{"ID","0"}},
{DeclarePart,{"TypeDec","VarDec","ProcDec","0"}},
{TypeDec,{"$","0"}},

{TypeDec,{"TypeDeclaration","0"}},
{TypeDeclaration,{"TYPE","TypeDecList","0"}},
{TypeDecList,{"TypeId","EQ","TypeName","SEMI","TypeDecMore","0"}},
{TypeDecMore,{"$","0"}},
{TypeDecMore,{"TypeDecList","0"}},
{TypeId,{"ID","0"}},
{TypeName,{"BaseType","0"}},
{TypeName,{"StructureType","0"}},
{TypeName,{"ID","0"}},
{BaseType,{"INTEGER","0"}},
{BaseType,{"CHAR","0"}},
{StructureType,{"ArrayType","0"}},
{StructureType,{"RecType","0"}},
{ArrayType,{"ARRAY","LMIDPAREN","Low","UNDERANGE","Top","RMIDPAREN","OF","BaseType","0"}},
////////////////////
{Low,{"INTC","0"}},
{Top,{"INTC","0"}},
{RecType,{"RECORD","FieldDecList","END","0"}},
{FieldDecList,{"BaseType","IdList","SEMI","FieldDecMore","0"}},
{FieldDecList,{"ArrayType","IdList","SEMI","FieldDecMore","0"}},
{FieldDecMore,{"$","0"}},
{FieldDecMore,{"FieldDecList","0"}},
{IdList,{"ID","IdMore","0"}},
{IdMore,{"$","0"}},
{IdMore,{ "COMMA","IdList","0"}},
{VarDec,{"$","0"}},
{VarDec,{"VarDeclaration","0"}},
{VarDeclaration,{"VAR","VarDecList","0"}},
{VarDecList,{"TypeName","VarIdList","SEMI","VarDecMore","0"}},
{VarDecMore,{"$","0"}},
{VarDecMore,{"VarDecList","0"}},
{VarIdList,{"ID","VarIdMore","0"}},
{VarIdMore,{"$","0"}},
{VarIdMore,{"COMMA","VarIdList","0"}},
{ProcDec,{"$","0"}},
{ProcDec,{"ProcDeclaration","0"}},
{ProcDeclaration,{"PROCEDURE","ProcName","LPAREN","ParamList","RPAREN","SEMI","ProcDecPart","ProcBody","ProcDecMore","0"}},
{ProcDecMore,{"$","0"}},
{ProcDecMore,{"ProcDeclaration","0"}},
{ProcName,{"ID","0"}},
{ParamList,{"$","0"}},
{ParamList,{"ParamDecList","0"}},
{ParamDecList,{"Param","ParamMore","0"}},
{ParamMore,{"$","0"}},
{ParamMore,{"SEMI","ParamDecList","0"}},
{Param,{"TypeName","FormList","0"}},
{Param,{"VAR","TypeName","FormList","0"}},
{FormList,{"ID","FidMore","0"}},
{FidMore,{"$","0"}},
{FidMore,{ "COMMA","FormList","0"}},
{ProcDecPart,{"DeclarePart","0"}},
{ProcBody,{"ProgramBody","0"}},
{ProgramBody,{"BEGIN","StmList","END","0"}},
{StmList,{"Stm","StmMore","0"}},
{StmMore,{"$","0"}},
{StmMore,{"SEMI","StmList","0"}},
{Stm,{"ConditionalStm","0"}},
{Stm,{"LoopStm","0"}},
{Stm,{"InputStm","0"}},
{Stm,{"OutputStm","0"}},
{Stm,{"ReturnStm","0"}},
{Stm,{"ID","AssCall","0"}},
{AssCall,{"AssignmentRest","0"}},
{AssCall,{"CallStmRest","0"}},
{AssignmentRest,{"VariMore","ASSIGN","Exp","0"}},
{ConditionalStm,{"IF","RelExp","THEN","StmList","ELSE","StmList","FI","0"}},
{LoopStm,{"WHILE","RelExp","DO","StmList","ENDWH","0"}},
{InputStm,{"READ","LPAREN","Invar","RPAREN","0"}},
{Invar,{"ID","0"}},
{OutputStm,{"WRITE","LPAREN","Exp","RPAREN","0"}},
{ReturnStm,{"RETURN","LPAREN","Exp","RPAREN","0"}},
{CallStmRest,{"LPAREN","ActParamList","RPAREN","0"}},
{ActParamList,{"$","0"}},
{ActParamList,{"Exp","ActParamMore","0"}},
{ActParamMore,{"$","0"}},
{ActParamMore,{ "COMMA","ActParamList","0"}},
{RelExp,{"Exp","OtherRelE","0"}},
{OtherRelE,{"CmpOp","Exp","0"}},
{Exp,{"Term","OtherTerm","0"}},
{OtherTerm,{"$","0"}},
{OtherTerm,{"AddOp","Exp","0"}},
{Term,{"Factor","OtherFactor","0"}},
{OtherFactor,{"$","0"}},
{OtherFactor,{"MultOp","Term","0"}},
{Factor,{"LPAREN","Exp","RPAREN","0"}},
{Factor,{"INTC","0"}},
{Factor,{"Variable","0"}},
{Variable,{"ID","VariMore","0"}},
{VariMore,{"$","0"}},
{VariMore,{"LMIDPAREN","Exp","RMIDPAREN","0"}},
{VariMore,{"DOT","FieldVar","0"}},
{FieldVar,{"ID","FieldVarMore","0"}},
{FieldVarMore,{"$","0"}},
{FieldVarMore,{"LMIDPAREN","Exp","RMIDPAREN","0"}},
{CmpOp,{"LT","0"}},
{CmpOp,{"EQ","0"}},
{AddOp,{"PLUS","0"}},
{AddOp,{"MINUS","0"}},
{MultOp,{"TIMES","0"}},
{MultOp,{"OVER","0"}}

};
class Base {
protected:
	
    int T;

    set<string> firstSet[maxsize];  // First集
    set<string> followSet[maxsize];  // Follow集
    vector<LexType> terminalNoEmpty; // 去$(空)的终结符
    vector<NonTerminals> nonterminal;  // 非终结符

    bool isNonterminal(string s);
    int getIndex(string target);  // 获得target在终结符集合中的下标
    int getNIndex(string target);  // 获得target在非终结符集合中的下标
    void getFirst(string target);  // 得到First(target)
    void getFollow(string target,int aa[]);  // 得到Follow(target)
    string tterminalNoEmpty(int l);
    string nonTerminals(int n);
	int rlen(string a[]){
	    int  len =0;
	    for (int j = 0; a[j]!= "0"; j++)
	        len++;
	    return len;
	}
	
public:
	Base(){
		T=104;
		//将非终结符加入terminalNoEmpty
		for(NonTerminals t=Program ;t<=MultOp; t=(NonTerminals)(t+1)){
			nonterminal.push_back(t);
			
	
		}
		//将终结符加入nonterminal
		for(LexType n=ENDFILE ;n<=UNDERANGE; n=(LexType)(n+1)){
			terminalNoEmpty.push_back(n);
		}	
	}
	
	void getFirstAndFollow();

};
#endif


