#include<stdio.h>
#include<cstring>
#include<stdlib.h>
int post[105];
int in[105];
int n=0;
struct tree{
	int d;
	tree *right;
	tree *left;
};
tree *newNode(int d){
	tree *p=(tree *)malloc(sizeof(tree));
	p->d=d;
	p->left=NULL;
	p->right=NULL;
	return p;
}
void inputFile(){
	FILE *infile=fopen("input3.txt","r");
	if(infile!=NULL){
		char line[105];
		char *pch;
		
		int i=0;
		fgets(line,103,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch){
			post[i++]=atoi(pch);
			pch=strtok(NULL," ");
		}
		
		i=0;
		fgets(line,103,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch){
			in[i++]=atoi(pch);
			pch=strtok(NULL," ");
		}
		n=i;
	}else{
		printf("no such file");
	}
}

int searchIn(int s,int e,int value){
	for(int i=s;i<=e;++i){
		if(in[i]==value) return i;
	}
	printf("Index not found\n");
}
tree *buildtree(int s,int e,int *pIndex){
	if(s>e) return NULL;/*1*/
	
	tree *node=newNode(post[(*pIndex)--]);//要記得加括號 /*2*/
	
	if(s==e) return node;/*3*/
	
	int index=searchIn(s,e,node->d);
	
	node->right=buildtree(index+1,e,pIndex);
	node->left=buildtree(s,index-1,pIndex);
	
	return node;
}
FILE *outfile=fopen("output1.txt","w");
void preOrder(tree* x){
	if(x==NULL) return;
	printf("%d ",x->d);
	fprintf(outfile,"%d ",x->d);
	preOrder(x->left);
	preOrder(x->right);
}

int main(){
	inputFile();
	int pIndex=n-1;
	tree *root=buildtree(0,n-1,&pIndex);
	preOrder(root);
	return 0;
}
