#include<iostream>//map
#include<stdlib.h>//malloc
#include<cstring>
using namespace std;
enum tag {whatever,yes,no};
enum who {head,A,B};
struct node{
	char data[3];
	//注意需要兩個next,不然會被覆蓋(寫註解編譯器不給過是在哈囉?) 
	node *sameF;
	node *sameN;
	tag t;
	who w;
};

bool done=false;//判斷有沒有找完 
node *newNode(){
	node *p=(node *)malloc(sizeof(node));
	return p;
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
//初始化 
void init(){
	for(int i=0;i<4;++i){
		fHead[i]=newNode();
		fHead[i]->sameF=NULL;
		fHead[i]->w=head;
		fHead[i]->t=whatever;
	}
	strcpy(fHead[0]->data,"H");
	strcpy(fHead[1]->data,"S");
	strcpy(fHead[2]->data,"D");
	strcpy(fHead[3]->data,"C");
}
void print_mark(){
	for(int i=0;i<4;++i){
		node *p=fHead[i];
		while(p!=NULL){
			printf("%d ",p->t);
			p=p->sameF;
		}
		cout<<endl;
	} 
	cout<<endl;
}
void print_mark_who(who w){
	for(int i=0;i<4;++i){
		node *p=fHead[i];
		while(p!=NULL){
			if(p->w==w ||p->w==head)
				printf("%d ",p->t);
			p=p->sameF;
		}
		cout<<endl;
	} 
	cout<<endl;
}
void print_F(){
	for(int i=0;i<4;++i){
		node *p=fHead[i];
		while(p!=NULL){
			printf("%s ",p->data);
			p=p->sameF;
		}
		cout<<endl;
	} 
	cout<<endl;
}
void print_F_who(who w){
	for(int i=0;i<4;++i){
		node *p=fHead[i];
		while(p!=NULL){
			if(p->w==w ||p->w==head)
				printf("%s ",p->data);
			p=p->sameF;
		}
		cout<<endl;
	} 
	cout<<endl;
}
void print_N(){
	for(int i=1;i<14;++i){
		node *p=nHead[i];
		while(p!=NULL){
			printf("%s",p->data);
			p=p->sameN;
		}
		cout<<endl;
	} 
}
//找到要插入的前一個node 
node *order_pre_node(int f,node *p){
	node *q=fHead[f];
	while(q->sameF!=NULL){
		int i=mapN(q->sameF->data);
		if( i > mapN(p->data) ) break;
		q=q->sameF;
	}
	return q;
}
void read(who w,FILE *infile){
	char line[6];//只能用陣列 
	char *pch;//只能用指標 
	 
	while (fgets(line,100,infile)!=NULL)//讀取一行 
	{ 
		if(strcmp(line,"\n")==0) break;
		line[strlen(line)-1] = '\0';//去掉'\n' 
		//讀取花色 
		pch = strtok(line," ");
//		printf("%s ",pch);
		int f=mapF(pch);
		//讀取數字 
		pch = strtok(NULL, " ");
		int n=mapN(pch);
//		printf("%s ",pch);
		//創新節點 
		node *p=newNode();
		strcpy(p->data,pch);
		p->w=w;
		p->t=whatever;
		p->sameF=NULL;
		p->sameN=NULL;
		//加入(由小排到大) 
		//F
		node *q=order_pre_node(f,p);
		p->sameF=q->sameF;
		q->sameF=p;
		//N
		p->sameN=nHead[n];
		nHead[n]=p;
//		cout<<endl;
	}
}
void inputFile(){
	FILE *infile=fopen("input4.txt","r");
	if(infile!=NULL){
		read(A,infile);
//		printf("break\n");
		read(B,infile);
	}else{
		printf("無法開啟檔案\n");
	}
}

node *find_node(int f,int n){
	node *p=fHead[f]->sameF;
	while(p!=NULL){
		if(mapN(p->data)==n){
			return p;
		}
		p=p->sameF;
	}
	return NULL;
}
int len_from_i_to_j(int f,int i,int j){//總長度 
	node *s=find_node(f,i);
	node *e=find_node(f,j);
	int len=1;
	if(s && e){
		while(s!=e){
			if(s->t==whatever)
				len++;
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
int w_len_from_i_to_j(who w,int f,int i,int j){
	node *s=find_node(f,i);
	node *e=find_node(f,j);
	int len=0;
	while(s){
		if(s->w==w && s->t==whatever){
			len++;
//			printf("%s ",s->data);
		}
		s=s->sameF;
		if(s==NULL){
			s=fHead[f]->sameF;
		}
		if(s==e){
			if(s->w==w && s->t==whatever){
				++len;
//				printf("%s ",s->data);
			}
			break;
		}
	}
	return len;
}
bool isBTH(int f){
	if(len_from_i_to_j(f,10,1)==5){
		return true;
	}
	return false;
}
bool isTH(int f,int i){
	if(len_from_i_to_j(f,i,(i+3)%13+1)==5){
		return true;
	}
	return false;
}
void mark(who w,tag t,int f,int i,int j){
	node *s=find_node(f,i);
	node *e=find_node(f,j);
	while(s){
		if(s->w==w){
			s->t=t;
		}
		s=s->sameF;
		if(s==NULL){
			s=fHead[f]->sameF;
		}
		if(s==e){
			if(s->w==w){
				s->t=t;
			}
			break;
		}
	}
}
void markBTH(int f){
	if(w_len_from_i_to_j(A,f,10,1)>w_len_from_i_to_j(B,f,10,1)){
		mark(A,no,f,10,1);//A留下 
		mark(B,yes,f,10,1);//B交換 
	}
	else{
		mark(A,yes,f,10,1);
		mark(B,no,f,10,1);
	}
}
void markTH(int f,int i){
	int e=(i+3)%13+1;
	if(w_len_from_i_to_j(A,f,i,e)>w_len_from_i_to_j(B,f,i,e)){
		mark(A,no,f,i,e);//A留下 
		mark(B,yes,f,i,e);//B交換 
	}
	else{
		mark(A,yes,f,i,e);
		mark(B,no,f,i,e);
	}
}
int w_t_num(who w,tag t){
	int n=0;
	for(int i=0;i<4;++i){
		node *p=fHead[i]->sameF;
		while(p!=NULL){
			if(p->w==w && p->t==t)
				++n;
			p=p->sameF;
		}
	} 
	return n;
}
void change(who from,who to,tag t,int n){
	for(int i=0;i<4,n;++i){
		node *p=fHead[i]->sameF;
		while(p!=NULL && n){
			if(p->w==from && p->t==t){
				p->w=to;
				if(t==yes)
					p->t=no;
				--n;
			}
			p=p->sameF;
		}
	} 
}
int BTH(){
	int num=0;
	for(int i=0;i<4;++i){
		if(isBTH(i)){
			markBTH(i);
		}
	}
	int ay=w_t_num(A,yes);
	int by=w_t_num(B,yes);
	int aw=w_t_num(A,whatever);
	int bw=w_t_num(B,whatever);
	if(ay>=by && bw>=ay-by){
		num=w_t_num(A,yes);
		change(A,B,yes,ay);//A to B
		change(B,A,yes,by);
		change(B,A,whatever,ay-by);
	}
	else if(by>=ay && aw>=by-ay){
		num=w_t_num(B,yes);
		change(B,A,yes,by);//B to A
		change(A,B,yes,ay);
		change(A,B,whatever,by-ay);
	}else{
		printf("這解法我還沒想到哭哭");
	}
	if(aw<5 || bw<5){
		printf("done!\n");
		done=true;
	}
	return num;
}
int TH(){
	int num=0;
	for(int f=0;f<4;++f){
		node *p=fHead[f]->sameF;
		while(p!=NULL){
			int i=mapN(p->data);
			if(isTH(f,i)){
//				printf("%d is TH\n",i);
				markTH(f,i);
			}
			p=p->sameF;
		}
	}
	int ay=w_t_num(A,yes);
	int by=w_t_num(B,yes);
	int aw=w_t_num(A,whatever);
	int bw=w_t_num(B,whatever);
	if(ay>=by && bw>=ay-by){
		num=w_t_num(A,yes);
		change(A,B,yes,ay);//A to B
		change(B,A,yes,by);
		change(B,A,whatever,ay-by);
	}
	else if(by>=ay && aw>=by-ay){
		num=w_t_num(B,yes);
		change(B,A,yes,by);//B to A
		change(A,B,yes,ay);
		change(A,B,whatever,by-ay);
	}else{
		printf("這解法我還沒想到哭哭");
	}
	if(aw<5 || bw<5){
		printf("done!\n");
		done=true;
	}
	return num;
}
int change(){
	int n=0;
	if(!done) n+=BTH();
	if(!done) n+=TH();
//	if(!done) n+=TT();
	return n;
}
void i_max_span(int f,int i){
	int span=1;
	while(true){
//		printf("i=%d, span=%d\n",i,span);
		int len=len_from_i_to_j(f,i,i+span);
//		printf("len=%d\n",len);
		if(len==span+1){
			++span;
		}else{
			break;
		}
	}
}
void outputFile(int n){
	FILE *outfile=fopen("output4.txt","w");
	fprintf(outfile,"%d\n",n);
	for(int i=0;i<4;++i){
		node *p=fHead[i];
		while(p!=NULL){
			if(p->w==A ||p->w==head)
				fprintf(outfile,"%s ",p->data);
			p=p->sameF;
		}
		fprintf(outfile,"\n");
	} 
	fprintf(outfile,"\n");
	for(int i=0;i<4;++i){
		node *p=fHead[i];
		while(p!=NULL){
			if(p->w==B ||p->w==head)
				fprintf(outfile,"%s ",p->data);
			p=p->sameF;
		}
		fprintf(outfile,"\n");
	} 
	fprintf(outfile,"\n");
}
int main(){
	init();
	inputFile();
//	cout<<endl;
//	print_F();
  	int n=change();
	printf("%d\n",n);
	print_F_who(A);
	print_F_who(B);
	outputFile(n);
	return 0;
}
