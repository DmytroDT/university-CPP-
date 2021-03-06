#include <string> 
#include <iostream>
#include <iomanip>  
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
				os << setprecision(2) << ref.m << "M";
			}
			else {
				os << "+"  << setprecision(2) << ref.m << "M";
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

	bool operator==(double rhs) const {
		return (!checkIfM())&&(this->number == rhs);
	}

	bool operator!=(double rhs) const {
		return !(*this == rhs);
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
		if (!checkIfM()&&(getN() != 0)) {
			//m = (number * rhs.m);
			//number = 0.;
			*this = rhs * this->getN();
		}
		return *this;
	}

	mNumb operator*(const mNumb& rhs) const {
		mNumb temp(*this);
		temp *= rhs;
		return temp;
	}

	mNumb& operator/= (const mNumb& rhs) {
		if (!checkIfM()&&(getN() != 0)) {
			//number = (m/rhs.m);
			//m = 0.;
			*this = rhs / this->getN();
		}
		return *this;
	}

	mNumb operator/(const mNumb& rhs) const {
		mNumb temp(*this);
		temp /= rhs;
		return temp;
	}

	mNumb& operator*=(double coef) {
		number *= coef;
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
		cout << "\n";
		for (unsigned int i = 0; i < dArr.D1size; i++) {
			for (unsigned int j = 0; j < dArr.D2size; j++) {
				//os << "A[" << i << "][" << j << "]=" << dArr.Array[i][j] << "\t";
				os << dArr.Array[i][j]<<"\t";
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
	bool minOrMax;
	mNumb* objectiveF;
public:

    simplexSolver(bool minOrMax,mNumb aArr[],mNumb bArr[],string sArr[],int eqN,int xN) {
		this->minOrMax = minOrMax;
			mArr=new Dynamic2Darray<mNumb>(aArr, eqN, xN);
			if (minOrMax) {
				inverseTargetF();
			}
			addArtificialBasis(mArr, sArr);
			mArr->addCol(bArr);
			printSolution();
			inverseTargetF();
			eliminateObjectiveM(seekMBasis(seekBasis()));
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

		for (int i = 0; i < eqN-1; i++) {
			if (signV[i] == "<=") {
				arr->addCol(additionalBasis(i, 1, eqN));
			}
		
			if (signV[i] == ">=") {
				arr->addCol(additionalBasis(i, 1, eqN));
				(*arr)(eqN - 1, arr->getColCount() - 1).setM(-1);
				arr->addCol(additionalBasis(i, -1, eqN));
			}
			
			if (signV[i] == "=") {
				arr->addCol(additionalBasis(i, 1, eqN));
				(*arr)(eqN - 1, arr->getColCount() - 1).setM(-1);
			}
		}
	}

	void inverseTargetF() {
		for (int i = 0; i < mArr->getColCount(); i++) {
			(*mArr)(mArr->getRowCount() - 1, i) *= (-1);
		}
	}

	vector<int> seekBasis() {
		int rowC = mArr->getRowCount()-1;
		int colC = mArr->getColCount()-1;
		int numbersInc;
		int row = 0;
		vector<int> indexVect;
		
		for (int i = 0; i < colC; i++) {
			numbersInc = 0;
			for (int j = 0; j < rowC; j++) {
				if ((*mArr)(j, i) > 0.) {
					numbersInc++;
					row = j;
				}
			}
			if (numbersInc == 1) {
				indexVect.push_back(row);
				indexVect.push_back(i);
			}
		}
		return indexVect;
	}

	vector<int> seekMBasis(vector<int> nAIV) {
		vector<int> nBV;

		if (nAIV.size() > 1) {
			for (int i = 0; i < nAIV.size(); i += 2) {
				if ((*mArr)(mArr->getRowCount() - 1, nAIV[i + 1]).checkIfM()) {
					nBV.push_back(nAIV[i]);
					nBV.push_back(nAIV[i + 1]);
				}
			}
			return nBV;
		}
	}

	void eliminateObjectiveM(vector<int> nAIV) {
		
		if (nAIV.size() > 1) {
			for (int i = 0; i < nAIV.size(); i += 2) {
				addRowsM(copyRow(nAIV[i]), mArr->getRowCount() - 1, (*mArr)(mArr->getRowCount() - 1,nAIV[i+1])*(-1));
			}
		}
	}

	mNumb* copyRow(int rIndex) {
		int rSize = mArr->getColCount();
		mNumb* tArr = new mNumb[rSize];

		for (int i = 0; i < rSize; i++) {
			tArr[i] = (*mArr)(rIndex, i);
		}
		return tArr;
	}

	void addRowsM(mNumb* copy,int rIndex, mNumb coef) {
		int rSize = mArr->getColCount();

		for (int i = 0; i < rSize; i++) {
			copy[i] *= coef;
			 (*mArr)(rIndex, i)+=copy[i];
		}
	}

	void addRowsCoef(mNumb* copy, int rIndex, double coef) {
		int rSize = mArr->getColCount();

		for (int i = 0; i < rSize; i++) {
			copy[i] *= coef;
			(*mArr)(rIndex, i) += copy[i] ;
		}
	}

	int findMinCol() {
		int index=0;
		mNumb min(0., 0.);
		mNumb* ref;

		for (int i = 0; i < mArr->getColCount()-1; i++) {
			ref = &(*mArr)(mArr->getRowCount() - 1, i);
			if ((*ref<0)&&(min> *ref)) {
				min = *ref;
				index = i;
			}
		}
		return index;
	}

	int findMinRrow(int col) {
		int row=0;
		mNumb ratio;
		mNumb min(30);
		mNumb* ref;
		mNumb* refB;

		for (int i = 0; i < mArr->getRowCount() - 1; i++) {
			ref = &(*mArr)(i, col);
			refB = &(*mArr)(i, mArr->getColCount()-1);
			ratio = (*refB !=0)? (*refB / (ref->getN())) : (*ref*0.001);
			ratio = (*refB / (ref->getN()));
			if ((ratio > 0) && ((min > ratio))) {
				row = i;
				min = ratio;
			}
		}
		return row;
	}

	void normalise(int row, int col) {
		double coef = (*mArr)(row, col).getN();

		for (int i = 0; i < mArr->getColCount(); i++) {
			(*mArr)(row, i) /= coef;
		}

	}

	void pivot(int row, int col) {
		mNumb mCoef;
		double coef = 0;
		normalise(row, col);

		for (int i = 0; i < mArr->getRowCount(); i++) {
			copyRow(row);
			if (i != row) {
				if ((*mArr)(i, col).checkIfM()) {
					mCoef = (*mArr)(i, col)*(-1);
					addRowsM(copyRow(row), i, mCoef);
				}
				else {					
					coef = -((*mArr)(i, col).getN());
					addRowsCoef(copyRow(row), i, coef);
				}
			}
		}
	}

	bool optimal() {
		bool result = true;
		for (int i = 0; i < mArr->getColCount()-1; i++) {
			if ((*mArr)(mArr->getRowCount() - 1, i) < 0.) {
				result = false;
			}
		}
		return result;
	}

	void solve() {
		int opR = 0;
		int opC = 0;

		while (!optimal()) {			
			opC = findMinCol();
			opR = findMinRrow(opC);
			cout << "\nmin col -" << opC << " min row -" << opR;
			pivot(opR, opC);
			printSolution();
		}
	}

	void printSolution() {
		cout << *mArr;
	}

};

int main()
{
	cout << "MMDO lab  # 6-7" << endl << "Creator: Dmytro Dutkovskyi" << endl;
	cout << "----------------------------------\n" << endl;

	int eqN = 5;
	int xN = 4;

	mNumb arr1[] = {
	{2}, { -1 },
	{ 1 }, { 1 },
	{ -3 }, { 2 },
	{ -2 }, { 1 },
};

	mNumb bArr1[] = { 8,5,3,0 };
	
	string sArr1[4] = { "<=","<=",">=","=" };
	
	simplexSolver sMaxlb7(false, arr1, bArr1, sArr1, eqN-1, xN - 2);
	
	simplexSolver sMinlb7(true, arr1, bArr1, sArr1, eqN-1, xN - 2);
	

	cout << "\nSeeking max of objective function:\n";
	sMaxlb7.solve();
	sMaxlb7.printSolution();
	
	
	cout << "\nSeeking min of objective function:\n";
	sMinlb7.solve();
	sMinlb7.printSolution();

	mNumb arr[] = { 
		{-8}, {2}, {-1},
		{-4}, {1}, {1},
		{-3}, {-3},{2},
		{0},  {2},{3},
		{0},  {2}, {-1} };

	mNumb bArr[] = { 0,0,0,1,0 };

    string sArr[5] = { "<=","<=",">=","=","=" };

	cout << "\nSeeking max of objective function:\n";

	simplexSolver sMax(false,arr,bArr,sArr,eqN,xN-1);
	sMax.printSolution();
	sMax.solve();

	cout << "\nSeeking min of objective function:\n";

	simplexSolver sMin(true, arr, bArr, sArr, eqN, xN - 1);
	sMin.printSolution();
	sMin.solve();

}

