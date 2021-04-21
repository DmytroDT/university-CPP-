#include <iostream>
#include <random>
#include <algorithm>
#include <time.h>
using namespace std;

template <typename T>
class Dynamic2Darray {

private:
	T** Array;
	unsigned int D1size=1, D2size=1;
	clock_t SortTime, ReverseTime, ShuffleTime;

public:

	Dynamic2Darray( unsigned int D1size, unsigned int D2size) {	

		this->D1size = D1size;
		this->D2size = D2size;

		Array = new T* [D1size];
		for (unsigned int i = 0; i < D1size; i++) {
			Array[i] = new T[D2size];
		}
	}

	 Dynamic2Darray(const Dynamic2Darray<T>& refArr) {

		 this->D1size = refArr.D1size;
		 this->D2size = refArr.D2size;
		
		 Array = new T* [D1size];
		 for (unsigned int i = 0; i < D1size; i++) {
			 Array[i] = new T[D2size];
		 }

		 for (unsigned int i = 0; i < D1size; i++) {
			 for (unsigned int j = 0; j < D2size; j++) {
				 Array[i][j] = refArr.Array[i][j];
			 }
		 }
	 }

	 Dynamic2Darray( T* arr,int D1size, int D2size ) {

		 this->D1size = D1size;
		 this->D2size = D2size;

		 Array = new T * [D1size];
		 for (unsigned int i = 0; i < D1size; i++) {
			 Array[i] = new T[D2size];
		 }

		 for (unsigned int i = 0; i < D1size; i++) {
			 for (unsigned int j = 0; j < D2size; j++) {

				 Array[i][j] = arr[i*D2size+j];
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
		this->D1size = D1size+1;

		newArray = new T * [D1size];
		for (unsigned int i = 0; i < D1size; i++) {
			newArray[i] = new T[D2size];
		}

		for (unsigned int i = 0; i < D1size-1; i++) {
			for (unsigned int j = 0; j < D2size; j++) {
				newArray[i][j] = Array[i][j];
			}
		}

		for (int j = 0; j < D2size; j++) {
			newArray[D1size-1][j] = row[j];
		}

		for (unsigned int i = 0; i < D1size-1; i++) {
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

		for (unsigned int i = 0; i < D1size ; i++) {
			for (unsigned int j = 0; j < D2size-1; j++) {
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

	bool inputEl(unsigned int row, unsigned int col, T value) {
		if (row<D1size&&col<D2size){
			Array[row][col] = value;
			return true;
		}
		else{
			return false;
		}
	}

	 friend ostream& operator<<(ostream& os, Dynamic2Darray& dArr) {

		 os << "\nDynamic array elements:\n";
		 for (unsigned int i = 0; i < dArr.D1size; i++) {
			 for (unsigned int j = 0; j < dArr.D2size; j++) {
				 os <<"A["<<i<<"]["<<j<<"]=" << dArr.Array[i][j]<<"\t";
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

	 void fillWithRandom(int D1size, int D2size) {
	
		 this->D1size = D1size;
		 this->D2size = D2size;
	
		 Array = new T * [D1size];
		 for (unsigned int i = 0; i < D1size; i++) {
			 Array[i] = new T[D2size];
		 }


		 default_random_engine eng;
		 uniform_int_distribution<T> val(0, 100);
	
		 for (int i = 0; i < D1size; i++) {
			 for (int j = 0; j < D2size; j++) {
				 Array[i][j] = val(eng);
			 }
		 }
	
	 }

	 void  swap(int* a, int* b) {
		 int temp = *a;
		 *a = *b;
		 *b = temp;
	 }

	 void sortOut()
	 {
		 clock_t start, stop;
		 start = clock();

		 for (int i = 0; i < D1size; i++) {
			 sort(&Array[i][0], &Array[i][D2size - 1]);
		 }

		 stop = clock();
		 SortTime += stop - start;
	 }

	 void reverseSelf()
	 {

		 clock_t start, stop;
		 start = clock();

		 for (int i = 0; i < D1size; i++) {
			 reverse(&Array[i][0], &Array[i][D2size - 1]);
		 }
		

		 stop = clock();
		 ReverseTime += stop - start;
	 }

	 void shuffle() {

		 clock_t start, stop;
		 start = clock();
		 for (int i = 0; i < D1size; i++) {
			 sort(&Array[i][0], &Array[i][D2size - 1]);
		 }
		 stop = clock();
		 ShuffleTime += stop - start;

	 }

	 void printTime() {
		 cout << "\nSort time=" << (double)SortTime / CLK_TCK << " reverese time=" << (double)ReverseTime / CLK_TCK << " shuffle time=" << (double)ShuffleTime / CLK_TCK << "\n";
	 }

	  T getElement(int indR, int indC) {
		 return Array[indR][indC];
	}

	 template<typename T>
	 friend class Dynamic2DIterator;

};


template<typename T>
class Dynamic2DIterator {
private:
	 Dynamic2Darray<T>& arrRef;
	int index=1;
public:

	Dynamic2DIterator( Dynamic2Darray<T>& ref) : arrRef(ref){
		index = 1;
	}

	void operator++(int){
		index++;
	}

	bool operator()(){
		return index != arrRef.D1size * arrRef.D2size;
	}

	T operator *(){
		int rowIndex = 0;
		int colIndex = index;
		T retVal;

		if (colIndex > (arrRef.D2size)) {
			while (colIndex > (arrRef.D2size)) {
				colIndex -= arrRef.D2size ;
				rowIndex++;
			}
		}
		retVal = arrRef.getElement(rowIndex, colIndex-1);

		return retVal;
	}

};

int main()
{
	int eh[4][4] = { {5,2,6,7},{3,4,3,1},{1,7,3,5},{12,7,5,2} };

	char eeh[5][4] = { "abs","adg","bey","eqc" ,"jkt" };

	Dynamic2Darray<int> Arr3(*eh, 4,4);
	Dynamic2Darray<char> Arr2(*eeh, 5, 4);

	cout << Arr3;
	cout << Arr2;

	Dynamic2DIterator<int> iter(Arr3);
	
	cout << "\nLine of ints:\n";

	while (iter()) {
		cout <<" "<< *iter;
		iter++;
	}

	cout << "\n\n";

	Dynamic2DIterator<char> iter2(Arr2);

	cout << "\nLine of chars:\n";

	while (iter2()) {
		cout << " " << *iter2;
		iter2++;
	}

	cout << "\n\n";

}
