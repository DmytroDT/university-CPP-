#include <string> 
#include <iostream>
#include <vector>
using  namespace std;

class mNumb {
private:
    double number = 0.;
    double m = 0.;
public:

#pragma region constructors

    mNumb() : number(0.), m(0.) {}

    mNumb(double number_, double m_) : number(number_), m(m_) {}

    mNumb(double number_) : number(number_), m(0.) {}

    mNumb(const mNumb& copy) : number(copy.number), m(copy.m) {}

#pragma endregion

#pragma region gettersAndSetters
    double getN() const {
        return number;
    }

    double getM() const {
        return m;
    }

	void setN(double number) {
		this->number = number;
	}

	void setM(double m) {
		this->m = m;
	}

#pragma endregion
  
	friend ostream& operator<<(ostream& os, const mNumb& ref) {
		os << ref.number;
		if (ref.checkIfM()) {
			if (ref.m < 0) {
				os << ref.m << "M";
			}
			else {
				os << "+" << ref.m << "M";
			}
		}

		return os;
	}

#pragma region bool_same_type

    bool checkIfM() const {
        return (this->m != 0.);
    }

    bool checkIfRhsM(const mNumb& rhs) const {
        return (this->checkIfM() || rhs.checkIfM());
    }

    bool operator<(const mNumb& rhs) const {
        return (checkIfRhsM(rhs)) ? (this->m < rhs.m) : (this->number < rhs.number);
    }
    
    bool operator>(const mNumb& rhs) const {
        return rhs<*this;
    }

    bool operator<=(const mNumb& rhs) const {
        return !(*this > rhs);
    }

    bool operator>=(const mNumb& rhs) const {
        return !(*this < rhs);
    }
    
    bool operator==(const mNumb& rhs) const {
        return ((this->number==rhs.number)&&(this->m==rhs.m));
    }

    bool operator!=(const mNumb& rhs) const {
        return !(*this == rhs);
    }

#pragma endregion 

#pragma region bool_double

	bool operator<(double rhs) const {
		return (checkIfM()) ? (this->m < rhs) : (this->number < rhs);
	}

	bool operator>(double rhs) const {
		return (checkIfM()) ? (this->m > rhs) : (this->number > rhs);
	}

	bool operator<=(double rhs) const {
		return !(*this > rhs);
	}

	bool operator>=(double rhs) const {
		return !(*this < rhs);
	}

#pragma endregion 

#pragma region arithmetic

    mNumb& operator=(const mNumb& ref) {

        if (this != &ref) {
            number = ref.number;
            m = ref.m;
        }
        return *this;
    }

    mNumb& operator+=(const mNumb& rhs) {
        number += rhs.number;
        m += rhs.m;

        return *this;
    }

    mNumb& operator-=(const mNumb& rhs) {
        number -= rhs.number;
        m -= rhs.m;
        
        return *this;
    }

    mNumb operator+(const mNumb& rhs) const {
        mNumb temp(*this);
        temp += rhs;
        return temp;
    }

    mNumb operator-(const mNumb& rhs) const {
        mNumb temp(*this);
        temp -= rhs;
        return temp;
    }



	mNumb& operator*= (const mNumb & rhs) {
		if (!checkIfM()) {
			m = (number * rhs.m);
		}
		return *this;
	}

	mNumb operator*(const mNumb& rhs) const {
		mNumb temp(*this);
		temp *= rhs;
		return temp;
	}

	mNumb& operator/= (const mNumb& rhs) {
		if (!checkIfM()) {
			number = (m/rhs.m);
		}
		return *this;
	}

	mNumb operator/(const mNumb& rhs) const {
		mNumb temp(*this);
		temp /= rhs;
		return temp;
	}

	mNumb& operator*=(double coef) {
		number /= coef;
		if (checkIfM()) {
			m *= coef;
		}
		return *this;
	}

	mNumb operator*(double coef) const {
		mNumb temp(*this);
		temp *= coef;
		return temp;
	}

    mNumb& operator/=(double coef) {
        number /= coef;
        if (checkIfM()) {
            m /= coef;
        }
        return *this;
    }

    mNumb operator/(double coef) const {
        mNumb temp(*this);
        temp /= coef;
        return temp;
    }

#pragma endregion

};


template <typename T>
class Dynamic2Darray {

private:
	T** Array;
	unsigned int D1size = 1, D2size = 1;

public:
#pragma region constructors
	Dynamic2Darray(unsigned int D1size, unsigned int D2size) {

		this->D1size = D1size;
		this->D2size = D2size;

		Array = new T * [D1size];
		for (unsigned int i = 0; i < D1size; i++) {
			Array[i] = new T[D2size];
		}
	}

	Dynamic2Darray(const Dynamic2Darray<T>& refArr) {

		this->D1size = refArr.D1size;
		this->D2size = refArr.D2size;

		Array = new T * [D1size];
		for (unsigned int i = 0; i < D1size; i++) {
			Array[i] = new T[D2size];
		}

		for (unsigned int i = 0; i < D1size; i++) {
			for (unsigned int j = 0; j < D2size; j++) {
				Array[i][j] = refArr.Array[i][j];
			}
		}
	}

	Dynamic2Darray(T* arr, int D1size, int D2size) {

		this->D1size = D1size;
		this->D2size = D2size;

		Array = new T * [D1size];
		for (unsigned int i = 0; i < D1size; i++) {
			Array[i] = new T[D2size];
		}

		for (unsigned int i = 0; i < D1size; i++) {
			for (unsigned int j = 0; j < D2size; j++) {

				Array[i][j] = arr[i * D2size + j];
			}
		}
	}

	~Dynamic2Darray() {

		for (unsigned int i = 0; i < D1size; i++) {
			delete[] Array[i];
		}

		delete[] Array;
	}

	int getRowCount() {
		return D1size;
	}
	int getColCount() {
		return D2size;
	}

	void CopyTranspose(T* arr, int D1size, int D2size) {

		this->D1size = D1size;
		this->D2size = D2size;

		Array = new T * [D1size];
		for (unsigned int i = 0; i < D1size; i++) {
			Array[i] = new T[D2size];
		}

		for (unsigned int i = 0; i < D1size; i++) {
			for (unsigned int j = 0; j < D2size; j++) {

				Array[i][j] = arr[j * D2size + i];
			}
		}
	}
#pragma endregion

#pragma region structure_manipulation 
	void addRow(T* row) {

		T** newArray;
		this->D1size = D1size + 1;

		newArray = new T * [D1size];
		for (unsigned int i = 0; i < D1size; i++) {
			newArray[i] = new T[D2size];
		}

		for (unsigned int i = 0; i < D1size - 1; i++) {
			for (unsigned int j = 0; j < D2size; j++) {
				newArray[i][j] = Array[i][j];
			}
		}

		for (int j = 0; j < D2size; j++) {
			newArray[D1size - 1][j] = row[j];
		}

		for (unsigned int i = 0; i < D1size - 1; i++) {
			delete[] Array[i];
		}
		delete[] Array;

		Array = newArray;

	}

	void addCol(T* col) {

		T** newArray;
		this->D2size = D2size + 1;

		newArray = new T * [D1size];
		for (unsigned int i = 0; i < D1size; i++) {
			newArray[i] = new T[D2size];
		}

		for (unsigned int i = 0; i < D1size; i++) {
			for (unsigned int j = 0; j < D2size - 1; j++) {
				newArray[i][j] = Array[i][j];
			}
		}

		for (int j = 0; j < D1size; j++) {
			newArray[j][D2size - 1] = col[j];
		}

		for (unsigned int i = 0; i < D1size; i++) {
			delete[] Array[i];
		}
		delete[] Array;

		Array = newArray;

	}
#pragma endregion

	T& operator()(int indexR, int indexC) {
		return Array[indexR][indexC];
	}

	friend ostream& operator<<(ostream& os, Dynamic2Darray& dArr) {

		os << "\nDynamic array elements:\n";
		for (unsigned int i = 0; i < dArr.D1size; i++) {
			for (unsigned int j = 0; j < dArr.D2size; j++) {
				os << "A[" << i << "][" << j << "]=" << dArr.Array[i][j] << "\t";
			}
			os << endl;
		}
		return os;
	}

	Dynamic2Darray<T>& operator = (const Dynamic2Darray& arrCpy) {


		for (unsigned int i = 0; i < D1size; i++) {
			delete[] Array[i];
		}

		delete[] Array;

		this->D1size = arrCpy.D1size;
		this->D2size = arrCpy.D2size;

		Array = new T * [D1size];
		for (unsigned int i = 0; i < D1size; i++) {
			Array[i] = new T[D2size];
		}

		for (unsigned int i = 0; i < D1size; i++) {
			for (unsigned int j = 0; j < D2size; j++) {
				Array[i][j] = arrCpy.Array[i][j];
			}
		}

		return *this;

	}

};

class simplexSolver {
private:
	Dynamic2Darray<mNumb>* mArr;
public:

    simplexSolver(mNumb aArr[],mNumb bArr[],string sArr[],int eqN,int xN) {
		mArr=new Dynamic2Darray<mNumb>(aArr, eqN, xN);

			addArtificialBasis(mArr, sArr);
			mArr->addCol(bArr);
			inverseTargetF();
			seekBasis(-1);
    }

	mNumb* additionalBasis(int pos,int val,int size) {
		mNumb* arr = new mNumb[size];

		for (int i = 0; i < size; i++) {
			arr[i] = (i == pos) ? *(new mNumb(val)) : *(new mNumb(0));
		}
		return arr;
	}

	void addArtificialBasis(Dynamic2Darray<mNumb> *arr, string signV[]) {
		int eqN = arr->getRowCount();

		for (int i = 0; i < eqN; i++) {
			if (signV[i] == "<=") {
				arr->addCol(additionalBasis(i, 1, eqN));
			}
			else {
				if (signV[i] == ">=") {
					arr->addCol(additionalBasis(i, 1, eqN));
					arr->addCol(additionalBasis(i, -1, eqN));
					(*arr)(eqN-1, arr->getColCount()-1).setM(-1);
				}
			}
		}
	}

	void inverseTargetF() {
		for (int i = 0; i < mArr->getColCount(); i++) {
			(*mArr)(mArr->getRowCount() - 1, i) *= (-1);
		}
	}

	vector<int> seekBasis(int sign) {
		int rowC = mArr->getRowCount()-1;
		int colC = mArr->getColCount()-1;
		int numbersInc;
		vector<int> indexVect;
		
		for (int i = 0; i < rowC; i++) {
			numbersInc = 0;
			for (int j = 0; j < colC; j++) {
				if (((*mArr)(i, j)*sign) > 0.) {
					numbersInc++;
				}
				if (numbersInc == 1) {
					indexVect.push_back(i);
					indexVect.push_back(j);
				}
			}
		}
		return indexVect;
	}

	void eliminateObjectiveM(vector<int> nAIV) {
		for (int i = 0; i < nAIV.size(); i+=2) {

		}
	}

	void printSolution() {
		cout << *mArr;
	}

};

int main()
{
	int eqN = 4;
	int xN = 3;

	mNumb arr[] = { 
	{2},{-1},
	{1},{1},
	{-3},{2}, 
	{2},{-1}, };

	mNumb bArr[] = { 8,4,3,0 };

    string sArr[4] = { "<=","<=",">=","=" };

	simplexSolver s(arr,bArr,sArr,eqN,xN-1);

	s.printSolution();

	mNumb a(0, 1);
	mNumb b(0);
	a= b-a;
	cout << "\n"<<a;
}

