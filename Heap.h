#pragma once
#define Minweight -1 //假设最大次数是-1
#define charnumber 127
typedef struct Heap * MinHeap;
typedef struct Node * HT;//**指向Node的指针，struct Node在这里必须和树的结点一摸一样
//否则无法利用最小堆来生成哈夫曼树！**
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
MinHeap Create(int n);//输入容量初始堆
void Insert(MinHeap H, HT a);
HT DeleteMin(MinHeap H);
/*其实前面这些操作（见Heap.c）设计的都麻烦了，问题的关键是创建一个哈夫曼树便于解压，创建一个
哈夫曼编码数组便于压缩，这个Heap可以不必放那么复杂的元素只放权重帮忙排序即可*/
MinHeap Build(MinHeap H,int* alpha);//使用一个给定的数组，来构建最小堆，其中主要操作就是把数组元素转化
//成结构类型struct character,然后使用最小堆插入，Insert函数

//另：需要注意的是，最小堆中以结构体保存字符，不再和最开始统计字频数组一样用下标值就是字符