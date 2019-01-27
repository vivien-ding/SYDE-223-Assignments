//Written by Vivien (Zhaowei) Ding & Christina Lim 
//Student numbers: 20654920 & 

#ifndef LAB02_H
#define LAB02_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
using std::vector;


class Polynomial {
	
	vector<int> data;

	public:

	friend class PolynomialTest;

	Polynomial (int A[], int size){

		// PURPOSE: Construct a polynomial from array
			// INPUTS: Array of coefficients, size (degree) of polynomial vector
			// OUTPUTS: Polynomial
		
		for(int i = 0; i < size; i++){
			data.push_back(A[i]);
		}

	}

	Polynomial(){

		// PURPOSE: Construct a random polynomial
			// INPUTS: none
			// OUTPUTS: Polynomial from deg 0-1000, with coefficients from -1000 to 1000

		int size;

		size = rand() % 1001;

		for(int i = 0; i < size; i++){
			int sign = rand() % 2;
			int num = rand() % 1001;
			if (sign == 1){
				num *= (-1);
			}

			data.push_back(num);
		}
	}

<<<<<<< HEAD

=======
	// constructor that takes in file of coefficients
>>>>>>> 001065402b93f655449e3242c345ef2ef8782aa8
	Polynomial(string fileName){

		// PURPOSE: Construct a polynomial from a file, with file's first like as the polynomials degree
			//and the rest of the numbers in the file as coefficients
			// INPUTS: name of the file to 
			// OUTPUTS: Polynomial

		string line;
		int index = 0;
		int size = 0;

		ifstream file(fileName);

		while(getline(file, line) && index <= size){
			
			if (index == 0){
				size = stoi(line);
			}
			else{
				
				data.push_back(stoi(line));
			}

			index++;
		}


	}


	// operator override == to check if polynomials are equal
	bool operator==(const Polynomial& target){

		// PURPOSE: Overrides == operator to check equality of *this and another polynomial 
			// INPUTS: Polynomial
			// OUTPUTS: boolean value (0 or 1) depending on equality or not


		if (data.size() != target.data.size()) return false;
			
		for (int i = 0; i < data.size(); i++){
			if (data[i] != target.data[i]) return false;
		}

		return true;

	}

	// function prints polynomial
	void print(){

		// PURPOSE: Prints polynomial to a.out from highest to lowest degree with corresponding coeffs
			// INPUTS: none, use Polynomial.print()
			// OUTPUTS: none, cout polynoial

		int first_non_zero = data.size() - 1;
		
		while (data[first_non_zero] == 0){
			first_non_zero--;
		}

		for (int pow = first_non_zero; pow >= 0; pow--){
			if (pow == first_non_zero) cout << data[pow] << "x^" << pow;
			if ((pow != first_non_zero) && (data[pow] > 0)) cout << " + " << data[pow] << "x^" << pow;
			if ((pow != first_non_zero) && (data[pow] < 0)) cout << " - " << abs(data[pow]) << "x^" << pow;
		}

		cout << "\n\n\n";

	}

	// operator override + to add polynomials
	Polynomial operator+(const Polynomial& target){

		// PURPOSE: Overrides + operator to add *this and another polynomial 
			// INPUTS: Polynomial
			// OUTPUTS: Sum of Polynomials
		
		int sizeA = data.size();
		int sizeB = target.data.size();
		int size;

		if (sizeA>=sizeB) size = sizeA;
		else size = sizeB;

		int *sum = new int[size]();
		
		if (sizeA > sizeB) {
			for (int i = 0; i < sizeB; i++){
				sum[i] = data[i] + target.data[i];
			}
		}
		else{
			for (int i = 0; i < sizeA; i++){
				sum[i] = data[i] + target.data[i];
			}
			for (int i = sizeA; i < sizeB; i++){
				sum[i] = target.data[i];
			}
		}

		return Polynomial(sum, size);

	}

<<<<<<< HEAD

=======
	// operator override - to subtract polynomials
>>>>>>> 001065402b93f655449e3242c345ef2ef8782aa8
	Polynomial operator-(const Polynomial& target){

		// PURPOSE: Overrides - operator to subtract another polynomial from *this
			// INPUTS: Polynomial
			// OUTPUTS: Difference between the two Polynomials
		
		int sizeA = data.size();
		int sizeB = target.data.size();
		int size;

		if (sizeA>=sizeB) size = sizeA;
		else size = sizeB;

		int *diff = new int[size]();

		
		if (sizeA > sizeB) {
			for (int i = 0; i < sizeB; i++){
				diff[i] = data[i] - target.data[i];
			}
			for (int i = sizeB; i < sizeA; i++){
				diff[i] = data[i];
			}
		}
		else{
			for (int i = 0; i < sizeA; i++){
				diff[i] = data[i] - target.data[i];
			}
			for (int i = sizeA; i < sizeB; i++){
				diff[i] = -1 * (target.data[i]);
			}
		}

		return Polynomial(diff, size);

	}

<<<<<<< HEAD

=======
	//operator override * to multiply polynomials
>>>>>>> 001065402b93f655449e3242c345ef2ef8782aa8
	Polynomial operator*(const Polynomial& target){
		
		// PURPOSE: Overrides * operator to multiply *this and another polynomial 
			// INPUTS: Polynomial
			// OUTPUTS: Product of Polynomials

		int sizeA = data.size();
		int sizeB = target.data.size();
		int size = sizeA + sizeB - 1;

		int *prod = new int[size]();

		for (int i = 0; i < sizeA; i++){
			for (int j = 0; j < sizeB; j++){
				prod[i+j] += (data[i] * target.data[j]);
			}
		}

		return Polynomial(prod, size);

	}

	// function of class polynomial to derive polynomials
	Polynomial derivative(){

		// PURPOSE: Finds the derivative of a polynomial
			// INPUTS: None, use Polynomial.derivative()
			// OUTPUTS: Derivative of Polynomial
		
		int size = data.size()-1;
		int *der = new int[size]();

		for (int i = 1; i < data.size(); i++){
			der[i-1] = i * data[i];
		}

		return Polynomial(der, size);
	}


};

#endif



