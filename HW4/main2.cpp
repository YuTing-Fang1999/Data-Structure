#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<stack>
using namespace std;

int map[105][105];
int V=0;
int mark[105]={0};
stack<int> s;

struct List{
	int d;
	struct List *next;
};

List *list[105]={NULL};

List *newNode(int d){
	List *p=(List *)malloc(sizeof(List));
	p->next=NULL;
	p->d=d;
	return p;
}

void inputFile(){
	FILE *infile=fopen("input2.txt","r");
	if(infile!=NULL){
		char *pch;
		char line[105];
		
		fgets(line,102,infile);
		int i=0;
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
			
		int j=-1;
		pch=strtok(line," ");
		while(pch!=NULL){
			map[i][++j]=atoi(pch);
			pch=strtok(NULL," ");
		};
		V=j+1;//第一行先記有幾個 
		
		while(fgets(line,102,infile)!=NULL){
			++i;
			if(line[strlen(line)-1]=='\n')
				line[strlen(line)-1]='\0';
				
			int j=-1;
			pch=strtok(line," ");
			while(pch!=NULL){
				map[i][++j]=atoi(pch);
				pch=strtok(NULL," ");
			};
		}

	}else{
		printf("無法開啟"); 
	}
	for(int i=0;i<V;++i){
		for(int j=0;j<V;++j){
//			printf("%d ",map[i][j]);
			if(map[i][j]>0){
				map[j][i]=1;//變雙向圖 
			}
		}
//		printf("\n");
	}
}

void createList(){
	for(int i=0;i<V;++i){
		List *p=newNode(i);
		list[i]=p;
		
		for(int j=0;j<V;++j){
			if(map[i][j]!=0 ){
				p->next=newNode(j);
				p=p->next;
			}
		}
	}
// list
//	for(int j=0;j<V;++j){
//		List *p=list[j];
//		while(p!=NULL){
//			printf("%d ",p->d);
//			p=p->next;
//		}
//		printf("\n");	
//	}
}

// 找剩下的NODE 
List *startNode(){
	for(int i=0;i<V;++i){
		if(mark[i]==0){
			return list[i];
		}
	}
	return NULL;
}
void dfs(List *v){
	while(v!=NULL){
		if(mark[v->d]==0){
			mark[v->d]=1;
//			printf("%d ",v->d);
			dfs(list[v->d]);
		}
		v=v->next;
	}
}

int compute(){
	List *x=startNode();
	int n=0;
	while(x!=NULL){
		++n;
		dfs(x);
//		printf("\n");
		x=startNode();
	}
	return n;
}

void outputFile(){
	FILE *outfile=fopen("output2.txt","w");
	int n=compute();
	fprintf(outfile,"%d",n);
	printf("%d",n);
	fclose(outfile);
}
int main() 
{  
	inputFile();
	createList();
//	printf("------------------\n");
	outputFile();
	return 0; 
} 
