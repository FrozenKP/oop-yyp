#include"sstream"
#include"typeinfo"
#include"iostream"

using namespace std;

struct bad_lexical_cast : bad_cast{};

template<typename To, typename From>
To lexical_cast(const From& val){
	try{
		bad_lexical_cast b;
		stringstream ss;
		ss<<val;
		To out;
		ss>>noskipws>>out;
		//cout<<out<<endl;					//check out
		if(ss.fail()||ss.peek()!=EOF){
			//cout<<"err\n";				//check find error
			throw b;
		}
		//cout<<"fine"<<endl;				//check no error
		return out;
	}catch(bad_cast& bc){
		bad_lexical_cast b2;
		throw b2;
	}
}
