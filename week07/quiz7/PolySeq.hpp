#ifndef POLYSEQ
#define POLYSEQ
#include<iostream>
using namespace std;
class PolySeq{
private:
	int term;
	int *ptr;
public :
	PolySeq();
	PolySeq(int n);
	PolySeq( int n, int arr[]); 
        ~PolySeq();
        PolySeq Add(const PolySeq &);
        PolySeq Multiply(const PolySeq &);
        PolySeq Derivative(); 
        double  Integral(int form ,int end);
	void Print();

};

#endif 
