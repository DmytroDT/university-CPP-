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

	for (int i = 0; i < vect.size(); i++) {
		if (i < splitPoint) {
			newCount = (vect[i]->getCode()+="0");
		}
		else {
			newCount = (vect[i]->getCode() += "1");
		}
		vect[i]->setCode(newCount);
	}
}

bool  assignSubBits(vector<dChar*> vect) {
	vector<int> groupLengths;
	int counter=0;
	int beg = 0;
	bool checkAvailableGroups = false;
	
	for (int i = 1; i < vect.size(); i++){
		if (vect[i - 1]->getCode() == vect[i]->getCode()) {
			counter++;
		}
		else {
			if ((abs(counter - beg) > 1)) {
				beg = counter; 
				counter = 0;
			}
		}

		if (((i- counter) >1)&&((vect[i - 1]->getCode() != vect[i]->getCode())||(i==vect.size()-1))) {
			vector<dChar*> subgroup(&vect[counter], &vect[i]);
			groupLengths.push_back(subgroup.size());
			counter += i;

			assignBits(subgroup, splitByEq(subgroup));
			checkAvailableGroups = true;
		}
	}
	return checkAvailableGroups;
}

vector<dChar*> subVect(vector<dChar*> vect,int begin,int end) {
	vector<dChar*> subvect;

	for (int i = begin; i < end; i++) {
		subvect.push_back(vect[i]);
	}
	return subvect;
}

bool  assignSubBits2(vector<dChar*> vect) {
	vector<int> groupLengths;
	int counter = 0;
	bool checkAvailableGroups = false;

	for (int i = 1; i < vect.size(); i++) {

		if ((vect[i]->getCode()!=vect[i -1]->getCode())||(i==vect.size()-1)) {
			if (counter > 0) {
				//vector<dChar*> subgroup(&vect[i - (counter+1)], &vect[i]);
				vector<dChar*> subgroup = subVect(vect, i - (1+ counter), i);
				assignBits(subgroup, splitByEq(subgroup));
				counter = 0;
			}
		}else {
			counter++;
			checkAvailableGroups = true;
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
		groupCount = assignSubBits2(vect);
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

	vector<dChar*> chrV{	new dChar({L'à'},{L'À'},0.11f),
							new dChar({L'á'},{L'Á'},0.09f), 
							new dChar({L'â'},{L'Â'},0.08f), 
							new dChar({L'ã'},{L'Ã'},0.15f), 
							new dChar({L'ä'},{L'Ä'},0.06f), 
							new dChar({L'å'},{L'Å'},0.16f), 
							new dChar({L'º'},{L'ª'},0.13f),
							new dChar({L'æ'},{L'Æ'},0.22f)
						};
	
	sort(chrV.begin(), chrV.end(), &ptrCmpP);

	printPiTable(chrV);

	algorithmSP(chrV);

	//vector<dChar*> 

	//vector<dChar*> sub(&chrV[0], &(chrV[chrV.size() - 1]));

	//printPiTable(sub);


}


