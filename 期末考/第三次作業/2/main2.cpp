#include<stdio.h>
#include<cstring>
#include<stdlib.h>

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

tree *heap[105];
int n=0;

void inputFile(){
	FILE *infile=fopen("input3.txt","r");
	if(infile!=NULL){
		char line[105];
		char *pch;
		
		int i=1;//要由1開始放!!!這樣比較好做min-heap
		fgets(line,103,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch){
			heap[i++]=newNode(atoi(pch));
			pch=strtok(NULL," ");
		}
		n=i;
		
	}else{
		printf("no such file");
	}
}
void adjust_i(int i){
	if(i*2>=n) return;//這裡邏輯要清楚，表示沒有子節點 
//	printf("i=%d\n",i);

	//照ppt演算法 
	int child=i*2;
	if(i*2+1<n){//這裡邏輯要清楚 ，表示有右子節點 
		if(heap[i*2]->d > heap[i*2+1]->d)//找最小子節點 
			++child;
	}
	
//	printf("p=%d ,c=%d\n",heap[i]->d,heap[child]->d);
	if(heap[i]->d > heap[child]->d){
		//交換 
		int t=heap[i]->d;
		heap[i]->d=heap[child]->d;
		heap[child]->d=t;
//		for(int k=1;k<n;++k)
//			printf("%d ",heap[k]->d);
//		printf("\n");
		adjust_i(child);
	}
	else{
		return;
	}
}
void inOrder(tree* x){
	if(x==NULL) return;
	inOrder(x->left);
	printf("%d ",x->d);
	inOrder(x->right);
}
int main(){
	inputFile();
	int i=n/2;
	for(;i>0;--i){//i要>0 
		adjust_i(i);
	}
	for(int i=1;i<=n/2;++i){//從1開始，建構tree 
		heap[i]->left=heap[i*2];
		heap[i]->right=heap[i*2+1];
	}
	tree *root=heap[1];	
	inOrder(root);
	return 0;
}
