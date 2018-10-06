#pragma once
#include"Heap.h"

HT CreatHuffmanTree(MinHeap H);
char** Code(HT T);//给出哈夫曼树，给一个字符串数组数组下标是相应asc码，
//编码不能以int形式储存，因为这样的话无法分清楚编码001和01
//编码必须用字符串形式存储
void PreTravel(HT T, char*** a, char* temp,int i);//先序遍历树,同时写入code数组相应的编码
