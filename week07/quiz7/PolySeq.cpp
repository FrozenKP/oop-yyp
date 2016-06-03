#include"PolySeq.hpp"

PolySeq::PolySeq(int n){
	term=n;
	ptr=new int[n];
}

PolySeq::PolySeq( int n, int arr[]){
	term=n;
	ptr=new int[n];
	for(int a=0;a<n;a++)ptr[a]=arr[a];
}

PolySeq::~PolySeq(){
	delete ptr;
}

PolySeq PolySeq::Add(const PolySeq &in){
	const PolySeq &max=term>in.term?*this:in;
	const PolySeq &min=term>in.term?in:*this;
	int oa[max.term],dt=max.term-min.term;
	for(int a=0;a<max.term;a++){
		if(a<dt)oa[a]=max.ptr[a];
		else oa[a]=max.ptr[a]+min.ptr[a-dt];
	}
	PolySeq out(max.term,oa);
	return out;
}

PolySeq PolySeq::Multiply(const PolySeq &in){
	int oa[in.term+term];
	for(int a=in.term+term-1;a>=0;a--)oa[a]=0;
	for(int a=0;a<in.term;a++){
		for(int b=0;b<in.term;b++){
			oa[in.term+term-(in.term-a-1)-(term-b-1)-1]+=in.ptr[a]*ptr[b];
		}
	}
	PolySeq out(in.term+term,oa);
	return out;
}
PolySeq PolySeq::Derivative(){
	int oa[term-1];
	for(int a=term-1;a>=0;a--)oa[a]=0;
	for(int a=0;a<term-1;a++){
		oa[a]=ptr[a]*(term-a-1);
	}
	PolySeq out(term-1,oa);
	return out;
}

double  PolySeq::Integral(int form ,int end){
	double out=0;
	int tmpf,tmpe;
	for(int a=0;a<term;a++){
		tmpf=1;
		tmpe=1;
		for(int b=0;b<term-a;b++){
			tmpf*=form;
			tmpe*=end;
		}
		//cout<<tmpf<<" "<<tmpe<<" ";
		out+=(ptr[a]*(tmpe-tmpf))/term-a;
	}
	return out;
}

void PolySeq::Print(){
	int check=1;
	for(int a=0;a<term;a++){
		//cout<<"in ";
		if(check&&ptr[a]==0)continue;
		check=0;
		cout<<ptr[a]<<" "; 	
	}
	cout<<"\n";
}
