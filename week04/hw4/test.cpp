#include"BigNum.h"
#include"iostream"
#include"string"

using namespace std;

int main(){
	string c="-12345678",d="-7777";
	BigNum a(c),b(d),e;
	cout<<a<<endl;
	cout<<b<<endl;
	cout<<a+b<<endl;
	cout<<a-b<<endl;
	cin >> e;
	cout<< a+e <<endl;
	cout<<a+151684<<endl;
	cout<<a-1289198<<endl;
	cout<<1289198-a<<endl;
	cout<<a++<<endl;
	cout<<++a<<endl;
	cout<<a<<endl;
	cout<<a*e<<endl;
	return 0;
}
