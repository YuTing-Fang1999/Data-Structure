#include<stdio.h>
#include<stdlib.h>
#include<cstring>
//用霍夫曼做第五題，失敗 

using namespace std;

struct tree{
	int data;
	tree *left, *right;
	bool isLeaf=false;
};


tree *newNode(int data){
	tree *p=(tree *)malloc(sizeof(tree));
	p->left=p->right=NULL;
	p->data=data;
	return p;
}

tree *heap[120];//使用min_heap去取出與插入資料 
int n=0;//總節點數 
tree *nL[105];
int nl=-1;//非葉節點數 
tree *queqe[105]={NULL};
int qHead=0,qTail=0;

void push(tree *x,int *n){
	int i=++(*n);//新插入的節點的index 
	
	while(i!=1 && x->data<heap[i/2]->data){//如果data比父節點大的話 
		heap[i]=heap[i/2];//父節點換到子節點 
		i=i/2;
	}
	heap[i]=x;
} 

tree *pop(int *n){
	tree *item=heap[1];//取出頭點 
	tree *temp=heap[(*n)--];//移動最後一個點 
	int parent=1;
	int child=2;
	while(child<=*n){
		if(child<*n && heap[child+1]->data<heap[child]->data){
			child++;//找出最小子節點 
		}
		if(temp->data <= heap[child]->data) break;//直接移到parent
		heap[parent]=heap[child];//子節點移到父節點
		parent=child;//移到下一層(繼續處理) 
		child=child*2; 
	}
	heap[parent]=temp;
	return item;
}

void inputFile(){
	FILE *infile=fopen("input5.txt","r");
	if(infile!=NULL){
		char line[115];
		char *pch;
		//nL
		fgets(line,110,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch!=NULL){
			tree *x=newNode(atoi(pch));
			x->isLeaf=false;
			nL[++nl]=x;
			pch=strtok(NULL," ");
		}
		//L
		fgets(line,110,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch!=NULL){
			tree *x=newNode(atoi(pch));
			x->isLeaf=true;
			push(x,&n);
			pch=strtok(NULL," ");
		}
	}
	else{
		printf("無法開啟");
	}
	fclose(infile);
	for(int i=0;i<=nl;++i){
		for(int j=i+1;j<=nl;++j){
			if(nL[i]->data<nL[j]->data){
				tree *temp=nL[i];
				nL[i]=nL[j];
				nL[j]=temp;
			}
		}
	}
//	for(int j=0;j<=nl;++j){
//			printf("%d ",nL[j]->data);
//		}
}

tree *huffman(int n){
	while(n){
		tree *a=pop(&n);
		tree *b=pop(&n);
		tree *root=newNode(a->data+b->data);
		root->isLeaf=false;
		root->left=a;
		root->right=b;
//		printf("a=%d,b=%d,r=%d\n",a->data,b->data,root->data);
		push(root,&n);
		if(n==1){
			return root;
			break;
		}
	}
}
void inOrder(tree *x){
	if(x==NULL) return;
	inOrder(x->left);
	printf("%d ",x->data);
	inOrder(x->right);
}

void bfs(tree *x){
	queqe[qTail++]=x;
	int i=0;
	while(qHead<qTail){
		x=queqe[qHead++];//要先取出 
		if(!x->isLeaf){
//			x->data=nL[i++]->data;
		}
//		printf("qH=%d,qT=%d\n",qHead,qTail);
		if(x->left!=NULL){
			queqe[qTail++]=x->left;
		}
		if(x->right!=NULL){
			queqe[qTail++]=x->right;
		}
		printf("%d ",x->data);
	}
	
}
void compute(tree *x,int w,int *s){
	if(x->left==NULL && x->right==NULL){
		*s+=x->data*w; 
//		printf("%d\n",*s);
		return;
	}
	compute(x->left,w+1,s);
	compute(x->right,w+1,s);
}
void outputFile(tree *x){
	FILE *outfile=fopen("output4.txt","w");
	int s=0;
	compute(x,1,&s);
	printf("%d",s);
	fprintf(outfile,"%d",s);
	fclose(outfile);
}
int main(){
	inputFile();
	for(int i=0;i<=nl;++i){
		
	}
	int t=n;
	tree *root=huffman(t);
//	inOrder(root);
	printf("\n");
	bfs(root);
	outputFile(root);
	return 0;
}
