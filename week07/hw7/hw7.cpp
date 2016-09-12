#include"iostream"
#include"fstream"
#include"string"
#include"string.h"
#include"sstream"

using namespace std;

class cmd{
//	private:
	public:
		int valid; 					//0:invalid 1:unused 2:need input file 3:out
		int action; 				//0:cat 1:removtag 2:exit 3;error
		int run; 					//when run=0,it will execute the command
		string ofname; 				//output file name
		string ifname; 				//input file name
		string is; 					//input string
		bool file,delay;
		string command_o;
//	public:
		cmd(){
			valid=0;
			action=4;
			run=0;
			file=false;
			delay=false;
		}

		void in(ifstream &o){
			int space;
			string tmp,command;
			getline(o,command);
			command_o=command;
			while(*(command.end()-1)==' ')command.erase(command.length()-1,1);
			//check what to do
			while(*command.begin()==' ')command.erase(0,1);
			space=command.find_first_of(' ');
			if(space==std::string::npos)space=command.length();
			tmp=command.substr(0,space);
			if(tmp.compare("cat")==0)action=0;
			else if(tmp.compare("removetag")==0)action=1;
			else if(tmp.compare("exit")==0){
				action=2;
				valid=1;
			}else {
				action=3;
				valid=3;
			}
			if(command.length()==space)command.clear();
			else command.erase(0,space+1);
			//check input file
			if(action==1||action==0){
				while(*command.begin()==' ')command.erase(0,1);
				space=command.find_first_of(' ');
				if(space==std::string::npos)space=command.length();
				tmp=command.substr(0,space);
				if(tmp.compare(">")==0||*(tmp.begin())=='|')valid=2;
				else{
					ifname=tmp;
					valid=1;
					if(command.length()==space)command.clear();
					else command.erase(0,space+1);
				}
			}
			//check other action
			while(!command.empty()){
				while(*command.begin()==' ')command.erase(0,1);
				space=command.find_first_of(' ');
				if(space==std::string::npos)space=command.length();
				tmp=command.substr(0,space);
				if(tmp.compare(">")==0){
					file=true;
					if(command.length()==space)command.clear();
					else command.erase(0,space+1);
					while(*command.begin()==' ')command.erase(0,1);
					space=command.find_first_of(' ');
					if(space==std::string::npos)space=command.length();
					tmp=command.substr(0,space);
					ofname=tmp;
					if(command.length()==space)command.clear();
					else command.erase(0,space+1);
				}else if(*(tmp.begin())=='|'){
					delay=true;
					tmp.erase(tmp.begin());
					stringstream ss;
					ss<<tmp;
					ss>>run;
					if(command.length()==space)command.clear();
					else command.erase(0,space+1);
				}else valid=3;
			}
		}

		bool execute(){
			if(valid==3||valid==0)return false;
			else{
				if(delay==true&&run!=0){
					run--;
					return false;
				}else return true;
			}
		}

		void showcmd(){
			cout<<"% "<<command_o<<endl;
		}

		void info(){
			cout<<"valid:"<<valid<<endl;
			cout<<"file:"<<file<<endl;
			cout<<"delay:"<<delay<<endl;
			cout<<"run:"<<run<<endl;
			cout<<"action:"<<action<<endl;
			cout<<"ifname:"<<ifname<<endl;
			cout<<"ofname:"<<ofname<<endl;
			cout<<"is:"<<is<<endl;
		}

};

int main(int argc,char* argv[]){
	if(argc==1){
		cout<<"error:no command file"<<endl;
		return 0;
	}
	ifstream command_file(argv[1],ios::in);

	cmd c[11][11];
	int now=0;

	while(now!=11){
		c[now][9].in(command_file);
		if(command_file.eof()){
			command_file.close();
			exit(0);
		}
		c[now][9].showcmd();
		if(c[now][9].valid==3){
			cout<<"unknow command"<<endl;
			for(int a=0;a<10;a++)c[now][a].valid=3;
			now++;
			continue;
		}
		for(int precmd=0;precmd<=now;precmd++){
			for(int down=0;down<10;down++){
				//cout<<precmd<<" "<<down<<" "<<c[precmd][down].valid<<endl;
				if(c[precmd][down].execute()){
					//cout<<"->"<<precmd<<" "<<down<<endl;
					if(c[precmd][down].delay==true){
						//switch to other command
						switch(c[precmd][down].action){
							case 0:
								if(c[precmd][down].ifname.empty()){
									if(c[precmd][down].is.empty())break;
									int pos;
									for(int a=0;a<9;a++){
										if(c[now][a].valid==0){
											pos=a;
											break;
										}
									}
									c[now][pos]=c[now][9];
									c[now][pos].valid=1;
									c[now][pos].is=c[precmd][down].is;
								}else{
									ifstream ipf(c[precmd][down].ifname,ios::in);
									int pos;
									for(int a=0;a<9;a++){
										if(c[now][a].valid==0){
											pos=a;
											break;
										}
									}
									c[now][pos]=c[now][9];
									c[now][pos].valid=1;
									char tmp;
									while(1){
										tmp=ipf.get();
										if(tmp==EOF)break;
										c[now][pos].is+=tmp;
									}
									ipf.close();
								}
								break;
							case 1:
								if(c[precmd][down].ifname.empty()){
									if(c[precmd][down].is.empty())break;
									int pos;
									for(int a=0;a<9;a++){
										if(c[now][a].valid==0){
											pos=a;
											break;
										}
									}
									c[now][pos]=c[now][9];
									c[now][pos].valid=1;
									c[now][pos].is=c[precmd][down].is;
									int found;
									found=c[now][pos].is.find_first_of("=+,.'\\\"!-;()'");
									while(found!=std::string::npos){
										c[now][pos].is.erase(found,1);
										found=c[now][pos].is.find_first_of("=+,.'\\\"!-;()'");
									}
								}else{
									ifstream ipf(c[precmd][down].ifname,ios::in);
									int pos;
									for(int a=0;a<9;a++){
										if(c[now][a].valid==0){
											pos=a;
											break;
										}
									}
									c[now][pos]=c[now][9];
									c[now][pos].valid=1;
									char tmp;
									while(1){
										tmp=ipf.get();
										if(tmp==EOF)break;
										c[now][pos].is+=tmp;
									}
									int found;
									found=c[now][pos].is.find_first_of("=+,.'\\\"!-;()'");
									while(found!=std::string::npos){
										c[now][pos].is.erase(found,1);
										found=c[now][pos].is.find_first_of("=+,.'\\\"!-;()'");
									}
									ipf.close();
								}
								break;
						}
						c[precmd][down].valid=3;
					}else{
						//execute the action if it don't have delay
						switch(c[precmd][down].action){
							case 0:
								//cat
								if(c[precmd][down].valid!=1)break;
								if(c[precmd][down].file==true){
									ofstream opf(c[precmd][down].ofname,ios::app);
									if(!c[precmd][down].ifname.empty()){
										ifstream ipf(c[precmd][down].ifname,ios::in);
										char tmp;
										while(1){
											tmp=ipf.get();
											if(tmp==EOF)break;
											c[precmd][down].is+=tmp;
										}
										ipf.close();
									}
									opf<<c[precmd][down].is;
									opf.close();
								}else{
									if(!c[precmd][down].ifname.empty()){
										ifstream ipf(c[precmd][down].ifname,ios::in);
										char tmp;
										while(1){
											tmp=ipf.get();
											if(tmp==EOF)break;
											c[precmd][down].is+=tmp;
										}
										ipf.close();
									}
									cout<<c[precmd][down].is;
								}
								break;
							case 1:
								//removetag
								if(c[precmd][down].file==true){
									ofstream opf(c[precmd][down].ofname,ios::app);
									if(!c[precmd][down].ifname.empty()){
										ifstream ipf(c[precmd][down].ifname,ios::in);
										char tmp;
										while(1){
											tmp=ipf.get();
											if(tmp==EOF)break;
											c[precmd][down].is+=tmp;
										}
										/*int found;
										found=c[precmd][down].is.find_first_of("=+,.'\\\"!-;()'");
										while(found!=std::string::npos){
											c[precmd][down].is.erase(found,1);
											found=c[precmd][down].is.find_first_of("=+,.'\\\"!-;()'");
										}*/
										ipf.close();
									}
									int found;
									found=c[precmd][down].is.find_first_of("=+,.'\\\"!-;()'");
									while(found!=std::string::npos){
										c[precmd][down].is.erase(found,1);
										found=c[precmd][down].is.find_first_of("=+,.'\\\"!-;()'");
									}
									opf<<c[precmd][down].is;
									opf.close();
								}/*else{
									if(!c[precmd][down].ifname.empty()){
										ifstream ipf(c[precmd][down].ifname,ios::in);
										char tmp;
										while(1){
											tmp=ipf.get();
											if(tmp==EOF)break;
											c[precmd][down].is+=tmp;
										}
										int found;
										found=c[precmd][down].is.find_first_of("=+,.'\\\"!-;()'");
										while(found!=std::string::npos){
											c[precmd][down].is.erase(found,1);
											found=c[precmd][down].is.find_first_of("=+,.'\\\"!-;()'");
										}
										ipf.close();
									}
									cout<<c[precmd][down].is<<endl;
								}*/
								break;
							case 2:
								command_file.close();
								exit(0);
								break;
						}
						c[precmd][down].valid=3;
					}
				}
			}
		}
		now++;
	}
	return 0;
}
