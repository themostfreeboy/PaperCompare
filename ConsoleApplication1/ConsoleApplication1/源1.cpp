//#include <stdio.h>
//#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#define LunwenN 6//������ƪ��


class Lunwen
{
public:
	string LunwenName;
	string ZuozheName[3];
	string ZuozheWork[3];
	string FabiaoTime;
	string LunwenKeyword[3];
};

Lunwen lw[LunwenN];//����������
int a[LunwenN], b[LunwenN];//�ֱ�洢2��ָ���˵������������е��±�
int a_n = 0, b_n = 0;//�ֱ�洢a,b���������������������Ŀ
string Name_1 = "����";//ָ���ĵ�һ���˵����� 
string Name_2 = "����";//ָ���ĵڶ����˵����� 

//���ݶ�ȡ
void ReadData(ifstream* in ,int num)
{
	int i;
	for (i = 0; i < num; i++)
	{
		cout << "��" << i+1 << "ƪ����" << endl;
		*in >> lw[i].LunwenName;
		cout << "��������:" << lw[i].LunwenName << endl;
		*in >> lw[i].ZuozheName[0];
		cout << "����1����:" << lw[i].ZuozheName[0] << endl;
		*in >> lw[i].ZuozheWork[0];
		cout << "����1�����ڵ�λ:" << lw[i].ZuozheWork[0] << endl;
		*in >> lw[i].ZuozheName[1];
		cout << "����2����:" << lw[i].ZuozheName[1] << endl;
		*in >> lw[i].ZuozheWork[1];
		cout << "����2�����ڵ�λ:" << lw[i].ZuozheWork[1] << endl;
		*in >> lw[i].ZuozheName[2];
		cout << "����3����:" << lw[i].ZuozheName[2] << endl;
		*in >> lw[i].ZuozheWork[2];
		cout << "����3�����ڵ�λ:" << lw[i].ZuozheWork[2] << endl;
		*in >> lw[i].FabiaoTime;
		cout << "���ķ���ʱ��:" << lw[i].FabiaoTime << endl;
		*in >> lw[i].LunwenKeyword[0];
		cout << "���Ĺؼ���1:" << lw[i].LunwenKeyword[0] << endl;
		*in >> lw[i].LunwenKeyword[1];
		cout << "���Ĺؼ���2:" << lw[i].LunwenKeyword[1] << endl;
		*in >> lw[i].LunwenKeyword[2];
		cout << "���Ĺؼ���3:" << lw[i].LunwenKeyword[2] << endl;

		cout << endl;
	}
}

//2��ָ����ɸѡ
void select(string name1,string name2,int num)
{
	int i,j;
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (strcmp(name1.c_str(), lw[i].ZuozheName[j].c_str()) == 0)
			{
				a[a_n++] = i;
			}
			if (strcmp(name2.c_str(), lw[i].ZuozheName[j].c_str()) == 0)
			{
				b[b_n++] = i;
			}
		}
	}
	cout << "����" << name1 << "�����Ĺ���" << a_n << "ƪ" << endl;
	cout << "����" << name2 << "�����Ĺ���" << b_n << "ƪ" << endl;

	cout << endl;
}


//ѡ������ָ��������һ�𷢱��ʱ��
void TimeSelect()
{
	int i, j;
	int tag = 0;//�Ƿ�һ�𷢱�����ĵı��
	for (i = 0; i < a_n; i++)
	{
		for (j = 0; j < b_n; j++)
		{
			if (a[i]==b[j])
			{
				cout << Name_1 << "��" << Name_2 << "��" << (lw[a[i]]).FabiaoTime << "��һʱ��һ�𷢱������" << endl;
				tag = 1;
			}
		}
	}
	if (tag == 0)
	{
		cout << Name_1 << "��" << Name_2 << "��δ��һ�𷢱������" << endl;
	}

	cout << endl;
}

//ָ�������˵��о��������ƶȼ���
double SimilarSelect()
{
	int i, j, k, l;
	int temp_number;//��¼ĳ��ƪ���ĵĹؼ�����ͬ�ĸ���
	double single_similar[LunwenN*LunwenN];//ĳ��ƪ�����о���������ƶ�
	int single_similar_i=0;//�洢ĳ��ƪ�����о���������ƶ�����ĵ�ǰ�±�
	double similar;//���յ��о��������ƶ�
	for (i = 0; i < a_n; i++)
	{
		for (j = 0; j < b_n; j++)
		{
			temp_number = 0;
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					if (strcmp((lw[a[i]]).LunwenKeyword[k].c_str(), (lw[b[j]]).LunwenKeyword[l].c_str()) == 0)
					{
						temp_number++;
					}
				}
				
			}
			single_similar[single_similar_i++] = temp_number*1.0 / 3;
		}
	}
	//�����������ƶ�
	double sum = 0.0;
	for (i = 0; i < single_similar_i; i++)
	{	
		sum += single_similar[i];
	}
	similar = sum*1.0 / single_similar_i;

	return similar;
}

int main()
{	
	//���ļ�
	ifstream in;
	in.open("test.txt", ios::in);
	if (!in.is_open())
    {
		cout << "The file cannot open!" << endl;
		system("pause");
		return 0;
    }

	ReadData(&in, LunwenN);//���ݶ�ȡ

	in.close();//�ر��ļ�

	select(Name_1, Name_2, LunwenN);//ɸѡ������ָ�������˵��������ı��
	
	TimeSelect();//ѡ������ָ��������һ�𷢱��ʱ��
   
	double similar = SimilarSelect();//ָ�������˵��о��������ƶ�

	cout << Name_1 << "��" << Name_2 << "���о��������ƶ�Ϊ:" << similar << endl;

	cout << endl;

	system("pause");
	return 0;
}
