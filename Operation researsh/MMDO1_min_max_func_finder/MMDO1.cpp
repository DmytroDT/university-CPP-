#include <iostream>
#include <vector>
using namespace std;
#define n 3

class Point {
private:	
	double x, y;
public:
	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}

	Point(Point &pt) {
		this->x = pt.x;
		this->y = pt.y;
	}

	double getX() {
		return x;
	}

	double getY() {
		return y;
	}

	friend ostream& operator <<(ostream& os, Point& p) {
		os << "\n(" << p.x << ";" << p.y << ");";
		return os;
	}

};

class Equation {
private:
	double cArr[3];
	bool sign;

public:

	Equation() {
		for (int i = 0; i < 3; i++) {
			cArr[i] = 0;
		}
		sign = 1;
	}

	Equation(double x, double y, double c, bool sign){
		cArr[0] = x;
		cArr[1] = y;
		cArr[2] = c;
		this->sign = sign;
	}

	Equation(Equation& refE) {
		for (int i = 0; i < sizeof(cArr); i++) {
			cArr[i] = refE.cArr[i];
		}
		this->sign = refE.sign;
	}

	double calcX(double y) {
		return (cArr[2] - cArr[1]*y) / cArr[0];
	}

	double calcY(double x) {
		return (cArr[2] - cArr[0]*x) / cArr[1];
	}

	bool checkRange(double x,double y) {
		if (sign) {
			return (cArr[0]*x+cArr[1]*y)+ 0.0001 >= cArr[2];
		}else {
			return (cArr[0] * x + cArr[1] * y)-0.0001 <= cArr[2];
		}
	}

	double findInterX(Equation e) {

		double hold = cArr[1];
		Equation thisE(cArr[0], cArr[1], cArr[2], sign);

		for (int i = 0; i < 3; i++) {
			thisE.cArr[i] /= hold;
			thisE.cArr[i] *= e.cArr[1];
			thisE.cArr[i] -= e.cArr[i];
		}

		return thisE.calcX(0);
	}

	double findSolution(double x, double y) {
		return (cArr[0] * x + cArr[1] * y);
	}

};

bool checkPoint(Point p , vector<Equation*> eV) {
	bool state = true;

	for (int i = 0; i < eV.size(); i++) {
		if (!(eV[i]->checkRange(p.getX(), p.getY()))) {
			state = false;
		}
	}
	return state;
}

bool checkQuad(Point pt) {
	return ((pt.getX() >= 0) && (pt.getY() >= 0));
}

void addXint(vector<Point*> &p,vector<Equation*> eV) {

	for (int i = 0; i < eV.size(); i++) {
		Point pt(eV[i]->calcX(0), 0);
		if (checkPoint(pt, eV) && checkQuad(pt)) {
			p.push_back(new Point(pt));
		}
	}
}

void addYint(vector<Point*>& p, vector<Equation*> eV) {

	for (int i = 0; i < eV.size(); i++) {
		Point pt(0,eV[i]->calcY(0));
		if (checkPoint(pt, eV) && checkQuad(pt)) {
			p.push_back(new Point(pt));
		}
	}
}

void addInter(vector<Point*>& p, vector<Equation*> eV) {

	for(int i = 0; i < eV.size()-1 ;i++){

		double tempX = eV[i]->findInterX(*eV[i + 1]);
		Point pt(tempX,eV[i]->calcY(tempX));

		if (checkPoint(pt, eV) && checkQuad(pt)) {
			p.push_back(new Point(pt));
		}
	}

	double tempX = eV[eV.size()-1]->findInterX(*eV[0]);
	Point ptE(tempX, eV[eV.size()-1]->calcY(tempX));
	
	if (checkPoint(ptE, eV) && checkQuad(ptE)) {
		p.push_back(new Point(ptE));
	}

}

void findMax(vector<Point*>& p, Equation e) {
	double max = 0;
	Point* ref = NULL;

	for (int i = 0; i < p.size(); i++) {
		double temp = e.findSolution(p[i]->getX(), p[i]->getY());
		if (max < temp) {
			max = temp;
			ref = p[i];
		}
	}

	cout << "\nPoint of maximum: " << *ref << " , value=" << e.findSolution(ref->getX(), ref->getY());
}

void findMin(vector<Point*>& p, Equation e) {
	double min = 0;
	Point* ref = NULL;

	for (int i = 0; i < p.size(); i++) {
		double temp = e.findSolution(p[i]->getX(), p[i]->getY());
		if (min > temp) {
			min = temp;
			ref = p[i];
		}
	}

	cout << "\nPoint of minimum: " << *ref << " , value=" << e.findSolution(ref->getX(), ref->getY());
}

int main()
{

	cout << "MMDO lab  # 1" << endl << "Creator: Dmytro Dutkovskyi" << endl;
	cout << "----------------------------------" << endl;
	

	cout << "\npoints in range of functions:" << endl;

	Equation target(-2,1,0,0);

	vector<Equation*> equations;

	equations.push_back(new Equation(2, -1, 8, 0));
	equations.push_back(new Equation(1, 1, 5, 0));
	equations.push_back(new Equation(-3, 2, 3, 0));

	vector<Point*> points;
	points.push_back(new Point(0,0));

	addXint(points, equations);
	addYint(points, equations);
	addInter(points, equations);

	for (int i = 0; i < points.size(); i++) {
		cout << *points[i];
	}

	findMax(points, target);

	findMin(points, target);

	cout << "\n";
}
