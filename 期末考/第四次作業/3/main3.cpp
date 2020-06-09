#include <string.h> //memset
#include<cstring>
#include<stdlib.h>
#include<stdio.h>
#define INF 99999
//考試前再寫一遍 
int map[105][105];
int visited[105];
int last[105];
int min[105];
int queqe[105];
int qTail,qHead;
int V=0;//V個點 

void inputFile(){
	FILE *infile=fopen("input3.txt","r");
	if(infile!=NULL){
		char *pch;
		char line[105];
		while(fgets(line,102,infile)!=NULL){
			if(line[strlen(line)-1]=='\n')
				line[strlen(line)-1]='\0';
			int i=-1;
			pch=strtok(line," ");
			while(pch!=NULL){
				map[V][++i]=atoi(pch);
				pch=strtok(NULL," ");
			}
			++V;
		}

	}else{
		printf("無法開啟"); 
	}
}
void build_res(){
	int flow=min[V-1];
	int cur=V-1;
	while(last[cur]!=-1){
		map[last[cur]][cur]-=flow;
		map[cur][last[cur]]+=flow;
		cur=last[cur];//注意cur要變，不然會無限迴圈 
	}
}
int bfs(){
	memset(visited,0,sizeof(visited));
	min[0]=INF;
	queqe[0]=0;
	qTail=1;
	last[0]=-1;
	visited[0]=1;//重要 
	
	for(qHead=0;qHead<qTail;++qHead){
		int cur=queqe[qHead];
//			printf("cur%d \n",cur);
		if(cur==V-1) break;
		for(int i=0;i<V;++i){
			if(visited[i]==0 && map[cur][i]!=0){
				queqe[qTail++]=i;
				if(min[cur]>map[cur][i]){//重要 
					min[i]=map[cur][i];
				}else{
					min[i]=min[cur];
				}
				last[i]=cur;
				visited[i]=1;
			}
		}
	}
	if(qHead==qTail) return 0;
	
	build_res();
	
	return min[V-1];
	
}
int maxFlow(){
	int newF=0;
	int maxF=0;
	do{
		newF=bfs();
//		printf("%d ",newF);
		maxF+=newF;
	}while(newF!=0);
	return maxF;
}
int main(){
	inputFile();
	printf("%d ",maxFlow());
	return 0;
}
