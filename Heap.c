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
	H->item[0].weight = Minweight;//-1，哨兵
	return H;
}
void Insert(MinHeap H, HT a) {//这里传指针是为了减小空间消耗，虽然意义不是太大
	int i;
	if (H->capacity == H->size) {
		printf("堆已满");
		return;
	}
	i = ++H->size;//可以插入的话那么堆的大小加一，同时赋给i保证了0号位不存数值
	for (;H->item[i / 2].weight > a->weight;i /= 2)//只要这个结点a权重小，那么母结点挪下来腾出位置
		H->item[i] = H->item[i / 2];
	H->item[i] = *a;
}
HT DeleteMin(MinHeap H) {
	int parent, child;
	struct Node temp;
	HT Min = malloc(sizeof(struct Node));
	if (H->size == 0) {
		printf("最小堆为空");
		return NULL;
	}
	*Min = H->item[1];//取出最小值
	temp = H->item[H->size--];//取最后一个元素（下标size）并减小堆
	for (parent = 1;parent * 2 <= H->size;parent = child) {
		child = parent * 2;//这是左子树，等会比较左右子树谁更小
		if ((child != H->size) &&
			(H->item[child].weight > H->item[child + 1].weight))
			child++;//说明右儿子更小，否则不用加
		if (temp.weight <= H->item[child].weight) break;//如果临时结点权重比较小的话，便找到了该放的位置（parent）
		else
			H->item[parent] = H->item[child];//移动较小孩子到父母结点，进入下一层
	}
	H->item[parent] = temp;//把目标结点放入合适的位置上
	return Min;//返回取出的那一个权重最小的结点，结构指针类型返回
}
MinHeap Build(MinHeap H, int* alpha) {
	HT a=(HT)malloc(sizeof(struct Node));
	for (int i = 1;i < charnumber;i++) {
		if (alpha[i] > 0) {//为了节省空间和时间，最小堆中只放频度不为零的字符
			a->weight = alpha[i];
			a->c = i;//装填临时结构struct Node a
			a->left = a->right = NULL;//堆中暂且用不到左右孩子
			Insert(H, a);
		}
	}
	return H;//返回构造好了的最小堆
}