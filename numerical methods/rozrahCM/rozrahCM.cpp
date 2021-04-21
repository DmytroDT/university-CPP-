#include <cmath>
#include <iostream>
#include <iomanip>  
#include <string>
#include <locale>
#include <clocale>
using namespace std;

class PartialSolver {
private:
    double** arr;
    double** cpy;

    int col=1, row=1;
    double xA=0, xB=1;
    double h=0;

    double* a;

public:

    PartialSolver(int n) {

        h = (xB - xA) / n;
        col = n+2;
        row = n+1;

        arr = new double* [row];
        for (int i = 0; i < row; i++) {
            arr[i] = new double[col];
        }

        nullify();

        generate2dArr();

        a = new double[row];
    }

    void generate2dArr() {

        int inc = 1;
        arr[0][0] = beginUN(h);
        arr[0][1] = 0;

        arr[row - 1][col - 2] = cEndUn(h);
        arr[row - 1][col - 3] = cEndUn1();
        arr[row - 1][col - 4] = cEndUn2();


        arr[0][col - 1] = beginAN(h);
        arr[row - 1][col - 1] = 0;

        for (double x = xA + h; x < xB-h ; x += h) {

            arr[inc][inc] = calcUN(x, h);
            arr[inc][inc - 1] = calcU1N(x);
            arr[inc][inc + 1] = calcUN1(x, h);
            arr[inc][col - 1] = calcF(h, x);
            inc++;

        }
    }

    void copyArr() {
        cpy = new double* [row];
        for (int i = 0; i < row; i++) {
            cpy[i] = new double[col];
        }


        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cpy[i][j] = arr[i][j];
            }
        }

    }

    void printcpy() {
        for (int i = 0; i < row; i++) {
            cout << "\n";
            for (int j = 0; j < col; j++) {
                cout << setw(9) << left << setprecision(6) << cpy[i][j];
            }
        }
    }

    void computeAbErr() {

        a[0] = abs(cpy[0][col - 1]-arr[0][col - 1]*cpy[0][0]);
        a[row-1] = abs(cpy[row - 1][col - 1] - (arr[row - 1][col - 1] * cpy[row - 1][col - 2] + arr[row - 2][col - 1] * cpy[row - 1][col - 3]+ arr[row - 3][col - 1] * cpy[row - 1][col - 4]));

        for (int i = 1; i < row-1;i ++) {
            a[i] = abs(cpy[i][col - 1] - (arr[i-1][col - 1] * cpy[i][i-1] + arr[i][col - 1] * cpy[i][i] + arr[i + 1][col - 1] * cpy[i ][i+1]));
        }

    }

    void nullify() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                arr[i][j] = 0;
            }
        }
    }

    void thomasForward() {
        double* divHold;
        divHold = new double[row];
        double numHold = 0;

        numHold= arr[0][0];

        arr[0][0] /= numHold;
        arr[0][1] /= numHold;
        arr[0][col-1] /= numHold;

        for (int i = 1; i < row-1; i++) {
            numHold = arr[i][i - 1];
            
            for (int j = 0; j < col; j++) {
                divHold[j] = arr[i - 1][j] * numHold;
                arr[i][j] -= divHold[j];
            }

            numHold = arr[i][i];

            for (int j = 0; j < col; j++) {
                arr[i][j] /= numHold;
            }
       }

        numHold = arr[row-1][col-4];
       
        for (int j = 0; j < col; j++) {
            divHold[j] = arr[row - 3][j] * numHold;
            arr[row - 1][j] -= divHold[j];
        }

        numHold = arr[row - 1][col - 3];
        
        for (int j = 0; j < col; j++) {
            divHold[j] = arr[row - 2][j] * numHold;
            arr[row - 1][j] -= divHold[j];
        }

        arr[row - 1][col - 1] /= arr[row - 1][col - 2];
        arr[row - 1][col - 2] /= arr[row - 1][col - 2];
    }

    void thomasBackwards() {

         for (int j = row-2; j >0; j--) {
             arr[j][col-1] -= arr[j+1][col - 1] *arr[j][j+1];
             
         }
    }

    void solveMatrix() {
        thomasForward();
        thomasBackwards();
    }

    double  calcQ() {
        return -2;
    }

    double  calcP() {
        return 1;
    }

    double calcF(double h,double x) {
        return pow(h, 2)*(-2*x+1);
    }

    double calcU1N(double h) {
        return (1 - h*calcP()/ 2);
    }

    double calcUN(double x, double h) {
        return (pow(h, 2)*calcQ()-2);
    }

    double calcUN1(double x, double h) {
        return (1 + h *calcP()/ 2);
    }

    double beginUN(double h) {
        return 1*h;
    }

    double beginAN(double h) {
        return 2*h;
    }

    double beginUN1() {
        return 0;
    }

    double cEndUn2() {
        return -1;
    }

    double cEndUn1() {
        return 4;
    }

    double cEndUn(double h) {
        return 2 * h - 3;

    }

    void printSolution() {
        int inc = 0;
        cout << "\n\nResults are:";
        for (double i = xA ; i <= xB; i += h) {
            cout << "\ny[ " << i << " ]= " << setprecision(4) << arr[inc][col-1]<<" ";
            inc++;
        }
        cout << "\n";
        cout << "\nAbsolute errors are:\tRelative errors are:";
        cout << "\n";
        for (int i = 0; i < row; i++) {
            cout << "a["<<i<<"]= " << a[i] << " \t" << setprecision(4) << 100 * abs(a[i] / arr[i][col - 1])<<" \n";
        }

    }

    friend ostream& operator<<(ostream& os, PartialSolver& es) {
    
        for (int i = 0; i < es.row; i++) {
            os << "\n";
            for (int j = 0; j < es.col; j++) {
                os << setw(9) << left << setprecision(6) << es.arr[i][j] ;
            }
        }
        return os;

    }

    ~PartialSolver() {
        
        for (int i = 0; i < row; i++) {
            delete[] arr[i];
        }
        delete[] arr;
        delete[] a;
    }

};

int main()
{
    int n;
    cout << "4M Rozrahunkova" << endl << "Creator: Dmytro Dutkovskyi" << endl;
    cout << "----------------------------------" << endl;
    cout << "input n:" << endl;
    std::setlocale(LC_ALL, ""); 
    std::locale::global(std::locale("")); 
    std::cout.imbue(std::locale());
    cin >> n;
    PartialSolver Ps(n);
    
    cout << Ps;
    Ps.copyArr();
    cout << "\n";
    Ps.solveMatrix();
    cout << Ps;
    cout << "\n";
    Ps.computeAbErr();
    Ps.printSolution();

}
