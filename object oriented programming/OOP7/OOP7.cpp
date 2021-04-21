#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;



class DynamicVector {
private:	
	vector < vector<int>> vect;
	clock_t SortTime=0, ReverseTime=0, ShuffleTime=0;

public:

	DynamicVector() {}

	DynamicVector(int* arr, int sizeA, int sizeB) {
		
		for (int i = 0; i < sizeA; i++) {
			addRow(&arr[i* sizeB ], sizeB);
		}
	}

	DynamicVector( DynamicVector& vectCopy) {
		vect.clear();

		for (int i = 0; i < vectCopy.vect.size(); i++) {
			addRow(&vectCopy.vect[i][0], vectCopy.vect[i].size());
		}
	}

	void addRow(int* arr, int sizeA) {
		vector<int> temp;
		for (int i = 0; i < sizeA; i++) {
			temp.push_back(arr[i]);
		}
		this->vect.push_back(temp);
	}


	void addRow(vector<int> RefTemp) {
		vector<int> temp;
		for (int i = 0; i < RefTemp.size(); i++) {
			temp.push_back(RefTemp[i]);
		}
		this->vect.push_back(temp);
	}

	void concatVect(DynamicVector& ref) {
		for (int i = 0; i < ref.vect.size(); i++) {
			addRow(ref.vect[i]);
		}
	}

	void addCol(int* arr, int size,int pos) {
		
		if (size > vect.size()) {
			for (int i = 0; i <= abs((int)(size - vect.size())); i++) {
				vector<int> Temp;
				vect.push_back(Temp);
			}
		}

		for (int i = 0; i < size; i++) {
			vect[i].push_back(arr[i * size + pos]);
		}

	}

	void addEl(int vctR,int value) {
		this->vect[vctR].push_back(value);
	}

	void changeEl(int vctR,int vctC,int value) {
		this->vect[vctR][vctC] = value;
	}

	void copyT(DynamicVector& vectRef) {
		bool status=true;

		for (int i = 0; i < vectRef.vect.size()-1; i++) {
			if (vectRef.vect[i].size() != vectRef.vect[i + 1].size()) {
				status = false;
			}
		}

		if (status) {
			vect.clear();
		
			for (int i = 0; i < vectRef.vect[0].size() ; i++) {
				vector<int> Temp;

				for (int j = 0; j < vectRef.vect.size(); j++) {
					Temp.push_back(vectRef.vect[j][i]);
				}
				vect.push_back(Temp);
			}
		}
		else {
			cout << "\nCopy transposed conditions aren't met.";
		}

	}

	DynamicVector& operator=( DynamicVector& vectCopy) {
		
		vect.clear();

		for (int i = 0; i < vectCopy.vect.size(); i++) {
			addRow(&vectCopy.vect[i][0], vectCopy.vect[i].size());
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, DynamicVector& vArr) {
		for (int i = 0; i < vArr.vect.size(); i++){
			for (int j = 0; j < vArr.vect[i].size(); j++) {
				os << "V[" << i << "][" << j << "]=" << vArr.vect[i][j] << "\t";
			}
			os << "\n";
		}
		return os;
	}

	void saveDynamicVector(string name) {

		ofstream SF(name);
		SF << *this;
		SF.close();
	}
		
	static void fillVector(string str, vector<int>& vect) {
		string bufStr;
		string::iterator st=str.begin();

		while (st != str.end()) {

			if (*st == '=') {
				st++;
				
				while (*st != '\t') {
					bufStr += *st;
					st++;
				}

				vect.push_back(stoi(bufStr));
				bufStr = "";
			}
			st++;
		}
	}
	//--------------------------------------------------
	void  readSavedVector2(string name) {
		vect.clear();

		DynamicVector rdv;

		string opStr;
		ifstream  SR(name);

		while (getline(SR, opStr)) {

			vector<int> Temp;

			fillVector(opStr, Temp);
			vect.push_back(Temp);

		}
	}

	void fillWithRandom(int n,int m) {
		vect.clear();
		default_random_engine eng;
		uniform_int_distribution<int> val(0, 100);

		for (int i = 0; i < n; i++) {
			vector<int> temp;
			for (int j = 0; j < m; j++) {
				temp.push_back(val(eng));
			}
			vect.push_back(temp);
		}

	}

	void sortOut() {

		clock_t start, stop;
		start = clock();

		for (int i = 0; i < vect.size(); i++) {
			sort(vect[i].begin(), vect[i].end());
		}

		stop = clock();
		SortTime += stop - start;
	}

	void reverseSelf() {

		clock_t start, stop;
		start = clock();

		for (int i = 0; i < vect.size(); i++) {
			reverse(vect[i].begin(), vect[i].end());
		}

		stop = clock();
		ReverseTime += stop - start;
	}

	void shuffle() {

		clock_t start, stop;
		start = clock();

		for (int i = 0; i < vect.size(); i++) {
			random_shuffle(vect[i].begin(), vect[i].end());
		}

		stop = clock();
		ShuffleTime += stop - start;
	}

	void findElPos(vector<int> Position,int seekingValue) {
	

		for (int i = 0; i < vect.size(); i++) {
			for (int j = 0; j <vect[i].size(); j++) {
				if (vect[i][j] == seekingValue) {
					Position.push_back(i);
					Position.push_back(j);
					break;
				}
			}
		}

	}

	void printTime() {
		cout << "\nSort time=" << (double)SortTime / CLK_TCK << " reverese time=" << (double)ReverseTime / CLK_TCK << " shuffle time=" << (double)ShuffleTime / CLK_TCK << "\n";
	}

};



int main()
{
	int eh[4] = { 1,2,6,4 };
	int eeh[4][4] = { {1,5,3,9},
					  {5,1,7,4},
					  {4,2,3,6},
					  {6,7,8,4} };

	DynamicVector vec(*eeh, 4, 4);


}
