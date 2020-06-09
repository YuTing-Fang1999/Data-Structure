#include<iostream>
#include <fstream>
#include<stack>
using namespace std;

#define N 10//東西有10件

int W;//最大承重量

int item[99999] = { 0 }; //最大承重量 

int weight[N + 1];//物品的重量

void readFile(){
	ifstream infile("input3.txt");  //將測資檔名放在程式碼中
	infile >> W;
    for (int i=1;i<=10;i++){
      	infile >> weight[i];
//      	cout << weight[i] << endl ;
   	}
}

void bag() {
//w: 背包重量 
//weight[i]: 第i個物品重量 
//item[w]: 最後一個裝滿重量 w 的物品重量 
	for (int i = 1; i <= N; i++) {
//		cout<<i<<"要裝的體重"<<weight[i]<<endl;
		for (int w = 1; w <= W; w++) {
			//如果不能裝入 
			if(weight[i] > W) break;
			//直接填滿目前的空背包 w 
			if ((item[w] == 0) && (weight[i] == w)) {
				item[w] = i;
			}
			//如果此重w的背包可累裝且還有空間裝入且只裝一次 
			else if((item[w] > 0) && (item[w + weight[i]]==0) 
						&& ((w + weight[i])<=W) && (item[w] != i)){
				item[w + weight[i]] = i;
			}
//			if(item[w])
//				cout<<w<<"  "<<item[w]<<endl;
		}
	}	
}
stack<int> searhForStack(){
	int w=W;
	while(item[w]==0){
		w--;
	}
	int maxW=w;
	stack<int> items;/******使用stack******/ 
	while(item[w]!=0){
		items.push(weight[item[w]]);
		w=w-weight[item[w]];
	}
	items.push(maxW);
	return items;
}
void outputFile(){
	ofstream outfile("output3.txt");
	stack<int> s = searhForStack();/******使用stack******/
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
	bag();
	outputFile();
	stack<int> s = searhForStack();/******使用stack******/
	cout<<s.top()<<endl;
	s.pop();
	while(!s.empty()){
		cout<<s.top()<<" ";
		s.pop();
	}
	return 0;
}
