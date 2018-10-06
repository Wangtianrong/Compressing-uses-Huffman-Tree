#include<stdio.h>
#include<stdlib.h>
#include"Heap.h"
#include"HuffmanTree.h"
#define Max 100//文件地址的最大值长度

/*本源文件中只声明和定义与文件读取，压缩，解压等直接相关的函数
与哈夫曼树哈夫曼编码相关的声明见HuffmanTree.h
与构建哈夫曼所需最小堆相关的声明见Heap.h*/
/*整体思路：1.首先读取用户输入的文件名，记录字符出现的频率，区分大小写，也记录符号
2.依据该字符频率数组，借助最小堆，构建哈夫曼树，将时间复杂度从O(N^2)降到O(NlogN)
3.依据该二叉树，结合深度优先遍历和队列，构造出一个哈夫曼编码数组，为方便操作，选用大数组，不用链表了
4.读取该文件，对于对应的每个字符，写入二进制文件compre.bi中
5.读取compre.bi */

void Alpha(int* alpha,char* fname);//读取文件，构建字频数组
void Compress(char** huffcode,char* fname);//把目标文件，按huffcode压缩到D:\compress.bi中去
void Decopress(HT T);//解压D:\compress.bi，写入D:\copy.txt中去！
int countbit = 0;//记录总共的bit数
int main() {
	char fname[Max] = { 0 };//用来保存文件名的字符串
	printf("请输入待压文件绝对路径：\n");
	scanf("%[^\n]", &fname);//仅读取回车号之前的字符！
	int alpha[charnumber+1] = { 0 };//#define charnumber 127
	Alpha(alpha,fname);
	MinHeap H=Create(charnumber);//初始化一个容量为127的最小堆
	Build(H, alpha);//使用alpha中的数据构造最小堆H
	HT T = CreatHuffmanTree(H);//将这个最小堆*转化*成哈夫曼树
	char** huffcode=Code(T);//利用哈夫曼树，构造出哈夫曼数组huffcode，下标为字符对应asc码，内容为哈夫曼编码
	Compress(huffcode, fname);
	Decopress(T);
	return 0;
}
void Alpha(int* alpha, char* fname) {
	char c;//buffle of current letter
	int ret = 0;//用来判断是否读取成功
	FILE* fp = fopen(fname, "r");
	ret = fscanf(fp, "%c", &c);
	while (ret == 1) {//读到最后ret会变成EOF从而退出
		alpha[c]++;//为了完整还原，这里还是保存了所有的alpha，但是构建最小堆的过程中只取频度非零元素即可
		ret = fscanf(fp, "%c", &c);//笔记：fscanf会使文件结构体中指向文件内容的指针下移一个单位
	}
	return;
}
void Compress(char** huffcode, char* fname) {
	unsigned char c = 0;
	int ret = 0;
	int bitnumber = 8;//每次用char型传八个bit进去
	int i = 0;
	unsigned char a = 0;//用来保存编码的,八个字节写一次,不要符号调试起来方便
	FILE* fp = fopen(fname, "r");
	FILE* bip = fopen("D:\compress.bi", "wb");
	ret = fscanf(fp, "%c", &c);
	int k = 0;//用来记录bit位，从零开始，到7为满
	while (ret == 1) {//待压缩文本的字符循环
		i = 0;
		//下一节中，控制循环用，记录已使用的bit位
		while (huffcode[c][i] != 0) {//码位循环，读入c对应的哈夫曼码，写入a中
			for (;k < bitnumber&&huffcode[c][i] != 0;k++,i++) {//当这一个编码没读完，并且还不到八个字节时
				if (huffcode[c][i] == '0')
					a += 0;
				else //huffcode等1时
					a += 1;	
				countbit++;//总字节数加一
				if(k!=7)a=a << 1;//最后一次不位移
			}
			
			if (k != bitnumber) {//因哈夫曼码读完跳出
				/*这里用用feof也行但是要注意feof在fscanf完最后一个字符之后，才会
				指向文件最后的那个EOF字符*/
				ret = fscanf(fp, "%c", &c);//文件的指针碰见回车会移动两个位置。。。。。
				if (ret!=1) {//假如说读到最后了，那么需要向左推移a至目标的八位
					a=a << bitnumber - k;
					fwrite(&a, 1, 1, bip);
					fclose(fp);
					fclose(bip);
					printf("压缩完成，压缩到了D盘上的compress.bi\n");
					return;
				}
				else {//源文件没读到头，去继续字符循环
					if (c != '\n')
						fseek(fp, -2L, SEEK_CUR);//注意要回退一格
					else
						fseek(fp, -3L, SEEK_CUR);//要是读到的是回车fscanf会使文件指针
					//向前多挪动一格，那么就回退两格！
					ret = fscanf(fp, "%c", &c);//回到原来状态
					break;
				}
			}
			else if(huffcode[c][i]!=0) {//如果是满八位退出了,且码还没读完
				fwrite(&a, 1, 1, bip);
				k = 0;//k归零
				a = 0;//a清零
			}
			else {//剩下的情况是满八位码还读完了
				fwrite(&a, 1, 1, bip);
				k = 0;
				a = 0;
				break;//跳出码位循环，去读下一个字符
			}
		}
		ret = fscanf(fp, "%c", &c);
	}
	fclose(fp);
	fclose(bip);
	printf("压缩完成，压缩到了D盘上的compress.bi\n");
	return;
}
void Decopress(HT T) {//解压的时候要处理最后几位可能无效的情况,目前想不到特别好的办法
	//这个bug暂且留着（可能的改进是在判断已经读完最后八个bit的时候，如果读到了标点编码则终止）
	unsigned char a = 0;
	int ret = 0;
	int bitnumber = 8;//一个字节八个bit
	int k = 1;//用来控制读的位数的，从1开始
	HT temp = T;//用来指树节点的临时结点
	FILE* bip = fopen("D:\compress.bi", "r");
	FILE* fp = fopen("D:\copy.txt", "w");
	ret = !feof(bip);//到结尾的话ret==0
	fread(&a, 1, 1, bip);//注意生成哈夫曼码的时候把
	while (ret !=0) {
		for (k=1;k <= bitnumber;k++) {
			if (temp->left==NULL&&temp->right==NULL) {//叶子结点
				fwrite(&temp->c, 1, 1, fp);
				temp = T;
			}
			if ((a >> bitnumber - k) - ((a >> bitnumber - k + 1) << 1) == 1) {//用位运算表示出当前位，如果当前位是1
				temp = temp->right;
			}
			else {//当前是0
				temp = temp->left;
			}
			countbit--;
			if (countbit == 0) {
				fclose(fp);
				fclose(bip);
				printf("解压完成，压缩到了D盘上的copy.txt\n");
				return;
			}
		}
		ret = !feof(bip);//到结尾的话ret==0,这两句千万不能颠倒，否则最后8位无法进入循环
		fread(&a, 1, 1, bip);
	}

}
