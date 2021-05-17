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

	dChar(const dChar& one, const dChar& two) {

		lowerCase = one.lowerCase + two.lowerCase;
		upperCase = one.lowerCase + two.lowerCase;

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

	void conCode(char c) {
		code += c;
	}
};

class dString {
private:
	vector<dChar*> mVect;
	string code = "";
	float compP = 0.;
	vector<dString*> dVect;
	wstring compStr = L"";

public:
	dString() {

	}

	dString(dChar* c) {
		mVect.push_back(c);
		compP = c->getP();
		compStr += c->getlChar();
	}

	dString(dChar* o, dChar* t) {
		mVect.push_back(o);
		mVect.push_back(t);
		compP = o->getP() * t->getP();
		compStr += o->getlChar();
		compStr+=t->getlChar();
	}

	dString(dString* o, dChar* t) {

		mVect.push_back(t);
		compP = o->getP() * t->getP();
		compStr += o->getStr();
		compStr += t->getlChar();
	}

	dString( dString* o,  dString* t) {
		//cmpndJoin(o, t);
		dVect.push_back(o);
		dVect.push_back(t);
		compP = calCmP();
		compStr += (*o).compStr + (*t).compStr;
	}

	//void cmpndJoin(const dString& o, const dString& t) {
	//	for (int i = 0; i < o.mVect.size(); i++) {
	//		this->mVect.push_back(o.mVect[i]);
	//	}
	//	for (int i = 0; i < t.mVect.size(); i++) {
	//		this->mVect.push_back(t.mVect[i]);
	//	}
	//}

	float calCmP() {
		float out = 0.;
		for (int i = 0; i < dVect.size(); i++) {
			out += (*dVect[i]).compP;
		}
		return out;
	}

	float calJointP() {
		float out = 1.;
		for (int i = 0; i < mVect.size(); i++) {
			out *= mVect[i]->getP();
		}
		return out;
	}

	//wstring calcStr() {
	//	wstring out=L"";
	//	for (int i = 0; i < mVect.size(); i++) {
	//		out += mVect[i]->getlChar();
	//	}
	//	return out;
	//}
	
	int getLen() {
		return mVect.size();
	}

	dChar* getRef(int ind) {
		return mVect[ind];
	}

	string getCode() {
		return code;
	}

	//void conCode(char c) {
	//	for (int i = 0; i < mVect.size(); i++) {
	//		mVect[i]->conCode(c);
	//	}
	//	code = mVect[0]->getCode();
	//}

	void conCode(char c) {	
		code += c;
		for (int i = 0; i < dVect.size(); i++) {
		
			(*dVect[i]).conCode(c);
		}
	}

	int codeLen() {
		int counter = 0;
		while (code[counter] != '\0') {
			counter++;
		}
		return counter;
	}

	float getP() {
		return compP;
	}

	wstring getStr() {
		return compStr;
	}

};

class ShennonFano {
	vector<dChar*> vect;

	ShennonFano(vector<dChar*> vect) {
		this->vect = subVect(vect, 0, vect.size());
		initialise();
	}
		
	void initialise() {
		//sort(vect.begin(), vect.end(), ptrCmpP);
		reverse(vect.begin(), vect.end());
		printPiTable(vect);
	}

	vector<dChar*> subVect(vector<dChar*> vect, int begin, int end) {
		vector<dChar*> subvect;

		for (int i = begin; i < end; i++) {
			subvect.push_back(vect[i]);
		}
		return subvect;
	}

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
			cin.get();
		} while (groupCount);
	}
};

void localeInit() {
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

bool dStrPtrCmp(dString* a, dString* b) { return (a->getP() < b->getP()); }

void printDStrs(vector<dString*> strV) {

	cout << "\n";

	for (int i = 0; i < strV.size(); i++) {
		wcout << "\n" << strV[i]->getStr() + L" " << strV[i]->getP() << " ";
		cout << strV[i]->getCode();
	}

}

void sortDStr(vector<dString*>& strV) {
	sort(strV.begin(), strV.end(), &dStrPtrCmp);
	reverse(strV.begin(), strV.end());
}

void huffmanForwardPass(vector<vector<dString*>>& stepV) {
	do {
		int svSize = stepV.back().size();
		vector<dString*> strNew;
		for (int i = 0; i < svSize - 2; i++) {
			strNew.push_back(stepV.back()[i]);
		}
		strNew.push_back(new dString(stepV.back()[svSize - 1],stepV.back()[svSize - 2]));
		sortDStr(strNew);
		stepV.push_back(strNew);

	} while (stepV.back().size() != 1);
}

void huffmanBackwardsPass(vector<vector<dString*>>& stepV) {
	for (int i = stepV.size() - 2; i >= 0; i--) {
		
		stepV[i][stepV[i].size() - 1]->conCode('0');
		stepV[i][stepV[i].size() - 2]->conCode('1');
	}
}

void huffmanAlgorithm(vector<vector<dString*>> stepV) {
	sortDStr(stepV.back());
	huffmanForwardPass(stepV);
	huffmanBackwardsPass(stepV);
	for (int i = 0; i < stepV.size(); i++) {
		printDStrs(stepV[i]);
	}
}

float avgCodeLen(vector<dString*>& strV) {
	float result = 0.;

	for (int i = 0; i < strV.size(); i++) {
		result += strV[i]->getP() * strV[i]->codeLen();
	}
	return result;
}

float minCodeLen(vector<dString*>& strV) {
	float result = 0.;

	for (int i = 0; i < strV.size(); i++) {
		result += strV[i]->getP()*(log2(strV[i]->getP()));
	}
	return -result;
}

void printCodeLengths(vector<dString*>& strV) {
	cout <<  "\n\n Minimal code length: " << minCodeLen(strV)<<"\n Average code length: " << avgCodeLen(strV);
}

vector<dString*> createBlock2(vector<dChar*>& strV) {
	vector<dString*> newV;
	for (int i = 0; i < strV.size(); i++) {
		for (int j = 0; j < strV.size(); j++) {
			newV.push_back(new dString(strV[i],strV[j]));
		}
	}
	return newV;
}



int main()
{
	localeInit();

	vector<dChar*> blChrSt{		new dChar({L'a'},{L'A'},0.45f),
								new dChar({L'b'},{L'B'},0.11f),
								new dChar({L'c'},{L'C'},0.44f)
	};

	vector<dChar*> chrV{	new dChar({L'à'},{L'À'},0.11f),
							new dChar({L'á'},{L'Á'},0.09f),
							new dChar({L'â'},{L'Â'},0.08f),
							new dChar({L'ã'},{L'Ã'},0.15f),
							new dChar({L'ä'},{L'Ä'},0.06f),
							new dChar({L'å'},{L'Å'},0.16f),
							new dChar({L'º'},{L'ª'},0.13f),
							new dChar({L'æ'},{L'Æ'},0.22f)
	};


	
	vector<dString*> strV;

	vector<vector<dString*>> stepV;
	
	//create dstr vect
	for (int i = 0; i < chrV.size(); i++) {
		strV.push_back(new dString(chrV[i]));
	}
	//init
	
	
	stepV.push_back(strV);
	
	huffmanAlgorithm(stepV);
	printCodeLengths(strV);
	//fix blocks
	stepV.clear();
	stepV.push_back(createBlock2(blChrSt));
	huffmanAlgorithm(stepV);
	printCodeLengths(stepV[0]);
	stepV.clear();

}

