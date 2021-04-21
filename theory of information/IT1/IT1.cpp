#include <iostream>
#include <fstream>
#include <string>
#include "windows.h";
#include <locale>         
#include <codecvt> 
#include <cmath>
#include <iomanip>  
#include <vector>

using namespace std;

#define p 2
#define wd 8

class dChar {
private:
	wchar_t  lowerCase = NULL;
	wchar_t  upperCase = NULL;
	
	int  counter = 0;
	
	double probability = 0.;
	double amountI = 0.;
	double entropy = 0.;

public:

	dChar() {

	}

	dChar(wchar_t  l,wchar_t  u) {
		lowerCase = l;
		upperCase = u;
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
};



wstring readIntoWStr(string path) {
	string rtStr;

	wstring_convert<codecvt_utf8<wchar_t> > converter;
	ifstream AS("./" + path + ".txt");
	rtStr = string(istreambuf_iterator<char>(AS), istreambuf_iterator<char>());
	AS.close();
	return converter.from_bytes(rtStr);
}

void analyseStr(vector<dChar*> v, wstring aStr) {
	
	for (int i = 0; i < aStr.size(); i++) {

		for (int j = 0; j < v.size(); j++) {
			if (v[j]->cmp(aStr[i])) {
				v[j]->inc();
			}
		}
	}

}

int calcCount(vector<dChar*> v){
	int genCount = 0;

	for (int i = 0; i < v.size(); i++) {
		genCount += v[i]->getCount();
	}

	for (int i = 0; i < v.size(); i++) {
		v[i]->calcStats(genCount);
	}
	return genCount;
}

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251);

	string inputPath;
	wstring alphabetStr;
	wstring inputStr;

	int gCount = 0;
	double gEntropy = 0.;
	double gAmountI = 0; 

	cout << "\nInput alphabet file name.\n";
	cin >>inputPath;

	alphabetStr = readIntoWStr(inputPath);

	cout << "\nInput text file name.\n";
	cin >> inputPath;

	inputStr  = readIntoWStr(inputPath);


	vector<dChar*> aV;

	for (int i = 0; i < alphabetStr.size(); i+=2) {
		aV.push_back(new dChar(alphabetStr[i], alphabetStr[i +1]));
	}

	analyseStr(aV, inputStr);
	gCount = calcCount(aV);

	cout << "\nNumber of characters in document: "<<gCount<<"\n";
	
	cout << "\nC: ";

	for (int i = 0; i < aV.size(); i++) {
		wcout << setw(wd) << left << aV[i]->getlChar();
	}
	
	cout << "\nn: ";
	
	for (int i = 0; i < aV.size(); i++) {
		wcout << setw(wd) << left << aV[i]->getCount();
	}
	cout << "\np: ";
	for (int i = 0; i < aV.size(); i++) {
		wcout << setw(wd) << left <<setprecision(p)<< aV[i]->getP();
	}
	cout << "\nI: ";
	for (int i = 0; i < aV.size(); i++) {
		wcout << setw(wd) << left << setprecision(p) << aV[i]->getI();
	}
	cout << "\nH: ";
	for (int i = 0; i < aV.size(); i++) {
		wcout << setw(wd) << left << setprecision(p) << aV[i]->getH();
	}
	
	for (int i = 0; i < aV.size(); i++) {
		gEntropy += aV[i]->getH();
	}
	
	for (int i = 0; i < aV.size(); i++) {
		gAmountI += aV[i]->getI();
	}

	cout << "\n\nGeneral amount of information: " <<gAmountI<< "\nGeneral entropy: " << gEntropy<<"\n\n" ;

}


