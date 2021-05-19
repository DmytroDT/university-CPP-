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

	dChar(wchar_t  l) {
		lowerCase = l;
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
	int numb = 0;

public:
	dString() {

	}

	dString(dChar* c) {
		mVect.push_back(c);
		compP = c->getP();
		compStr += c->getlChar();
	}

	dString(dChar* c,int numb) {
		mVect.push_back(c);
		compP = c->getP();
		compStr += c->getlChar();
		this->numb = numb;
	}

	dString(dChar* o, dChar* t) {
		mVect.push_back(o);
		mVect.push_back(t);
		compP = o->getP() * t->getP();
		compStr += o->getlChar();
		compStr += t->getlChar();
	}

	dString(dString* o, dChar* t) {

		mVect.push_back(t);
		compP = o->getP() * t->getP();
		compStr += o->getStr();
		compStr += t->getlChar();
	}

	dString(dString* o, dString* t) {
		dVect.push_back(o);
		dVect.push_back(t);
		compP = calCmP();
		compStr += (*o).compStr + (*t).compStr;
	}

	dString(dString* o, dString* t, int numb) {
		dVect.push_back(o);
		dVect.push_back(t);
		compP = calCmP();
		compStr += (*o).compStr + (*t).compStr;
		this->numb = numb;
	}

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

	int getLen() {
		return mVect.size();
	}

	dChar* getRef(int ind) {
		return mVect[ind];
	}

	string getCode() {
		return code;
	}

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

	int getNum() {
		return numb;
	}

};

wstring readIntoWStr(string path) {
	string rtStr;

	wstring_convert<codecvt_utf8<wchar_t> > converter;
	ifstream AS("./txt/" + path + ".txt");
	rtStr = string(istreambuf_iterator<char>(AS), istreambuf_iterator<char>());
	AS.close();
	return converter.from_bytes(rtStr);
}

vector<dChar*> initDchrV(wstring alphabetStr) {
	vector<dChar*> aV;
	for (int i = 0; i < alphabetStr.size(); i += 2) {
		(aV).push_back(new dChar(alphabetStr[i], alphabetStr[i + 1]));
	}
	return aV;
}

void localeInit() {
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

bool dStrPtrCmp(dString* a, dString* b) { return (a->getP() < b->getP()); }

wstring convert2lowerCase(wstring inpStr, vector<dChar*> aVect ) {
	wstring outStr = L"";
	
	for (int i = 0; i < inpStr.size(); i++) {
		for (int j = 0; j < aVect.size(); j++) {
			(inpStr[i] == aVect[j]->getUChar()) ? (outStr += aVect[j]->getlChar()) :
			(inpStr[i] == aVect[j]->getlChar()) ? (outStr += aVect[j]->getlChar()) : (outStr += L"");
		}
	}
	return outStr;
}

vector<dChar*> wstr2dChar(wstring inptStr) {
	vector<dChar*> out;

	for (int i = 0; i < inptStr.size(); i++) {
		out.push_back(new dChar(inptStr[i]));
	}
	return out;
}

vector<dString*> dchar2dStr(vector<dChar*> inptStr) {
	vector<dString*> out;

	for (int i = 0; i < inptStr.size(); i++) {
		out.push_back(new dString(inptStr[i]));
	}
	return out;
}

bool dStrMatch(dString a, vector<dString*> inV) {

	for (int i = 0; i < inV.size(); i++) {
		if (inV[i]->getStr() == a.getStr()) {
			return true;
		}
	}
	return false;
}

int findC(dString a, vector<dString*> inV) {

	for (int i = 0; i < inV.size(); i++) {
		if (inV[i]->getStr() == a.getStr()) {
			return inV[i]->getNum();
		}
	}
	return 0;
}

vector<dString*> baseAlphabet(vector<dChar*> inpStr) {
	int counter = 1;
	vector<dString*> resV;

	for (int i = 0; i < inpStr.size(); i++) {
		
		if (!dStrMatch(inpStr[i], resV)) {
			resV.push_back(new dString(inpStr[i], counter++));
		}
	}
	return resV;
}

void printDstrs(vector<dString*> a) {

	for (int i = 0; i < a.size(); i++) {
		wcout <<"\n"<< a[i]->getStr() << " " << a[i]->getNum();
	}
}

class LZW {
private:
	vector< dString*> cV;
	vector< dString*> alV;
	vector<int> encodedSeq;
	vector< dString*> orV;

public:
	LZW(vector< dString*> cV, vector< dString*> alV) {
		this->cV = cV;
		this->alV = alV;
		orV = copyVect();
	}

	int recG(dString* str, int* pos) {
		int ret = findC(*str, alV);
		if ((*pos) + 1 < cV.size()) {
			dString* a = new dString(str, cV[(*pos) + 1], alV.size() + 1);

			if (dStrMatch(*a, alV)) {
				(*pos)++;
				ret = recG(a, pos);
			}
			else {
				alV.push_back(a);
			}
		}
		return ret;
	}

	int decG(dString* str, int* pos) {
		int ret = str->getNum();

		if ((*pos) + 1 < encodedSeq.size()) {
			dString* a = new dString(str, getByN(encodedSeq[(*pos) + 1]), orV.size() + 1);

			if (dStrMatch(*a, orV)) {
				(*pos)++;
				ret = recG(a, pos);
			}
			else {
				orV.push_back(a);
			}
		}
		return ret;
	}

	void encode() {
		encodedSeq.clear();
		for (int i = 0; i < cV.size(); i++) {
			encodedSeq.push_back(recG(cV[i], &i));
		}
	}

	wstring decode() {
		wstring out = L"";
		for (int i = 0; i < encodedSeq.size(); i++) {
			out+= getByN(decG(getByN(encodedSeq[i]), &i))->getStr();
			wcout << "\n" << out;
		}
		wcout << "\n\n"<<out<<"\n\n";
		return out;
	}

	void disCode() {
		cout << "\n";
		for (int i = 0; i < encodedSeq.size(); i++) {
			cout <<" "<<encodedSeq[i];
		}
	}

	void disAlphabet() {
		printDstrs(orV);
	}

	vector< dString*> copyVect() {
		vector< dString*> a;
		for (int i = 0; i < alV.size(); i++) {
			a.push_back(alV[i]);
		}
		return a;
	}

	dString* getByN(int n) {
		dString* d = new dString();
		for (int i = 0; i < orV.size(); i++) {
			if (orV[i]->getNum() == n) {
				d= orV[i];
			}
		}
		return d;
	}

};

void rec(dString str, vector< dString*> cV, vector< dString*>& al, int pos) {
	if (pos + 1 != al.size()) {
		dString a(&str, cV[pos + 1], al.size() + 1);
		if (dStrMatch(a, al)) {
			rec(a, cV,al, pos + 1);
		}
		else {
			al.push_back(&a);
			//return a.getNum();
		}
	}
}

int main()
{
	localeInit();
	


	wstring alphabetStr = readIntoWStr("a3");
	vector<dChar*> vect = initDchrV(alphabetStr);
	//wstring namel = convert2lowerCase(readIntoWStr("name"), vect);
	wstring inet;
	wcin >> inet;

	wstring namel = convert2lowerCase(inet, vect);

	vector<dString*> alV = baseAlphabet(wstr2dChar(namel));

	wcout << namel;

	vector<dString*> opV = dchar2dStr(wstr2dChar(namel));

	LZW e(opV, alV);
	e.disAlphabet();
	e.encode();
	e.disCode();
	
	e.decode();
}



