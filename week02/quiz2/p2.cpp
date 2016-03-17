#include "p2.hpp"
#include "iostream"
#include "cstdlib"

namespace oop{
	
	Node* push(Node *top,int n){
		struct Node *in=(struct Node*)malloc(sizeof(struct Node));
		in->num=n;
		in->next=top;
		return in;
	}
    	Node* pop(Node *top){
		struct Node *tmp;
		tmp=top->next;
		free(top);
		return tmp;
	}
    	void print(Node *top ){ 
     //Output specification: top->space->top->space->¡K¡K 
     //std::cout<<top<<" "; //show example
		while(top!=NULL){
			std::cout << top->num << " ";
			top = top->next;
		}
		std::cout << std::endl;
    	} 
}
