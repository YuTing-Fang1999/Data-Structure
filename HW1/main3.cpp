#include<iostream>
#include <fstream>
#include<stack>
using namespace std;

#define N 10//�F�観10��

int W;//�̤j�ӭ��q

int item[99999] = { 0 }; //�̤j�ӭ��q 

int weight[N + 1];//���~�����q

void readFile(){
	ifstream infile("input3.txt");  //�N�����ɦW��b�{���X��
	infile >> W;
    for (int i=1;i<=10;i++){
      	infile >> weight[i];
//      	cout << weight[i] << endl ;
   	}
}

void bag() {
//w: �I�]���q 
//weight[i]: ��i�Ӫ��~���q 
//item[w]: �̫�@�Ӹ˺����q w �����~���q 
	for (int i = 1; i <= N; i++) {
//		cout<<i<<"�n�˪��魫"<<weight[i]<<endl;
		for (int w = 1; w <= W; w++) {
			//�p�G����ˤJ 
			if(weight[i] > W) break;
			//�����񺡥ثe���ŭI�] w 
			if ((item[w] == 0) && (weight[i] == w)) {
				item[w] = i;
			}
			//�p�G����w���I�]�i�ָ˥B�٦��Ŷ��ˤJ�B�u�ˤ@�� 
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
	stack<int> items;/******�ϥ�stack******/ 
	while(item[w]!=0){
		items.push(weight[item[w]]);
		w=w-weight[item[w]];
	}
	items.push(maxW);
	return items;
}
void outputFile(){
	ofstream outfile("output3.txt");
	stack<int> s = searhForStack();/******�ϥ�stack******/
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
	stack<int> s = searhForStack();/******�ϥ�stack******/
	cout<<s.top()<<endl;
	s.pop();
	while(!s.empty()){
		cout<<s.top()<<" ";
		s.pop();
	}
	return 0;
}
