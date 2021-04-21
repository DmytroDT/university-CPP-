#include <iostream>
#include <math.h>
using namespace std;

double cF(double x, double y) {
	return sin(2 * x + 1) - 0.1 * y - 1;
}

double cG(double x, double y) {
	return x + cos(y) - 1;
}

double dFx(double x) {
	return 2 * cos(2 * x + 1);
}

double dGx() {
	return 1;
}

double dFy() {
	return - 0.1;
}

double dGy( double y) {
	return -sin(y);
}

double frstCoef(double df1, double dg1, double df2,  double dg2) {
	return -(dg2 / (df1 * dg2 - df2 * dg1));
}

double scndCoef(double df1, double dg1, double df2,  double dg2) {
	return (df2 / (df1 * dg2 - df2 * dg1));
}


void cIM(double x,double y,double e) {

	double px, py, r;
	int inc = 0;
	double alpha = frstCoef(dFx(x), dGx(), dFy(), dGy(y));
	double beta = scndCoef(dFx(x), dGx(), dFy(), dGy(y));
	double gamma = frstCoef(dFy(), dGy(y), dFx(x), dGx());
	double delta = scndCoef(dFy(), dGy(y), dFx(x), dGx());

	do {
		px = x;
		py = y;

		x = px + alpha * cF(px,py) + beta * cG(px,py);
		y = py + gamma * cF(px, py) + delta * cG(px, py);

		r = sqrt(pow(x - px, 2) + pow(y - py, 2));

		inc++;
	}while(r>=e);

	cout << "\nN:" << inc << " x=" << x<<" y="<<y<<"\n";
}	


int main()
{
	double inX, inY,e;
	cout << "4m lab  # 5" << endl << "Creator: Dmytro Dutkovskyi" << endl;
	cout << "----------------------------------" << endl;
	cout << "input first approximated points:\nX=";
	cin >> inX;
	cout << "\nY=";
	cin >> inY;

	cout << "Solution of the system with e=0.0001.";
	cIM(inX, inY, 0.0001);


	for (int i = 1; i <= 10; i++) {
		e = pow(0.1, i);
		cout << "\ne=" << e << "\n";
		cIM(inX, inY, e);
	}
}
