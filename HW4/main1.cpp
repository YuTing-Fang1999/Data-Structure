#include <iostream> 
#include <string.h> //memset
#include<cstring>
#include<stdlib.h>
#define INF 99999;

int graph[105][105];
int queqe[105];
int qTail,qHead;
int last[105];//�����e�@���I 
int min[105];//�����̤p�������� 
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
		printf("�L�k�}��"); 
	}
}
void build_res(int t){//�سѾl���� 
	int flow=min[t];
	int cur=t;
	
	//�q���I����_�I
	while(last[cur]!=-1){
		graph[last[cur]][cur]-=flow;
		graph[cur][last[cur]]+=flow;
		cur=last[cur];
	}
}
int bfs(int s,int t){
	//��l�� 
	memset(visited,0,sizeof(visited));
	min[s]=INF;
	last[s]=-1;
	visited[s]=1;
	
	//�Ns��Jqueqe
	queqe[0]=s;
	qTail=1;
	
	for(qHead=0;qHead<qTail;++qHead){//��F��qqueqe�@�ӭӮ��X�� 
		int cur=queqe[qHead];//�ثe���I 

		if(cur==t) break;//������I�F 
		
		for(int i=0;i<V;++i){//�M���Ҧ�node
		
			//�p�G�S���L�B�i����
			//�]���p�G���L�N���Χ�W�@���I�O�֤F(�]���w�g���F)
			if(visited[i]==0 && graph[cur][i]!=0){
				
				queqe[qTail++]=i;//��Pcur�s�����I��Jqueqe�A�n����A++ 
				
				//�O����i�o���I���̤pedge
				if(min[cur]>graph[cur][i]){
					min[i]=graph[cur][i];
				}else{ 
					min[i]=min[cur];
				}
				
				visited[i]=1;
				
				//�O���e�@���I�~��Ѳ��I���e�� 
				last[i]=cur; 

			} 
		}
	}
	
//	�p�G���쩳���٨S����t; 
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
	int max=findMaxFlow(0, V-1);//�`�N���I�OV-1�A���M�û�������
	outputFile(max); 
	printf("%d",max); 
	return 0; 
} 

