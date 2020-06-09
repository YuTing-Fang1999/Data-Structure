#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;

typedef struct node *pointer;
struct node{
	char data[3];//�n�Φr��!�]����10 
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
//��l�� 
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
		int i=pos(c);//c=��� 
//		printf("�쥻�� list\n");
//		print_list(i);

		//�Ф@�ӷs�I 
		node *p = newNode();
		getc(infile);//Ū���Ů� 
		fscanf(infile,"%s",p->data);//Ū���U�@��Num 
		getc(infile);
		p->next=NULL;
		
		//�[�J 
		rear[i]->next = p;
		rear[i]=p;
//		printf("�[�J%c %s\n",c,p->data);
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
		fscanf(infile,"%s",g);//Ū���U�@��Num
		getc(infile);
//		printf("�쥻�� list\n");
//		print_list(i);
//		printf("�R�� %c %s\n",c,g);
		node *q=head[i];
		while(q->next!=NULL){
			node *next=q->next;
			if(strcmp(next->data,g)==0){//�R���U�@��node 
				q->next=next->next;
				free(next);
				break;
			}
			q=q->next;
		}
		if(q->next==NULL)//���n!!�]��rear�|�� 
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
		printf("�}���ɮץ���");
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
