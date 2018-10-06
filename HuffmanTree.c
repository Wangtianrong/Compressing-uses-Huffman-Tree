#include<stdio.h>
#include<stdlib.h>
#include"Heap.h"
#include"HuffmanTree.h"
//这种方法建立哈夫曼树的过程是将最小堆中的森林逐渐聚集成单独的一棵哈夫曼树的过程
HT CreatHuffmanTree(MinHeap H) {
	int i;
	HT T;
	int t = H->size;//下面控制条件中不能放size-1!但可以选择做while循环，当H->size==1的时候退出
	for (i = 1;i < t;i++) {//**注意此处做size-1次合并，否则下面delete的时候可能
		//会出现在空堆中删除的情况！
		T = (HT)malloc(sizeof(struct Node));//每次进入循环都要新弄一个结点，用来挂两片权值最小的叶子的
		
		T->left=DeleteMin(H);//**注意堆在此处被破坏掉了**
		
		T->right= DeleteMin(H);
		//挂两侧叶子完成
		T->weight = T->left->weight + T->right->weight;
		T->c = 128;//用128表示等会哈夫曼树中的非叶子结点的字符
		Insert(H, T);//别忘了自己定义的是传指针
	}
	T=DeleteMin(H);//这时候拿出堆中最后一个元素，已做成想要的哈夫曼树了
	return T;
}

char**  Code(HT T) {
	char**  huffcode = (char**)malloc(sizeof(char*)*(charnumber+1));
	for (int i = 0;i < charnumber + 1;i++) {
		huffcode[i] = (char*)malloc(sizeof(char)*(charnumber + 1));
		for (int j = 0;j < charnumber + 1;j++) {
			huffcode[i][j] = 0;
		}//初始化字符串
	}//这里不太易读，就是构建了字符串数组，字符串数组包含128个字符指针char*作为单元
	 //同时为了存huffman码，数组的每一个char*单元都开了可能的最大空间charnumber+1个char
	char temp[128] = { 0 };
	int i = 0;//i用来记录temp当前的下标，数组和下标传指针这样避免使用了全局变量
	PreTravel(T, &huffcode,temp,i);
	return huffcode;
}
	

void PreTravel(HT T, char*** huffcode,char* temp,int i)  {
	if (T->left == NULL&&T->right == NULL) {
		for(int j=0;j<i;j++){
			(*huffcode)[T->c][j] = temp[j];
		}//i是当前应该操作的字符下标，若是叶子结点，则把
		//之前的所有字符都赋上去，不用加\0，因为huffcode元素默认的字符串初始化时全为零
		return;
	}
	if (T->left != NULL) {
		temp[i] = '0';
		i++;
		PreTravel(T->left, huffcode, temp,i);
		i--;//要去赋右边的了，回溯！右边不可能是NULL的
	}
	if (T->right != NULL) {
		temp[i] = '1';//树向右边走了字符串赋上‘1’
		i++;
		PreTravel(T->right, huffcode, temp,i);
	}
	return;
}
