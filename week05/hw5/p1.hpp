#include <iostream>
#include <string>
#include"sstream"
#include"list"
#include<iomanip>


/*add the header if you need*/
using namespace std;

//Abstract base class for Dessert Item hierarchy
class DessertItem{
    private:
        //Name of the DessertItem object
        string name;

    public:
        DessertItem(){}
        DessertItem(string name):name(name){}
        //Empty virtual destructor for DessertItem class
        virtual ~DessertItem(){}     
        //returns Name of DessertItem  
        string getName(){ return name;}
        virtual string getDetails() = 0;
        virtual double getCost() = 0;
};

class IceCream : public DessertItem {
    public:
        IceCream(string name, double cost):DessertItem(name),cost(cost){}
        virtual double getCost(){return cost;}
		virtual string getDetails(){
			string out;
			return out;		
		}        

    private:
        double cost;
};

class Topping : public IceCream {
    public:
        Topping(string iceCreamName, double iceCreamCost,string toppingName, double toppingCost):IceCream(toppingName+" Sundae with "+iceCreamName,iceCreamCost),toppingName(toppingName),toppingCost(toppingCost){}
        virtual double getCost(){return toppingCost+IceCream::getCost();}
		virtual string getDetails(){
			string out;
			return out;		
		}        
 	
	
    private:
        string toppingName;
        double toppingCost;
};

class Cookie : public DessertItem {
    public:
        Cookie(string name, int number, double pricePerDozen):DessertItem(name),number(number),pricePerDozen(pricePerDozen){}
        virtual double getCost(){return number*pricePerDozen;}
        virtual string getDetails(){
            stringstream ss;
            string n,d;
            ss<<number;
            ss>>n;
            ss.str("");
            ss.clear();
            ss<<pricePerDozen;
            ss>>d;
            return "("+n+" dozen(s) * "+d+"/dozen)";
        }
    private:
    //Number of dozens of Cookie
        int number;
        double pricePerDozen;
};

class Candy : public DessertItem {
    public:
        Candy(string name, double weight, double pricePerGram):DessertItem(name),weight(weight),pricePerGram(pricePerGram){}
        virtual double getCost(){return weight*pricePerGram;}
        virtual string getDetails(){
            stringstream ss;
            string w,g;
            ss<<weight;
            ss>>w;
            ss.str("");
            ss.clear();
            ss<<pricePerGram;
            ss>>g;
            return "("+w+" gram(s) * "+g+"/gram)";
        }
            
    private:
    //Weight of Candy
        double weight;
        double pricePerGram;
};



class Checkout {
    public:
        friend ostream &operator<<(std::ostream &, Checkout &);

    
        /* Write about Checkout member functions
        1. "enterItem" function to add the element into the list
        2. "removeItem" function to remove the elemtent from the list
        3. calculate the total cost and tax in the list
        4. "numberOfItems" for number of Item in the list
        5. "clear" clear all Items from list
        */
        void enterItem(DessertItem* in){
            itemList.push_back(in);
        }
        void removeItem(DessertItem* in){
            itemList.remove(in);
        }
        void calculate(){
            Cost=0;
            Tax=0;
            list<DessertItem*>::iterator it;
            for(it=itemList.begin();it!=itemList.end();it++){
                Cost+=(*it)->getCost();
            }
            Tax=Cost*TaxRate;
        }
        int numberOfItems(){
            return itemList.size();
        }
        void clear(){
            for(unsigned int a=0;a<itemList.size();a++) { itemList.pop_back();}
			while(!itemList.empty())itemList.pop_back();
        }

    private:
        list<DessertItem*> itemList;
        const double TaxRate=0.05;
        double Cost,Tax;
};


ostream &operator<<(ostream &output, Checkout &checkout){
    output<<"Welcome to OOP’s shop"<<endl;
    output<<"------------------------------"<<endl;
    output<<"\n";
    output<<"Number of items: "<<checkout.numberOfItems()<<endl;
    output<<"\n";
    for(list<DessertItem*>::iterator it=checkout.itemList.begin();it!=checkout.itemList.end();it++){
        output<<(*it)->getName()<<setw(45-(*it)->getName().length())<<(int)((*it)->getCost()+0.5)<<endl;
		if(!((*it)->getDetails().empty()))output<<(*it)->getDetails()<<endl;
    }
    output<<"\n";
    output<<"------------------------------"<<endl;
    checkout.calculate();
    output<<"Cost"<<setw(41)<<(int)(checkout.Cost+0.5)<<endl;
    output<<"Tax"<<setw(42)<<(int)(checkout.Tax+0.5)<<endl;
    output<<"\n";
    output<<"Total cost"<<setw(35)<<(int)(checkout.Cost+0.5)+(int)(checkout.Tax+0.5)<<endl;
	return output;
}
