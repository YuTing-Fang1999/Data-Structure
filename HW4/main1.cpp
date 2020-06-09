#include <iostream> 
#include <string.h> //memset
#include<cstring>
#include<stdlib.h>
#define INF 99999;

int graph[105][105];
int queqe[105];
int qTail,qHead;
int last[105];//紀錄前一個點 
int min[105];//紀錄最小的那個邊 
int visited[105];
int V=0;

void inputFile(){
	FILE *infile=fopen("input1.txt","r");
	if(infile!=NULL){
		char *pch;
		char line[105];
		while(fgets(line,102,infile)!=NULL){
			if(line[strlen(line)-1]=='\n')
				line[strlen(line)-1]='\0';
			int i=-1;
			pch=strtok(line," ");
			while(pch!=NULL){
				graph[V][++i]=atoi(pch);
				pch=strtok(NULL," ");
			}
			++V;
		}

	}else{
		printf("無法開啟"); 
	}
}
void build_res(int t){//建剩餘網路 
	int flow=min[t];
	int cur=t;
	
	//從終點走到起點
	while(last[cur]!=-1){
		graph[last[cur]][cur]-=flow;
		graph[cur][last[cur]]+=flow;
		cur=last[cur];
	}
}
int bfs(int s,int t){
	//初始化 
	memset(visited,0,sizeof(visited));
	min[s]=INF;
	last[s]=-1;
	visited[s]=1;
	
	//將s放入queqe
	queqe[0]=s;
	qTail=1;
	
	for(qHead=0;qHead<qTail;++qHead){//把東西從queqe一個個拿出來 
		int cur=queqe[qHead];//目前的點 

		if(cur==t) break;//走到終點了 
		
		for(int i=0;i<V;++i){//遍歷所有node
		
			//如果沒走過且可走到
			//因為如果走過就不用找上一個點是誰了(因為已經找到了)
			if(visited[i]==0 && graph[cur][i]!=0){
				
				queqe[qTail++]=i;//把與cur連接的點放入queqe，要先放再++ 
				
				//記錄到i這個點的最小edge
				if(min[cur]>graph[cur][i]){
					min[i]=graph[cur][i];
				}else{ 
					min[i]=min[cur];
				}
				
				visited[i]=1;
				
				//記錄前一個點才能由終點往前推 
				last[i]=cur; 

			} 
		}
	}
	
//	如果走到底都還沒走到t; 
	if(qHead==qTail) return 0;
	
	build_res(t);

	return min[t];
}
int findMaxFlow(int s,int t){
	int newFlow=0;
	int maxFlow=0;
	do{
		newFlow=bfs(s,t);
		maxFlow+=newFlow;
	}while(newFlow!=0);
	
	return maxFlow;
}
void outputFile(int max){
	FILE *outfile=fopen("output1.txt","w");
	fprintf(outfile,"%d",max);
	fclose(outfile);
}
int main() 
{  
	inputFile();
	int max=findMaxFlow(0, V-1);//注意終點是V-1，不然永遠走不到
	outputFile(max); 
	printf("%d",max); 
	return 0; 
} 

