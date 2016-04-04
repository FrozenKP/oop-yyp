#include"cstdio"
#include"cstdlib"
#include"map"
#include"string"
#include"iostream"

using namespace std;

int main(){
	map<string,int>menu;
	map<string,int>::iterator in;
	int amount_m,amount_a,price,sum;
	string name;

	scanf("%d%d",&amount_m,&amount_a);
	for(int a=amount_m;a>0;a--){
		cin >> name >>	price;
		menu[name]=price;
	}
	for(;amount_a>0;amount_a--){
		sum=0;
		cin >> name;
		do{
			in=menu.find(name);
			if(in!=menu.end())sum+=in->second;
			cin >> name;
		}while(name!=".");
		printf("%d\n",sum);
	}
	return 0;
}
