#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<cstring>//strcpy
using namespace std;

typedef struct node *pointer;
struct node{
	char data[3];//注意不能用string 
	pointer next;
};
int pos(char c){
	if(c=='H'){
		return 0;
	}
	if(c=='S'){
		return 1;
	}
	if(c=='D'){
		return 2;
	}
	if(c=='C'){
		return 3;
	}
	return NULL;
}
node *newNode(){
	node *p = (node *)malloc(sizeof(node));
	return p;
}

pointer head[4];
pointer rear[4];
void inputFile(){
	ifstream infile("input1.txt");
	char c;
	string s;
	while(infile >> c){
		int i=pos(c);
		
		//創一個新點 
		node *p = newNode();
		infile>>s;
		strcpy(p->data,s.c_str());
		p->next=NULL;
//		printf("%c %s\n",c,s.c_str());

		if(head[i]){//not empty
			rear[i]->next = p;
//			cout<<c<<"是有的"<<endl; 
		}
		else{//empty p是第一個點 
			head[i]=p;
//			cout<<head[i]->data<<"是空的"<<endl; 
		}
		rear[i]=p;
	}
}
void outputFile(){
	ofstream outfile("output1.txt");
	char pair[4]={'H','S','D','C'};
	for(int i=0;i<4;++i){
		node *q=head[i];
		outfile<<pair[i]<<" ";
		while(q!=NULL){
			outfile<<q->data<<" ";
			q=q->next;
		}
		outfile<<endl;
	}
	outfile.close();
}
void print_to_cmd(){
	char pair[4]={'H','S','D','C'};
	for(int i=0;i<4;++i){
		node *q=head[i];
		cout<<pair[i]<<" ";
		while(q!=NULL){
			cout<<q->data<<" ";
			q=q->next;
		}
		cout<<endl;
	}
	
}
int main(){
	inputFile();
	outputFile();
	print_to_cmd();
	return 0;
}
