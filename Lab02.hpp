//Written by Vivien (Zhaowei) Ding and Christina Lim 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
using std::vector;

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class Polynomial {
	
	vector<int> data;

	public:

	friend class PolynomialTest;

	Polynomial (int A[], int size){
		
		for(int i = 0; i < size; i++){
			data.push_back(A[i]);
		}

	}

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

		while(getline(file, line)){
			
			if (index == 0){
				size = stoi(line);
			}
			else{
				
				if (index > size){
					break;
				} 
				data.push_back(stoi(line));
			}

			index++;
		}


		// istream& getline(file, line);
		// int size = stoi(line);

		// for (int i = 0; i < size + 1; i++){

		// 	string coef_line;

		// 	istream& getline(file, coef_line);

		// 	int coef = stoi(coef_line);	
		// 	data.push_back(coef);
		// }


		// if (file.is_open()){
		// 	getline ()

		// }


	}

	// ~Polynomial();

	bool operator==(const Polynomial& target){
		if (data.size() != target.data.size()) return false;
			
		for (int i = 0; i < data.size(); i++){
			if (data[i] != target.data[i]) return false;
		}

		return true;

	}

	void print(){

		for (int pow = data.size() - 1; pow >= 0; pow--){
			if (data[pow] != 0) cout << data[pow] << "x^" << pow << "+";

		}
	}

	Polynomial operator+(const Polynomial& target){
		int sizeA = data.size();
		int sizeB = target.data.size();

		if (sizeA > sizeB) {
			for (int i = 0; i < sizeB; i++){
				data[i] += target.data[i];
			}
		}
		else{
			for (int i = 0; i < sizeA; i++){
				data[i] += target.data[i];
			}
			for (int i = sizeA; i < sizeB; i++){
				data.push_back(target.data[i]);
			}
		}

	}

	Polynomial operator-(const Polynomial& target){
		int sizeA = data.size();
		int sizeB = target.data.size();

		if (sizeA > sizeB) {
			for (int i = 0; i < sizeB; i++){
				data[i] -= target.data[i];
			}
		}
		else{
			for (int i = 0; i < sizeA; i++){
				data[i] -= target.data[i];
			}
			for (int i = sizeA; i < sizeB; i++){
				data.push_back(target.data[i]*(-1));
			}
		}

	}

	Polynomial operator*(const Polynomial& target){
		

		int sizeA = data.size();
		int sizeB = target.data.size();

		Polynomial sum;

		for (int i = 0; i < sizeB; i++){
			Polynomial a;
			
			for (int x = 0; x < i; x++){
				a.data.push_back(0);
			}
			
			for (int j = 0; j < sizeA; j++){
				a.data.push_back(data[j]*target.data[i]);
			}
			sum = sum + a;
		}

		data = sum.data;
	}

	Polynomial derivative(){
		Polynomial temp;
		for (int i = 1; i < data.size(); i++){
			temp.data.push_back(i*data[i]);
		}
		data = temp.data;
	}
};



