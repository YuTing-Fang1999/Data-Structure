#include<stdio.h>
#include<stdlib.h>
#include<cstring>
//�i�H�ϥΰ}�C�h���A���²��A�Ҹիe�A�g�@���a 
int A[5][14]={0};
int B[5][14]={0};
int change[5]={0};//�n�洫���P�� 
int getV(char v[]){
	if(strcmp(v,"A")==0) return 1;//���n����cpy!!! 
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
			pch=strtok(NULL," ");//�h����� 
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
			pch=strtok(NULL," ");//�h����� 
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
bool isBTH(int i){//���ᶶ�B��schange 
	int an=0,bn=0;
	for(int j=10;j!=2;j=j%13+1){//�`�N���[ 
//		printf("A[%d][%d]=%d\n",i,j,A[i][j]);
		if(A[i][j]==1) ++an;
	}
	for(int j=10;j!=2;j=j%13+1){
		if(B[i][j]==1) ++bn;
	}
//	printf("an=%d, bn=%d\n",an,bn);
	//��X�n�洫���P��
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
		//�p�G���ݭn�洫�N�����[ 
		if(isBTH(i) && change[i]==0) ++n;
//		printf("chamge=%d\n",change[i]);
	}
	int k=3;//�洫�W��
	//����洫�@�i�� 
	while(ch1() && k){
		++n;
		k--;
	}
	//�A��洫��i�� 
	while(ch2() && k){
		++n;
		k-=2;
	}
	printf("%d",n);
	return 0;
}
