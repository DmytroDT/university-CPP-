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

#pragma region messy code
bool ptrCmpP(dChar* a, dChar* b) { return (a->getP() < b->getP()); }

int splitByEq(vector<dChar*> vect) {

	int i;
	double sumPre = 0, sumPost;

	for (i = 0; i < vect.size(); i++) {
		sumPre += vect[i]->getP();
		sumPost = 0;
		for (int j = i; j < vect.size(); j++) {
			sumPost += vect[j]->getP();
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

void asgnGroupBits(vector<dChar*> vect, int splitPoint, int initBit) {

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

vector<dChar*> subVect(vector<dChar*> vect, int begin, int end) {
	vector<dChar*> subvect;

	for (int i = begin; i < end; i++) {
		subvect.push_back(vect[i]);
	}
	return subvect;
}

bool  assignSubBits3(vector<dChar*> vect, int groupBit) {

	int counter = 0;
	bool checkAvailableGroups = false;

	for (int i = 1; i < vect.size() + 1; i++) {
		if (i != vect.size()) {
			if ((vect[i]->getCode() == vect[i - 1]->getCode())) {
				counter++;
				checkAvailableGroups = true;
			}
			else {
				if (counter > 0) {
					vector<dChar*> subgroup = subVect(vect, i - (1 + counter), i);
					asgnGroupBits(subgroup, splitByEq(subgroup), groupBit);
					counter = 0;
				}
			}
		}
		else {
			if ((vect[i - 1]->getCode() == vect[i - 2]->getCode())) {
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
		wcout << "\n" << vect[i]->getlChar() << " ";
		cout << (vect[i]->getCode());
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
	int gBt = chooseGroupBits(vect, splitByEq(vect));

	do {
		groupCount = assignSubBits3(vect, gBt);
		printGroup(vect);
		//cin.get();
	} while (groupCount);
}

#pragma endregion 

#pragma region Hemmings_code
void inverB(string& code, int p) {
	(code[p] == '0') ? (code[p] = '1') : (code[p] = '0');
}

bool pow2e(int i) {
	return (i != 0) && (i != 1) && (i != 2) && (i != 4) && (i != 8) && (i != 16);
}

char getParity0(string code) {
	int x = 0;
	int cC = 0;
	char out;
	for (int i = 1; i < code.size(); i++) {
		if (pow2e(i)) {
			if (code[i] == '1') {
				x ^= 1;
			}
		}
	}
	(x == 1) ? (out = '1') : (out = '0');
	return out;
}



string preCode(string code) {
	int r = 0;
	int c = 0;
	for (int i = 0; i < code.size() + 4; i++){
		if (pow2e(i)) {

			if ((c<code.size())&&(code[c] == '1')) {
				r ^= i;
			}
			c++;
		}
	}
	return bitset<3>(r).to_string();
}
  
int checkC(string code) {
	int r = 0;

	for (int i = 1; i < code.size(); i++) {
			if ( (code[i] == '1')) {
				r ^= i;
			}
	}
	return r;
}

string hEncode(string code) {

	string out = "n";

	string hc = preCode(code);
	int cH = 0, cC = 0;

	for (int i = 1; i < code.size()+4; i++){
		if (!pow2e(i)) {
			out += hc[cH];
			cH++;
		}
		else {
			out += code[cC];
			cC++;
		}
	}

	out[0] = getParity0(out);

	return out;
}

string getOgCode(string code) {
	string out = "";

	for (int i = 0; i < code.size(); i++) {
		if (pow2e(i)) {
			out += code[i];
		}
	}
	return out;
}

void tryToCorrect(string code) {
	int pos= checkC(code);


	if ((pos == 0) && (getParity0(code) == '0')) {
		cout << "\nNo errors detected,extracted original sequence = "<< getOgCode(code)<< "\n";
	}
	else {
		inverB(code, pos);

		if ((checkC(code) == 0) && (getParity0(code) == '0')) {
			cout << "\nCorrected bit "<<pos<<" ,extracted original sequence = " << getOgCode(code)<<"\n";
		}
		else {
			cout << "\ndouble error occured, resend the code"<< "\n";
		}

	}

	

}

#pragma endregion

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int ind = 0;

	string inputPath;
	wstring alphabetStr;
	wstring inputStr;
	string code;
	wstring_convert<codecvt_utf8<wchar_t> > converter;

	vector<dChar*> chrV{ new dChar({L'?'},{L'?'},0.11f),
							new dChar({L'?'},{L'?'},0.09f),
							new dChar({L'?'},{L'?'},0.08f),
							new dChar({L'?'},{L'?'},0.15f),
							new dChar({L'?'},{L'?'},0.06f),
							new dChar({L'?'},{L'?'},0.16f),
							new dChar({L'?'},{L'?'},0.13f),
							new dChar({L'?'},{L'?'},0.22f)
	};

	sort(chrV.begin(), chrV.end(), &ptrCmpP);
	reverse(chrV.begin(), chrV.end());
	printPiTable(chrV);

	algorithmSP(chrV);



	code = hEncode(chrV[1]->getCode());
	cout << "\n\n" << chrV[1]->getCode();

	cout << "\n0-don't inver bits, 1-invert 1 bit, 2-invert 2 bits.";
	cin >> ind;

	switch (ind) {
	case(0):
		cout << "\n" << code;
		tryToCorrect(code); 
		break;
	case(1):
		cout << "\nInput bit to be inverted:";
		cin >> ind;
		inverB(code, ind);
		cout << "\n" << code ;
		tryToCorrect(code);
		break;
	case(2):
		cout << "\nInput first bit to be inverted:";
		cin >> ind;
		inverB(code, ind);
		cout << "\nInput second bit to be inverted:";
		cin >> ind;
		inverB(code, ind);
		cout << "\n" << code;
		tryToCorrect(code);
		break;

	}
}


