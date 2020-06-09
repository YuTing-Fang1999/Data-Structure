#include<iostream>
#include<fstream>
using namespace std;
typedef struct{
	int d=0;//�ثe�̵u�Z�� 
//	int p=0;//�g�ѭ����I��o��(�W�@���I) 
	bool s=false;//���S���⧹���I���̵u���| 
}Dis;

const int Nodenum = 7;//�I���Ӽ� 
const int maxint = 999999;//�N������ 
int C[Nodenum][Nodenum];//���|�v�� 
Dis dis[Nodenum]; //�C���I 

//�L�X�}�CC 
void printC(){	
	for(int i=0;i<7;++i){
		for(int j=0;j<7;++j){
			printf("%7d",C[i][j]);
		}
		cout<<endl;
	}
}

//Ū�� 
void readFile(){ 
	ifstream infile("input5.txt");
	for(int i=0;i<7;++i){
		dis[i].d = C[0][i];//�q�_�I�}�l 
		for(int j=0;j<7;++j){
			infile >> C[i][j];
			if(C[i][j]==0) C[i][j]=maxint;
		}
	}
//	printC();
}

//��X�S�䧹(���bS���X)�B�ثe�����I�̪��I 
int updateD(){
	int tmp = maxint;
	int u = 0;
	// ��X��e�S�䧹���Ij��dist[j]�̤p��(�����I�̪�) 
	for(int j=1; j<Nodenum; ++j)
		if((!dis[j].s) && dis[j].d<tmp)
		{
			u = j;              // u�O�s��e�����I�̪��I
			tmp = dis[j].d;
		}
	dis[u].s = 1;    // ���u�I�w�s�JS���X��(�w�Q�䧹) 
	return u;
}

//���I0��ت��a6
void go(){
	for(int i=1; i<Nodenum; ++i)//��ѤU�����I���̵u���| 
	{
		int u = updateD();//�U�@�ӭn�⪺�I 
		// ��sdist
		for(int j=1; j<Nodenum; ++j)
			if((!dis[j].s) && C[u][j]<maxint) //�p�G�٨S���̵u���|�B�i�H������ 
			{
				int newdist = dis[u].d + C[u][j];
				if(newdist < dis[j].d) //�p�G��s�᪺���|���u 
				{
					dis[j].d = newdist;
//					dis[j].p = u;
				}
			}
	}
}

//�L�X�}�CD�MP 
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
