#include<iostream>
template<class Type, int MaxSize>
class Stack{
	//variables you need.
private:
	Type sta[MaxSize];
	int max;
	int now;
public:
	Stack(); //constructor of class Stack.
	void push(Type);//push function.
	Type pop();	//pop function.
	bool empty();	//return true if there has nothing in Stack.
	bool full();	//return true if Stack is full.
	void dump();	//print the items of Stack.
};

template<class Type, int MaxSize>
Stack<Type,MaxSize>::Stack(){
	max=MaxSize;
	now=0;
};

template<class Type, int MaxSize>
void Stack<Type,MaxSize>::push(Type in){
	if(now==max)std::cout<<"Stack is already full."<<std::endl;
	else{
		sta[now]=in;
		now++;
	}
}

template<class Type, int MaxSize>
Type Stack<Type,MaxSize>::pop(){
	if(now==0){
		std::cout<<"Stack is empty now."<<std::endl;
		return 0;
	}
	now--;
	return sta[now];
}

template<class Type, int MaxSize>
bool Stack<Type,MaxSize>::empty(){
	return now==0?true:false;
}

template<class Type, int MaxSize>
bool Stack<Type,MaxSize>::full(){
	return now==max?true:false;
}

template<class Type, int MaxSize>
void Stack<Type,MaxSize>::dump(){
	for(int a=now-1;a>=0;a--)std::cout<<sta[a]<<" ";
	std::cout<<std::endl;
}
