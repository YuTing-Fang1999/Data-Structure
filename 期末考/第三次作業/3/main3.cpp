#include<stdio.h>
#include<stdlib.h>
#include<cstring>

struct tree{
	int data;
	tree *left, *right;
};
tree *heap[120];//�ϥ�min_heap�h���X�P���J��� 
int n=0;//�`�`�I�� 

tree *newNode(int data){
	tree *p=(tree *)malloc(sizeof(tree));
	p->left=p->right=NULL;
	p->data=data;
	return p;
}
void push(tree *x){
	int i=++n;
	while(i!=1 && x->data<heap[i/2]->data){//�p�G����`�I�p�N�洫 
		heap[i]=heap[i/2];
		i=i/2;
	}
	heap[i]=x;
}

tree *pop(){
	tree *item=heap[1];
	tree *temp=heap[n--];
	int pa=1;
	int ch=2;
	while(ch<=n){
		if(heap[ch+1]->data < heap[ch]->data && ch+1<=n){
			++ch;
		}
		if(temp->data<heap[ch]->data) break;
		heap[pa]=heap[ch];
		pa=ch;//�n����child! 
		ch=ch*2;
	}
	heap[pa]=temp;
	return item;
}

tree *huffman(){
	while(n>1){//�O�o�nwhile�A�n�@�����ƪ���heap�S�F�� 
		tree *a=pop();
		tree *b=pop();
		tree *c=newNode(a->data+b->data);
		c->left=a;
		c->right=b;
//		printf("a=%d,b=%d,c=%d\n",a->data,b->data,c->data);
		push(c);
	}
	return pop();
}
void inOrder(tree *x){
	if(x==NULL) return;
	inOrder(x->left);
	printf("%d ",x->data);
	inOrder(x->right);
}
void inputFile(){
	FILE *infile=fopen("input3.txt","r");
	if(infile!=NULL){
		char line[115];
		char *pch;
		fgets(line,110,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch!=NULL){
			tree *x=newNode(atoi(pch));
			push(x);
			pch=strtok(NULL," ");
		}
	}
	else{
		printf("�L�k�}��");
	}
	fclose(infile);
}
void compute(tree *x,int L,int *s){
	if(x->left==NULL && x->right==NULL){//�u�n�⸭�`�I 
		*s+=x->data*L;
		return;
	}
	compute(x->left,L+1,s);
	compute(x->right,L+1,s);
}
int main(){
	inputFile();
	tree *root=huffman();
//	inOrder(root);
	int s=0;
	compute(root,1,&s);
	printf("%d",s);
	return 0;
}
