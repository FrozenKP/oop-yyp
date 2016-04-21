#include <string>
#include <iostream>
using namespace std;

namespace figure{
    
    //You can add member function in this class
    class BasePoint{
        public:
            BasePoint(int px, int py):x(px),y(py){}
            virtual ~BasePoint(){}
            virtual void info(){
                cout<<"figure: "<<type<<endl;
                cout<<"position x:"<<x<<" y:"<<y<<endl;
            }
            void settype(string in){
            	type.assign(in);
			}
			string showtype(){
				return type;
			}
        
        protected:
            int x,y;
        private:
            string type;
    }; 
    //Fill your code here
	class Figure1P:public BasePoint{
		protected:
			int p1;
		
		public:
			Figure1P(int px,int py,int p1_):BasePoint(px,py),p1(p1_){};
			void info(){
				cout<<"figure: "<<BasePoint::showtype()<<endl;
                cout<<"position x:"<<x<<" y:"<<y<<endl;
                cout<<"property 1: p1="<<p1<<endl;
			}
	};
	
	class Square:public Figure1P{
		public:
			Square(int px,int py,int p1_):Figure1P(px,py,p1_){
				BasePoint::settype("square");
			}
			void info(){
				cout<<"figure: "<<BasePoint::showtype()<<endl;
                cout<<"position x:"<<x<<" y:"<<y<<endl;
                cout<<"property 1: p1="<<p1<<endl;
                cout<<"area: "<<p1*p1<<endl;
			}
	};
	
	class Figure2P:public Figure1P{
		protected:
			int p2;
		
		public:
			Figure2P(int px,int py,int p1_,int p2_):Figure1P(px,py,p1_),p2(p2_){};
			void info(){
				cout<<"figure: "<<BasePoint::showtype()<<endl;
                cout<<"position x:"<<x<<" y:"<<y<<endl;
                cout<<"property 1: p1="<<p1<<endl;
                cout<<"property 2: p2="<<p2<<endl;
			}
	};
	
	class Rectangle:public Figure2P{
		public:
			Rectangle(int px,int py,int p1_,int p2_):Figure2P(px,py,p1_,p2_){
				BasePoint::settype("rectangle");
			}
			void info(){
				cout<<"figure: "<<BasePoint::showtype()<<endl;
                cout<<"position x:"<<x<<" y:"<<y<<endl;
                cout<<"property 1: p1="<<p1<<endl;
                cout<<"property 2: p2="<<p2<<endl;
                cout<<"area: "<<p1*p2<<endl;
			}
	};
}
