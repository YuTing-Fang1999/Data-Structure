#include<iostream>
#include<fstream>
using namespace std;
int x1,x2,x3,x4;
void readFile(){
	ifstream infile("input1.txt");
	infile >> x1;
	infile >> x2;
	infile >> x3;
	infile >> x4;
	infile.close();
}
void outputFile(){
	ofstream outfile("output1.txt");
	outfile << 7*7*7*x4+7*7*x3+7*x2+x1+1;
	outfile.close();
}
int main(){
	readFile();
	outputFile();
	printf("%d",7*7*7*x4+7*7*x3+7*x2+x1+1);
	return 0;
}
