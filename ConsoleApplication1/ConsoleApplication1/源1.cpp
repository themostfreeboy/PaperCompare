//#include <stdio.h>
//#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#define LunwenN 6//论文总篇数


class Lunwen
{
public:
	string LunwenName;
	string ZuozheName[3];
	string ZuozheWork[3];
	string FabiaoTime;
	string LunwenKeyword[3];
};

Lunwen lw[LunwenN];//论文类数组
int a[LunwenN], b[LunwenN];//分别存储2个指定人的论文类数组中的下标
int a_n = 0, b_n = 0;//分别存储a,b两数组中所存的论文总数目
string Name_1 = "张三";//指定的第一个人的姓名 
string Name_2 = "李四";//指定的第二个人的姓名 

//数据读取
void ReadData(ifstream* in ,int num)
{
	int i;
	for (i = 0; i < num; i++)
	{
		cout << "第" << i+1 << "篇论文" << endl;
		*in >> lw[i].LunwenName;
		cout << "论文名称:" << lw[i].LunwenName << endl;
		*in >> lw[i].ZuozheName[0];
		cout << "作者1姓名:" << lw[i].ZuozheName[0] << endl;
		*in >> lw[i].ZuozheWork[0];
		cout << "作者1的所在单位:" << lw[i].ZuozheWork[0] << endl;
		*in >> lw[i].ZuozheName[1];
		cout << "作者2姓名:" << lw[i].ZuozheName[1] << endl;
		*in >> lw[i].ZuozheWork[1];
		cout << "作者2的所在单位:" << lw[i].ZuozheWork[1] << endl;
		*in >> lw[i].ZuozheName[2];
		cout << "作者3姓名:" << lw[i].ZuozheName[2] << endl;
		*in >> lw[i].ZuozheWork[2];
		cout << "作者3的所在单位:" << lw[i].ZuozheWork[2] << endl;
		*in >> lw[i].FabiaoTime;
		cout << "论文发表时间:" << lw[i].FabiaoTime << endl;
		*in >> lw[i].LunwenKeyword[0];
		cout << "论文关键词1:" << lw[i].LunwenKeyword[0] << endl;
		*in >> lw[i].LunwenKeyword[1];
		cout << "论文关键词2:" << lw[i].LunwenKeyword[1] << endl;
		*in >> lw[i].LunwenKeyword[2];
		cout << "论文关键词3:" << lw[i].LunwenKeyword[2] << endl;

		cout << endl;
	}
}

//2个指定人筛选
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
	cout << "含有" << name1 << "的论文共有" << a_n << "篇" << endl;
	cout << "含有" << name2 << "的论文共有" << b_n << "篇" << endl;

	cout << endl;
}


//选出含有指定两个人一起发表的时间
void TimeSelect()
{
	int i, j;
	int tag = 0;//是否一起发表过论文的标记
	for (i = 0; i < a_n; i++)
	{
		for (j = 0; j < b_n; j++)
		{
			if (a[i]==b[j])
			{
				cout << Name_1 << "与" << Name_2 << "在" << (lw[a[i]]).FabiaoTime << "这一时间一起发表过论文" << endl;
				tag = 1;
			}
		}
	}
	if (tag == 0)
	{
		cout << Name_1 << "与" << Name_2 << "从未在一起发表过论文" << endl;
	}

	cout << endl;
}

//指定两个人的研究领域相似度计算
double SimilarSelect()
{
	int i, j, k, l;
	int temp_number;//记录某两篇论文的关键词相同的个数
	double single_similar[LunwenN*LunwenN];//某两篇论文研究领域的相似度
	int single_similar_i=0;//存储某两篇论文研究领域的相似度数组的当前下标
	double similar;//最终的研究领域相似度
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
	//计算最终相似度
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
	//打开文件
	ifstream in;
	in.open("test.txt", ios::in);
	if (!in.is_open())
    {
		cout << "The file cannot open!" << endl;
		system("pause");
		return 0;
    }

	ReadData(&in, LunwenN);//数据读取

	in.close();//关闭文件

	select(Name_1, Name_2, LunwenN);//筛选出含有指定两个人的所有论文编号
	
	TimeSelect();//选出含有指定两个人一起发表的时间
   
	double similar = SimilarSelect();//指定两个人的研究领域相似度

	cout << Name_1 << "与" << Name_2 << "的研究领域相似度为:" << similar << endl;

	cout << endl;

	system("pause");
	return 0;
}
