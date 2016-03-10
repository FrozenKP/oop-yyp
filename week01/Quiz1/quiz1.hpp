#include <vector>
#include <math.h>
#include <cstdlib>
namespace quiz1{

	template<class T>
	T EuclideanDistance(const std::vector<T>& Pa,
	                    const std::vector<T>& Pb){

		if( Pa.size() != Pb.size() )
			throw ":(";

		T Distance = 0;

		// Fill your code here
		int a;
		for(a=Pa.size()-1;a>=0;a--)Distance+=(Pa[a]-Pb[a])*(Pa[a]-Pb[a]);
		Distance=sqrt(Distance);
		return Distance;

		}

	}
