#include<stdio.h>
#include<stdlib.h>
#include"Heap.h"
#include"HuffmanTree.h"
//���ַ����������������Ĺ����ǽ���С���е�ɭ���𽥾ۼ��ɵ�����һ�ù��������Ĺ���
HT CreatHuffmanTree(MinHeap H) {
	int i;
	HT T;
	int t = H->size;//������������в��ܷ�size-1!������ѡ����whileѭ������H->size==1��ʱ���˳�
	for (i = 1;i < t;i++) {//**ע��˴���size-1�κϲ�����������delete��ʱ�����
		//������ڿն���ɾ���������
		T = (HT)malloc(sizeof(struct Node));//ÿ�ν���ѭ����Ҫ��Ūһ����㣬��������ƬȨֵ��С��Ҷ�ӵ�
		
		T->left=DeleteMin(H);//**ע����ڴ˴����ƻ�����**
		
		T->right= DeleteMin(H);
		//������Ҷ�����
		T->weight = T->left->weight + T->right->weight;
		T->c = 128;//��128��ʾ�Ȼ���������еķ�Ҷ�ӽ����ַ�
		Insert(H, T);//�������Լ�������Ǵ�ָ��
	}
	T=DeleteMin(H);//��ʱ���ó��������һ��Ԫ�أ���������Ҫ�Ĺ���������
	return T;
}

char**  Code(HT T) {
	char**  huffcode = (char**)malloc(sizeof(char*)*(charnumber+1));
	for (int i = 0;i < charnumber + 1;i++) {
		huffcode[i] = (char*)malloc(sizeof(char)*(charnumber + 1));
		for (int j = 0;j < charnumber + 1;j++) {
			huffcode[i][j] = 0;
		}//��ʼ���ַ���
	}//���ﲻ̫�׶������ǹ������ַ������飬�ַ����������128���ַ�ָ��char*��Ϊ��Ԫ
	 //ͬʱΪ�˴�huffman�룬�����ÿһ��char*��Ԫ�����˿��ܵ����ռ�charnumber+1��char
	char temp[128] = { 0 };
	int i = 0;//i������¼temp��ǰ���±꣬������±괫ָ����������ʹ����ȫ�ֱ���
	PreTravel(T, &huffcode,temp,i);
	return huffcode;
}
	

void PreTravel(HT T, char*** huffcode,char* temp,int i)  {
	if (T->left == NULL&&T->right == NULL) {
		for(int j=0;j<i;j++){
			(*huffcode)[T->c][j] = temp[j];
		}//i�ǵ�ǰӦ�ò������ַ��±꣬����Ҷ�ӽ�㣬���
		//֮ǰ�������ַ�������ȥ�����ü�\0����ΪhuffcodeԪ��Ĭ�ϵ��ַ�����ʼ��ʱȫΪ��
		return;
	}
	if (T->left != NULL) {
		temp[i] = '0';
		i++;
		PreTravel(T->left, huffcode, temp,i);
		i--;//Ҫȥ���ұߵ��ˣ����ݣ��ұ߲�������NULL��
	}
	if (T->right != NULL) {
		temp[i] = '1';//�����ұ������ַ������ϡ�1��
		i++;
		PreTravel(T->right, huffcode, temp,i);
	}
	return;
}
