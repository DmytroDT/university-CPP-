#include <string> 
#include <iostream>
using  namespace std;

class mNumb {
private:
    double number = 0.;
    double m = 0.;
public:

#pragma region constructors

    mNumb() : number(0.), m(0.) {}

    mNumb(double number_, double m_) : number(number_), m(m_) {}

    mNumb(double number_) : number(number_), m(0.) {}

    mNumb(const mNumb& copy) : number(copy.number), m(copy.m) {}

#pragma endregion

    double getN() const {
        return number;
    }

    double getM() const {
        return m;
    }

    friend ostream& operator<<(ostream& os, const mNumb& ref) {
        os << ref.number;
        if (ref.checkIfM()) {
            if (ref.m < 0) {
                os << ref.m << "M";
            }
            else {
                os << "+" << ref.m << "M";
            }
        }

        return os;
    }


#pragma region bool_1

    bool checkIfM() const {
        return (m != 0.);
    }

    bool checkIfRhsM(const mNumb& rhs) const {
        return (this->checkIfM() || rhs.checkIfM());
    }

    bool operator<(const mNumb& rhs) const {
        return (checkIfRhsM(rhs)) ? (this->m < rhs.m) : (this->number < rhs.number);
    }
    
    bool operator>(const mNumb& rhs) const {
        return rhs<*this;
    }

    bool operator<=(const mNumb& rhs) const {
        return !(*this > rhs);
    }

    bool operator>=(const mNumb& rhs) const {
        return !(*this < rhs);
    }
    
    bool operator==(const mNumb& rhs) const {
        return ((this->number==rhs.number)&&(this->m==rhs.m));
    }

    bool operator!=(const mNumb& rhs) const {
        return !(*this == rhs);
    }

#pragma endregion 

#pragma region arithmetic

    mNumb& operator=(const mNumb& ref) {

        if (this != &ref) {
            number = ref.number;
            m = ref.m;
        }
        return *this;
    }

    mNumb& operator+=(const mNumb& rhs) {
        number += rhs.number;
        if (checkIfRhsM(rhs)) {
            m += rhs.m;
        }
        return *this;
    }

    mNumb& operator-=(const mNumb& rhs) {
        number -= rhs.number;
        if (checkIfRhsM(rhs)) {
            m -= rhs.m;
        }
        return *this;
    }

    mNumb operator+(const mNumb& rhs) const {
        mNumb temp(*this);
        temp += rhs;
        return temp;
    }

    mNumb operator-(const mNumb& rhs) const {
        mNumb temp(*this);
        temp -= rhs;
        return temp;
    }

    mNumb& operator*=(double coef) {
        number *= coef;
        if (checkIfM()) {
            m *= coef;
        }
        return *this;
    }

    mNumb& operator/=(double coef) {
        number /= coef;
        if (checkIfM()) {
            m /= coef;
        }
        return *this;
    }

    mNumb operator*(double coef) const {
        mNumb temp(*this);
        temp *= coef;
        return temp;
    }

    mNumb operator/(double coef) const {
        mNumb temp(*this);
        temp /= coef;
        return temp;
    }

#pragma endregion

};

int main()
{
   
   
}

