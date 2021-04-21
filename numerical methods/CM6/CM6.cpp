#include <iostream>
#include <cmath>
#include <iomanip>  
#include <string>
using namespace std;


class EitkenScheme {
private:
	double** arr;
	int n;
	double x;

public:
	EitkenScheme(double a, double b, double h, double x) {

		int n = round(((b - a) / h) + 1);
		this->n = n;
		this->x = x;
		double temp;

		arr = new  double* [n];
		for (int i = 0; i < n; i++) {
			arr[i] = new  double[n];
		}

		zerofy(n);

		for (int i = 0; i < n; i++) {
			temp = a + i * h;
			arr[i][1] = cos(temp);
			arr[i][0] = temp;
		}

	}

	void zerofy(int n) {

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				arr[i][j] = 0;
			}
		}
	}

	void compute() {
		double yn, yn1, xn, xn1;
		int inc = 0;


		for (int i = 2; i < n; i++) {

			yn = arr[0][i - 1];
			xn = arr[i - 2][0];

			for (int j = 0; j < n - i + 1; j++) {

				yn1 = arr[j + 1][i - 1];

				xn1 = arr[j + i - 1][0];

				arr[j][i] = (yn * (xn1 - x) - yn1 * (xn - x)) / (xn1 - xn);
			}

		}
	}

	double getResult() {
		double result = 0;
		for (int i = 1; i < n - 1; i++) {
			if (abs(arr[0][i + 1] - arr[0][i]) <= abs(arr[0][i - 1] - arr[0][i])) {
				result = arr[0][i + 1];
			}
		}
		return result;
	}

	friend ostream& operator<<(ostream& os, EitkenScheme& es) {

		os << "\n";
		os << setw(15) << left << "x" << right << " y\t";
		string str = "0";
		for (int i = 1; i < es.n - 1; i++) {
			str += to_string(i);
			os << "\tP" + str + "\t";
		}
		os << "\n";

		for (int i = 0; i < es.n; i++) {
			os << "\n";
			for (int j = 0; j < es.n; j++) {
				os << setw(15) << left << setprecision(7) << es.arr[i][j] << "\t";
			}
		}
		return os;
	}

	void getE() {
		double r = cos(x);
		cout << "\n\nAbsolute me:";
		for (int i = 2; i < n; i++) {
			cout << "\n";
			for (int j = 0; j < n - i + 1; j++) {
				cout << setw(10) << left << setprecision(10) << fixed << abs(arr[j][i] - r) << " ";
			}
		}
		cout << "\nRelative me:";
		for (int i = 2; i < n; i++) {
			cout << "\n";
			for (int j = 0; j < n - i + 1; j++) {
				cout << setw(10) << left << setprecision(10) << fixed << 100 * abs(arr[j][i] - r) / r << "% ";
			}
		}
		cout << "\n";
	}

	~EitkenScheme() {
		for (int i = 0; i < n; i++) {
			delete[] arr[i];
		}
		delete[] arr;
	}
};

int main()
{

	double a = 0.7511, b = 0.8511, h = 0.025;
	double x = 0.775;
	double result, ap, vp;

	cout << "4M lab  # 6" << endl << "Creator: Dmytro Dutkovskyi" << endl;
	cout << "----------------------------------" << endl;
	cout << "input a,b,h,x:" << endl;
	cin >> a >> b >> h >> x;

	EitkenScheme es(a, b, h, x);

	es.compute();
	cout << es;
	result = es.getResult();
	ap = abs(cos(x) - result);
	vp = abs(100 * ap / cos(x));
	es.getE();

	cout << "\nAbsolute me=" << fixed << setw(10) << setprecision(10) << ap << " relative me=" << fixed << setw(10) << setprecision(10) << vp << "%";
	cout << "\n";
	return 0;
}
