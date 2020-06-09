#include<stdlib.h>
#include<iostream>
#include<map>
#include<string.h>//stroke
using namespace std;

struct cmp_str//自己做一個比較字元陣列的struct 
{
   bool operator()(char const *a, char const *b)
   {
      return strcmp(a, b) < 0;
   }
};
//flower和number的map 
map<char const *,int,cmp_str> mapF;
map<char const *,int,cmp_str> mapN;

struct node{
	char data[3];
	struct node *nextSameF;
	struct node *nextSameN;
};
node *newNode(){
	node *p=(node *)malloc(sizeof(node));
	return p;
}
node *fHead[4];
node *fRear[4];
node *nHead[13];
node *nRear[13];

void init(){
	mapF["H"]=0;
	mapF["S"]=1;
	mapF["D"]=2;
	mapF["C"]=3;
	
	mapN["A"]=0;
	mapN["2"]=1;
	mapN["3"]=2;
	mapN["4"]=3;
	mapN["5"]=4;
	mapN["6"]=5;
	mapN["7"]=6;
	mapN["8"]=7;
	mapN["9"]=8;
	mapN["10"]=9; 
	mapN["J"]=10;
	mapN["Q"]=11;
	mapN["K"]=12;

	for(int i=0;i<4;++i){
		fHead[i]=newNode();
		fHead[i]->nextSameF=NULL;
		fHead[i]->nextSameN=NULL;
		fRear[i]=fHead[i];
	}
	for(int i=0;i<13;++i){
		nHead[i]=newNode();
		strcmp(nHead[i]->data,"*");
		nHead[i]->nextSameF=NULL;
		nHead[i]->nextSameN=NULL;
		nRear[i]=nHead[i];
	}
	
}
bool isInBigTongHua(char c[3]){
//	printf("cmp %s K=%d",c,strcmp(c,"K"));
	if(strcmp(c,"J")==0 || strcmp(c,"Q")==0 || strcmp(c,"K")==0 
	|| strcmp(c,"A")==0 || strcmp(c,"10")==0
	) return true;
	return false;
}
void print_list_F(int i){
	node *p=fHead[i];
		while(p!=NULL){
			printf("%s ",p->data);
			p=p->nextSameF;
		}
	cout<<endl;
}
void print_BTH(){
	printf("straight flush :\n");
	for(int i=0;i<4;++i){
		node *p=fHead[i]->nextSameF;
		int n=0;
		while(p!=NULL){
			if(isInBigTongHua(p->data)){
//				printf("%2s is in BTH\n",p->data);
				++n;
			}
			p=p->nextSameF;
		}
		if(n>=5){
			printf("%s ",fHead[i]);
			p=fHead[i]->nextSameF;
			while(p!=NULL){
				if(isInBigTongHua(p->data)){
					printf("%s ",p->data);
				}
				p=p->nextSameF;
			}
			cout<<endl;
		}
	}
}

void FH(int d){
	for(int i=0;i<13;++i){
		int n=0;
		node *p=nHead[i]->nextSameN;
		while(p!=NULL){
//			printf("%s",p->data);
			p=p->nextSameN;
			++n;
		}
		int b=0;
		if(n>=d){
//			printf("FH%d: \n",d);
			p=nHead[i]->nextSameN;
			while(p!=NULL){
				++b;
				if(b>d ) break;
				printf("%s",p->data);
				p=p->nextSameN;
			}
			cout<<" ";
		}
	}
	cout<<endl;
}
void print_FH(){
	printf("full house : \n");
	FH(3);
	FH(2);
}

void inputFile(){
	FILE *infile=fopen("input3.txt","r");
	if(infile!=NULL){
		char line[100];//只能用陣列 
		char *pch;//只能用指標 
		int i=1;
		while (fgets(line,100,infile)!=NULL)//讀取一行 
		{ 
			if(i==5) break;//讀取超過4行就離開 
			line[strlen(line)-1] = '\0';//去掉'\n' 
			//處理flower 
			pch = strtok(line," ");
			int f=mapF[pch];
			strcpy(fHead[f]->data,pch);
			pch = strtok(NULL, " ");//切割一次之後就要放NULL
			//處理number 
			while (pch != NULL)
			{
				int n=mapN[pch];
//				printf ("開始處理%s \n",pch);
				node *p=newNode();
				strcpy(p->data,pch);
				p->nextSameF=NULL;
				p->nextSameN=NULL;
				nRear[n]->nextSameN=p;
				nRear[n]=p;
//				printf("%d",isBigTongHua(pch));
				fRear[f]->nextSameF=p;
				fRear[f]=p;
				pch = strtok(NULL, " ");
			}      
			++i;
		}
	}else{
		printf("開啟檔案失敗");
	}
}
void outputFile(){
	FILE *outfile=fopen("output3.txt","w");
	fprintf(outfile,"straight flush :\n");
	for(int i=0;i<4;++i){
		node *p=fHead[i]->nextSameF;
		int n=0;
		while(p!=NULL){
			if(isInBigTongHua(p->data)){
//				printf("%2s is in BTH\n",p->data);
				++n;
			}
			p=p->nextSameF;
		}
		if(n>=5){
			fprintf(outfile,"%s ",fHead[i]);
			p=fHead[i]->nextSameF;
			while(p!=NULL){
				if(isInBigTongHua(p->data)){
					fprintf(outfile,"%s ",p->data);
				}
				p=p->nextSameF;
			}
			fprintf(outfile,"\n");
		}
	}
	fprintf(outfile,"\n");
	fprintf(outfile,"full house : \n");
	for(int i=0;i<13;++i){
		int n=0;
		node *p=nHead[i]->nextSameN;
		while(p!=NULL){
//			printf("%s",p->data);
			p=p->nextSameN;
			++n;
		}
		int b=0;
		if(n>=3){
//			printf("FH%d: \n",d);
			p=nHead[i]->nextSameN;
			while(p!=NULL){
				++b;
				if(b>3 ) break;
				fprintf(outfile,"%s",p->data);
				p=p->nextSameN;
			}
			fprintf(outfile," ");
		}
	}
	fprintf(outfile,"\n");
	for(int i=0;i<13;++i){
		int n=0;
		node *p=nHead[i]->nextSameN;
		while(p!=NULL){
//			printf("%s",p->data);
			p=p->nextSameN;
			++n;
		}
		int b=0;
		if(n>=2){
//			printf("FH%d: \n",d);
			p=nHead[i]->nextSameN;
			while(p!=NULL){
				++b;
				if(b>2 ) break;
				fprintf(outfile,"%s",p->data);
				p=p->nextSameN;
			}
			fprintf(outfile," ");
		}
	}
	fprintf(outfile,"\n");
}
int main(){
	init();
	inputFile();
	outputFile();
//	for(int i=0;i<4;++i){
//		if(fHead[i]->nextSameF!=NULL)
//			print_list_F(i);
//	}
//	cout<<endl;
	print_BTH();
	cout<<endl;
	print_FH();
	return 0;
}
