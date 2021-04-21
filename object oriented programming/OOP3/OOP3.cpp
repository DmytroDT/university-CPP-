#include <iostream>
#include <cmath>
using namespace std;

#define col 2 
#define row 4

class Square
{
private:
    double* Coords[2];
    int N = 0;
    static int wasCreated;
    static Square *ObjectReference;

    Square()
    {
        Initialization();
    }

    Square(int n, double* coords)
    {

        if ((n % 2 != 0) || (n / 2) < 2)
        {
            Initialization();
        }
        else
        {
            AssignPoints(n, coords);
        }

    }

    ~Square()
    {
        if (Coords)
        {
            delete Coords[0];
            delete Coords[1];
        }

    }

    Square(const Square& Sq)
    {
        N = Sq.N;
        Coords[0] = new double[N];
        Coords[1] = new double[N];

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < N; j++)
            {
                Coords[i][j] = Sq.Coords[i][j];

            }
        }
    }

public:

    static Square& getInstance() {

        if (!wasCreated) {
            ObjectReference = new Square();
            wasCreated = true;
        }
        return *ObjectReference;
    }

    Square& operator = (const Square& sqrcpy)
    {
        N = sqrcpy.N;
        delete[] Coords[0];
        delete[] Coords[1];

        Coords[0] = new double[N];
        Coords[1] = new double[N];

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < N; j++)
            {
                Coords[i][j] = sqrcpy.Coords[i][j];

            }
        }
        return *this;
    }


    friend istream& operator>>(istream& is, Square& square)
    {
        double* Cube3;
        int numb;
        cout << "Input number of elements (should be even):" << endl;
        is >> numb;

        Cube3 = new double[numb];
        cout << "Input elements (difference between elements of first and corresponding of second one should be equal):" << endl;
        for (int i = 0; i < numb; i++)
        {
            cout << "\nEl[" << i << "]=";
            is >> Cube3[i];
        }
        square.AssignPoints(numb, Cube3);
        delete[] Cube3;

        return is;
    }


    friend ostream& operator<<(ostream& os, Square& square)
    {
         
       
        os << "\nNumber of dimensions = " <<square.N<<"\nThe side length = " << square.SideLength() << "\nDiagonal length = " << square.diagonalLength() << "\nPerimeter = " << square.Perimeter() << "\nArea = " << square.Area()<< endl;
        return os;
    }

    void DisplayPoints()
    {
        cout << endl;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << "Element[" << i << "][" << j << "]" << GetPoints()[i][j] << endl;
            }
        }
    }

    Square operator -(double numb)
    {
        Square Sq;

        Sq = *this; 

        double diagonal = Sq.diagonalLength();
        double Side = Sq.SideLength();
        double difference = Side - (diagonal - numb) / sqrt(N);

        if (Coords[1][0] < 0)
            difference *= -1;

        for (int i = 0; i < N; i++)
        {
            Sq.Coords[1][i] -= difference;
        }

        return Sq;
    }

    Square operator -=(double numb)
    {
        *this  = *this - numb;
        return *this;
    }

    friend bool operator>=(Square& sq1,Square& sq2)
    {
        return (sq1.diagonalLength() >= sq2.diagonalLength());
    }

    friend bool operator<=(Square& sq1, Square& sq2)
    {
        return (sq1.diagonalLength() <= sq2.diagonalLength());
    }

    friend bool operator==(Square& sq1, Square& sq2)
    {
        return (sq1.diagonalLength() == sq2.diagonalLength());
    }


    double diagonalLength() 
    {
        return sqrt(N)*SideLength();
    }

    void Initialization()
    {
        double InitialArray[4] = { 1,1,3,3 };
        AssignPoints(4, InitialArray);
    }

    double SideLength()
    {
        return  fabs(Coords[1][0] - Coords[0][0]);
    }

    double Area()
    {
        double calcResult;

        if (N == 2)
        {
            calcResult = pow(SideLength(), 2);
        }
        else
        {
            calcResult = pow(SideLength(), (N - 1)) * 2 * N;
        }

        return calcResult;
    }

    double Perimeter()
    {
        return SideLength() * (pow(2, N) * N / 2);
    }

    double** GetPoints()
    {
        return Coords;
    }


    void AssignPoints(int N, double* Coords)
    {
        this->N = N / 2;
        int  isOk = 0;
        double intermediateResult = 0;
        intermediateResult = abs(Coords[this->N] - Coords[0]);

        for (int i = 0; i < this->N; i++)
        {
            if (abs(Coords[i + this->N] - Coords[i]) != intermediateResult)
            {
                isOk = 1;
                break;
            }
        }
        if (isOk == 0)
        {
            int d1index = 0;
            this->Coords[0] = new double[this->N];
            this->Coords[1] = new double[this->N];

            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < this->N; j++)
                {
                    this->Coords[i][j] = Coords[d1index];
                    d1index++;
                }
            }
        }
        else
        {
            Initialization();
        }
    }

};

 int Square::wasCreated=false;
 Square* Square::ObjectReference=nullptr;



int main()
{
    double Cube4[][12] = { {3,3,5,5},{0,0,0,1,1,1},{1,1,1,1,5.5f,5.5f,5.5f,5.5f},{-1,-1,-1,-1,-1,-3,-3,-3,-3,-3},{4,4,4,4,4,4,10.6f,10.6f,10.6f,10.6f,10.6f,10.6f} };

    Square& sq = Square::getInstance();

    cout << sq;
  
    Square& sq2 = Square::getInstance();

    sq2.AssignPoints(6, Cube4[1]);

    cout << sq;

    return 0;
}
