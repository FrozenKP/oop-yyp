/*

  For more info, please visit here:
  https://leetcode.com/problems/flatten-nested-list-iterator/

*/

#include <iostream>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <string>
#include <cctype>
#include <vector>
#include <stdexcept>
#include <stack>



class NestedInteger {

	bool IsNumber;
	int  Number;
	std::vector<NestedInteger> List;

public:

	NestedInteger() = delete;
	NestedInteger(NestedInteger&& ) = default;
	NestedInteger(const NestedInteger& ) = default;

	NestedInteger(int InitNumber):
		IsNumber(true), Number(InitNumber) {
		;
		}

	NestedInteger(std::vector<NestedInteger> InitList):
		IsNumber(false), List( std::move(InitList) ) {
		;
		}

	~NestedInteger() = default;

	// Return true if this NestedInteger holds a single integer, rather than a nested list.
	bool isInteger() const noexcept {

		return IsNumber;

		}

	// Return the single integer that this NestedInteger holds, if it holds a single integer
	// The result is undefined if this NestedInteger holds a nested list
	int getInteger() const noexcept {

		return Number;

		}

	NestedInteger& operator=(const NestedInteger& ) = delete;
	NestedInteger& operator=(NestedInteger&& ) = delete;

	// Return the nested list that this NestedInteger holds, if it holds a nested list
	// The result is undefined if this NestedInteger holds a single integer
	const std::vector<NestedInteger>& getList() const noexcept {

		return List;

		}

	};


// You need to complete the following class
class NestedIterator {
public:
	NestedIterator(const std::vector<NestedInteger>& InitList) {
	}
        
	int next() {
	}

	bool hasNext() {
    }
};



int main(){
    
	std::stack<std::vector<NestedInteger>> EvalStack;

	EvalStack.emplace( std::vector<NestedInteger>() );

	while( (std::cin >> std::ws).peek() != EOF ) {

		if( isdigit(std::cin.peek()) ) {

			int Number;

			if( std::cin >> Number )
				EvalStack.top().emplace_back( Number );
			else
				assert("Bad input");

			}
		else {

			char Char;

			if( std::cin >> Char ) {

				if( Char == '[' )
					EvalStack.emplace( std::vector<NestedInteger>() );
				else if( Char == ']' ) {

					auto Temp = std::move(EvalStack.top());
					EvalStack.pop();
					assert(EvalStack.size() != 0 && "Bad input" );
					EvalStack.top().emplace_back( std::move(Temp) );

					}
				else
					assert("Bad input");

				}
			else
				assert("Bad input");

			}

		}
 
	assert(EvalStack.size() == 1
	    && EvalStack.top().size() == 1
	    && EvalStack.top()[0].isInteger() == false
	    && "Bad input");

	NestedIterator It( EvalStack.top() );

	if( It.hasNext() )
		std::cout << It.next();

	while( It.hasNext() )
		std::cout << ' ' << It.next();

	std::cout << std::endl;

	return 0;

	}

