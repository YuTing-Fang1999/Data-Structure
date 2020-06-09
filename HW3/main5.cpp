// 創一個窮舉的陣列
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<math.h>
#include<vector>
using namespace std;
int nLeaf[105];
int Leaf[105];
int n1=0;
int n2=0;

void inputFile(){
	FILE *infile=fopen("input5.txt","r");
	if(infile!=NULL){
		char line[110];
		char *pch;
		fgets(line,105,infile);
		if(line[strlen(line)-1]=='\n') line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch!=NULL){
			nLeaf[++n1]=atoi(pch);
			pch=strtok(NULL," ");
		}
		fgets(line,105,infile);
		if(line[strlen(line)-1]=='\n') line[strlen(line)-1]='\0';
		pch=strtok(line," ");
		while(pch!=NULL){
			Leaf[++n2]=atoi(pch);
			pch=strtok(NULL," ");
		}
	}
	else{
		printf("無法開啟");
	}
}
void sort(int arr[],int n){//由大排到小 
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			if(arr[i]<arr[j]){
				int t=arr[i];
				arr[i]=arr[j];
				arr[j]=t;
			}
		}
	}
}

int f(){
	int min=0;
	int w=0;
	for(int j=0;j<n1;++j){//算nL 
		w=floor(log2(j+1))+1;
		min+=nLeaf[j+1]*w;
	}
	for(int j=0;j<n2;++j){//算L 
		w=floor(log2(n1+j+1))+1;
		min+=Leaf[j+1]*w;
	}
	return min;
}
int f3(){
	int nLP[2][3]={{1,2,4},{1,2,3}};
	int LP[2][4]={{3,5,8,9},{4,5,6,7}};
	int min=99999;
	for(int i=0;i<2;++i){//總共兩種tree 
		int s=0;
		int w=0;
		for(int j=0;j<n1;++j){//算nL 
			w=floor(log2(nLP[i][j]))+1;
//			printf("w=%d\n",w);
//			printf("nLeaf[j+1]=%d\n",nLeaf[j+1]);
			s+=nLeaf[j+1]*w;
		}
		for(int j=0;j<n2;++j){//算L 
			w=floor(log2(LP[i][j]))+1;
//			printf("w=%d\n",w);
//			printf("Leaf[j+1]=%d\n",Leaf[j+1]);
			s+=Leaf[j+1]*w;
		}
  		if(s<min) {
  			min=s;
//  			printf("%d\n",i);
		}
	}
	return min;
}
int f4(){
	int nLP[3][4]={{1,2,4,8},{1,2,4,5},{1,2,3,4}};
	int LP[3][5]={{3,5,9,16,17},{3,8,9,10,11},{5,6,7,8,9}};
	int min=99999;
	for(int i=0;i<3;++i){//總共3種tree 
		int s=0;
		int w=0;
		for(int j=0;j<n1;++j){//算nL 
			w=floor(log2(nLP[i][j]))+1;
//			printf("w=%d\n",w);
//			printf("nLeaf[j+1]=%d\n",nLeaf[j+1]);
			s+=nLeaf[j+1]*w;
		}
		for(int j=0;j<n2;++j){//算L 
			w=floor(log2(LP[i][j]))+1;
//			printf("w=%d\n",w);
//			printf("Leaf[j+1]=%d\n",Leaf[j+1]);
			s+=Leaf[j+1]*w;
		}
  		if(s<min) {
  			min=s;
//  			printf("%d\n",i);
		}
	}
	return min;
}
int f5(){
	int nLP[5][5]={{1,2,4,8,16},{1,2,4,8,9},{1,2,4,5,8},{1,2,3,4,8},{1,2,3,4,5}};
	int LP[5][6]={{3,5,9,17,32,33},{3,5,16,17,18,19},{3,9,10,11,16,17},
					{5,6,7,9,16,17},{6,7,8,9,10,11}};
	int min=99999;
	for(int i=0;i<5;++i){//總共5種tree 
		int s=0;
		int w=0;
		for(int j=0;j<n1;++j){//算nL 
			w=floor(log2(nLP[i][j]))+1;
			s+=nLeaf[j+1]*w;
		}
		for(int j=0;j<n2;++j){//算L 
			w=floor(log2(LP[i][j]))+1;
			s+=Leaf[j+1]*w;
		}
  		if(s<min) min=s;
	}
	return min;
}
int f6(){
	int nLP[11][6]={{1,2,4,8,16,32},{1,2,4,8,16,17},{1,2,4,8,9,16},{1,2,4,5,8,16},
	{1,2,3,4,8,16},{1,2,4,5,8,9},{1,2,3,4,8,9},{1,2,3,4,5,8},{1,2,4,5,8,11},
	{1,2,3,4,7,8},{1,2,3,4,5,6}};
	
	int LP[11][7]={{3,5,9,17,33,64,65},{3,5,9,32,33,34,35},{3,5,17,18,19,32,33},
	{3,9,10,11,17,32,33},{5,6,7,9,17,32,33},{3,10,11,16,17,18,19},{5,6,7,16,17,18,19},
	{6,7,9,10,11,16,17},{3,9,10,16,17,22,23},{5,6,9,14,15,16,17},{7,8,9,10,11,12,13}};
	
	int min=99999;
	for(int i=0;i<11;++i){//總共11種tree 
		int s=0;
		int w=0;
		for(int j=0;j<n1;++j){//算nL 
			w=floor(log2(nLP[i][j]))+1;
			s+=nLeaf[j+1]*w;
		}
		for(int j=0;j<n2;++j){//算L 
			w=floor(log2(LP[i][j]))+1;
			s+=Leaf[j+1]*w;
		}
  		if(s<min) min=s;
	}
	return min;
}
void outputFile(int s){
	FILE *outfile=fopen("output5.txt","w");
	fprintf(outfile,"%d",s);
	fclose(outfile);
}
int main()  
{  
	inputFile();
  	sort(nLeaf,n1);
  	sort(Leaf,n2);
	int s=0;
	if(n1==3) s=f3();
	else if(n1==4) s=f4();
	else if(n1==5) s=f5();
	else if(n1==6) s=f6();
	else s=f();
  	
	printf("%d",s);
	outputFile(s);
    return 0;  
}
