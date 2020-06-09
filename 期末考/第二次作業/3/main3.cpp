#include<stdio.h>
#include<stdlib.h>
#include<cstring>
int F[4][14];
int kind[6]={0};
int HL3[14]={0};
int HL2[14]={0};
int getH(char c){
	if(c=='H') return 0;
	if(c=='S') return 1;
	if(c=='D') return 2;
	if(c=='C') return 3;
	return 5;
}
int getV(char v[4]){
	if(strcmp(v,"A")==0) return 1;//不要打成cpy!!! 
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
	FILE *infile=fopen("input1.txt","r");
	if(infile!=NULL){
		int i=0;
		char c;
		char v[4];
		fscanf(infile,"%d\n",&i);
		while(i){
			fscanf(infile,"%c %s\n",&c,v);//形態要注意 
			F[getH(c)][getV(v)]=1;
			--i;
		}
	}else{
		printf("no such file");
	}
}
//先處理大桐花 
bool isBTH(int i){
	for(int j=10;j!=2;j=j%13+1){
		if(F[i][j]==0) return false;
	}
	return true;
}
void BTH(){
	for(int i=0;i<4;++i){
		if(isBTH(i)){
			++kind[0];
			for(int j=10;j!=2;j=j%13+1){
				F[i][j]=0;
			}
		}
	}
}
int THspan(int i,int j){
	if(F[i][j]==0) return 0;
	int n=0;
	for(int k=j;;k=k%13+1){
		if(F[i][k]==1) ++n;
		if(F[i][k]==0) return n;
	}
}
void TH(){//這裡要根據測資處理好 
	for(int i=0;i<4;++i){
		for(int j=1;j<=13;++j){
			if(THspan(i,j)==5){
				++kind[1];
				for(int k=j;k!=(j+5)%13;k=k%13+1){
					F[i][k]=0;
				}
			}
		}
	}
}
bool isTS(int j){
	for(int k=0;k<4;++k){
		if(F[k][j]==0) return false;
	}
	return true;
}
void TS(){
	for(int j=1;j<=13;++j){
		if(isTS(j)){
			++kind[2];
			for(int i=0;i<4;++i){
				F[i][j]=0;
			}
		}
	}
}
//葫蘆的處理方法要記一下 
int HL3_number=0;
int HL2_number=0;
void markHL3(int j){
	int n=0;
	for(int k=0;k<4;++k){
		if(F[k][j]==1) ++n;
	}
	if(n==3) {
		HL3[j]=1;
		++HL3_number;
	}
}
void markHL2(int j){
	int n=0;
	for(int k=0;k<4;++k){
		if(F[k][j]==1) ++n;
	}
	if(n==2) {
		HL2[j]=1;
		++HL2_number;
	}
}
void HL(){
	for(int j=1;j<=13;++j){
		markHL3(j); 
		markHL2(j); 
	}
	while(HL2_number && HL3_number){
		for(int j=1;j<=13;++j){
			if(HL3[j]==1){
				HL3[j]=0;
				--HL3_number;
				for(int i=0;i<4;++i)
					F[i][j]==0;
				break;
			}
		}
		for(int j=1;j<=13;++j){
			if(HL2[j]==1){
				HL2[j]=0;
				--HL2_number;
				for(int i=0;i<4;++i)
					F[i][j]==0;
				break;
			}
		}
		++kind[3];
	}
}
void Pair(){
	while(HL2_number){
		++kind[4];
		--HL2_number;
	}
}
int main(){
	inputFile();
	for(int i=0;i<4;++i){
		for(int j=1;j<=13;++j){
			printf("%d ",F[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	BTH();
	TH();
	HL();
	TS();
	Pair();
//	for(int i=0;i<4;++i){
//		for(int j=1;j<=13;++j){
//			printf("%d ",F[i][j]);
//		}
//		printf("\n");
//	}
	for(int i=0;i<5;++i){
		printf("%d\n",kind[i]);
	}
	return 0;
}
