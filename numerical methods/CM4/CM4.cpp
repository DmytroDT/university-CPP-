#include <iostream>
#include <math.h>
using namespace std;

long double cF(long double x) {
	return pow(x, 5) - 2 * x + 4 - 1.1 * cos(x);
}

long double cdf(long double x) {
	return 5*pow(x, 4) - 2 + 1.1 * sin(x);
}

long double cdf2(long double x) {
	return 20 * pow(x, 3) + 1.1 * cos(x);
}

void cNM(long double x, long double e) {
	long double p, r;
	int i = 0;

	do {
		p = x;
		x = x - (cF(x) / cdf(x));
		r = abs(x - p);
		i++;
	} while (r >= e);

	cout << "N:" << i << " x=" << x;
}

void cHM(long double x, long double e) {
	long double xn=0, xnm, r;
	int i = 0;

	do {
		xnm = xn;
		xn = x;
		x = x - cF(x) * ((x - xnm) / (cF(x) - cF(xnm)));
		r = abs(x - xn);
		i++;
	} while (r >= e);

	cout << "N:" << i << " x=" << x ;
}

void cSM(long double x, long double e,double st) {
	long double xn = 0, xnm, r;
	int i = 0;

	do {
		xnm = xn;
		xn = x;
		x = x - cF(x)*st / ( (cF(x+st) - cF(x)));
		r = abs(x - xn);
		i++;
	} while (r >= e);

	cout << "N:" << i << " x=" << x ;
}


int main()
{	
	long double e;
	long double inpt;
	cout << "4m lab  # 4" << endl << "Creator: Dmytro Dutkovskyi" << endl;
	cout << "----------------------------------" << endl;
	cout << "input beginning point:";
	cin >> inpt;
	cout << "\nNewton's method: ";
	cNM(inpt, 0.00001);
	cout << "\nSecant method: ";
	cHM(inpt, 0.00001);
	cout << "\nCoeficient bisection method: ";
	cSM(inpt, 0.00001,0.001);
	cout << "\n";

	for (int i = 1; i <= 10; i++) {
		e = pow(0.1, i);
		cout <<"\n\ne=" << e << "\n\n";
		cNM(inpt, e);
		cout << "\n";
		cHM(inpt, e);
		cout << "\n ";
		cSM(inpt, e, pow(0.1, i/2));
	}
}

