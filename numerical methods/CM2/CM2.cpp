#include <iostream>
#include <vector>
#include <math.h>
#define arl 6

using namespace std;

void displayEqu(vector<double> v) {
	
	int j = 0;
	
	cout << "\n";
	for (int i = v.size() - 1; i >= 0; i--) {

		if (i != 0) {
			if (v[j] != 0) {
				if (v[j] > 0) {
					cout << "+" << v[j] << "x^" << i << " ";
				}
				else { cout << v[j] << "x^" << i << " "; }
			}
		}
		else {
			if (v[j] != 0) {
				if (v[j] != 0) {
					if (v[j] > 0) {
						cout << "+" << v[j];
					}
					else { cout << v[j]; }
				}
			}
		}

		j++;
	}
	cout << "\n";
}

vector<double> takeDerivative(vector<double> a) {

	vector<double> resultingVector(a.size() - 1);

	for (int i = 0; i < (a.size() - 1); i++) {
		resultingVector[i] = a[i] * (a.size() - (1. + i));
	}
	return resultingVector;
}

void revEqu(vector<double>& a) {

	for (int i = 0; i <= a.size() - 1; i++) {
		a[i] *= -1;
	}
}

vector<double> multiplybyx(vector<double> v) {

	vector<double> resultingVector(v.size() + 1);

	for (int i = 0; i < (v.size() - 1); i++) {
		resultingVector[i + 1.] = v[i];
	}
	return resultingVector;
}

void vectNorm(vector<double>& a) {
	
	while (a[0] == 0) {
		for (int i = 0; i < a.size() - 1; i++) {
			a[i] = a[i + 1.];
		}
		a.pop_back();
	}
}

vector<double> subtractEqu(vector<double> a, vector<double> b) {

	vector<double> resultingVector(a.size());
	double coef = (a[0] / b[0]);
	int dif = (int)abs((double)a.size() - b.size());

	for (int i = 0; i < dif; i++) {
		b.push_back(0);
	}
	for (int i = 0; i <= (a.size() - 1.); i++) {
		resultingVector[i] = a[i] - b[i] * coef;
	}

	vectNorm(resultingVector);
	return resultingVector;
}

double equSum(vector<double> a, int num) {
	
	double result = 0;

	for (int i = 0; i <= (a.size() - 1.); i++) {
		result += a[i] * pow(num, (a.size() - 1.) - i);
	}
	return result;
}

void normCoef(vector<double>& a) {
	double dif = abs(a[0]);
	for (int i = 0; i <= a.size() - 1; i++) {
		a[i] /= dif;
	}
}

vector<double> equDivision(vector<double> a, vector<double> b) {

	vector<double> resultingVector = a;

	while (resultingVector.size() >= b.size()) {
		resultingVector = subtractEqu(resultingVector, b);
	}
	normCoef(resultingVector);
	revEqu(resultingVector);

	return resultingVector;
}

char rangeSign(vector<double> a, int num) {
	double sm = equSum(a, num);
	if (sm == 0) {
		return '0';
	}
	else {
		if (sm > 0) {
			return '+';
		}
		else {
			return '-';
		}
	}
	
}

void fillSign(char* ar, vector<double>* vr,int size, int num) {
	for (int i = 0; i < size; i++) {
		ar[i] = rangeSign(vr[i], num);
	}
}


int countSigns(char* ar, int size) {
	char lastSign='0';
	int  inc = 0;
	for (int j = 0; j <= size; j++) {

		if (ar[j] != '0') {
			lastSign = ar[j];
		}

		if ((ar[j + 1] != '0')&&(lastSign!='0')) {

			if (lastSign != ar[j + 1]) {
				inc++;
			}
		}
		else { continue; }
	}
	return inc;
}

void countRoots(int* ind,int* val,int size) {
	int inc = 1;
	for (int i = 0; i < size-1; i++) {
		if (val[i] != val[i + 1]) {
			cout << "\n" << ind[i] << "<x" << inc << "<" << ind[i + 1];
			inc++;
		}
	}
}

void displayRow(char* ar){
	cout << " |  " << ar[0] << "  | " << ar[1] << " | " << ar[2] << " | " << ar[3] << " | " << ar[4] << " | " << ar[5] << " |  " << countSigns(ar, arl-2) << "  |";
}

vector<double> minusX(vector<double> a) {
	vector<double> b=a;
	for (int i = 0; i <= a.size() - 1.; i++) {
		if(i%2==0){
			b[i] *= (-1);
		}
	}
	return b;
}

int main()
{

	char sA[arl];
	int countAr[arl-1];
	int indxAr[arl - 1];
	int amntOfRts = 0,infCp,infCm;
	int upperborder=1, lowerborder=1;
	int input;

	cout << "4m lab  # 2" << endl << "Creator: Dmytro Dutkovskyi" << endl;
	cout << "----------------------------------" << endl;

	vector<double> original;

	for (int i = 0; i < arl-1; i++) {
		cout << "input coeficient of x^" << arl -1-i << ":";
		cin >> input;
		original.push_back(input);
		cout << endl;
	}
	cout << "input C:";
	cin >> input;
	original.push_back(input);
	cout << endl;

	vector<double> VectArray[arl];
	VectArray[0] = original;

	cout << "\nF:";
	displayEqu(VectArray[0]);

	cout << "\nf0:";
	vector<double> s1 = takeDerivative(original);
	VectArray[1] = s1;
	displayEqu(VectArray[1]);

	for (int i = 2; i < arl; i++) {
		cout << "\nf"<<i-1<<":";
		VectArray[i] = equDivision(VectArray[i-2], VectArray[i-1]);
		displayEqu(VectArray[i]);
	}

	while (equSum(original,upperborder) <= 0) {
		upperborder++;
	}

	while (equSum(minusX(original), lowerborder) >= 0) {
		lowerborder++;
	}

	lowerborder *= (-1);

	cout << "\nUpper boundry : " << upperborder << " , lower boundry : " << lowerborder<<".\n";

	cout << "\nSturm sequence:\n";
	cout << "+---+-----+---+---+---+---+---+-----+\n| x |F(x) |f0 |f1 |f2 |f3 |f4 |W(x) |";
	cout << "\n+---+-----+---+---+---+---+---+-----+";
	cout << "\n|-8";

	fillSign(sA, VectArray, arl, lowerborder -8);
	displayRow(sA);
	infCm = countSigns(sA, arl);

	fillSign(sA, VectArray, arl, upperborder +8);
	infCp = countSigns(sA, arl);

	amntOfRts = abs(infCm - infCp);

	for (int i = lowerborder; i <= upperborder; i++) {

		fillSign(sA, VectArray, arl, i);
		indxAr[i+ abs(lowerborder)] = i;
		countAr[i + abs(lowerborder)] = countSigns(sA, arl);
		

		if (i < 0) {
			cout << "\n|" << i;	
		}
		else{	
			cout << "\n| " << i;	
		}

		displayRow(sA);

	}
	cout << "\n|+8";
	fillSign(sA, VectArray, arl, upperborder + 8);
	displayRow(sA);
	cout << "\n+---+-----+---+---+---+---+---+-----+\n\n";

	cout << "Amount of roots in this equation = " << amntOfRts << endl;
	cout << "Ranges of roots:";
	countRoots(indxAr, countAr, (abs(lowerborder)+abs(upperborder)+1));
	cout << "\n";

	system("pause");
}

