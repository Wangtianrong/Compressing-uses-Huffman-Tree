#include<stdio.h>
#include<stdlib.h>
#include"Heap.h"
#include"HuffmanTree.h"
#define Max 100//�ļ���ַ�����ֵ����

/*��Դ�ļ���ֻ�����Ͷ������ļ���ȡ��ѹ������ѹ��ֱ����صĺ���
���������������������ص�������HuffmanTree.h
�빹��������������С����ص�������Heap.h*/
/*����˼·��1.���ȶ�ȡ�û�������ļ�������¼�ַ����ֵ�Ƶ�ʣ����ִ�Сд��Ҳ��¼����
2.���ݸ��ַ�Ƶ�����飬������С�ѣ�����������������ʱ�临�Ӷȴ�O(N^2)����O(NlogN)
3.���ݸö����������������ȱ����Ͷ��У������һ���������������飬Ϊ���������ѡ�ô����飬����������
4.��ȡ���ļ������ڶ�Ӧ��ÿ���ַ���д��������ļ�compre.bi��
5.��ȡcompre.bi */

void Alpha(int* alpha,char* fname);//��ȡ�ļ���������Ƶ����
void Compress(char** huffcode,char* fname);//��Ŀ���ļ�����huffcodeѹ����D:\compress.bi��ȥ
void Decopress(HT T);//��ѹD:\compress.bi��д��D:\copy.txt��ȥ��
int countbit = 0;//��¼�ܹ���bit��
int main() {
	char fname[Max] = { 0 };//���������ļ������ַ���
	printf("�������ѹ�ļ�����·����\n");
	scanf("%[^\n]", &fname);//����ȡ�س���֮ǰ���ַ���
	int alpha[charnumber+1] = { 0 };//#define charnumber 127
	Alpha(alpha,fname);
	MinHeap H=Create(charnumber);//��ʼ��һ������Ϊ127����С��
	Build(H, alpha);//ʹ��alpha�е����ݹ�����С��H
	HT T = CreatHuffmanTree(H);//�������С��*ת��*�ɹ�������
	char** huffcode=Code(T);//���ù������������������������huffcode���±�Ϊ�ַ���Ӧasc�룬����Ϊ����������
	Compress(huffcode, fname);
	Decopress(T);
	return 0;
}
void Alpha(int* alpha, char* fname) {
	char c;//buffle of current letter
	int ret = 0;//�����ж��Ƿ��ȡ�ɹ�
	FILE* fp = fopen(fname, "r");
	ret = fscanf(fp, "%c", &c);
	while (ret == 1) {//�������ret����EOF�Ӷ��˳�
		alpha[c]++;//Ϊ��������ԭ�����ﻹ�Ǳ��������е�alpha�����ǹ�����С�ѵĹ�����ֻȡƵ�ȷ���Ԫ�ؼ���
		ret = fscanf(fp, "%c", &c);//�ʼǣ�fscanf��ʹ�ļ��ṹ����ָ���ļ����ݵ�ָ������һ����λ
	}
	return;
}
void Compress(char** huffcode, char* fname) {
	unsigned char c = 0;
	int ret = 0;
	int bitnumber = 8;//ÿ����char�ʹ��˸�bit��ȥ
	int i = 0;
	unsigned char a = 0;//������������,�˸��ֽ�дһ��,��Ҫ���ŵ�����������
	FILE* fp = fopen(fname, "r");
	FILE* bip = fopen("D:\compress.bi", "wb");
	ret = fscanf(fp, "%c", &c);
	int k = 0;//������¼bitλ�����㿪ʼ����7Ϊ��
	while (ret == 1) {//��ѹ���ı����ַ�ѭ��
		i = 0;
		//��һ���У�����ѭ���ã���¼��ʹ�õ�bitλ
		while (huffcode[c][i] != 0) {//��λѭ��������c��Ӧ�Ĺ������룬д��a��
			for (;k < bitnumber&&huffcode[c][i] != 0;k++,i++) {//����һ������û���꣬���һ������˸��ֽ�ʱ
				if (huffcode[c][i] == '0')
					a += 0;
				else //huffcode��1ʱ
					a += 1;	
				countbit++;//���ֽ�����һ
				if(k!=7)a=a << 1;//���һ�β�λ��
			}
			
			if (k != bitnumber) {//����������������
				/*��������feofҲ�е���Ҫע��feof��fscanf�����һ���ַ�֮�󣬲Ż�
				ָ���ļ������Ǹ�EOF�ַ�*/
				ret = fscanf(fp, "%c", &c);//�ļ���ָ�������س����ƶ�����λ�á���������
				if (ret!=1) {//����˵��������ˣ���ô��Ҫ��������a��Ŀ��İ�λ
					a=a << bitnumber - k;
					fwrite(&a, 1, 1, bip);
					fclose(fp);
					fclose(bip);
					printf("ѹ����ɣ�ѹ������D���ϵ�compress.bi\n");
					return;
				}
				else {//Դ�ļ�û����ͷ��ȥ�����ַ�ѭ��
					if (c != '\n')
						fseek(fp, -2L, SEEK_CUR);//ע��Ҫ����һ��
					else
						fseek(fp, -3L, SEEK_CUR);//Ҫ�Ƕ������ǻس�fscanf��ʹ�ļ�ָ��
					//��ǰ��Ų��һ����ô�ͻ�������
					ret = fscanf(fp, "%c", &c);//�ص�ԭ��״̬
					break;
				}
			}
			else if(huffcode[c][i]!=0) {//���������λ�˳���,���뻹û����
				fwrite(&a, 1, 1, bip);
				k = 0;//k����
				a = 0;//a����
			}
			else {//ʣ�µ����������λ�뻹������
				fwrite(&a, 1, 1, bip);
				k = 0;
				a = 0;
				break;//������λѭ����ȥ����һ���ַ�
			}
		}
		ret = fscanf(fp, "%c", &c);
	}
	fclose(fp);
	fclose(bip);
	printf("ѹ����ɣ�ѹ������D���ϵ�compress.bi\n");
	return;
}
void Decopress(HT T) {//��ѹ��ʱ��Ҫ�������λ������Ч�����,Ŀǰ�벻���ر�õİ취
	//���bug�������ţ����ܵĸĽ������ж��Ѿ��������˸�bit��ʱ����������˱���������ֹ��
	unsigned char a = 0;
	int ret = 0;
	int bitnumber = 8;//һ���ֽڰ˸�bit
	int k = 1;//�������ƶ���λ���ģ���1��ʼ
	HT temp = T;//����ָ���ڵ����ʱ���
	FILE* bip = fopen("D:\compress.bi", "r");
	FILE* fp = fopen("D:\copy.txt", "w");
	ret = !feof(bip);//����β�Ļ�ret==0
	fread(&a, 1, 1, bip);//ע�����ɹ��������ʱ���
	while (ret !=0) {
		for (k=1;k <= bitnumber;k++) {
			if (temp->left==NULL&&temp->right==NULL) {//Ҷ�ӽ��
				fwrite(&temp->c, 1, 1, fp);
				temp = T;
			}
			if ((a >> bitnumber - k) - ((a >> bitnumber - k + 1) << 1) == 1) {//��λ�����ʾ����ǰλ�������ǰλ��1
				temp = temp->right;
			}
			else {//��ǰ��0
				temp = temp->left;
			}
			countbit--;
			if (countbit == 0) {
				fclose(fp);
				fclose(bip);
				printf("��ѹ��ɣ�ѹ������D���ϵ�copy.txt\n");
				return;
			}
		}
		ret = !feof(bip);//����β�Ļ�ret==0,������ǧ���ܵߵ����������8λ�޷�����ѭ��
		fread(&a, 1, 1, bip);
	}

}
