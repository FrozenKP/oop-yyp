#include"iostream"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>  

using namespace std;

int main(){
	vector<int>first;
	vector<int>second;
	vector<int>ans;
	int tmp2;
	string tmp;
	stringstream ss,sss;
	
	getline(cin,tmp);
	ss<<tmp;
	while(ss>>tmp2)first.push_back(tmp2);
	sort(first.begin(),first.end());
	
	getline(cin,tmp);
	sss<<tmp;
	while(sss>>tmp2)second.push_back(tmp2);
	sort(second.begin(),second.end());
	
	while((!first.empty())&&(!second.empty())){
		if(*first.begin()==*second.begin()){
			ans.push_back(*first.begin());
			first.erase(first.begin());
			second.erase(second.begin());
		}else if(*first.begin()>*second.begin())second.erase(second.begin());
		else first.erase(first.begin());
	}
	
	while(!ans.empty()){
		cout<<*ans.begin()<<" ";
		ans.erase(ans.begin());
	}
	cout<<endl;
}
