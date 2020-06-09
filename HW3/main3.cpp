#include<stdio.h>
#include<cstring>
#include<stdlib.h>
int arr[120];
char cmd[6];
int n=0;
struct tree{
	int data;
	tree *left;
	tree *right;
};
void inputFile(){
	FILE *infile=fopen("input3.txt","r");
	char line[120];
	char *pch;
	if(infile!=NULL){
		fscanf(infile,"%s\n",cmd);//猔種传︽才 
		printf("%s\n",cmd);
		fgets(line,110,infile);
		if(line[strlen(line)-1]=='\n')//Τ传︽才薄猵
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		int i=0;
		while(pch!=NULL){
			arr[++i]=atoi(pch);
			printf("%d ",arr[i]);
			pch=strtok(NULL," ");
		}
		n=i;//猔種 
		fclose(infile);
	}
	else{
		printf("礚猭秨币");
	}
}

tree *newNode(int d){
	tree *p=(tree *)malloc(sizeof(tree));
	p->data=d;
	p->left=p->right=NULL;
	return p;
}

tree *insert(tree *root,int i,int n,int arr[]){
	if(i<=n){
		tree *temp=newNode(arr[i]);
		root=temp;
//		printf("node:%d\n",root->data);
		root->left=insert(root->left,i*2,n,arr);
		root->right=insert(root->right,i*2+1,n,arr);
		
	}
	return root;
}

tree *min_heap(){
	
}

void max_heap(int arr[],int parent,int n){
	if(0<parent && parent<=n){
		int child=parent*2;
		if(child<=n){
			if(0<child && child <n && arr[child+1]>arr[child])
				++child;//т程child
//			printf("p=%d, c=%d\n",parent,child);
			if(arr[child]>arr[parent]){//ユ传 
//				printf("ユ传%d, %d\n",arr[parent],arr[child]);
				int t=arr[child];
				arr[child]=arr[parent];
				arr[parent]=t;
				//狦ユ传碞璶パユ传êchild秨﹍┕т 
				max_heap(arr,child,n);
			}
		}
		max_heap(arr,parent-1,n);
	}
}

void min_heap(int arr[],int parent,int n){
	if(0<parent && parent<=n){
		int child=parent*2;
		if(child<=n){
			if(0<child && child <n && arr[child+1]<arr[child])
				++child;//т程child
//			printf("p=%d %d, c=%d %d\n",parent,arr[parent],child,arr[child]);
			if(arr[child]<arr[parent]){//ユ传 
//				printf("ユ传%d, %d\n",arr[parent],arr[child]);
				int t=arr[child];
				arr[child]=arr[parent];
				arr[parent]=t;
				//狦ユ传碞璶パユ传êchild秨﹍┕т 
				min_heap(arr,child,n);//ぃ璶copy碞а癘эΘmin==
			}
		}
		min_heap(arr,parent-1,n);
	}
}

void inOrder(tree *x){
	if(x==NULL) return;
	inOrder(x->left);
	printf("%d ",x->data);
	inOrder(x->right);
}

void output(FILE *outfile,tree *x){
	if(x==NULL) return;
	output(outfile,x->left);
	fprintf(outfile,"%d ",x->data);
	output(outfile,x->right);
	
}
void outputFile(tree *x){
	FILE *outfile=fopen("output3.txt","w");
	output(outfile,x);
	fclose(outfile);
}

int main(){
	inputFile();
	printf("\n");
	if(strcmp(cmd,"max")==0) max_heap(arr,n/2,n);
	else if(strcmp(cmd,"min")==0) min_heap(arr,n/2,n);
	else printf("礚猭耞");
	printf("э皚: \n");
	for(int i=1;i<=n;++i){
		printf("%d ",arr[i]);
	}
	printf("\n");
	printf("い块: \n");
	tree *root=insert(root,1,n,arr);
	inOrder(root);
	outputFile(root);
	return 0;
}
