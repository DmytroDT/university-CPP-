
#include <iostream>
#include <vector>

using namespace std;

#define n 3
#define m 4
#define r 99

void zerofy(int arr[n][m]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = 0;
		}
	}
}

int colSum(int arr[n][m],int j) {
	int colHolder = 0;
	for (int t = 0; t < n; t++) {
		colHolder += arr[t][j];
	}
	return colHolder;
}

int rowSum(int arr[n][m], int i) {
	int rowHolder = 0;
	for (int t = 0; t < m; t++) {
		rowHolder += arr[i][t];
	}
	return rowHolder;
}

void SouthWestAngle(int arr[n][m], int bArr[m],int aArr[n]) {

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < m; j++) {

			if (colSum(arr, j) <= bArr[j]) {

				arr[i][j] = min(bArr[j] - colSum(arr, j), aArr[i] - rowSum(arr, i));
			}
		}
	}

}

void printArr(int arr[n][m]) {

	cout << "\n";

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << arr[i][j] << "\t";
		}
		cout << "\n";
	}
}

void getEstimationArr(int arr[n][m], int tArr[n][m],  int estArr[n][m]) {

	int uVect[n];
	int vVect[m];

	for (int i = 0; i < n; i++) {
		uVect[i] = r;
	}
	for (int i = 0; i < m; i++) {
		vVect[i] = r;
	}

	uVect[0] = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((arr[i][j] != 0)&& (arr[i][j] != r)) {

				if (uVect[i] != r) {
					vVect[j] = tArr[i][j] - uVect[i];
				}
				else {
					if (vVect[j] != r) {
						uVect[i] = tArr[i][j] - vVect[j];
					}
					else {
						vVect[j] = 0;
						uVect[i] = tArr[i][j] ;
					}
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			estArr[i][j] = tArr[i][j] - (uVect[i] + vVect[j]);
		}
	}

}

int findNegativeEl(int estArr[n][m]) {
	int min = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
				if (estArr[i][j] < min) {
					min = estArr[i][j];
				}
		}
	}
	return min;
}

void cycleShift(int estArr[n][m],int arr[n][m]) {
	
	int minEl = findNegativeEl(estArr);
	int cEl, rEl;
	int minimal = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (minEl == estArr[i][j]) {
				cEl = j; rEl = i;
			}
		}
	}

		for (int i = 0; i < n; i++) {
			if ((i != rEl) && (arr[i][cEl] != 0) && (arr[i][cEl] != r)) {
				for (int j = 0; j < m; j++) {		
					if ((j != cEl) && (arr[i][j] != 0) && (arr[i][j] != r)) {
						if ((arr[rEl][j] != 0) && (arr[rEl][j] != r)) {
						
							minimal = min(arr[i][cEl], arr[rEl][j]);
							arr[rEl][cEl] += minimal;

							if ((arr[i][cEl] - minimal) == 0) {
								arr[i][cEl] = r;
							}
							else {
								arr[i][cEl] -= minimal;
							}
							
							if ((arr[rEl][j] - minimal) == 0) {
								arr[rEl][j] = r;
							}
							else {
								arr[rEl][j] -= minimal;
							}

							arr[i][j] += minimal;
							break;

						}
					}
				}
			}
		}

}

void eraseMarks(int arr[n][m]) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] == r) {
				arr[i][j] = 0;
			}
		}
	}
}

int calculateCost(int arr[n][m], int tArr[n][m]) {
	int amount = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			amount += (arr[i][j] * tArr[i][j]);
		}
	}
	return amount;
}

int main()
{
	cout << "MMDO lab  # 4-5" << endl << "Creator: Dmytro Dutkovskyi" << endl;
	cout << "----------------------------------" << endl;

	int exCount = 0;

	int tArr[n][m] = {	{2,4,5,1},
						{2,3,9,4},
						{3,4,2,5} };


	int bArr[] = { 40,30,30,50 };
	int aArr[] = { 60,70,20 };

	int oArr[n][m];

	int estArr[n][m];
	
	zerofy(oArr);
	zerofy(estArr);

	SouthWestAngle(oArr, bArr, aArr);

	getEstimationArr(oArr, tArr, estArr);

	cout << "\nOriginal cost matrix:\n";
	printArr(oArr);

	cout << "\nGeneral cost:" << calculateCost(oArr, tArr) << "\n";

	while (findNegativeEl(estArr) != 0 ){
		cout << "\nTransport matrix:\n";
		printArr(oArr);
	
		getEstimationArr(oArr, tArr, estArr);
		cout << "\nEstimation matrix:\n";
		printArr(estArr);
	
		cycleShift(estArr, oArr);
	
		exCount++;
	}

	eraseMarks(oArr);

	cout << "\nOptimised cost matrix:\n";
	printArr(oArr);

	cout << "\nGeneral cost:" << calculateCost(oArr, tArr)<<"\n";


	return 0;
}
