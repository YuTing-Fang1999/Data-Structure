#include<stdio.h>
#include<stdlib.h>
#include<cstring>
//�i�H�ϥΰ}�C�h���A���²��A�Ҹիe�A�g�@���a 
enum who {A, B};//�n�O�o���� 
struct Node{
	char v[4];
	struct Node *nextH;
	who w;
};
Node *head[5];
int change[5];//�n�洫���P�� 
int getV(char v[4]){
	if(strcmp(v,"A")==0) return 1;//���n����cpy!!! 
	if(strcmp(v,"2")==0) return 2;
	if(strcmp(v,"3")==0) return 3;
	if(strcmp(v,"4")==0) return 4;
	if(strcmp(v,"5")==0) return 5;
	if(strcmp(v,"6")==0) return 6;
	if(strcmp(v,"7")==0) return 7;
	if(strcmp(v,"8")==0) return 8;
	if(strcmp(v,"9")==0) return 9;
	if(strcmp(v,"10")==0) return 10;
	if(strcmp(v,"J")==0) return 11;
	if(strcmp(v,"Q")==0) return 12;
	if(strcmp(v,"K")==0) return 13;
	return 0;
}
Node *newNdoe(char v[4]){
	Node *p=(Node *)malloc(sizeof(Node));
	strcpy(p->v,v);
	p->nextH=NULL;
	return p;
}
//�Ѥp�ƨ�j 
void insert(Node *p,int i){
	Node *q=head[i];
	int k=getV(p->v);
//	printf("v=%s, k=%d \n",p->v,k);
	if(getV(q->v) > k){//��head�٭n�p 
		head[i]=p;//����e�� 
		p->nextH=q;
		//q->nextH���n�]��NULL!!! 
		return;
	}else{
		Node *h=head[i];
		while(q->nextH!=NULL){//��e�@��Node
			if(getV(q->nextH->v) > k) break;//�`�N�n�ݤU�@�Ӫ�V!!! 
			q=q->nextH;
		}
//		printf("last=%s \n",q->v);
		p->nextH=q->nextH;//����᭱ 
		q->nextH=p;
	}
}
void input(who w,FILE *infile){
	char line[105];
	char *pch;
	int i=0;
	while(i<4){
		fgets(line,102,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		pch=strtok(NULL," ");//�h����� 
		while(pch){
			Node *p=newNdoe(pch);
			p->w=w;
			if(head[i]){
				insert(p,i);//���ݭn�Ѥp�ƨ�j�A�]�@��rear���J�N�� 
			}else{
				head[i]=p;
			}
			pch=strtok(NULL," ");
		}
		++i;
	}
}
void inputFile(){
	FILE *infile=fopen("input1.txt","r");
	if(infile!=NULL){
		input(A,infile);
		input(B,infile);
	}else{
		printf("no such file");
	}
}
bool isTH(Node *h,int k){//���ᶶ�B��schange 
	int i=0;
	int an=0,bn=0;
	while(h){
		if(strcmp(h->v,"10")==0 || strcmp(h->v,"J")==0 || strcmp(h->v,"Q")==0 ||
		strcmp(h->v,"K")==0 || strcmp(h->v,"A")==0){
			++i;
			if(h->w==A) ++an;
			if(h->w==B) ++bn;
		}
		h=h->nextH;
	}
	//��X�n�洫���P�� 
	if(an>bn) change[k]=bn;
	else change[k]=an;
	if(i==5) return true;
	else return false;
}
int ch1(){
	for(int i=0;i<4;++i){
		if(change[i]==1){
			change[i]=0;
			return 1;
		}
	}
}
int ch2(){
	for(int i=0;i<4;++i){
		if(change[i]==2){
			change[i]=0;
			return 2;
		}
	}
}
int main(){
	inputFile();
	int n=0;
	for(int i=0;i<4;++i){
		Node *p=head[i];
		//�p�G���ݭn�洫�N�����[ 
		if(isTH(p,i) && change[i]==0) ++n;
//		printf("chamge=%d\n",change[i]);
	}
	int k=3;//�洫�W��
	//����洫�@�i�� 
	while(ch1() && k){
		++n;
		k--;
	}
	//�A��洫��i�� 
	while(ch2() && k){
		++n;
		k-=2;
	}
	printf("%d",n);
	return 0;
}
