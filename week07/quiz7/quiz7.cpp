#include<iostream>
#include "PolySeq.hpp" 
using namespace std ;

int main()
{
	int n1,n2,x1,x2; cin >> n1;
	int *c1=new int[n1];
	for(int i=0;i<n1;i++){
	cin >> c1[i];
	}
	cin >> n2;
	int *c2=new int[n2];
	 for(int i=0;i<n2;i++){
	cin >> c2[i];
	}

	PolySeq P1(n1, c1); 
	PolySeq P2(n2, c2);
	PolySeq P3=P1.Add(P2); 
	P3.Print();
	PolySeq P4=P1.Multiply(P2);
	P4.Print();
	PolySeq P5=P1.Derivative();
	P5.Print();
	cout<<P2.Integral(2,3)<<endl;
	delete [ ]c1;
	delete [ ]c2;
	
	return 0;
}





