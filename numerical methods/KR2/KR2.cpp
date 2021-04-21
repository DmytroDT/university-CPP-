#include <iostream>
#include <math.h>

using namespace std;

double cF(double x, double y) {
	return (sin(x)/cos(x+y));
}

void Euler() {
	double py = 19, y = 19, x = 19;
	double h = 0.1;

	for (int i = 1; i <= 10; i++) {
		y = py + h * cF(x, y);
		x = 7 + i * h;
		cout << "\nN:" << i << " y=" << y << " x=" << x;
		py = y;

	}
}

void RungeKutt2() {
	double py = 19, y = 19, x = 19;
	double h = 0.1;
	double k1, k2;


	for (int i = 1; i <= 10; i++) {

		k1 = h * cF(x, y);
		k2 = h * cF(x + h, y + k1);

		y = py + 0.5 * (k1 + k2);
		x = 7 + i * h;
		cout << "\nN:" << i <<" k1="<<k1<<" k2="<<k2<< " y=" << y << " x=" << x;
		py = y;

	}

}

int main()
{
	Euler();
	cout << "\n\n";
	RungeKutt2();
	cout << "\n\n";
}
