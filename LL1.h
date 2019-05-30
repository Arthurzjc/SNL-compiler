#ifndef _LL1_H_
#define _LL1_H_

#include"Base.h"
#include<vector>
#include<set>
#define NonTerminalsSize 67
#define terminalNoEmptySize 42

class LL1 : public Base {
private:
    vector<string> analyStack; // ����ջ
    vector<string> leftExpr;  // ʣ�����봮
    int LL1Table[NonTerminalsSize][terminalNoEmptySize]; //LL1������

public:
    LL1(){
	    for(int i = 0 ; i < NonTerminalsSize ; i++){
	        for(int j = 0 ; j < terminalNoEmptySize ; j++){
	            LL1Table[i][j] = -1;   //LL1Table��ʼ��
	        }
	    }
	}

    void CreatLL1Table(); //�õ�LL1������
    void analyExpression(struct token s[]);  // �����������s
    void printPredictTable();  // ���Ԥ���
    void getResult(FILE *fpin); // �ۺϴ���
};
#endif

