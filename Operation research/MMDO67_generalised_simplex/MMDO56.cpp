#include <string> 
#include <iostream>
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
        if (checkIfRhsM(rhs)) {
            m += rhs.m;
        }
        return *this;
    }

    mNumb& operator-=(const mNumb& rhs) {
        number -= rhs.number;
        if (checkIfRhsM(rhs)) {
            m -= rhs.m;
        }
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

    mNumb& operator*=(double coef) {
        number *= coef;
        if (checkIfM()) {
            m *= coef;
        }
        return *this;
    }

    mNumb& operator/=(double coef) {
        number /= coef;
        if (checkIfM()) {
            m /= coef;
        }
        return *this;
    }

    mNumb operator*(double coef) const {
        mNumb temp(*this);
        temp *= coef;
        return temp;
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

    simplexSolver(double *aArr,string *sArr,int eqN,int xN) {
    
    }

};

int main()
{
	int eqN = 4;
	int xN = 3;

	mNumb arr[] = { 
	{2},{-1},{8},
	{1},{1},{4},
	{-3},{2},{3}, 
	{2},{-1},{0} };

    string sArr[4] = { "<=","<=",">=","=" };

}

