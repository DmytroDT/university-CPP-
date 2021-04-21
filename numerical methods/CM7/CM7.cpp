#include <iostream>
#include <cmath>
#include <iomanip>  
using namespace std;

class IntegralPolynom {
private:

	double arrX[11] = { 1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2 };

	double arrY[11] = { 3.82,4.1,4.42,4.77,5.16,5.58,6.05,6.57,7.15,7.79,8.49 };

	int n = 11;

public:

	double calcPolynomial(double x, int degree) {
		double p = 1, result = 0;

		for (int i = 0; i <= degree; i++) {

			p = 1;
			for (int j = 0; j <= degree; j++) {
				if (i != j) {

					p *= (x - arrX[j]) / (arrX[i] - arrX[j]);
				}
			}
			result += p * arrY[i];
		}

		return result;
	}

	double integrateBySquares(double a, double b, int n, int dg) {
		double h = (b - a) / n;
		double result = 0;

		for (double i = a; i < b + h; i += h) {
			result += calcPolynomial(i, dg);
		}
		return result *= h;
	}

	double integrateByTrapeze(double a, double b, int n, int dg) {
		double h = (b - a) / n;
		double result = 0;
		int inc = 1;

		for (double i = a + h; i < b; i += h) {
			result += calcPolynomial(i, dg);
			inc++;
		}
		result += (calcPolynomial(a, dg) + calcPolynomial(b, dg)) / 2;

		return result *= h;
	}

	double itegrateBySimpson(double a, double b, int n, int dg) {
		double h = (b - a) / n;
		double result = 0;
		double sum1 = 0, sum2 = 0;
		int inc = 1;
		result += calcPolynomial(a, dg) + calcPolynomial(b, dg);
		for (double i = a + h; i < b; i += h) {

			if (inc % 2 == 0) {
				sum2 += calcPolynomial(i, dg);
			}
			else {
				sum1 += calcPolynomial(i, dg);
			}
			inc++;
		}
		result += 4 * sum1 + 2 * sum2;
		return result * h / 3;
	}

	double pSimson(double a, double b, double h) {
		double max = 0;
		for (double i = a + h; i < b + h; i += h) {
			if (abs(calcPolynomial(i, 4)) > abs(calcPolynomial(i - h, 4))) {
				max = abs(calcPolynomial(i, 4));
			}
		}
		return abs((pow(h, 4) * (b - a) / 180) * max);
	}

	double integrate38(double a, double b, int dg) {
		double h = (b - a) / 3;

		return ((b - a) / 8) * (calcPolynomial(a, dg) +
			3 * calcPolynomial(a + h, dg) +
			3 * calcPolynomial(a + 2 * h, dg) +
			calcPolynomial(b, dg)) + p38(a, b);
	}

	double p38(double a, double b) {
		double h = (b - a) / 3;
		return -(pow(h, 5) * calcPolynomial((b + a) / 2, 4) / 80);
	}


};

int main()
{

	IntegralPolynom Ip;
	double a, b, n, d;
	double ref, sq, tr, sim, te;

	cout << "4M lab  # 7" << endl << "Creator: Dmytro Dutkovskyi" << endl;
	cout << "----------------------------------" << endl;
	cout << "input a,b,n, degree of polynomial (between 2 an 10):" << endl;


	cin >> a >> b >> n >> d;

	ref = Ip.itegrateBySimpson(a, b, 10000, 10);

	cout << "\nSsq=" << Ip.integrateBySquares(a, b, n, d);

	cout << "\nStr=" << Ip.integrateByTrapeze(a, b, n, d);

	cout << "\nSsp=" << Ip.itegrateBySimpson(a, b, n, d);

	cout << "\nS38=" << Ip.integrate38(a, b, d);

	cout << "\n\n";

	for (int i = 2; i < 11; i++) {

		cout << "\nN:" << i;

		sq = Ip.integrateBySquares(a, b, n, i);

		tr = Ip.integrateByTrapeze(a, b, n, i);

		sim = Ip.itegrateBySimpson(a, b, n, i);

		te = Ip.integrate38(a, b, i);

		cout << "\nSquares absolute me=" << abs(ref - sq) << "  relative me= " << 100 * abs(ref - sq) / ref << " %";

		cout << "\nTrapeze absolute me=" << abs(ref - tr) << "  relative me= " << 100 * abs(ref - tr) / ref << " %";

		cout << "\nSimpson absolute me=" << abs(ref - sim) << "  relative me= " << 100 * abs(ref - sim) / ref << " %";

		cout << "\n3/8 absolute me=" << abs(ref - te) << "  relative me= " << 100 * abs(ref - te) / ref << " %";

	}

	cout << "\n\n";

}
