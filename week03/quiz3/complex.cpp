#include"complex.h"
#include"math.h"
#include"iostream"

using namespace std;

ComplexNumber::ComplexNumber(){
	real=0;
	imag=0;
}

ComplexNumber::ComplexNumber(double a, double b){
	real=a;
	imag=b;
}

double ComplexNumber::getReal() const{
	return real;
}

double ComplexNumber::getImag() const{
	return imag;
}

void ComplexNumber::setReal(double a){
	real=a;
}

void ComplexNumber::setImag(double a){
	imag=a;
}

double ComplexNumber::Magnitude() const{
	return sqrt(real*real+imag*imag);
}

double ComplexNumber::Phase() const{
	return acos(real/sqrt(real*real+imag*imag))*180/3.1415926;
}

ComplexNumber ComplexNumber::operator!(){
	ComplexNumber out(real,(-1)*imag);
	return out;
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& in){
	ComplexNumber out(real+in.getReal(),imag+in.getImag());
	return out;
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& in){
	ComplexNumber out(real-in.getReal(),imag-in.getImag());
	return out;
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber& in){
	ComplexNumber out(real*in.getReal()-imag*in.getImag(),real*in.getImag()+imag*in.getReal());
	return out;
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber& in){
	ComplexNumber out((real*in.getReal()+imag*in.getImag())/(in.getReal()*in.getReal()+in.getImag()*in.getImag()) , (real*(-1)*in.getImag()+imag*in.getReal())/(in.getReal()*in.getReal()+in.getImag()*in.getImag()));
	return out;
}

void ComplexNumber::show(){
	cout << "(" << real << "," << imag << ")" <<endl;
}
void ComplexNumber::polar_coordinate(){
	cout << Magnitude() <<" and "<<Phase()<<" degree\n";
}
