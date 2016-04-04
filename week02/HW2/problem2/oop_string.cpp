#include"oop_string.h"
#include<algorithm>
#include<functional>
#include<iostream>

namespace oop{
  void reverse( std::string &str){
	//int length=str.length();
	/*std::string tmp;
	int a,b;
	for(int b=0;str[b]!='\0';b++){
		tmp[b]=str[b];
		std::cout<<b<<" ";
	}
	std::cout<<"\n";
	for(int a=0;tmp[a]!='\0';a++){
		str[a]=tmp[b-a-1];
		std::cout<<a<<" ";
	}
	std::cout<<"\n";*/
	int length;
	for(length=0;str[length]!='\0';length++);
	std::reverse(str.begin(),str.end());
 }

  void toUpperCase( std::string &str){
  	for(int a=str.length()-1;a>=0;a--){
		if(str[a]>='a'&&str[a]<='z'){
			str[a]=str[a]-'a'+'A';
		}
	}
  }
  
  void trim( std::string &str){
  	for(int a=str.length()-1;a>=0;a--){
		if(str[a]==' '){
			str.pop_back();
		}else break;
	}
	for(int a=0;a<str.length();a++){
		if(str[a]==' '){
			for(int b=a+1;b<str.length();b++){
				str[b-1]=str[b];
			}
			str.pop_back();
			a--;
		}else break;
	}
 }	
};

