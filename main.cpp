#include <iostream>

#include "LL1.h"

using namespace std;

int main()
{   FILE *fpin;//���ڴ��ļ�
    string file_name;//�ļ���
    LL1 ll1 ;
    //cout << "�������ļ�����";
    //cin >> file_name;//��ȡ������ļ���
    fpin=fopen("C:\\Users\\NASA\\Desktop\\C4.TXT", "r");//�����ļ������ļ����򿪷�ʽ�Ƕ�ȡ
    if (!fpin)//���û���ҵ�����ļ�
    {
       cerr << "���ļ�" << file_name << "ʧ��" << endl;
        return -1;
    }
    ll1.getResult(fpin); //������Ҫ�������ļ�
    
    return 0;
}

