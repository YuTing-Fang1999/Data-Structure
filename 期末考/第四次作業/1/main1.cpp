#include<cstring>
#include<stdlib.h>
#include<stdio.h>
//�n��list�h�]dfs 
int map[105][105];
int V=0;
int visited[105]={0};
struct Node{
	int d;
	Node *next;
};
Node *newNode(int d){
	Node *p=(Node *)malloc(sizeof(Node));
	p->d=d;
	p->next=NULL;
	return p;
}
Node *list[105];
void inputFile(){
	FILE *infile=fopen("input3.txt","r");
	if(infile!=NULL){
		char *pch;
		char line[105];
		while(fgets(line,102,infile)!=NULL){
			if(line[strlen(line)-1]=='\n')
				line[strlen(line)-1]='\0';
			int i=-1;
			pch=strtok(line," ");
			while(pch!=NULL){
			/*����b�o�������V�ϡA�]���|�Q���᪺0�л\ */
				map[V][++i]=atoi(pch);
				pch=strtok(NULL," ");
			}
			++V;
		}
		for(int i=0;i<V;++i){
			for(int j=0;j<V;++j){
				if(map[i][j]>0){
					map[j][i]=1;//�����V�� 
				}
//				printf("%d ",map[i][j]);
			}
//			printf("\n");
		}
	}else{
		printf("�L�k�}��"); 
	}
}
createList(){
	for(int i=0;i<V;++i){
		list[i]=newNode(i);//�Ĥ@�ө�ۤv���Ʀr 
		Node *p=list[i];
		for(int j=0;j<V;++j){
			if(map[i][j]>0){
				p->next=newNode(j);
				p=p->next;
			}
		}
	}
}
void dfs(int i){//dfs���k�ҫe�n�I 
	Node *x=list[i];
	while(x!=NULL){
		if(visited[x->d]==0){
			visited[x->d]=1;
			dfs(x->d);
		}
		x=x->next; 
	}
}
int compute(){
	int n=0;
	for(int i=0;i<V;++i){
		if(visited[i]==0){
			++n;
			dfs(i);
		}
	}
	return n;
}
int main(){
	inputFile();
	createList();
	printf("%d \n",compute());
//	for(int i=0;i<V;++i){
//		Node *x=list[i];
//		while(x!=NULL){
//			printf("%d ",x->d);
//			x=x->next; 
//		}
//		printf("\n");
//	}
	
	return 0;
}
