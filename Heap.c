#include<stdio.h>
#include<stdlib.h>
#include"Heap.h"
MinHeap Create(int n) {
	MinHeap H = (MinHeap)malloc(sizeof(struct Heap));
	H->capacity = n;
	H->size = 0;
	H->item = (HT)malloc(sizeof(struct Node)*(n+1));
	for (int i = 0;i < charnumber;i++) {
		H->item[i].c = 0;
		H->item[i].weight = 0;
	}
	H->item[0].weight = Minweight;//-1���ڱ�
	return H;
}
void Insert(MinHeap H, HT a) {//���ﴫָ����Ϊ�˼�С�ռ����ģ���Ȼ���岻��̫��
	int i;
	if (H->capacity == H->size) {
		printf("������");
		return;
	}
	i = ++H->size;//���Բ���Ļ���ô�ѵĴ�С��һ��ͬʱ����i��֤��0��λ������ֵ
	for (;H->item[i / 2].weight > a->weight;i /= 2)//ֻҪ������aȨ��С����ôĸ���Ų�����ڳ�λ��
		H->item[i] = H->item[i / 2];
	H->item[i] = *a;
}
HT DeleteMin(MinHeap H) {
	int parent, child;
	struct Node temp;
	HT Min = malloc(sizeof(struct Node));
	if (H->size == 0) {
		printf("��С��Ϊ��");
		return NULL;
	}
	*Min = H->item[1];//ȡ����Сֵ
	temp = H->item[H->size--];//ȡ���һ��Ԫ�أ��±�size������С��
	for (parent = 1;parent * 2 <= H->size;parent = child) {
		child = parent * 2;//�������������Ȼ�Ƚ���������˭��С
		if ((child != H->size) &&
			(H->item[child].weight > H->item[child + 1].weight))
			child++;//˵���Ҷ��Ӹ�С�������ü�
		if (temp.weight <= H->item[child].weight) break;//�����ʱ���Ȩ�رȽ�С�Ļ������ҵ��˸÷ŵ�λ�ã�parent��
		else
			H->item[parent] = H->item[child];//�ƶ���С���ӵ���ĸ��㣬������һ��
	}
	H->item[parent] = temp;//��Ŀ���������ʵ�λ����
	return Min;//����ȡ������һ��Ȩ����С�Ľ�㣬�ṹָ�����ͷ���
}
MinHeap Build(MinHeap H, int* alpha) {
	HT a=(HT)malloc(sizeof(struct Node));
	for (int i = 1;i < charnumber;i++) {
		if (alpha[i] > 0) {//Ϊ�˽�ʡ�ռ��ʱ�䣬��С����ֻ��Ƶ�Ȳ�Ϊ����ַ�
			a->weight = alpha[i];
			a->c = i;//װ����ʱ�ṹstruct Node a
			a->left = a->right = NULL;//���������ò������Һ���
			Insert(H, a);
		}
	}
	return H;//���ع�����˵���С��
}