#include<stdio.h>
#include<stdlib.h>
#include<cstring>
//ㄏノ皚暗ゑ耕虏虫σ刚玡糶Ω 
int A[5][14]={0};
int B[5][14]={0};
int change[5]={0};//璶ユ传礟计 
int getV(char v[]){
	if(strcmp(v,"A")==0) return 1;//ぃ璶ゴΘcpy!!! 
	if(strcmp(v,"2")==0) return 2;
	if(strcmp(v,"3")==0) return 3;
	if(strcmp(v,"4")==0) return 4;
	if(strcmp(v,"5")==0) return 5;
	if(strcmp(v,"6")==0) return 6;
	if(strcmp(v,"7")==0) return 7;
	if(strcmp(v,"8")==0) return 8;
	if(strcmp(v,"9")==0) return 9;
	if(strcmp(v,"10")==0) return 10;
	if(strcmp(v,"J")==0) return 11;
	if(strcmp(v,"Q")==0) return 12;
	if(strcmp(v,"K")==0) return 13;
	return 0;
}

void inputFile(){
	FILE *infile=fopen("input3.txt","r");
	if(infile!=NULL){
		char line[105];
		char *pch;
		//A
		int i=0;
		while(i<4){
			fgets(line,102,infile);
			if(line[strlen(line)-1]=='\n')
				line[strlen(line)-1]='\0';
			pch=strtok(line," ");
			pch=strtok(NULL," ");//奔︹ 
			while(pch){
				A[i][getV(pch)]=1;
				pch=strtok(NULL," ");
			}
			++i;
		}
		//B
		i=0;
		while(i<4){
			fgets(line,102,infile);
			if(line[strlen(line)-1]=='\n')
				line[strlen(line)-1]='\0';
			pch=strtok(line," ");
			pch=strtok(NULL," ");//奔︹ 
			while(pch){
				B[i][getV(pch)]=1;
				pch=strtok(NULL," ");
			}
			++i;
		}
//		for(int i=0;i<4;++i){
//			for(int j=1;j<=13;++j){
//				if(A[i][j]==1) printf("%d ",1);
//				else printf("%d ",0);
//			}
//			printf("\n");
//		}
	}else{
		printf("no such file");
	}
}
bool isBTH(int i){//т抖穝change 
	int an=0,bn=0;
	for(int j=10;j!=2;j=j%13+1){//猔種或 
//		printf("A[%d][%d]=%d\n",i,j,A[i][j]);
		if(A[i][j]==1) ++an;
	}
	for(int j=10;j!=2;j=j%13+1){
		if(B[i][j]==1) ++bn;
	}
//	printf("an=%d, bn=%d\n",an,bn);
	//т璶ユ传礟计
	if(an+bn==5){
		if(an>bn) change[i]=bn;
		else change[i]=an;
		return true;
	}
	else return false;
}
int ch1(){
	for(int i=0;i<4;++i){
		if(change[i]==1){
			change[i]=0;
			return 1;
		}
	}
}
int ch2(){
	for(int i=0;i<4;++i){
		if(change[i]==2){
			change[i]=0;
			return 2;
		}
	}
}
int main(){
	inputFile();
	int n=0;
	for(int i=0;i<4;++i){
		//狦ぃ惠璶ユ传碞钡 
		if(isBTH(i) && change[i]==0) ++n;
//		printf("chamge=%d\n",change[i]);
	}
	int k=3;//ユ传
	//тユ传眎 
	while(ch1() && k){
		++n;
		k--;
	}
	//тユ传ㄢ眎 
	while(ch2() && k){
		++n;
		k-=2;
	}
	printf("%d",n);
	return 0;
}
