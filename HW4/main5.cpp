#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<iostream>
#include<vector>
using namespace std;

int DFN[105]; //記錄在做dfs時節點的搜索次序
int low[105]; //記錄節點能夠找到的最先訪問的祖先的記號
int take[105];
int count=1; //標記訪問次序，時間戳
int stack[105]; //stack
int top=-1;
int flag[105]; //標記節點是否已經在stack中
int number=0; //通圖的數量
int length; //圖的長度 
int map[105][105];
int V=0;
int N=0; //點的個數 
vector<int> list; // 排列組合的陣列 
int orign=0;
bool findout=false;

void inputFile(){
	FILE *infile=fopen("input5.txt","r");
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
			map[i][j++]=atoi(pch);
			pch=strtok(NULL," ");
		};
		V=j;//第一行先記有幾個 
		
		while(fgets(line,102,infile)!=NULL){
			++i;
			if(line[strlen(line)-1]=='\n')
				line[strlen(line)-1]='\0';
				
			int j=-1;
			pch=strtok(line," ");
			while(pch!=NULL){
				map[i][++j]=atoi(pch);
				pch=strtok(NULL," ");
			};
		}

	}else{
		printf("無法開啟"); 
	}
// map	
//	for(int i=0;i<V;++i){
//		for(int j=0;j<V;++j){
//			printf("%d ",map[i][j]);
//		}
//		printf("%\n");
//	}
}

void outputFile(){
	FILE *outfile=fopen("output5.txt","w");
	if(findout){
		for(int i=0;i<N;++i)
		{
			fprintf(outfile,"%d ",list[i]+1);
		}
	}else{
		fprintf(outfile,"0");
	}
	
	fclose(outfile);
}

void tarjan(int u){
	
	if(take[u]==1){ 
//		printf("跳過%d\n",u+1); 
		return;
	}// 跳過
	
	DFN[u]=low[u]=count++; // 初始化為深度優先順序 
	stack[++top]=u;// 放入stack 
	flag[u]=1; // 標記為已經在stack
	
	for(int v=0;v<length;v++){// 這邊也要注意take能不能走 
		if(map[u][v] && take[v]!=1){ // 如果u->v有路可走 
			// 如果v沒有被拜訪過 
			if(!DFN[v]){ 
				tarjan(v); // dfs遞歸訪問，直到走到底，因為要從最底開始更新low 
				if(low[v]<low[u]) // 走到底回溯時從這裡繼續開始 
					low[u]=low[v]; 
			}
			// 如果訪問過且有在stack裡，就表示不只有一條路能到 
			else{ 		 
				if( DFN[v]<low[u] && flag[v] ) // 如果子節點的優先度先於父節點 
					low[u]=DFN[v];
			} 
		}
	}
	
	//dfn走到底了 
	//dfs回溯的時候，如果發現DFN和low相同的節點(表示是根節點) 
	//就可以把這個節點之後的節點全部取出，構成連通圖
	//如果不是就繼續回溯，直到到根節點 
	if(DFN[u]==low[u]){
//		printf("連通圖: ");
		int j=0;
		number++; //記錄連通圖的數量
		do{
			j=stack[top--]; //依次取出，直到u
//			cout<<j+1<<" ";
			flag[j]=0; //設置為不在stack中
		}while(j!=u);
//		cout<<endl;
	}
}
int maxComponent(){
	memset(DFN,0,sizeof(DFN));                  //初始化
    memset(low,0,sizeof(low));
    memset(flag,0,sizeof(flag));
	
	number=0;
    length=V;
    for(int i=0;i<V;++i){
    	if(DFN[i]==0){
		    tarjan(i);
		}
	}
	return number;
}
void comb(int m,int n){
	
	for(int i=0;i<n;++i)
	{
		list.push_back(i);
	}
	--list[n-1];
	do{
		for(int i=n-1;i>=0;--i)
		{
			if(list[i]<m+i-n)
			{
				++list[i];
				for(int j=i+1;j<n;++j)
				{
				     list[j]=list[i]+j-i;
				}
				break;
			}
		}
		
		memset(take,0,sizeof(take));
		for(int i=0;i<n;++i)
		{
//			cout<<list[i]+1<<'\t';
			take[list[i]]=1;
		}
//		cout<<endl;
		maxComponent();
		if(orign+n==number){
			findout=true;
			printf("找到了!移除%d個點  ",n);
			N=n; 
			for(int i=0;i<n;++i)
			{
				cout<<list[i]+1<<'\t';
			}
			cout<<endl;
			return;
		}
//		cout<<endl;
	}while(list[0]<(m-n));
}
int main(){
	inputFile();
	memset(take,0,sizeof(take));
	orign=maxComponent();
	for(int i=1;i<V;++i){
//		cout<<endl;
		list.clear();
		comb(V,i);
		if(findout) break;
	}
	if(!findout) printf("0");
	outputFile();
    return 0;
}
