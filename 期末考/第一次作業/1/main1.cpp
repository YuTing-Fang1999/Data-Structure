#include<stdio.h>
#include<cstring>
#include<stdlib.h>
struct Item{//���]��int 
	int v;
	int w;
	int cp;
};
Item item[12];
int maxW=0;
void inputFile(){
	FILE *infile=fopen("input1.txt","r");
	if(infile!=NULL){
		char line[105];
		char *pch;
		// maxW
		fscanf(infile,"%d\n",&maxW);//�O�o�[&�M\n 
//		//���q 
		fgets(line,102,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		int i=0;
		while(pch!=NULL){
			item[i++].w=atoi(pch);
			pch=strtok(NULL," ");
		}
		//value
		fgets(line,102,infile);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		i=0;
		while(pch!=NULL){
			item[i++].v=atoi(pch);
			//�����CP���� 
			item[i-1].cp=(int)((float)item[i-1].v/(float)item[i-1].w);
			pch=strtok(NULL," ");
		}
	}else{
		printf("�L�k�}��");
	}
}
int main(){
	inputFile();
	// sort
	Item t;
	for(int i=0;i<10;++i){
		for(int j=i+1;j<10;++j){
			if(item[i].cp<item[j].cp){
				t=item[i];
				item[i]=item[j];//���n�ʤߧ� = ����; 
				item[j]=t;
			}
		}
	}
	int i=0;
	int maxV=0;
	while(maxW!=0){
		if(maxW>=item[i].w){
			maxV+=item[i].cp*item[i].w;
			maxW-=item[i].w;
		}else
		{
			maxV+=item[i].cp*maxW;
			maxW=0;
		}
		++i;//�O�o�n�[ 
	}
	printf("%d",maxV);
	return 0;
}
