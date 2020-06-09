#include<iostream>
#include<fstream>
using namespace std;
typedef struct{
	int d=0;//目前最短距離 
//	int p=0;//經由哪個點到這裡(上一個點) 
	bool s=false;//有沒有算完此點的最短路徑 
}Dis;

const int Nodenum = 7;//點的個數 
const int maxint = 999999;//代表走不到 
int C[Nodenum][Nodenum];//路徑權重 
Dis dis[Nodenum]; //七個點 

//印出陣列C 
void printC(){	
	for(int i=0;i<7;++i){
		for(int j=0;j<7;++j){
			printf("%7d",C[i][j]);
		}
		cout<<endl;
	}
}

//讀檔 
void readFile(){ 
	ifstream infile("input5.txt");
	for(int i=0;i<7;++i){
		dis[i].d = C[0][i];//從起點開始 
		for(int j=0;j<7;++j){
			infile >> C[i][j];
			if(C[i][j]==0) C[i][j]=maxint;
		}
	}
//	printC();
}

//找出沒找完(不在S集合)且目前離原點最近的點 
int updateD(){
	int tmp = maxint;
	int u = 0;
	// 找出當前沒找完的點j的dist[j]最小值(離原點最近) 
	for(int j=1; j<Nodenum; ++j)
		if((!dis[j].s) && dis[j].d<tmp)
		{
			u = j;              // u保存當前離原點最近的點
			tmp = dis[j].d;
		}
	dis[u].s = 1;    // 表示u點已存入S集合中(已被找完) 
	return u;
}

//原點0到目的地6
void go(){
	for(int i=1; i<Nodenum; ++i)//找剩下六個點的最短路徑 
	{
		int u = updateD();//下一個要算的點 
		// 更新dist
		for(int j=1; j<Nodenum; ++j)
			if((!dis[j].s) && C[u][j]<maxint) //如果還沒找到最短路徑且可以走的話 
			{
				int newdist = dis[u].d + C[u][j];
				if(newdist < dis[j].d) //如果更新後的路徑較短 
				{
					dis[j].d = newdist;
//					dis[j].p = u;
				}
			}
	}
}

//印出陣列D和P 
void printDP(){
	for(int i=0;i<Nodenum;++i){
		printf("%2d ",dis[i].d); 
	}
	printf("\n"); 
//	for(int i=0;i<Nodenum;++i){
//		printf("%2d",dis[i].p); 
//	}
//	printf("\n"); 
}
void outputFile(){
	ofstream outfile("output5.txt");
	if(dis[Nodenum-1].d==maxint)
		outfile<<0<<endl;
	else
		outfile<<dis[Nodenum-1].d<<endl;
	outfile<<"O(n^2)";
	outfile.close();
}
int main(){
	readFile(); //cn^2
	go(); //cn^2
	outputFile();
//	printDP();
	if(dis[Nodenum-1].d==maxint)
		cout<<0<<endl;
	else
		cout<<dis[Nodenum-1].d<<endl;
	cout<<"O(n^2)"; //cn^2+cn^2=O(n^2)
	return 0;
}
