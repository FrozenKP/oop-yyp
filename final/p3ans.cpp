#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Person{
    private :
        string pName;
        bool flag;
    public :
        Person(string name):pName(name),flag(true){
        }
        Person():pName(0){
        }
        ~Person(){
            flag=false;
            cout << pName <<" is removed"<<endl;
        }
        string Display(){
            return pName;
        }
        bool getflag(){
            return flag;
        }
};

template <class T> class SmartPointer{
    public :
        SmartPointer():ref(0){
            ref_count=(unsigned*) malloc(sizeof(unsigned));
            *ref_count=0;
        }
        SmartPointer(T *ptr){
            ref=ptr;
            ref_count=(unsigned*) malloc(sizeof(unsigned));
            *ref_count=1;
        }
        //fill your code here
        SmartPointer<T> & operator=(SmartPointer<T> &sptr){
            if(this->ref!=sptr.ref){
                this->remove();
                this->ref=sptr.ref;
                this->ref_count=sptr.ref_count;
                (*(this->ref_count))++;
            }
            return *this;
        }

        ~SmartPointer(){
            remove();
        }
        unsigned get_count(){
            return *ref_count;
        }
        T* operator->(){
            return ref;
        }
        T& operator*(){
            return *ref;
        }

    protected:
        //fill your code here
        void remove(){
        	(*ref_count)--;
        	if((*ref_count)==0){
                //free(ref_count);
                delete ref;
        	}
        }
        T *ref;
        unsigned *ref_count;
};

int main(){
    Person *tp=new Person("Tom");
    SmartPointer<Person> p1(new Person("Amy"));
    SmartPointer<Person> p2(tp);
    SmartPointer<Person> p3(new Person("Willy"));
    SmartPointer<Person> p4,p5;

    p4=p5=p1;
    cout << p1->Display() <<" : "<<p1.get_count() <<endl;
    {
        SmartPointer <Person> p6, p7;
        p6=p7=p4;
        cout << p6->Display() <<" : "<<p6.get_count() <<endl;
    }
    cout << p1->Display() <<" : "<<p1.get_count() <<endl;

    p1=p4;
    cout << p1->Display() <<" : "<<p1.get_count() <<endl;

    p2=p3;
    cout << p2->Display() <<" : "<<p2.get_count() <<endl;
    p2=p4;
    cout << p2->Display() <<" : "<<p2.get_count() <<endl;
    cout << p3->Display() <<" : "<<p3.get_count() <<endl;
    if(tp->getflag())
        cout << "free memory in wrong way" <<endl;
}
