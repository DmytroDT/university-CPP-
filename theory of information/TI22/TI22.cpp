#include <iostream>
#include <fstream>
#include <string>
#include "windows.h";
#include <locale>         
#include <codecvt> 
#include <cmath>
#include <iomanip>  
#include <vector>
#include <algorithm> 
#include <bitset>
using namespace std;


#define wd 8

class dChar {
private:
	wchar_t  lowerCase = NULL;
	wchar_t  upperCase = NULL;

	int  counter = 0;

	string code = "";

	double probability = 0.;
	double amountI = 0.;
	double entropy = 0.;

public:

	dChar() {

	}

	dChar(wchar_t  l, wchar_t  u) {
		lowerCase = l;
		upperCase = u;
	}

	dChar(wchar_t  l, wchar_t  u, double p) {
		lowerCase = l;
		upperCase = u;
		probability = p;
	}


	void inc() {
		counter++;
	}

	wchar_t getlChar() {
		return lowerCase;
	}

	wchar_t getUChar() {
		return upperCase;
	}

	int getCount() {
		return counter;
	}

	void setCount(int newCount) {
		counter = newCount;
	}

	bool cmp(wchar_t c) {
		return ((int)c == (int)(lowerCase) || ((int)c == (int)(upperCase)));
	}

	void calcStats(double generalAmount) {
		probability = ((double)counter / generalAmount);
		amountI = -log2(probability);
		entropy = probability * amountI;
	}

	double getP() {
		return probability;
	}

	double getI() {
		return amountI;
	}

	double getH() {
		return entropy;
	}

	void setCode(string newCode) {
		code = newCode;
	}

	string getCode() {
		return code;
	}

};

bool ptrCmpP(dChar* a, dChar* b) { return (a->getP() < b->getP()); }

int splitByEq(vector<dChar*> vect) {

	int i;
	double sumPre=0, sumPost;

	for ( i = 0; i < vect.size(); i++){
		sumPre += vect[i]->getP();
		sumPost = 0;
		for (int j = i; j < vect.size(); j++) {
			sumPost+= vect[j]->getP();
		}
		if (sumPost < sumPre) {
			break;
		}
	}
	return i;
}

void assignBits(vector<dChar*> vect, int splitPoint) {

	string newCount;
	double probSumP=0;
	double probSumA=0;


	//for (int i = 0; i <vect.size() ; i++) {
	//	(i < splitPoint) ? (vect[i]->setCode(vect[i]->getCode() + "0")) : (vect[i]->setCode(vect[i]->getCode() + "1"));
	//}


	for (int i = 0; i <splitPoint ; i++) {
		probSumP += vect[i]->getP();
	}
	for (int i = splitPoint; i < vect.size(); i++) {
		probSumA += vect[i]->getP();
	}
	
	for (int i = 0; i < vect.size(); i++) {
		if (i < splitPoint) {
			(probSumP > probSumA) ? (vect[i]->setCode(vect[i]->getCode() + "1")) : (vect[i]->setCode(vect[i]->getCode() + "0"));
		}
		else {
			(probSumP < probSumA) ? (vect[i]->setCode(vect[i]->getCode() + "1")) : (vect[i]->setCode(vect[i]->getCode() + "0"));
		}
	}

}

vector<dChar*> subVect(vector<dChar*> vect,int begin,int end) {
	vector<dChar*> subvect;

	for (int i = begin; i < end; i++) {
		subvect.push_back(vect[i]);
	}
	return subvect;
}


bool  assignSubBits3(vector<dChar*> vect) {

	int counter = 0;
	bool checkAvailableGroups = false;

	for (int i = 1; i < vect.size()+1; i++) {
		if (i != vect.size()) {
			if ((vect[i]->getCode() == vect[i - 1]->getCode())) {
				counter++;
				checkAvailableGroups = true;
			}else {
				if (counter > 0) {
						vector<dChar*> subgroup = subVect(vect, i - (1+counter), i);
						assignBits(subgroup, splitByEq(subgroup));
						counter = 0;
				}
			}
		}else {
			if ((vect[i-1]->getCode() == vect[i - 2]->getCode())) {
				vector<dChar*> subgroup = subVect(vect, i - (1 + counter), i);
				assignBits(subgroup, splitByEq(subgroup));
			}
		}
	}

	return checkAvailableGroups;
}

void printGroup(vector<dChar*> vect) {
	cout << "\n";
	for (int i = 0; i < vect.size(); i++) {
		wcout <<"\n"<< vect[i]->getlChar() << " ";
		cout<<(vect[i]->getCode());
	}
}

void printPiTable(vector<dChar*> vect) {
	cout << "\nC:  ";

	for (int i = 0; i < vect.size(); i++) {
		wcout << setw(wd) << left << vect[i]->getlChar();
	}

	cout << "\npi: ";

	for (int i = 0; i < vect.size(); i++) {
		wcout << setw(wd) << left << vect[i]->getP();
	}
}

void algorithmSP(vector<dChar*> vect) {
	bool groupCount;
	assignBits(vect, splitByEq(vect));
	printGroup(vect);

	do {
		groupCount = assignSubBits3(vect);
		printGroup(vect);
		cin.get();
	} while (groupCount);
}

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	wstring_convert<codecvt_utf8<wchar_t> > converter;

	vector<dChar*> chrV{	new dChar({L'�'},{L'�'},0.11f),
							new dChar({L'�'},{L'�'},0.09f), 
							new dChar({L'�'},{L'�'},0.08f), 
							new dChar({L'�'},{L'�'},0.15f), 
							new dChar({L'�'},{L'�'},0.06f), 
							new dChar({L'�'},{L'�'},0.16f), 
							new dChar({L'�'},{L'�'},0.13f),
							new dChar({L'�'},{L'�'},0.22f)
						};
	
	sort(chrV.begin(), chrV.end(), &ptrCmpP);

	printPiTable(chrV);

	algorithmSP(chrV);

}


