#include<stdio.h>
#include<stdlib.h>
#include<cstring>
int map[9][9];
int visited[9]={0};
int dis[9];
int queqe[100];//使用queqe 
int qHead=0,qRear=0;
const int maxInt=99999;
void inputFile(){
	FILE *infile=fopen("input1.txt","r");
	if(infile!=NULL){
		char line[105];
		char *pch;
		while(fgets(line,102,infile)!=NULL){
			if(line[strlen(line)-1]=='\n')
				line[strlen(line)-1]='\0';
			pch=strtok(line," ");
			while(pch!=NULL){
				queqe[qRear++]=atoi(pch);//放入queqe 
				pch=strtok(NULL," ");
			}
		}
	}else{
		printf("無法開啟");
	}
}
int next(){//找到下一個最近的點 
	int u=0;
	int d=maxInt;
	for(int i=0;i<7;++i){
		if(visited[i]==0 && dis[i]<d){
			d=dis[i];
			u=i;
		}
	}
	visited[u]=1;
	return u;
}
int main(){
	inputFile();
	//從queqe輸入map
	for(int i=0;i<7;++i){
		for(int j=0;j<7;++j){
			map[i][j]=queqe[qHead++];//從queqe取出
			if(map[i][j]==0) map[i][j]=maxInt;//表示走不到  
		}
	}
	//初始化距離 
	for(int i=0;i<7;++i){
		dis[i]=map[0][i];
	}
	for(int i=0;i<7;++i){//遍歷所有點 
		int u=next();
		for(int j=0;j<7;++j){//更新所有dis 
			if(dis[j]>dis[u]+map[u][j]){
				dis[j]=dis[u]+map[u][j];
			}
		}
	}
	if(dis[6]==maxInt) printf("%d",0);
	else printf("%d",dis[6]);
	
	return 0;
}
