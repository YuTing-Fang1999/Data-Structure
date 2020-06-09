#include<iostream>
#include<vector>
using namespace std;
vector<int> list;
void comb(int m,int n);
int main()
{
     int V;
     cin>>V;
     for(int i=1;i<V;++i){
     	list.clear();
     	comb(V,i);
	 }
     
     system("pause");
     return 0;
}
void comb(int m,int n)
{
     
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
          for(int i=0;i<n;++i)
          {
               cout<<list[i]<<'\t';
          }
          cout<<endl;
     }while(list[0]<(m-n));
}
