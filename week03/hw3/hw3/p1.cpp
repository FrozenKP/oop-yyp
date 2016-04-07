#include"iostream"

using namespace std;

int main(){
	int number;
	while(1){
		cin >> number;
		if(cin.eof())break;
		if(cin.fail()){
			cout << "not a number!" << endl;
			cin.clear();
			cin.ignore(256,'\n');	
		}else{
			cout << hex << number << " " << oct << number << endl;
		}
	}
	return 0;
}
