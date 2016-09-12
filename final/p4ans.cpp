#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

void sort(vector<int> &arr){
	int tmp;
	for(int a=0;a<arr.size();a++){
		for(int b=0;b<a;b++){
			if(arr[b]<arr[a]){
				if(arr[b]%2==1&&arr[a]%2==1){
					tmp=arr[b];
					arr[b]=arr[a];
					arr[a]=tmp;
				}else if(arr[b]%2==0&&arr[a]%2==0){
					tmp=arr[b];
					arr[b]=arr[a];
					arr[a]=tmp;
				}else if(arr[b]%2==1&&arr[a]%2==0){
					tmp=arr[b];
					arr[b]=arr[a];
					arr[a]=tmp;
				}
			}else{
				if(arr[b]%2==1&&arr[a]%2==0){
					tmp=arr[b];
					arr[b]=arr[a];
					arr[a]=tmp;
				}
			}
		}
	}
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
