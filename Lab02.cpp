#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Lab02.hpp"

using namespace std;
using std::vector;

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class PolynomialTest{
	
	Polynomial a, b, c;
	int x, y, z;
	public:

	bool test_constructors1(){
		
		int temp [7] = {1, 2, 3, 4, 5, 6,7};
		int temp2 [5] = {1, 2, 3, 4, 5};
		
		x = 5;
		y = -2;

		a = Polynomial(temp, x);
		b = Polynomial(temp, y);
		
		ASSERT_TRUE((a.data.size() == 5));
		ASSERT_TRUE(a.data != b.data);
		return true;
	}

	void run(){
		if (test_constructors1())
			cout << "Test Constructors 1 Passed" << endl;
		else
			cout << "Test Constructors 1 Failed" << endl;
	}

};

int main(){
	PolynomialTest my_test;
	my_test.run();
	return 0;
}
