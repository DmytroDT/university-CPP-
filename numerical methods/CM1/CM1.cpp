#include <iostream>
#include <math.h>
#include <iomanip>
#include <cstdio>
using namespace std;

class Approx {
private:

	double x1, x2, x3;
	double d1, d2, d3;
	double f, aF, rF;
	int n=0,n1,n2,n3;


public:

	Approx(double x1, double x2, double x3, double d1, double d2, double d3) {
		this->x1 = x1;
		this->x2 = x2;
		this->x3 = x3;
		this->d1 = d1;
		this->d2 = d2;
		this->d3 = d3;
		n = 0;

		n1 = GetN(x1, d1);
		n2 = GetN(x2, d2);
		n3 = GetN(x3, d3);

		ComputeF();
		ComputeDF();
		ComputeRF();
	}

	Approx(double x1, double x2 , double x3, int n){
		this->x1 = x1;
		this->x2 = x2;
		this->x3 = x3;
		this->n = n;

		ComputeF();
		d1 = x1 * ComputeRX(x1);
		d2 = x2 * ComputeRX(x2);
		d3 = x3 * ComputeRX(x3);
		ComputeDF();
		ComputeRF();
	}

private:

	void ComputeF(){
		f = 4 * pow(x1, 2)+5*pow(x2,2)+ 5 * pow(x3, 2) +2*x1*x2-3*x3+14*tan((x2-x1));
	}

	void ComputeDF() {
		aF = abs(8 * x1 + 2 * x2 - 14  / pow(cos((x2 - x1) ) , 2)) *abs( d1 ) + abs(10*x2+2*x1+14/ pow(cos((x2 - x1)), 2))*abs(d2)+abs(10*x3-3)*abs(d3) ;
	}

	void ComputeRF() {
		rF = aF / f;
	}

	int GetFirstNumb(double number) {	 

		if (number > 1) {
			while (number > 10) {
				number /= 10;
			}
		}
		else {
			while (number < 1) {
				number *= 10;
			}
		}
		
		return (int)number;
	}

	int GetFirstNumPos(double number) {
		number = abs(number);
		int N = 0;

		if (number > 1) {
			while (number > 10) {
				number /= 10;
				N++;
			}
		}
		else {
			while (number < 1){
				number *= 10;
				N--;
			}
		}

		return N;
	}

	double ComputeRX(double number) {
		double result;

		if (n >= 2) {
			result = pow(1 / 10.f, n - 1) * ((double)1 /( 2 * (double)GetFirstNumb(number)));

		}
		else {
			result = (pow(1 / 10.f, n - 1) * (double)(1 / GetFirstNumb(number) ));
		}

		return result;
	}

	int GetN(double x,double d) {
		return (int)((GetFirstNumPos(x) + 1 - log10(2 * d)));
	}

public:

	friend ostream& operator<<(ostream& os, Approx& Ap) {
		os << "x1=" << Ap.x1 << " x2=" << Ap.x2 << " x3=" << Ap.x3<<endl;

		if (Ap.n != 0) {
			os << "Precision N=" << Ap.n << endl;
		}
		else {
			os << "Precision n1=" << Ap.n1 <<" n2="<< Ap.n2<< " n3=" << Ap.n3 <<endl;
		}

		os << "dx1=" << Ap.d1 << " dx2=" << Ap.d2 << " dx3=" << Ap.d3 << endl;
		os << "F=" << Ap.f << endl;
		os << "aF=" << Ap.aF << endl;
		os << "rF=" << Ap.rF*100 <<"%"<< endl;
			return os;
	}
};

int main()
{
	int x1, x2, x3, n;
	double d1, d2, d3;

	cout << "Numerical methods lab work # 1" << endl << "Creator: Dmytro Dutkovskyi" << endl;
	cout << "----------------------------------" << endl;
		cout << "Input parameters for task A - x1,x2,x3,precision N."<<endl;
		cout << "input x1:"<<endl;
		cin >> x1;
		cout << "input x2:" << endl;
		cin >> x2;
		cout << "input x2:" << endl;
		cin >> x3;
		cout << "input n:" << endl;
		cin >> n;
	Approx Ap(x1, x2, x3, n);
	cout << "\n\nInput parameters for task B - x1,x2,x3,dx1,dx2,dx3." << endl;
	cout << "input x1:" << endl;
	cin >> x1;
	cout << "input x2:" << endl;
	cin >> x2;
	cout << "input x2:" << endl;
	cin >> x3;
	cout << "input dx1,dx2,dx3, floating point values only:" << endl;
	cout << "\ninput delta1:" << endl;
	cin >> d1;
	cout << "input delta2:" << endl;
	cin >> d2;
	cout << "input delta3:" << endl;
	cin >> d3;
	Approx Ap2(x1, x2, x3, d1, d2,d3);

	cout << "\n\nResult of task A:" << endl;

	cout << Ap;
	cout << "\nResult of task B:" << endl;
	cout << Ap2;
	cout << "----------------------------------" << endl;
	
	system("pause");
}


