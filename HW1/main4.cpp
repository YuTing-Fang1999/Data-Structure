#include<iostream>
#include<fstream>
#include<stack>/*****�ϥ�stack*****/ 
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
void sortByCp(){//�Ѥj�ƨ�p 
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
//	printf("�ƦC\n"); 
//	for(int i=0;i<10;++i){
//		printf("v=%3d, w=%3d, cp=%f\n",items[i].v,items[i].w,items[i].cp);
//	}
}
stack<int> putInBag(){
	stack<int> s;/*****�ϥ�stack*****/ 
	int a=W;//�Ѿl�Ŷ�
	int maxV=0;//�̤j���� 
	int i=0;//���~�s�� 
	while(a){
//		printf("a=%d\n",a);
		if(items[i].w<=a){
			maxV+=(int)items[i].cp*items[i].w;
			a-=items[i].w;
			s.push(items[i].w);/*****�ϥ�stack*****/ 
		}else{
			maxV+=(int)items[i].cp*a;
			s.push(items[i].w);/*****�ϥ�stack*****/ 
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
	stack<int> s=putInBag();/*****�ϥ�stack*****/ 
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
	stack<int> s=putInBag();/*****�ϥ�stack*****/ 
	cout<<s.top()<<endl;
	s.pop();
	while(!s.empty()){
		printf("%d ",s.top());
		s.pop();
	}
	return 0;
}
  
