#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <array>
#include "Lab02.hpp"

using namespace std;
using std::vector;

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class PolynomialTest{
	
	Polynomial a, b, c, d;
	int x, y, z;

	public:

		// checks that array of coefficients are stored properly
		bool test_constructors_array(){
			
			int temp [7] = {1, 2, 3, 4, 5, 6,7};
			int temp2 [5] = {1, 2, 3, 4, 5};
			
			x = 5;
			y = -2;

			a = Polynomial(temp, x);
			b = Polynomial(temp, y);
			c = Polynomial(temp2, x);
			
			// a.print();
			// b.print();

			ASSERT_TRUE((a.data.size() == 5));
			ASSERT_FALSE(a.data == b.data);
			ASSERT_TRUE(a.data.size() == c.data.size());
			ASSERT_TRUE(a.data == c.data);
			return true;
		}



		// checks randomly generated polynomials are valid polynomials
		bool test_constructors_random(){
			a = Polynomial();
			b = Polynomial();
			c = Polynomial();

			// a.print();
			// b.print();
			// c.print();

			ASSERT_TRUE(a.data.size() >= 0 && b.data.size() >= 0 && c.data.size() >= 0);
			ASSERT_TRUE(a.data.size() <= 1000 && b.data.size() <= 1000 && c.data.size() <= 1000);

			return true;
		}

		// tests == operator
		bool test_equals(){
			int temp [7] = {1, 2, 3, 4, 5, 6,7};
			int temp2 [5] = {9, 32, 1, 4, 5};
			int temp3 [5] = {1, 2, 3, 4, 5};
			
			x = 5;
			y = -2;

			a = Polynomial(temp, x);
			b = Polynomial(temp, y);
			c = Polynomial(temp2, x);
			d = Polynomial(temp3, x);

			ASSERT_FALSE(a==b);
			ASSERT_FALSE(a==c);
			ASSERT_TRUE (a==d);

			return true;
		}

		// tests that constructor can take in text file of coefficients
		bool test_constructors_file(){
			
			x = 5;

			a = Polynomial("mypolynomial.txt");
			// a.print();

			int array[5] = {10, 9, 321321, 231, 7};

			b = Polynomial(array, 5);

			// b.print();
			
			ASSERT_TRUE(a==b);

			return true;

		}


		// checks that + operator adds polynomials
		bool add_polynomials(){
			
			int temp[4] = {2, 0, 4, 3};
			int temp2[5] = {3, 4, 1, 3, 5};
			int temp3[5] = {5, 4, 5, 6, 5};

			int x = 4;
			int y = 5;
			
			a = Polynomial(temp, x);
			b = Polynomial(temp2, y);

			c = a + b;
			d = Polynomial(temp3, 5);

			ASSERT_TRUE(c == d);
			return true;

		}

		// checks that - operator subtracts polynomials
		bool subtract_polynomials(){
			
			int temp[5] = {2, 7, 0, 4, 3};
			int temp2[3] = {3, 4, 1};
			int temp3[5] = {-1, 3, -1, 4, 3};

			int x = 5;
			int y = 3;
			
			a = Polynomial(temp, x);
			b = Polynomial(temp2, y);

			c = a - b;
			d = Polynomial(temp3, x);

			// c.print();
			// d.print();

			ASSERT_TRUE(c==d);

			return true;
		}

		// checks that * operator multiplies polynomials
		bool multiply_polynomials(){
			
			int temp[3] = {7, 2, 3};
			int temp2[2] = {1, 2};
			int temp3[4] = {7, 16, 7, 6};

			int x = 3;
			int y = 2;
			
			Polynomial a = Polynomial(temp, x);
			Polynomial b = Polynomial(temp2, y);

			c = a * b;
			d = Polynomial(temp3, 4);

			ASSERT_TRUE(c==d);

			return true;
		}

		// checks that derive function derives polynomials
		bool derive_polynomial(){
			
			int temp[3] = {-1, 2, 3};
			int temp2[2] = {2, 6};

			x = 3;
			
			a = Polynomial(temp, x);

			b = a.derivative();
			c = Polynomial(temp2, 2);

			ASSERT_TRUE(b==c);
			return true;
		}

	// runs tests
	void run(){
		if (test_constructors_array())
			cout << "Test Constructors with Array input Passed" << endl;
		else
			cout << "Test Constructors with Array input Failed" << endl;

		if (test_constructors_random())
			cout << "Test Constructors with Random input Passed" << endl;
		else
			cout << "Test Constructors with Random input Failed" << endl;


		if (test_equals())
			cout << "Test == Operator Passed" << endl;
		else
			cout << "Test == Operator Failed" << endl;


		if (test_constructors_file())
			cout << "Test Constructors with File input Passed" << endl;
		else
			cout << "Test Constructors with File input Failed" << endl;


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
