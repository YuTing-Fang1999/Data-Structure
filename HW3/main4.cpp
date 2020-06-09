#include<stdio.h>
#include<stdlib.h>
#include<cstring>

struct tree{
	int data;
	tree *left, *right;
};
tree *heap[120];//使用min_heap去取出與插入資料 
int n=0;//總節點數 

tree *newNode(int data){
	tree *p=(tree *)malloc(sizeof(tree));
	p->left=p->right=NULL;
	p->data=data;
	return p;
}

void push(tree *x,int *n){
	int i=++(*n);//新插入的節點的index 
	
	while(i!=1 && x->data<heap[i/2]->data){//如果data比父節點小的話 
		heap[i]=heap[i/2];//父節點換到子(data)節點 
		i=i/2;
	}
	heap[i]=x;//放入data 
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
	FILE *infile=fopen("input4.txt","r");
	if(infile!=NULL){
		char line[115];
		char *pch;
		fgets(line,110,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch!=NULL){
			tree *x=newNode(atoi(pch));
			push(x,&n);
			pch=strtok(NULL," ");
		}
	}
	else{
		printf("無法開啟");
	}
	fclose(infile);
}

tree *huffman(int n){
	while(n){
		tree *a=pop(&n);
		tree *b=pop(&n);
		tree *root=newNode(a->data+b->data);
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
	int t=n;
	tree *root=huffman(t);
	inOrder(root);
	outputFile(root);
	return 0;
}
