#include<stdio.h>
#include<stdlib.h>
#include<cstring>
//���N�ҰҰ��Ĥ��D�A���� 

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

tree *heap[120];//�ϥ�min_heap�h���X�P���J��� 
int n=0;//�`�`�I�� 
tree *nL[105];
int nl=-1;//�D���`�I�� 
tree *queqe[105]={NULL};
int qHead=0,qTail=0;

void push(tree *x,int *n){
	int i=++(*n);//�s���J���`�I��index 
	
	while(i!=1 && x->data<heap[i/2]->data){//�p�Gdata����`�I�j���� 
		heap[i]=heap[i/2];//���`�I����l�`�I 
		i=i/2;
	}
	heap[i]=x;
} 

tree *pop(int *n){
	tree *item=heap[1];//���X�Y�I 
	tree *temp=heap[(*n)--];//���ʳ̫�@���I 
	int parent=1;
	int child=2;
	while(child<=*n){
		if(child<*n && heap[child+1]->data<heap[child]->data){
			child++;//��X�̤p�l�`�I 
		}
		if(temp->data <= heap[child]->data) break;//��������parent
		heap[parent]=heap[child];//�l�`�I������`�I
		parent=child;//����U�@�h(�~��B�z) 
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
		printf("�L�k�}��");
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
		x=queqe[qHead++];//�n�����X 
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
