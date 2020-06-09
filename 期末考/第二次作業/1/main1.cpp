#include<stdio.h>
#include<stdlib.h>
#include<cstring>
struct Node{
	char v[4];
	struct Node *nextH;
};
Node *newNode(char v[4]){
	Node *p=(Node *)malloc(sizeof(Node));
	strcpy(p->v,v);
	p->nextH=NULL;
	return p;
}
int getH(char c){
	if(c=='H') return 0;
	if(c=='S') return 1;
	if(c=='D') return 2;
	if(c=='C') return 3;
}

Node *head[5];
Node *rear[5];
void inputFile(){
	FILE *infile=fopen("input3.txt","r");
	if(infile!=NULL){
		int n=0;
		char h;
		char v[4];
		fscanf(infile,"%d\n",&n);
		while(n){
			fscanf(infile,"%c %s\n",&h,v);
			int i=getH(h);
			Node *p=newNode(v);
			if(head[i]){//這裡要搞清楚 
				rear[i]->nextH=p;
			}
			else{
				head[i]=p;
			}
			rear[i]=p;
			n--;
		}
	}else{
		printf("無法開啟");
	}
}
int main(){
	inputFile();
	char pair[4]={'H','S','D','C'};//可以這樣做 
	for(int i=0;i<4;++i){
		Node *q=head[i];
		printf("%c ",pair[i]);
		while(q!=NULL){
			printf("%s ",q->v);
			q=q->nextH;
		}
		printf("\n");
	}
	return 0;
}
