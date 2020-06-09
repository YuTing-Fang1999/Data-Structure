#include<iostream>
#include<fstream>
#include<stack>/*****使用stack*****/ 
#define N 10
using namespace std;
int W=100;
typedef struct{
	int w;
	int v;
	float cp;
}Item; 
typedef struct{
	int w;
	int item;
	int value;
}Bag;

Item items[10];
void readFile(){
	ifstream infile("input4.txt");
	infile >> W;
    for (int i=0;i<10;i++){
      	infile >> items[i].w;
   	}
   	for (int i=0;i<10;i++){
      	infile >> items[i].v;
      	items[i].cp=(float)items[i].v/(float)items[i].w;
//      	printf("v=%3d, w=%3d, cp=%f\n",items[i].v,items[i].w,items[i].cp);
   	}
}
void sortByCp(){//由大排到小 
	Item t;
	for(int i=0;i<10;++i){
		for(int j=i;j<10;++j){
			if(items[i].cp<items[j].cp){
				t=items[i];
				items[i]=items[j];
				items[j]=t;
			}
		}
	}
//	printf("排列\n"); 
//	for(int i=0;i<10;++i){
//		printf("v=%3d, w=%3d, cp=%f\n",items[i].v,items[i].w,items[i].cp);
//	}
}
stack<int> putInBag(){
	stack<int> s;/*****使用stack*****/ 
	int a=W;//剩餘空間
	int maxV=0;//最大價值 
	int i=0;//物品編號 
	while(a){
//		printf("a=%d\n",a);
		if(items[i].w<=a){
			maxV+=(int)items[i].cp*items[i].w;
			a-=items[i].w;
			s.push(items[i].w);/*****使用stack*****/ 
		}else{
			maxV+=(int)items[i].cp*a;
			s.push(items[i].w);/*****使用stack*****/ 
			a=0;
		}
//		printf("v=%d\n",maxV);
		++i;
	} 
	s.push(maxV);
	return s;
}
void outputFile(){
	ofstream outfile("output4.txt");
	stack<int> s=putInBag();/*****使用stack*****/ 
	outfile<<s.top()<<endl;
	s.pop();
	while(!s.empty()){
		outfile<<s.top()<<" ";
		s.pop();
	}
	outfile.close();
}
int main(){
	readFile();
	sortByCp();
	outputFile();
	stack<int> s=putInBag();/*****使用stack*****/ 
	cout<<s.top()<<endl;
	s.pop();
	while(!s.empty()){
		printf("%d ",s.top());
		s.pop();
	}
	return 0;
}
  
