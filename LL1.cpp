#include "LL1.h"


void LL1::CreatLL1Table()
{
    getFirstAndFollow(); //�ȵ��øú������first����follow��
	for (int index = 0; index < T; index++) {  									                    // ����ÿ������ʽ(���index):A->��
		int row = getNIndex(nonTerminals(productions[index].left));
		int emptyCount = 0;
		for (int i = 0; productions[index].right[i]!= "0"; i++) { // 1) ��FIRST(��)�е�ÿ���ս����a,��index����(A, a)��
			string tmp = productions[index].right[i];
			
			if (!isNonterminal(tmp) || tmp == "$") { // tmp���ս��
				if (tmp != "$")
					LL1Table[row][getIndex(tmp)] = index;
				if (tmp == "$") {
					emptyCount++;
				}
				break;
			}
			else {  // tmp�Ƿ��ս��
				set<string>::iterator it;
				int tmpIndex = getNIndex(tmp);
				// ��FIRST(tmp)�е�ÿ���ս����a,��i����(A, a)��
				for (it = firstSet[tmpIndex].begin(); it != firstSet[tmpIndex].end(); it++) {
					LL1Table[row][getIndex(*it)] = index;
				}
				if (firstSet[tmpIndex].count("$") != 0) {      // 2) �����$��FIRST(tmp)��,���������е���һ������
					emptyCount++;
				}
				else {
					break;
				}
			}
		}
        // cout<< "cahngdu"<<rlen(productions[index].right)<<" ";
		// 2) �����$��FIRST(��)��,��FOLLOW(A)�е�ÿ���ս���������b,��i����(A,b)��
		if (emptyCount == rlen(productions[index].right)) {
			set<string>::iterator  it;
			for (it = followSet[row].begin(); it != followSet[row].end(); it++) {
				LL1Table[row][getIndex(*it)] = index;
			}
		}
	}
}

void LL1::analyExpression(struct token s[]) {
	/*int aa[1000];
	for(int i=0;i<1000;i++){
		aa[i]=0;
	} */
	ofstream mycout4("C:\\Users\\NASA\\Desktop\\��������.txt");
	vector<int> lineStack;
	
    for (int i = 0; s[i].w.tok!=ENDFILE; i++){ 
        leftExpr.push_back(tterminalNoEmpty(s[i].w.tok));
        lineStack.push_back(s[i].lineShow);
        //aa[i]=s[i].lineShow;
      //  cout<<tterminalNoEmpty(s[i].w.tok)<<endl;
    } 
    leftExpr.push_back("#");

    analyStack.push_back("#");
    analyStack.push_back(nonTerminals(nonterminal[0]));  // ���뿪ʼ����

   while (analyStack.size() > 0) {
        //cout<<"����ջ��";
        string outs = "";
        for (int i = 0; i < analyStack.size(); i++)
            outs += analyStack[i];
        mycout4<<endl;
        mycout4<<"����ջ:"<<endl;
        mycout4<<"+++++++++++++++++++++++++++++++++++++"<<endl;
        mycout4 << setw(15) << outs << endl;
        mycout4<<"+++++++++++++++++++++++++++++++++++++"<<endl;

        //cout<<"ʣ�����봮��";
        outs = "";
        for (int i = 0; i < leftExpr.size(); i++)
            outs = outs + leftExpr[i] + "  ";
        mycout4<<endl;
        mycout4<<"ʣ�����봮:"<<endl;
		mycout4<<"*************************************"<<endl; 
        mycout4 << setw(15) << outs << endl;
        mycout4<<"*************************************"<<endl;

        // ƥ��
        string string1 = analyStack.back();
        string string2 = leftExpr.front();
        if (string1 == string2 && string1 == "#") {
            mycout4 << setw(15) << "Accepted!" << endl;
            return;
        }
        if (string1 == string2) {
            analyStack.pop_back();
            leftExpr.erase(leftExpr.begin());
            lineStack.erase(lineStack.begin());
            mycout4  << "ƥ�䣺" << string1 << endl;
        }
        else if (LL1Table[getNIndex(string1)][getIndex(string2)] != -1) {  // Ԥ��������Ƶ���ɽ����Ƶ�
            int tg = LL1Table[getNIndex(string1)][getIndex(string2)];
            analyStack.pop_back();

            if (productions[tg].right[0]!= "$") {
                for (int i = rlen(productions[tg].right) - 1; i >= 0; i--){ // ע�������Ƿ���ģ�����ѹ��
                    analyStack.push_back(productions[tg].right[i]);
                }
            }
            
            string str="";
			 
			for (int i = 0 ; i < rlen(productions[tg].right) ; i++){ // ע�������Ƿ���ģ�����ѹ��
                str = str + productions[tg].right[i] + "  ";
            }
            mycout4 << "�Ƶ���" << nonTerminals(productions[tg].left) << "->" << str <<endl;
        }
        else {  // ����
            mycout4 << setw(15) << "error!" << endl;
            mycout4 << "��������Ϊ:" << lineStack.front() << "��";
			return;
        }  	
    }
    mycout4.close();
}

/*void LL1::printPredictTable() {
    // ��ͷ
    cout<<endl;
    cout<<"************************************************"<<endl;
    for (int i = 0; i < nonterminal.size(); i++) {
        cout << nonTerminals(nonterminal[i]) << ":";
        for (int j = 0; j < terminalNoEmpty.size(); j++) {
            if (LL1Table[i][j] == -1)
                cout << setw(10) << "   ";
            else{
			for (int n = 0; productions[LL1Table[i][j]].right[n]!= "0"; n++) {
                cout << productions[LL1Table[i][j]].right[n];
				}
        	}
		}
        cout << endl;
    }
    cout << endl;
}*/

void LL1::getResult(FILE *fpin) {
    Scanner scanner;

    token *s = scanner.getTokenList(fpin); //��ȡtokenlist
    scanner.PrintTokenList();   //���tokenlist

    CreatLL1Table();           //����LL1��
    // printPredictTable();       //���predict��
    //ջƥ��
    cout << endl; 
    //cout << setw(15) << "����ջ" << setw(15) << "ʣ�����봮" << setw(15) << "�Ƶ�ʽ" << endl;
    analyExpression(s);        //����tokenlist

}

