#include<stdio.h>
#include<cstring>
#include<stdlib.h>
int maxW=0,bagW=0;
int put[9999]={0};
int w[12]={0};
void inputFile(){
	FILE *infile=fopen("input3.txt","r");
	if(infile!=NULL){
		char line[105];
		char *pch;
		fscanf(infile,"%d %d\n",&maxW,&bagW);
		fgets(line,102,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		int i=1;//�n�q1�}�l��A�]��put����l�ȬO0 
		while(pch!=NULL){
			w[i++]=atoi(pch);
			pch=strtok(NULL," ");
		}
	}else{
		printf("�L�k�}��");
	}
}
int main(){
	inputFile();
	for(int i=1;i<=10;++i){//10�Ӫ��~�A�q1�}�l�� 
		for(int bw=1;bw<=maxW;++bw){ //0~maxW���I�]�e�q 
			//�L�k��J
			if(w[i] > maxW) break;
			//��J�I�] 
			if(put[bw]==0 && w[i]==bw){
				put[bw]=i;
			} 
			//�֥[�I�]�A�����Щ� 
			else if(put[bw]>0 && put[bw]!=i && w[i]+bw<=maxW && put[w[i]+bw]==0){
				put[w[i]+bw]=i;
			} 
		}
	}
	//��X��J���̤j���q 
	int bw=maxW;
	while(put[bw]==0){
		bw--;
	}
	printf("%d\n",bw+bagW);
	
//���ο�X��J�����q 
//	while(bw!=0){
//		printf("%d ",w[put[bw]]);
//		bw-=w[put[bw]];
//	}

	return 0;
}
