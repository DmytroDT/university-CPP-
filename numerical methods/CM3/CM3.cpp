#include <iostream>
#include <iomanip>  
#include <math.h>  

using namespace std;
#define rown 5

void displayMatrix(double** arr, int coln) {

	cout << "\nx1\tx2\tx3\tx4\tb\n\n";

	for (int i = 0; i < coln; i++) {
		for (int j = 0; j < rown; j++) {
			cout << setw(8) << left << setprecision(4) << arr[i][j];
		}
		cout << endl;
	}

}

//void solveMatrixJordana(double** arr, int coln) {
//
//	double numholder;
//	int ind = rown - 2, ink = 2,inc=1;
//	double hold[rown];
//
//	for (int i = 0; i < coln; i++) {
//
//		numholder = arr[i][ind];
//
//		for (int j = 0; j < rown; j++) {
//			arr[i][j] /= numholder;
//			hold[j] = arr[i][j];
//		}
//
//		for (int k = 0; k < coln; k++) {
//			if (k != i) {
//				numholder = arr[k][rown - ink];
//
//				for (int m = 0; m < rown; m++) {
//					arr[k][m] /= numholder;
//					arr[k][m] -= hold[m];
//				}
//			}
//		}
//		ink++;
//		ind--;
//		cout << "\nPass" << inc << ":\n";
//		displayMatrix(arr, 4);
//		inc++;
//	}
//}


void solveMatrixJordana(double** a, int coln) {
	double ratio = 0;


	for (int i = 0; i < rown; i++)
	{

		for (int j = 0; j < rown; j++)
		{
			if (i != j)
			{
				ratio = a[j][i] / a[i][i];
				for (int k = 1; k < coln; k++)
				{
					a[j][k] = a[j][k] - ratio * a[i][k];
				}
			}
		}
	}
	/* Obtaining Solution */
	for (int i = 1; i < rown; i++)
	{
		a[i][coln] = a[i][rown + 1] / a[i][i];
	}


}

void forwardPassGauss(double** arr, int coln) {

	double numholder,numh;
	int ink = 0;
	double hold[rown];

	for (int i = 0; i < coln; i++) {

		numholder = arr[i][i];
	
		for (int j = 0; j < rown; j++) {
			hold[j] = arr[i][j];
		}

		for (int h = i + 1; h < rown; h++) {
		
			numh = arr[h][ink];
			for (int j = 0; j < coln; j++) {
				arr[h][j] -= (hold[j] * numh) / numholder;
			}
		}
		displayMatrix(arr, 4);
		ink++;
	}
}



void findX(double** arr,int coln) {
	int inc = 0,ind=3;

	for (int h = 0; h < coln; h++)
	{
		for (int w = 0; w < rown; w++)
		{
			if ((h == inc) && (w == ind)) {
				arr[inc][4] /= arr[inc][ind];
				arr[inc][ind] /= arr[inc][ind];
			}
		}
		inc++;
		ind--;
	}
}


double** copyArr(double arr[][rown], int coln, double e)
{
	double** arr2D = 0;
	arr2D = new double* [coln];

	for (int h = 0; h < coln; h++)
	{
		arr2D[h] = new double[rown];

		for (int w = 0; w < rown; w++)
		{
			if ((h == 2) && (w == 2)) {
				arr2D[h][w] = e;
			}
			else {
				arr2D[h][w] = arr[h][w];
			}
			
		}
	}

	return arr2D;
}

int main()
{
	int N=1;
	cout << "4M lab  # 3" << endl << "Creator: Dmytro Dutkovskyi" << endl;
	cout << "----------------------------------" << endl;
	cout << "input N:" << endl;
	cin >> N;

	double k = 0.01*N, e = 0.1, numholder;
	 double enc = 0.1;
	int ind = rown - 2,ink=2;
	double hold[rown];

	//double sle[4][rown] = {
	//	{(1+k),2,3,-2,6},
	//	{2,-k,-2,-3,8*(1-k)},
	//	{3,2,-e,(2-k),4*k},
	//	{2,-3,2,1,-8*(1+3*k)} 
	//};


	double sle[4][rown] = {
		{1,2,0,0,6},
		{2,2,2,0,8},
		{0,2,2,2,4},
		{0,0,2,1,8}
	};


	double **cop1;
	cop1= copyArr(sle, 4, e);


	cout << "\nOriginal matrix:\n" << endl;
	displayMatrix(cop1, 4);

	solveMatrixJordana(cop1, 4);
	findX(cop1,4);
	cout << "result:\n";
	displayMatrix(cop1, 4);
	system("pause");
}
