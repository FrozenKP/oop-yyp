#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

void sort(vector<int> &arr){
}

int main(){
    int i,j;	
    vector<int> num;
    while(cin>>j)
        num.push_back(j);

    sort(num);
    std::cout<<"Sorted result: ";
    for(i=0;i<num.size();i++){
        std::cout<<num[i]<<" ";
    }
    std::cout<<std::endl;
    return 0;
}
