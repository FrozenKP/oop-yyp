#include"date.h"
#include"iostream"

using namespace std;

unsigned short int Date::getDate_data () const{
	return Date_data;
}

unsigned short int Date::getDay () const{
	unsigned short int out=Date_data;
	out=out<<11;
	out=out>>11;
	return out;
}

unsigned short int Date::getMon () const{
	unsigned short int out=Date_data;
	out=out<<7;
	out=out>>12;
	return out;
}

unsigned short int Date::getYr () const{
	unsigned short int out=Date_data;
	out=out>>9;
	out+=2000;
	return out;
}

void Date::setDate ( const short int &y, const short int &m , const short int &d){
    Date_data=y-2000;
    Date_data=(Date_data<<4);
    Date_data+=m;
    Date_data=(Date_data<<5);
    Date_data+=d;
}

void Date::showDate (){
    cout << getYr() << " " << getMon() << " " << getDay() << endl;
}
