#pragma once
#include"Heap.h"

HT CreatHuffmanTree(MinHeap H);
char** Code(HT T);//����������������һ���ַ������������±�����Ӧasc�룬
//���벻����int��ʽ���棬��Ϊ�����Ļ��޷����������001��01
//����������ַ�����ʽ�洢
void PreTravel(HT T, char*** a, char* temp,int i);//���������,ͬʱд��code������Ӧ�ı���
