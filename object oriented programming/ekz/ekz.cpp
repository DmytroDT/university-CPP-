#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

//bakery product
 class BkryPr {
protected:
    double wght;
    int nSize;
    char* name;

public:

    BkryPr() {
        nSize = 16;
        name = new char[nSize];
        strcpy(name, "basic bakery");
        wght = 0.5;

    }


    BkryPr(string name, double wght) {
        nSize = name.length();
        this->name = new char[nSize];
        strcpy(this->name, name.c_str());
        this->wght = wght;
    }

    ~BkryPr() {
        delete[] name;
    }

    string getName() {
        string ret = "";
        for (int i = 0; i < nSize; i++) {
            ret += name[i];
        }
        return ret;
    }

    virtual void addC(double component) {
        wght += component;
    }

    double getWeight() {
        return wght;
    }

    friend bool operator <= (BkryPr& pr1, BkryPr& pr2) {
        return (pr1.wght <= pr2.wght);
    }

    //Actual : outside of class
    friend  istream& operator >>(istream& is, BkryPr &pr) {
        string name; 
        double weight;
        
        cout << "\n input product name:";
        is >> name;
        cout << "\n input product weight:";
        is >> weight;

        pr.nSize = name.length();
        pr.name = new char[pr.nSize];
        strcpy(pr.name, name.c_str());
    }

    friend ostream& operator <<(ostream& os, BkryPr &pr) {
        os << "\n Bakery product: " << pr.name << " weight: " << pr.wght;
        return os;
    }

};

class SwtBun : public BkryPr {
private: 
    double sgrAmnt;
    int amnt;
    string type="";

public:
    SwtBun() {
        type = "roll";
        sgrAmnt = 0.8;
        amnt = 5;
    }

    SwtBun(double sgr, int amt, string tp) {
        sgrAmnt = sgr;
        amnt = amt;
        type = tp;
    }

    // add component and increase weight 
    void addC(double compnt) override {
        sgrAmnt += compnt;
        this->wght += (1 + compnt);
    }
 
    string getType() {
        string ret ;
       // strcpy(ret, type);
        ret = type;
    }

    double getSgr() { return sgrAmnt; }
    int getAmnt() { return amnt; }

    friend bool operator >(SwtBun& b1, SwtBun& b2) {
        return (b1.type.length() > b2.type.length());
    }

    //Actual : outside of class
    friend istream& operator >>(istream& is, SwtBun &sb) {
        string type;
        double sgr;
        int amnt;

        cout << "\n input bun's type:";
        is >> type;
        cout << "\n input bun's sugar content:";
        is >> sgr;
        cout << "\n input bun's amount in bakery:";
        is >> amnt;

        sb.sgrAmnt = sgr;
        sb.type = type;
        sb.amnt = amnt;
        return is;
    }

};


int main()
{
    BkryPr a;
    BkryPr b("bread", 1.);
    BkryPr c("Bagguette", 0.3);

    SwtBun sa;
    SwtBun sb(0.8, 2, "roll");
    SwtBun sm(0.5, 4, "makovs");

    vector<BkryPr> vc;
    vc.push_back(a);
    vc.push_back(b);
    vc.push_back(c);
    vc.push_back(sa);
    vc.push_back(sb);
    vc.push_back(sm);

        cin >> a;
        cin >> sa;

       // Actual: BkryPr* min;
        BkryPr* min = new BkryPr();

        for (int i = 0; i < vc.size(); i++) {
            if (dynamic_cast<BkryPr*>(&vc[i])) {
                if (*min <= vc[i]) {
                    min = &vc[i];
                }
            }
        }

        cout << *min;

        vector<SwtBun> vc2;

        for (int i = 0; i < vc.size(); i++) {
            if (dynamic_cast<SwtBun*>(&vc[i])) {

                //Actual: vc2.push_back(vc[i]);
                vc2.push_back(*dynamic_cast<SwtBun*>(&vc[i]));
            }
        }

        //compare bakery products by theur weight and output it

        // sort by type lenth

        for (int i = 0; i < vc2.size(); i++) {
            for (int j = 0; j < vc2.size(); j++) {
                if (vc2[j] > vc2[j + 1]) {
                    SwtBun temp;
                    temp = vc2[j + 1];
                    vc2[j + 1] = vc2[j];
                    vc2[j] = temp;
                }
            }
        }

        for (int i = 0; i < vc2.size(); i++) {
            cout << vc2[i];
        }

        vc.clear();
        vc2.clear();
}


