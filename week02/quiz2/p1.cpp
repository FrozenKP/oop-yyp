#include<iostream>
#include<stack>
#include<string>
int main()
{
	std::string s;
	std::stack<char> p; 
	while(std::cin>>s)
	{
	     //fill you code  
	   	int check=1;
		for(int a=0;a<(s.length()/2);a++)p.push(s[a]);
		for(int a=s.length()%2==1?s.length()/2+1:s.length()/2;a<s.length();a++){
			if(p.top()!=s[a]){
		 		//if the string is not a palindrome 
				std::cout<<"The string is not a Palindrome"<<std::endl;
		 		check=0;
				break;
			}
			p.pop();
		}
		//if the string is not a palindrome
		if(check)
			std::cout<<"The string is a Palindrome"<<std::endl;
		
		while(!p.empty())p.pop();
	}
	
	
	return 0;
}
