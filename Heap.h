#pragma once
#define Minweight -1 //������������-1
#define charnumber 127
typedef struct Heap * MinHeap;
typedef struct Node * HT;//**ָ��Node��ָ�룬struct Node�������������Ľ��һ��һ��
//�����޷�������С�������ɹ���������**
struct Heap {
	struct Node* item;
	int size;
	int capacity;
};
struct Node{
	char c;
	int weight;
	HT left, right;
};
MinHeap Create(int n);//����������ʼ��
void Insert(MinHeap H, HT a);
HT DeleteMin(MinHeap H);
/*��ʵǰ����Щ��������Heap.c����ƵĶ��鷳�ˣ�����Ĺؼ��Ǵ���һ�������������ڽ�ѹ������һ��
�����������������ѹ�������Heap���Բ��ط���ô���ӵ�Ԫ��ֻ��Ȩ�ذ�æ���򼴿�*/
MinHeap Build(MinHeap H,int* alpha);//ʹ��һ�����������飬��������С�ѣ�������Ҫ�������ǰ�����Ԫ��ת��
//�ɽṹ����struct character,Ȼ��ʹ����С�Ѳ��룬Insert����

//����Ҫע����ǣ���С�����Խṹ�屣���ַ������ٺ��ʼͳ����Ƶ����һ�����±�ֵ�����ַ�