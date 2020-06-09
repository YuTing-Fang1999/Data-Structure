#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<iostream>
#include<vector>
using namespace std;

int DFN[105]; //�O���b��dfs�ɸ`�I���j������
int low[105]; //�O���`�I�����쪺�̥��X�ݪ��������O��
int take[105];
int count=1; //�аO�X�ݦ��ǡA�ɶ��W
int stack[105]; //stack
int top=-1;
int flag[105]; //�аO�`�I�O�_�w�g�bstack��
int number=0; //�q�Ϫ��ƶq
int length; //�Ϫ����� 
int map[105][105];
int V=0;
int N=0; //�I���Ӽ� 
vector<int> list; // �ƦC�զX���}�C 
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
		V=j;//�Ĥ@����O���X�� 
		
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
		printf("�L�k�}��"); 
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
//		printf("���L%d\n",u+1); 
		return;
	}// ���L
	
	DFN[u]=low[u]=count++; // ��l�Ƭ��`���u������ 
	stack[++top]=u;// ��Jstack 
	flag[u]=1; // �аO���w�g�bstack
	
	for(int v=0;v<length;v++){// �o��]�n�`�Ntake�ण�ਫ 
		if(map[u][v] && take[v]!=1){ // �p�Gu->v�����i�� 
			// �p�Gv�S���Q���X�L 
			if(!DFN[v]){ 
				tarjan(v); // dfs���k�X�ݡA���쨫�쩳�A�]���n�q�̩��}�l��slow 
				if(low[v]<low[u]) // ���쩳�^���ɱq�o���~��}�l 
					low[u]=low[v]; 
			}
			// �p�G�X�ݹL�B���bstack�̡A�N��ܤ��u���@������� 
			else{ 		 
				if( DFN[v]<low[u] && flag[v] ) // �p�G�l�`�I���u���ץ�����`�I 
					low[u]=DFN[v];
			} 
		}
	}
	
	//dfn���쩳�F 
	//dfs�^�����ɭԡA�p�G�o�{DFN�Mlow�ۦP���`�I(��ܬO�ڸ`�I) 
	//�N�i�H��o�Ӹ`�I���᪺�`�I�������X�A�c���s�q��
	//�p�G���O�N�~��^���A�����ڸ`�I 
	if(DFN[u]==low[u]){
//		printf("�s�q��: ");
		int j=0;
		number++; //�O���s�q�Ϫ��ƶq
		do{
			j=stack[top--]; //�̦����X�A����u
//			cout<<j+1<<" ";
			flag[j]=0; //�]�m�����bstack��
		}while(j!=u);
//		cout<<endl;
	}
}
int maxComponent(){
	memset(DFN,0,sizeof(DFN));                  //��l��
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
			printf("���F!����%d���I  ",n);
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
