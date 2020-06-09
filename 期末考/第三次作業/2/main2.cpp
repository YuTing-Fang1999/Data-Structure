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
		
		int i=1;//�n��1�}�l��!!!�o�ˤ���n��min-heap
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
	if(i*2>=n) return;//�o���޿�n�M���A��ܨS���l�`�I 
//	printf("i=%d\n",i);

	//��ppt�t��k 
	int child=i*2;
	if(i*2+1<n){//�o���޿�n�M�� �A��ܦ��k�l�`�I 
		if(heap[i*2]->d > heap[i*2+1]->d)//��̤p�l�`�I 
			++child;
	}
	
//	printf("p=%d ,c=%d\n",heap[i]->d,heap[child]->d);
	if(heap[i]->d > heap[child]->d){
		//�洫 
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
	for(;i>0;--i){//i�n>0 
		adjust_i(i);
	}
	for(int i=1;i<=n/2;++i){//�q1�}�l�A�غctree 
		heap[i]->left=heap[i*2];
		heap[i]->right=heap[i*2+1];
	}
	tree *root=heap[1];	
	inOrder(root);
	return 0;
}
