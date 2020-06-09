#include<iostream>
#include<fstream>
using namespace std;
int r[4];
int x[4];
void readFile(){
	ifstream infile("input2.txt");
	
	infile >> x[0];
	infile >> x[1];
	infile >> x[2];
	infile >> x[3];
	
	infile >> r[0];
	infile >> r[1];
	infile >> r[2];
	infile >> r[3];
}
void outputFile(){
	ofstream outfile("output2.txt");
	outfile << r[1]*r[2]*r[3]*x[0]+r[2]*r[3]*x[1]+r[3]*x[2]+x[3]+1;
	outfile.close();
}
int main(){
	readFile();
	outputFile();
	printf("%d",r[1]*r[2]*r[3]*x[0]+r[2]*r[3]*x[1]+r[3]*x[2]+x[3]+1);
	return 0;
}
