#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;

typedef struct node *pointer;
struct node{
	char data[3];//要用字串!因為有10 
	pointer next;
};
int pos(char c){
	if(c=='H'){
		return 0;
	}
	if(c=='S'){
		return 1;
	}
	if(c=='D'){
		return 2;
	}
	if(c=='C'){
		return 3;
	}
	return NULL;
}
node *newNode(){
	node *p = (node *)malloc(sizeof(node));
	return p;
}

pointer head[4];
pointer rear[4];
//初始化 
void init(){
	head[0]=newNode();strcpy(head[0]->data,"H");
	head[1]=newNode();strcpy(head[1]->data,"S");
	head[2]=newNode();strcpy(head[2]->data,"D");
	head[3]=newNode();strcpy(head[3]->data,"C");
	for(int i=0;i<4;++i)
		head[i]->next=NULL;
	rear[0]=head[0];
	rear[1]=head[1];
	rear[2]=head[2];
	rear[3]=head[3];
}

void print_list(int i){
	node *q=head[i];
	q=head[i];
	cout<<q->data<<" ";
	q=q->next;
	while(q!=NULL){
		cout<<q->data<<" ";
		q=q->next;
	}
	cout<<endl;
}

void take(FILE *infile){
	char c;
	while((c=getc(infile))!=EOF){//take;
		if(c=='\n'){
//			printf("break");
			break;
		}
		int i=pos(c);//c=花色 
//		printf("原本的 list\n");
//		print_list(i);

		//創一個新點 
		node *p = newNode();
		getc(infile);//讀取空格 
		fscanf(infile,"%s",p->data);//讀取下一個Num 
		getc(infile);
		p->next=NULL;
		
		//加入 
		rear[i]->next = p;
		rear[i]=p;
//		printf("加入%c %s\n",c,p->data);
//		print_list(i);
	}
//	printf("\n");
}

void drop(FILE *infile){
	char c;
	while((c=getc(infile))!=EOF){//take;
		if(c=='\n'){
//			printf("break\n");
			break;
		}
		getc(infile);
		int i=pos(c);
		char g[3];
		fscanf(infile,"%s",g);//讀取下一個Num
		getc(infile);
//		printf("原本的 list\n");
//		print_list(i);
//		printf("刪掉 %c %s\n",c,g);
		node *q=head[i];
		while(q->next!=NULL){
			node *next=q->next;
			if(strcmp(next->data,g)==0){//刪掉下一個node 
				q->next=next->next;
				free(next);
				break;
			}
			q=q->next;
		}
		if(q->next==NULL)//重要!!因為rear會改 
			rear[i]=q;
//		print_list(i);
	}
}

void inputFile(){
	FILE *infile=fopen("input2.txt","r");
	if(infile!=NULL){
		take(infile);
		drop(infile);
		take(infile);
		
		fclose(infile);
	}else{
		printf("開啟檔案失敗");
	}
	
}
void outputFile(){
	FILE *outfile = fopen("output2.txt","w");
	for(int i=0;i<4;++i){
		node *q=head[i];
		q=head[i];
		fprintf(outfile,"%s ",q->data); 
		q=q->next;
		while(q!=NULL){
			fprintf(outfile,"%s ",q->data); 
			q=q->next;
		}
		fprintf(outfile,"\n");
	}
	fclose(outfile);
}
void print_to_cmd(){
	for(int i=0;i<4;++i){
		print_list(i);
	}
}
int main(){
	init();
	inputFile();
	outputFile();
	print_to_cmd();
	return 0;
}
