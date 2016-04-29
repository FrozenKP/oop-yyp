#include"BigNum.h"
#include"string"
#include"iostream"

using namespace std;

BigNum::BigNum(){
    for(int a=0;a<100;a++)value[a]=0;
    sign='+';
    size=0;
}

BigNum::BigNum(int const in){
    for(int a=0;a<100;a++)value[a]=0;
    size=0;
    
    int in_2=in;
    if(in<0){
        sign='-';
        in_2*=(-1);
    }else sign='+';
    
    for(int digit=0;in_2!=0;digit++){
        value[digit]=in_2%10;
        in_2/=10;
        size=digit+1;
    }
}

BigNum::BigNum(std::string const &in_2){
    string in=in_2;
    for(int a=0;a<100;a++)value[a]=0;
    int digit=0;
    if(*(in.begin())=='-'){
        sign='-';
        digit=in.length()-2;
        for(string::iterator it=in.begin()+1;it!=in.end();it++){
            value[digit]=*it-'0';
            digit--;
        }
        size=in.length()-1;
    }else{
        sign='+';
        digit=in.length()-1;
        for(string::iterator it=in.begin();it!=in.end();it++){
            value[digit]=*it-'0';
            digit--;
        }
        size=in.length();
    }
}

BigNum BigNum::operator+(const BigNum &in) const{
    BigNum out;
    //cout<<"plus"<<endl;
    if(sign=='-'&&in.sign=='+')out=in+*this;
    else if(sign=='-'&&in.sign=='-'){
        BigNum tmp1=*this,tmp2=in;
        tmp1.sign=tmp2.sign='+';
        out=tmp1+tmp2;
        out.sign='-';
    }else if(sign=='+'&&in.sign=='-'){
        BigNum tmp=in;
        tmp.sign='+';
        out=*this-tmp;
    }else{
        out.sign='+';
        for(int a=0;a<(size<in.size?in.size:size);a++){
            out.value[a]+=value[a]+in.value[a];
            if(out.value[a]>=10){
                out.value[a+1]=out.value[a]/10;
                out.value[a]=out.value[a]%10;
            }
            out.size=a+1;
        }
        if(out.value[out.size]!=0)out.size++;
    }
    return out;
}

BigNum BigNum::operator-(const BigNum & in) const{
    BigNum out;
    //cout<<"minus"<<endl;
    if(sign=='-'&&in.sign=='+'){
        //cout<<"-+"<<endl;
        BigNum tmp1=*this,tmp2=in;
        tmp1.sign=tmp2.sign='+';
        out=tmp1+tmp2;
        out.sign='-';
    }else if(sign=='-'&&in.sign=='-'){
        //cout<<"--"<<endl;
        BigNum tmp=in;
        tmp.sign='+';
        out=*this+tmp;
    }else if(sign=='+'&&in.sign=='-'){
        //cout<<"+-"<<endl;
        BigNum tmp=in;
        tmp.sign='+';
        out=*this+tmp;
    }else{
        //cout<<"++"<<endl;
        if(compare(*this,in)){
            BigNum tmp=*this;
            for(int a=0;a<size;a++){
                if(tmp.value[a]>=in.value[a])out.value[a]=tmp.value[a]-in.value[a];
                else{
                    tmp.value[a+1]-=1;
                    tmp.value[a]+=10;
                    out.value[a]=tmp.value[a]-in.value[a];
                }
            }
            out.sign='+';
            for(int a=0;a<100;a++){
                if(out.value[a]!=0)out.size=a+1;
            }
        }else{
            out=in-*this;
            out.sign='-';
        }
    }
    return out;
}

BigNum BigNum::operator*(const BigNum &in) const{
    BigNum out;
    if(sign=='-'&&in.sign=='-'){
        BigNum tmp_1=*this,tmp_2=in;
        tmp_1.sign=tmp_2.sign='+';
        out=tmp_1*tmp_2;
    }else if(sign=='-'&&in.sign=='+'){
        BigNum tmp=*this;
        tmp.sign='+';
        out=tmp*in;
        out.sign='-';
    }else if(sign=='+'&&in.sign=='-'){
        BigNum tmp=in;
        tmp.sign='+';
        out=*this*tmp;
        out.sign='-';
    }else{
        for(int a=0;a<(compare(*this,in)?in.size:size);a++){
            for(int b=0;b<(compare(*this,in)?size:in.size);b++){
                out.value[a+b]+=(compare(*this,in)?in.value[a]*value[b]:value[a]*in.value[b]);
            }
        }
        for(int a=0;a<100;a++){
            if(out.value[a]>9){
                out.value[a+1]+=out.value[a]/10;
                out.value[a]%=10;
            }
        }
        for(int a=0;a<100;a++){
            if(out.value[a]!=0)out.size=a+1;
        }
        out.sign='+';
    }
    return out;
}

BigNum& BigNum::operator++(){
    BigNum tmp(1);
    *this=*this+tmp;
    return *this;
}

BigNum BigNum::operator++(int){
    BigNum tmp_1(1),tmp_2(*this);
    *this=*this+tmp_1;
    return tmp_2;
}

std::ostream& operator<<(std::ostream &o,const BigNum &in){
    if(in.size==0){
        o<<0;
        return o;
    }
    if(in.sign=='-')o<<'-';
    for(int a=in.size-1;a>=0;a--)o<<in.value[a];
    return o;
}

std::istream& operator>>(std::istream &i, BigNum &in){
    string a;
    i >> a;
    BigNum tmp(a);
    in=tmp;
    return i;
}

BigNum operator+(const BigNum &in, const int plus){
    BigNum tmp(plus),out=tmp+in;
    return out;
}

BigNum operator+(const int plus, const BigNum &in){
    BigNum tmp(plus),out=tmp+in;
    return out;
}

BigNum operator-(const BigNum &in, const int minus){
    BigNum tmp(minus),out=in-tmp;
    return out;
}

BigNum operator-(const int minus, const BigNum &in){
    BigNum tmp(minus),out=tmp-in;
    return out;
}

BigNum operator*(const BigNum &in, const int mult){
    BigNum tmp(mult),out=tmp*in;
    return out;
}

BigNum operator*(const int mult, const BigNum &in){
    BigNum tmp(mult),out=tmp*in;
    return out;
}

bool compare(const BigNum &a,const BigNum &b){
    if(a.size > b.size)return true;
    else if(a.size < b.size) return false;
    else{
        for(int c=a.size-1;c>=0;c--){
            if(a.value[c]>b.value[c])return true;
            else if(a.value[c]<b.value[c])return false;
        }
    }
    return true;
}
