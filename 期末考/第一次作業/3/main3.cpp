#include<stdio.h>
#include<stdlib.h>
#include<cstring>
int map[9][9];
int visited[9]={0};
int dis[9];
int queqe[100];//�ϥ�queqe 
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
				queqe[qRear++]=atoi(pch);//��Jqueqe 
				pch=strtok(NULL," ");
			}
		}
	}else{
		printf("�L�k�}��");
	}
}
int next(){//���U�@�ӳ̪��I 
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
	//�qqueqe��Jmap
	for(int i=0;i<7;++i){
		for(int j=0;j<7;++j){
			map[i][j]=queqe[qHead++];//�qqueqe���X
			if(map[i][j]==0) map[i][j]=maxInt;//��ܨ�����  
		}
	}
	//��l�ƶZ�� 
	for(int i=0;i<7;++i){
		dis[i]=map[0][i];
	}
	for(int i=0;i<7;++i){//�M���Ҧ��I 
		int u=next();
		for(int j=0;j<7;++j){//��s�Ҧ�dis 
			if(dis[j]>dis[u]+map[u][j]){
				dis[j]=dis[u]+map[u][j];
			}
		}
	}
	if(dis[6]==maxInt) printf("%d",0);
	else printf("%d",dis[6]);
	
	return 0;
}
