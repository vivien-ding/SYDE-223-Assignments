//Written by Vivien (Zhaowei) Ding and Christina Lim 

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

	//constructor
	Polynomial (int A[], int size){
		
		for(int i = 0; i < size; i++){
			data.push_back(A[i]);
		}

	}

	//random constructor
	Polynomial(){
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

	Polynomial(string fileName){
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


	bool operator==(const Polynomial& target){
		if (data.size() != target.data.size()) return false;
			
		for (int i = 0; i < data.size(); i++){
			if (data[i] != target.data[i]) return false;
		}

		return true;

	}

	void print(){

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


	Polynomial operator+(const Polynomial& target){
		
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

	Polynomial operator-(const Polynomial& target){
		
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

	Polynomial operator*(const Polynomial& target){
		

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

	Polynomial derivative(){
		
		int size = data.size()-1;
		int *der = new int[size]();

		for (int i = 1; i < data.size(); i++){
			der[i-1] = i * data[i];
		}

		return Polynomial(der, size);
	}


};

#endif



