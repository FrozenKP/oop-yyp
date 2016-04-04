#include"cstdio"
#include"cstdlib"
#include"vector"

using namespace std;

int main(){
	vector<int> a,b,ans;
	int a_row,a_col,b_col;
	scanf("%d %d %d",&a_row,&a_col,&b_col);
	//printf("%d %d %d\n",a_row,a_col,b_col);
	
	int tmp,in;
	for(tmp=a_row*a_col;tmp>0;tmp--){
		scanf("%d",&in);
		a.push_back(in);
	}
	for(tmp=a_col*b_col;tmp>0;tmp--){
		scanf("%d",&in);
		b.push_back(in);
	}
	
	int ans_row,ans_col;
	for(ans_row=0;ans_row<a_row;ans_row++){
		for(ans_col=0;ans_col<b_col;ans_col++){
			in=0;
			for(tmp=0;tmp<a_col;tmp++){
				in+=a[ans_row*a_col+tmp]*b[tmp*b_col+ans_col];
			}
			ans.push_back(in);
		}
	}
	//system("pause");
	for(tmp=0;tmp<a_row*b_col;tmp++){
		printf("%d ",ans[tmp]);
		if(tmp%b_col==1)printf("\n");
	}

	return 0;
}
