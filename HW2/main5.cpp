#include<iostream>//map
#include<stdlib.h>//malloc
#include<cstring>
#include<math.h>
using namespace std;
struct node{
	char f[3];
	char n[3];
	//注意需要兩個next,不然會被覆蓋(寫註解編譯器不給過是在哈囉?) 
	node *sameF;
	node *sameN;
};
struct tog{
	int t;
	tog *next;
	tog *down;
};
struct kind{
	int score=0;
	node *node;
	kind *next;
	kind *down;
};
node *newNode(){
	node *p=(node *)malloc(sizeof(node));
	return p;
}
tog *newTog(){
	tog *p=(tog *)malloc(sizeof(tog));
	return p;
}
kind *newK(){
	kind *p=(kind *)malloc(sizeof(kind));
	return p;
}

node *copy(node *p){
	node *q=newNode();
	strcpy(q->f,p->f);
	strcpy(q->n,p->n);
	q->sameF=NULL;
	q->sameN=NULL;
	return q;
}
int mapF(char d[3]){
	if(strcmp(d,"H")==0)
		return 0;
	if(strcmp(d,"S")==0)
		return 1;
	if(strcmp(d,"D")==0)
		return 2;
	if(strcmp(d,"C")==0)
		return 3;
}
int mapN(char d[3]){
	if(strcmp(d,"A")==0)
		return 1;
	if(strcmp(d,"2")==0)
		return 2;
	if(strcmp(d,"3")==0)
		return 3;
	if(strcmp(d,"4")==0)
		return 4;
	if(strcmp(d,"5")==0)
		return 5;
	if(strcmp(d,"6")==0)
		return 6;
	if(strcmp(d,"7")==0)
		return 7;
	if(strcmp(d,"8")==0)
		return 8;
	if(strcmp(d,"9")==0)
		return 9;
	if(strcmp(d,"10")==0)
		return 10;
	if(strcmp(d,"J")==0)
		return 11;
	if(strcmp(d,"Q")==0)
		return 12;
	if(strcmp(d,"K")==0)
		return 13;
}

node *fHead[4];
node *nHead[14];//1~13
tog *togH;
kind *kH;
kind *kR;
void print_F(){
	for(int i=0;i<4;++i){
		node *p=fHead[i];
//		printf("%s ",fHead[i]->f);
		while(p!=NULL){
			printf("%s ",p->n);
			p=p->sameF;
		}
		printf("\n");
	} 
	cout<<endl;
}
void print_N(){
	for(int i=1;i<14;++i){
		node *p=nHead[i];
		while(p!=NULL){
			printf("%3s %3s|",p->f,p->n);
			p=p->sameN;
		}
		if(nHead[i]) printf("\n");
	} 
}
//初始化 
void init(){
	for(int i=0;i<4;++i){
		fHead[i]=newNode();
		fHead[i]->sameF=NULL;
	}
	strcpy(fHead[0]->f,"H");
	strcpy(fHead[1]->f,"S");
	strcpy(fHead[2]->f,"D");
	strcpy(fHead[3]->f,"C");
	
	strcpy(fHead[0]->n,"H");
	strcpy(fHead[1]->n,"S");
	strcpy(fHead[2]->n,"D");
	strcpy(fHead[3]->n,"C");
	
	kH=newK();
	kR=kH;
	kR->down=NULL;
	kR->next=NULL;
}
//找到要插入的前一個node 
node *order_pre_node(int f,node *p){
	node *q=fHead[f];
	while(q->sameF!=NULL){
		int i=mapN(q->sameF->n);
		if( i > mapN(p->n) ) break;
		q=q->sameF;
	}
	return q;
}
void add(char cf[3],char cn[3]){
	int f=mapF(cf);
	int n=mapN(cn);
	//創新節點 
	node *p=newNode();
	strcpy(p->f,cf);
	strcpy(p->n,cn);
	p->sameF=NULL;
	p->sameN=NULL;
	//加入(由小排到大) 
	//F
	node *q=order_pre_node(f,p);
	p->sameF=q->sameF;
	q->sameF=p;
	//N
	node *k=copy(p);//不知為何要新增一個node? 
	k->sameN=nHead[n];
	nHead[n]=k;
}
void read(FILE *infile){
	char line[100];//只能用陣列，空間大一點!! 
	char *pch;//只能用指標 
	char cf[3],cn[3];
	while (fgets(line,100,infile)!=NULL)//讀取一行 
	{ 
		line[strlen(line)-1] = '\0';//去掉'\n' 
		pch = strtok(line," ");
		strcpy(cf,pch);
		pch = strtok (NULL, " ");
  		while (pch != NULL)
		{
//			printf ("%s\n",pch);
			strcpy(cn,pch);
			add(cf,cn);
			pch = strtok (NULL, " ");
		}    
	}
}
void inputFile(){
	FILE *infile=fopen("input5.txt","r");
	if(infile!=NULL){
		read(infile);
	}else{
		printf("無法開啟檔案\n");
	}
}
node *find_node(int f,int n){
	node *p=fHead[f]->sameF;
	while(p!=NULL){
		if(mapN(p->n)==n){
			return p;
		}
		p=p->sameF;
	}
	return NULL;
}
int spanF(int f,int i,int j){//連續長度
	node *s=find_node(f,i);
	node *e=find_node(f,j);
	int len=1;
	if(s && e){
//		printf("%s~%s\n",s->n,e->n);
		while(s!=e){
			len++;
//			printf("%s ",s->n);
			s=s->sameF;
			if(s==NULL){
				s=fHead[f]->sameF;
			}
		}
	}else{
		return 0;
	}
	return len;
}
int spanN(int n){//連續長度
	node *p=nHead[n];
	int len=0;
	while(p!=NULL){
		++len;
//		printf("%s %s\n",p->f,p->n);
		p=p->sameN;
	}
	return len;
}
tog *createToggle(int n){
	tog *togH=newTog();
	tog *togR=togH;
	togR->down=NULL;
	togR->next=NULL;
	int powN=pow(2,n);
	int n2;
	int i2;
	for(int i=0;i<powN;++i){
		tog *th=NULL;//要指定成NULL 
		tog *tr=NULL;
		n2=n;
		i2=i;
		while(n2){
			tog *temp=newTog();
			temp->t=i2%2;
			temp->down=NULL;
			temp->next=NULL;
			if(th!=NULL){
				tr->down=temp;
				tr=tr->down;
			}else{
				tr=temp;
				th=tr;
			}
			i2=i2/2;
			--n2;
		}
		togR->down=th;
		togR->next=newTog();
		togR=togR->next;
		togR->next=NULL;
		togR->down=NULL;
	}
	return togH;
}
void print_tog(tog *togH){
	while(togH!=NULL){
		tog *th=togH->down;
		while(th!=NULL){
			printf("%d ",th->t);
			th=th->down;
		}
		printf("\n");
		togH=togH->next;
	}
}
void print_k(){
	kind *p=kH;
	while(p->next!=NULL){
		printf("score=%d\n",p->score);
		kind *kh=p->down;
		while(kh!=NULL){
			printf("%s %s\n",kh->node->f,kh->node->n);
			kh=kh->down;
		}
		printf("\n");
		p=p->next;
	}
}
int k_len(){
	kind *p=kH;
	int len=0;
	while(p->next!=NULL){
		++len;
		p=p->next;
	}
	return len;
}
void putInKF(int score,int f,node *s,node *e){
	kind *kh=NULL;//要指定成NULL 
	kind *kr=NULL;
	while(s){
		kind *temp=newK();
		temp->node=copy(s);
//		printf("%s %s\n",temp->node->f,temp->node->n);
		temp->down=NULL;
		temp->next=NULL;
		if(kh!=NULL){
			kr->down=temp;
			kr=kr->down;
		}else{
			kr=temp;
			kh=kr;
		}
		if(s==e){
			break;
		}
		s=s->sameF;
		if(s==NULL){
			s=fHead[f]->sameF;
		}
	}
	kR->score=score;
	kR->down=kh;
	kR->next=newK();
	kR=kR->next;
	kR->next=NULL;
	kR->down=NULL;
}
kind *newTemp(node *p){
	kind *temp=newK();
	temp->node=copy(p);
	temp->down=NULL;
	temp->next=NULL;
	return temp;
}
bool same(node *a,node *b){
	//!!!不要打成cpy!!! 
	if(strcmp(a->f,b->f)==0 && strcmp(a->n,b->n)==0){
		return true;
	}
	return false;
}
void putTTInK(int score,int n){
	node *nh=nHead[n];
	node *p=nh;
	kind *kh=NULL;//要指定成NULL 
	kind *kr=NULL;
	while(p!=NULL){
		kind *temp=newTemp(p);
		if(kh!=NULL){
			kr->down=temp;
			kr=kr->down;
		}else{
			kr=temp;
			kh=kr;
		}
		p=p->sameN;
	}
	kR->score=score;
	kR->down=kh;
	kR->next=newK();
	kR=kR->next;
	kR->next=NULL;
	kR->down=NULL;
}

void pushBTH(){
	for(int i=0;i<4;++i){
//		printf("%d\n",spanF(i,10,1));
		if(spanF(i,10,1)==5){
//			printf("%s is bth\n",fHead[i]->f);
			putInKF(6,i,find_node(i,10),find_node(i,1));
		}
	}
}
void pushTH(){
	for(int i=0;i<4;++i){
		node *p=fHead[i]->sameF;
		while(p!=NULL){
			int s=mapN(p->n);
			int e=(s+3)%13+1; 
			if(s !=10 && spanF(i,s,e)==5){
//				printf("%s is th\n",fHead[i]->f);
				putInKF(4,i,find_node(i,s),find_node(i,e));
			}
			p=p->sameF;
		}
	}
}

void pushTT(){
	for(int i=1;i<14;++i){
		if(spanN(i)==4){
			putTTInK(3,i);
		}
	}
}
void pushTwo(){
	for(int i=1;i<14;++i){
		if(spanN(i)==2){
			putTTInK(1,i);
		}
	}
}
void pushThree(){
	for(int i=1;i<14;++i){
		if(spanN(i)==3){
			putTTInK(1,i);
		}
	}
}
void outputFile(){
	int score=0;
	kind *p=kH;
	while(p->next!=NULL){
		score+=p->score;
		p=p->next;
	}
	FILE *outfile=fopen("output5.txt","w");
	fprintf(outfile,"%d",score);
}
int main(){
	init();
	inputFile();
//	print_tog(createToggle(4));
	pushBTH();
	pushTH();
	pushTT();
	pushTwo();
	pushThree();
	print_k();
//	printf("k_len=%d",k_len());
//	print_F();
//	print_N();
	outputFile();
	return 0;
}
