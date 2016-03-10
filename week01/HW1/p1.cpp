#include"cstdio"
#include"cstdlib"
#include"stack"

using namespace std;

int main(){
	stack<int> in;
	int tmp;
	char operate;
	bool end=1;
	while(end){
		switch(getchar()){
			case 'i':
				scanf("%d",&tmp);
				in.push(tmp);
				break;
			case '+':
				tmp=in.top();
				in.pop();
				tmp+=in.top();
				in.pop();
				in.push(tmp);
				break;
			case '-':
				tmp=in.top();
				in.pop();
				tmp=in.top()/tmp;
				in.pop();
				in.push(tmp);
				break;
			case '*':
				tmp=in.top();
				in.pop();
				tmp*=in.top();
				in.pop();
				in.push(tmp);
				break;
			case '/':
				tmp=in.top();
				in.pop();
				tmp=in.top()/tmp;
				in.pop();
				in.push(tmp);
				break;
			case ' ':
				break;
			default:
				printf("%d\n",in.top());
				end=0;
				break;
		}
		//printf("%d\n",in.top());
	}
	return 0;
}
