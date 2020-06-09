#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<string.h>
using namespace std;

const int maxint = 999999;//代表走不到 
int map[105][105];//路徑權重 
int V=0;
int dis[105];//V個點 
int sta=0;
int tar=0;


//讀檔 
void inputFile(){ 
	FILE *infile=fopen("input3.txt","r");
	if(infile!=NULL){
		char *pch;
		char line[105];
		
		fgets(line,102,infile);
		int i=0;
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
			
		int j=0;
		pch=strtok(line," ");
		while(pch!=NULL){
			if(atoi(pch)==0)
				map[i][j++]=maxint;
			else
				map[i][j++]=atoi(pch);
			pch=strtok(NULL," ");
		};
		V=j;//第一行先記有幾個 
		while(fgets(line,102,infile)!=NULL){
			++i;
			if(V==i){//map輸完了 
				pch=strtok(line," ");
				sta=atoi(pch)-1;
				pch=strtok(NULL," ");
				tar=atoi(pch)-1;
				break;
			}
			if(line[strlen(line)-1]=='\n')
				line[strlen(line)-1]='\0';
				
			int j=0;
			pch=strtok(line," ");
			while(pch!=NULL){
				if(atoi(pch)==0)
					map[i][j++]=maxint;
				else
					map[i][j++]=atoi(pch);
				pch=strtok(NULL," ");
			};
		}
	}else{
		printf("無法開啟"); 
	}
	//初始化 
	for(int i=0;i<V;++i){
		dis[i]=maxint;
		//因為要先從sta開始算，所以要先填 
		if(map[sta][i]!=maxint)
			dis[i]=map[sta][i];
	}
}

int go(){
	int i=sta;
	do{
//		printf("%d->%d\n",sta+1,i+1);
		int j=sta;
		do{
			if(map[i][j]!=maxint){
				if(dis[j]>dis[i]+map[i][j]){//原本的距離與經由i到達的距離比較 
					dis[j]=dis[i]+map[i][j];
				}
			}
			j=(j+1)%V;//要記得加，不然只會跑一次; 
		}while(j!=sta);
		
		i=(i+1)%V;
	}while(i!=sta);
	//檢查有無負環 
	i=sta;
	do{
		int j=sta;
		do{
			if(map[i][j]!=maxint){
				if(dis[j]>dis[i]+map[i][j]){//原本的距離與經由i到達的距離比較 
					int i;
					for(i=0;i<V;++i){
						if(map[i][i]<0) break;
					}
//					printf("%d",map[i][i]);
					return i+1;
					break;
				}
			}
			j=(j+1)%V;//要記得加，不然只會跑一次; 
		}while(j!=sta);
		i=(i+1)%V;
	}while(i!=sta);
	return dis[tar];
}

void outputFile(){
	FILE *outfile=fopen("output2.txt","w");
	int n=go();
	fprintf(outfile,"%d",n);
	printf("%d",n);
	fclose(outfile);
}
int main(){
	inputFile();
	
//	for(int i=0;i<V;++i){
//		for(int j=0;j<V;++j){
//			printf("%d ",map[i][j]);
//		}
//		printf("%\n");
//	}
//	for(int k=0;k<V;++k){
//		printf("%d ",dis[k]);
//	}
//	printf("\n");

	outputFile();
	return 0;
}
