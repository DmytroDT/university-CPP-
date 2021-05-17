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

int chooseGroupBits(vector<dChar*> vect, int splitPoint) {
	double probSumP = 0;
	double probSumA = 0;

	int fGroup = 0;

	for (int i = 0; i < splitPoint; i++) {
		probSumP += vect[i]->getP();
	}
	for (int i = splitPoint; i < vect.size(); i++) {
		probSumA += vect[i]->getP();
	}

	if (probSumP > probSumA) {
		fGroup = 1;
	}
	return fGroup;
}

void asgnGroupBits(vector<dChar*> vect, int splitPoint,int initBit) {

	int invBit = (initBit == 1) ? (0) : (1);
	string fGroupB = to_string(initBit);
	string sGroupB = to_string(invBit);

	for (int i = 0; i < splitPoint; i++) {
		vect[i]->setCode(vect[i]->getCode() + fGroupB);
	}
	for (int i = splitPoint; i < vect.size(); i++) {
		vect[i]->setCode(vect[i]->getCode() + sGroupB);
	}

}

vector<dChar*> subVect(vector<dChar*> vect,int begin,int end) {
	vector<dChar*> subvect;

	for (int i = begin; i < end; i++) {
		subvect.push_back(vect[i]);
	}
	return subvect;
}

bool  assignSubBits3(vector<dChar*> vect,int groupBit) {

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
						asgnGroupBits(subgroup, splitByEq(subgroup),groupBit);
						counter = 0;
				}
			}
		}else {
			if ((vect[i-1]->getCode() == vect[i - 2]->getCode())) {
				vector<dChar*> subgroup = subVect(vect, i - (1 + counter), i);
				asgnGroupBits(subgroup, splitByEq(subgroup), groupBit);
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
	int gBt= chooseGroupBits(vect, splitByEq(vect));

	do {
		groupCount = assignSubBits3(vect,gBt);
		printGroup(vect);
		cin.get();
	} while (groupCount);
}


int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string inputPath;
	wstring alphabetStr;
	wstring inputStr;

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
	reverse(chrV.begin(), chrV.end());
	printPiTable(chrV);

	algorithmSP(chrV);

	vector<dChar*> chrV2{	new dChar({L'à'},{L'À'},0.125f),
							new dChar({L'á'},{L'Á'},0.125f),
							new dChar({L'â'},{L'Â'},0.125f),
							new dChar({L'ã'},{L'Ã'},0.125f),

							new dChar({L'ä'},{L'Ä'},0.125f),
							new dChar({L'å'},{L'Å'},0.125f),
							new dChar({L'º'},{L'ª'},0.125f),
							new dChar({L'æ'},{L'Æ'},0.125f)
	};

	sort(chrV2.begin(), chrV2.end(), &ptrCmpP);
	reverse(chrV2.begin(), chrV2.end());
	printPiTable(chrV2);

	algorithmSP(chrV2);

}


