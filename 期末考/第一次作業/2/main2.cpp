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
		int i=1;//要從1開始放，因為put的初始值是0 
		while(pch!=NULL){
			w[i++]=atoi(pch);
			pch=strtok(NULL," ");
		}
	}else{
		printf("無法開啟");
	}
}
int main(){
	inputFile();
	for(int i=1;i<=10;++i){//10個物品，從1開始放 
		for(int bw=1;bw<=maxW;++bw){ //0~maxW的背包容量 
			//無法放入
			if(w[i] > maxW) break;
			//填入背包 
			if(put[bw]==0 && w[i]==bw){
				put[bw]=i;
			} 
			//累加背包，不重覆放 
			else if(put[bw]>0 && put[bw]!=i && w[i]+bw<=maxW && put[w[i]+bw]==0){
				put[w[i]+bw]=i;
			} 
		}
	}
	//找出放入的最大重量 
	int bw=maxW;
	while(put[bw]==0){
		bw--;
	}
	printf("%d\n",bw+bagW);
	
//不用輸出放入的重量 
//	while(bw!=0){
//		printf("%d ",w[put[bw]]);
//		bw-=w[put[bw]];
//	}

	return 0;
}
