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


	bool test_constructors2(){
		int temp [7] = {1, 2, 3, 4, 5, 6,7};
		Polynomial b = Polynomial(temp, 5);
		ASSERT_TRUE((b.data.size() == 5));
		ASSERT_TRUE((b.data == {1, 2, 3, 4, 5}));
		return true;
	}

	bool test_constructors3(){
		Polynomial c = Polynomial(coefficient_file);
		ASSERT_TRUE((c.data.size() == 5));
		ASSERT_TRUE((c.data == {2, 9, 4, 1, 4}));
		return true;
	}

	bool add_polynomials(){
		
		int temp[4] = {2, 0, 4, 3};
		int temp2[5] = {3, 4, 1, 3, 5};

		int x = 4;
		int y = 5;
		
		Polynomial a = Polynomial(temp, x);
		Polynomial b = Polynomial(temp2, y);

		a + b;

		ASSERT_TRUE((a.data.size() == 5));
		ASSERT_TRUE((a.data == {5, 4, 5, 6, 5}));
		return true;
	}

	bool subtract_polynomials(){
		
		int temp[5] = {2, 7, 0, 4, 3};
		int temp2[3] = {3, 4, 1};

		int x = 5;
		int y = 3;
		
		Polynomial a = Polynomial(temp, x);
		Polynomial b = Polynomial(temp2, y);

		a - b;

		ASSERT_TRUE((a.data.size() == 5));
		ASSERT_TRUE((a.data == {-1, 2, -1, 4, 3}));
<<<<<<< HEAD
=======
		return true;
	}

	bool multiply_polynomials(){
		
		int temp[3] = {7, 2, 3};
		int temp2[2] = {1, 2};

		int x = 3;
		int y = 2;
		
		Polynomial a = Polynomial(temp, x);
		Polynomial b = Polynomial(temp2, y);

		a * b;

		ASSERT_TRUE((a.data.size() == 4));
		ASSERT_TRUE((a.data == {7, 16, 7, 6}));
		return true;
	}

	bool derive_polynomial(){
		
		int temp[3] = {-1, 2, 3};

		int x = 3;
		
		Polynomial a = Polynomial(temp, x);

		a.derivative();

		ASSERT_TRUE((a.data.size() == 2));
		ASSERT_TRUE((a.data == {2, 6}));
>>>>>>> ec7068ef9aa69e67cd17ce19a02788d71019d431
		return true;
	}

	void run(){
		if (test_constructors1())
			cout << "Test Constructors 1 Passed" << endl;
		else
			cout << "Test Constructors 1 Failed" << endl;

		if (test_constructors2())
			cout << "Test Constructors 2 Passed" << endl;
		else
			cout << "Test Constructors 2 Failed" << endl;

		if (test_constructors3())
			cout << "Test Constructors 3 Passed" << endl;
		else
			cout << "Test Constructors 3 Failed" << endl;

		if (add_polynomials())
			cout << "Test Add Polynomials Passed" << endl;
		else
			cout << "Test Add Polynomials Failed" << endl;

		if (subtract_polynomials())
			cout << "Test Subtract Polynomials Passed" << endl;
		else
			cout << "Test Subtract Polynomials Failed" << endl;

		if (multiply_polynomials())
			cout << "Test Multiply Polynomials Passed" << endl;
		else
			cout << "Test Multiply Polynomials Failed" << endl;

		if (derive_polynomial())
			cout << "Test Derive Polynomials Passed" << endl;
		else
			cout << "Test Derive Polynomials Failed" << endl;
	}
	

};

int main(){
	PolynomialTest my_test;
	my_test.run();
	return 0;
}
