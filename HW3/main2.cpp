#include<stdio.h>
#include<cstring>
#include<stdlib.h>
int pre1[120];
int in1[120];
int post2[120];
int in2[120];
int n1;
int n2;

struct tree{
	int data;
	struct tree *left;
	struct tree *right;
};
void inputFile(){
	FILE *infile=fopen("input2.txt","r");
	if(infile!=NULL){
		char line[120];
		char *pch;
		//pre1
		int i=0;
		fgets(line,110,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch!=NULL){
			pre1[++i]=atoi(pch);
			pch=strtok(NULL," ");
		}
		n1=i;
		//in1
		i=0;
		fgets(line,110,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch!=NULL){
			in1[++i]=atoi(pch);
			pch=strtok(NULL," ");
		}
		//post2
		i=0;
		fgets(line,110,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch!=NULL){
			post2[++i]=atoi(pch);
			pch=strtok(NULL," ");
		}
		n2=i;
		//in2
		i=0;
		fgets(line,110,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch!=NULL){
			in2[++i]=atoi(pch);
			pch=strtok(NULL," ");
		}
		fclose(infile);
	}
	else{
		printf("無法開啟檔案");
	}
}
tree *newTreeNode(int d){
	tree *p=(tree *)malloc(sizeof(tree));
	p->data=d;
	p->left=p->right=NULL;//重要 
	return p;
}
int search(int arr[], int start, int end, int value) 
{ 
    int i; 
    for (i = start; i <= end; i++) { 
        if (arr[i] == value) 
            break; 
    } 
    return i; 
}
tree *buildTree1(int in[],int pre[],int start,int end, int *pIndex){
	if(start>end){
		return NULL;
	} 
	
	tree *node=newTreeNode(pre[*pIndex]);
	(*pIndex)++;
	
	int iIndex=search(in, start, end, node->data);
	
	if(start == end){
		return node;
	}
	node->left=buildTree1(in, pre, start, iIndex-1, pIndex);
	node->right=buildTree1(in, pre, iIndex+1, end, pIndex);
	
	return node;
}
tree *createTree1(int in[], int pre[], int n){
	int pIndex=1;
	return buildTree1(in, pre, 1, n, &pIndex);
}

tree *buildTree2(int in[],int post[],int start,int end, int *pIndex){
	if(start>end){
		return NULL;
	} 
	
	tree *node=newTreeNode(post[*pIndex]);
	(*pIndex)--;
	
	int iIndex=search(in, start, end, node->data);
	
	if(start == end){
		return node;
	}
	node->right=buildTree2(in, post, iIndex+1, end, pIndex);
	node->left=buildTree2(in, post, start, iIndex-1, pIndex);
	
	
	return node;
}
tree *createTree2(int in[], int post[], int n){
	int pIndex=n;
	//start, end 要設好,不然會出錯 
	return buildTree2(in, post, 1, n, &pIndex);
}

void inOrder(tree* x) 
{ 
    if (x == NULL) 
        return; 
    inOrder(x->left); 
    printf("%d ", x->data);
    inOrder(x->right); 
}

tree *merge(tree *T1, tree *T2){
	if(T1 == NULL) return T2;
	if(T2 == NULL) return T1;
	tree *root;
	if(T1->data < T2->data){
		root=T1;
		T1->right=merge(T1->right, T2);
	}
	if(T1->data > T2->data){
		root=T2;
		T2->right=merge(T2->right, T1);
	}
	return root;
}

//BadTree
tree *LeftChild(tree *x){
	return x->left;
}
tree *RightChild(tree *x){
	return x->right;
}
int min(int left,int right){
	if(left<=right) return left;
	else return right;
}
int shortest(tree *x){
	if(x==NULL) return 0;
	return 1+min(shortest(LeftChild(x)), shortest(RightChild(x)));
}

void testBad(tree* x, int *b) 
{ 
    if (x == NULL) 
        return; 
//    printf("node:%d \n", x->data);
//    printf("%d %d\n",shortest(LeftChild(x)),shortest(RightChild(x)));
    if(shortest(LeftChild(x)) < shortest(RightChild(x)))
    	*b=0;
    testBad(x->left, b); 
    testBad(x->right, b); 
    
}
void switchToBad(tree* x){
	if (x == NULL) 
        return;//重要，不然遞迴不會停止 
	if(shortest(LeftChild(x)) < shortest(RightChild(x))){
		tree *temp=x->left;
		x->left=x->right;
		x->right=temp;
	}
//	printf("node: %d\n",x->data);
	//如果是NULL,print出來會有問題，注意一下 
//	printf("left=%d , right=%d\n",x->left->data,x->right->data);
	switchToBad(x->left); 
    switchToBad(x->right); 
}

void output(tree *x, FILE *outfile){
	if(x==NULL) return;
	output(x->left, outfile);
	fprintf(outfile,"%d ",x->data);
	output(x->right, outfile);
}
void outputFile(tree *tree3){
	FILE *outfile=fopen("output2.txt","w");
	output(tree3, outfile);
	fclose(outfile);
}
int main(){
	inputFile();
	tree *tree1=createTree1(in1, pre1, n1);
	tree *tree2=createTree2(in2, post2, n2);
	tree *tree3=merge(tree1, tree2);
	switchToBad(tree3);
	int b=1;
	testBad(tree3,&b);
	printf("BadTree=%d\n",b);
	inOrder(tree3);
	outputFile(tree3);
	return 0;
}
