#include<stdio.h>
#include<stdlib.h>//atoi
#include<cstring>//strtok
int in[120];
int post[120];
int n=0;//���I�� 
struct tree{
	int data=-1;
	struct tree *LeftChild=NULL;
	struct tree *RightChild=NULL;
};
void inputFile(){
	FILE *infile=fopen("input1.txt","r");
	int i=0;//index
	if(infile!=NULL){
		char *pch;
		char line[120];
		//��J��� 
		fgets(line, 110, infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch!=NULL){
			post[++i]=atoi(pch);
//			printf("%d ",post[i]);
			pch=strtok(NULL," ");
		} 
		n=i;
		i=0;
		//��J���� 
//		printf("\n");
		fgets(line, 110, infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch!=NULL){
			in[++i]=atoi(pch);
//			printf("%d ",infex[i]);
			pch=strtok(NULL," ");
		} 
	}
	else{
		printf("�L�k�}���ɮ�\n"); 
	}
}
tree *newTreeNode(int data){
	tree *p=(tree *)malloc(sizeof(tree));
	p->data=data;
	p->LeftChild=p->RightChild=NULL;
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
//	���ǥi���X���k�l��
//	��Ǫ��˼ƲĤ@�ӵ��I�O��ڡA�ѫ᩹�e�A���إk�A�إ� 
tree* buildTree(int in[], int post[], int inStart, int inEnd, int* pIndex) 
{ 
    // left node 
    if (inStart > inEnd) 
        return NULL; 
  
    /* ��node�ѫ�qpost���X */
    tree* node = newTreeNode(post[*pIndex]); 
    (*pIndex)--; 
  
    /* If this node has no children then return */
    if (inStart == inEnd) 
        return node; 
  
    /* ��X�o��node�bin[]��index�A�ѥ����X���k�l�� */
    int iIndex = search(in, inStart, inEnd, node->data); 
  
//    				   iIndex
//    				   /	\
//    [inStrat~iIndex-1]   [iIndex+1~inEnd]

	//���إk�l�� 
    node->RightChild = buildTree(in, post, iIndex + 1, inEnd, pIndex); 
    //�A�إ��l�� 
    node->LeftChild = buildTree(in, post, inStart, iIndex - 1, pIndex); 
  
    return node; 
}
tree *createTree(int in[], int post[], int n){
	int pIndex = n; 
    return buildTree(in, post, 1, n, &pIndex); 
}

tree *LeftChild(tree *x){
	return x->LeftChild;
}
tree *RightChild(tree *x){
	return x->RightChild;
}
int min(int left,int right){
	if(left<=right) return left;
	else return right;
}
int shortest(tree *x){
	if(x==NULL) return 0;
	return 1+min(shortest(LeftChild(x)), shortest(RightChild(x)));
}
//test
bool isBad=true;
void postOrder(tree* x) 
{ 
    if (x == NULL) 
        return; 
//    printf("%d %d\n",shortest(LeftChild(x)),shortest(RightChild(x)));
    if(shortest(LeftChild(x)) < shortest(RightChild(x)))
    	isBad=false;
    postOrder(x->LeftChild); 
    postOrder(x->RightChild); 
//    printf("%d ", x->data);
}
void outputFile(bool isBad){
	FILE *outfile=fopen("output1.txt","w");
	fprintf(outfile,"%d",isBad);
	fclose(outfile);
} 
int main(){
	inputFile();
	tree *root=createTree(in,post,n);
	postOrder(root);
	printf("%d",isBad);
	outputFile(isBad);
	return 0;
}
