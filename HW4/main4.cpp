#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<string.h>
struct Node{
	int size;
	int pos;
};
/*最短路徑*/
const int maxint=99999;
int map[100][100];
int visited[100]={0};
int last[100];
int dis[100];
int Nodenum=0;
int tar=0;//目標節點 
/*最短路徑*/
int stack[30][30]={0};//存路徑[Node][stack] 
int top[30];
Node buffer[30][30];//Node buffer
int bufferSize[30];
int qHead[30]={0};
int qTail[30]={0};
//int inNode[30];//是否在Node裡
int deliver[30];//要發packet的Node 
int deliverNum=0;
int packet[30];//要發packet的大小 
int isInTar[30]={0};


void pushStack(int deliver,int path_len){
	stack[deliver][top[deliver]++]=path_len;
}
int popStack(int deliver){
	return stack[deliver][--top[deliver]];
}
bool isInNode(int i){
	if(stack[i][top[i]-1]<0){
//		printf("%d isInNode:%d\n",deliver[i],(-stack[i][top[i]-1]));
		return true;
	} 
	return false;
}
void putBuffer(int i, int packe,int node){
	if((qTail[node]-qHead[node]) == bufferSize[node]){//buffer full 
//		printf("aH=%d, qT=%d\n",qHead[node],qTail[node]);
		top[i]=0;//clearSrack=>done;
		isInTar[i]=1;
		printf("***buffer_%d full,clear stack_%d\n",node,deliver[i]);
	}
	else{//put buffer
		if(node==tar+1){//到達目的地 
			top[i]=0;//clearSrack=>done;
		}
		Node n;
		n.pos=i;
		n.size=packe;
//		printf("i=%d\n",i);
		printf("put deliver=%d in buffer %d\n",deliver[n.pos],node);
		buffer[node][qTail[node]++]=n;
	}
}
void go(int i){
	--stack[i][top[i]-1];
//	printf("%d go %d\n",deliver+1,stack[deliver][top[deliver]-1]);
	//
	if(stack[i][top[i]-1]==0)
		popStack(i);
	if(stack[i][top[i]-1]<0){
		if(-stack[i][top[i]-1]==tar+1){
			printf("Node_%d到達目的地_%d\n",deliver[i],tar+1);
			isInTar[i]=1;
			putBuffer(i, deliver[i], tar+1);
		}
		else//put buffer
			putBuffer(i,packet[i],-stack[i][top[i]-1]);
	}
}
bool isBufferEmpty(int i){
	if(qHead[i]==qTail[i]) return true;
	return false;
}
void goBuffer(){
	for(int node=1;node<=Nodenum;++node){// go all node buffer
		if(node==tar+1) continue;
		if(!isBufferEmpty(node)){
//			printf("node %d is not empty\n",node);
			--buffer[node][qHead[node]].size;
//			printf("node %d time=%d\n",node, buffer[node][qHead[node]].size);
			if(buffer[node][qHead[node]].size==0){
				printf("%d pop from Buffer %d\n",deliver[buffer[node][qHead[node]].pos],node);
				popStack(buffer[node][qHead[node]].pos);
				++qHead[node];
			}
		}
	}
}
bool done(){
	for(int i=0;i<deliverNum;++i){
		if(!isInTar[i]) return false;
	}
	return true;
}
//讀檔 
void inputFile(){ 
	FILE *infile=fopen("input4.txt","r");
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
		Nodenum=j;//第一行先記有幾個 
		while(fgets(line,102,infile)!=NULL){
			++i;
			if(Nodenum==i){//map輸完了 
				//要發packet的節點 => deliver
				if(line[strlen(line)-1]=='\n')
					line[strlen(line)-1]='\0';
				int i=0;
				pch=strtok(line," ");
				while(pch!=NULL){
					deliver[i++]=atoi(pch);
					pch=strtok(NULL," ");
				};
				deliverNum=i;
				//packet的大小 
				fgets(line,102,infile);
				if(line[strlen(line)-1]=='\n')
					line[strlen(line)-1]='\0';
				pch=strtok(line," ");
				i=0;
				while(pch!=NULL){
					packet[i++]=atoi(pch);
					pch=strtok(NULL," ");
				};
				
				//目標節點
				fgets(line,102,infile);
				if(line[strlen(line)-1]=='\n')
					line[strlen(line)-1]='\0';
				pch=strtok(line," ");
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
//		for(int i=0;i<Nodenum;++i){
//			for(int j=0;j<Nodenum;++j){
//				printf("%7d",map[i][j]);
//			}
//			printf("\n");
//		}
	}else{
		printf("無法開啟"); 
	}
}

int next(){//找到下一個最近的點 
	int u=0;
	int d=maxint;
	for(int i=0;i<Nodenum;++i){
		if(visited[i]==0 && dis[i]<d){
			d=dis[i];
			u=i;
		}
	}
	visited[u]=1;
	return u;
}
void findShortestPath(int deliver,int pos){
	//初始化
	memset(last,-1,sizeof(last));
	memset(visited,0,sizeof(last));
//	printf("dis: ");
	for(int i=0;i<Nodenum;++i){
		dis[i]=map[deliver][i];
//		printf("%d ",dis[i]);
	}
//	printf("\n");
	last[deliver]=-1;
	int i=deliver;
	do{//遍歷所有點 
		int u=next();
//		printf("u=%d\n",u);
		for(int j=0;j<Nodenum;++j){//更新所有dis 
			if(dis[j]>dis[u]+map[u][j]){
				dis[j]=dis[u]+map[u][j];
				last[j]=u;
//				printf("%d\n",last[j]);
			}
		}
		i=(i+1)%Nodenum;
	}while(i!=deliver);
	pushStack(pos,-tar-1);
	int cur;
	for(cur=tar;last[cur]!=-1;cur=last[cur]){
//		printf("node=%d \n",last[cur]+1); 
//		printf("%d \n",map[last[cur]][cur]); 
		pushStack(pos,map[last[cur]][cur]);
		pushStack(pos,-last[cur]-1);
	}
//	printf("node=%d \n",tar+1); 
//	printf("%d \n",map[sta][cur]); 
	pushStack(pos,map[deliver][cur]);
//	printf("\n");
}

void outputFile(){
	FILE *outfile=fopen("output4.txt","w");
	for(int i=qHead[tar+1];i<qTail[tar+1];++i){
		fprintf(outfile,"%d ",buffer[tar+1][i]);
	}
	fclose(outfile); 
}
int main(){
	inputFile();
	//初始化buffer size
	for(int i=1;i<30;++i){
		bufferSize[i]=i;
	}
	//print 最短路徑 
	for(int i=0;i<deliverNum;++i){
		printf("sta=%d\n",deliver[i]);
		findShortestPath(deliver[i]-1,i);
		while(top[i]!=0){
			printf("%d ",popStack(i));
		}
		printf("\n");
	}
	//初始化路徑 
	for(int i=0;i<deliverNum;++i){
		findShortestPath(deliver[i]-1,i);
	}
	//模擬packet走法，每while一次代表過一秒 
	while(!done()){
		for(int i=0;i<deliverNum;++i){
			if(!isInTar[i]){
				if(!isInNode(i)){
					go(i);
				}
			}
		}
		goBuffer();
	}
	//print tar buffer
	for(int i=qHead[tar+1];i<qTail[tar+1];++i){
		printf("%d ",buffer[tar+1][i]);
	}
	outputFile();
	return 0;
} 

