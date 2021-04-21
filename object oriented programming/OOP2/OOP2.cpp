#include <iostream>
#include <cmath>
using namespace std;

#define col 2 
#define row 4

class Square
{
private:
    int* Coords[2];
    int N = 0;
public:

    Square()
    {
        Initialization();
    }

    Square(int n, int* coords)
    {
      
        if ((n % 2 != 0)||(n/2)<2)
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
    
      
        cout << endl << "This object is destroyed." << endl;
    }

    Square(const Square& Sq)
    {
        N = Sq.N;
        Coords[0] = new int[N];
        Coords[1] = new int[N];

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < N; j++)
            {
                Coords[i][j] = Sq.Coords[i][j];
               
            }
        }
    }

    Square& operator = (const Square& sqrcpy)
    {
        N = sqrcpy.N;
        delete[] Coords[0];
        delete[] Coords[1];

        Coords[0] = new int[N];
        Coords[1] = new int[N];

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < N; j++)
            {
                Coords[i][j] = sqrcpy.Coords[i][j];

            }
        }
        return *this;
    }


    void Initialization()
    {
        int InitialArray[4] = { 1,1,3,3 };
        AssignPoints(4, InitialArray);
        cout << "\nCreated default square." << endl;
    }

    double SideLength()
    {
        return abs(Coords[1][0]-Coords[0][0]);
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
            calcResult =pow(SideLength(), (N - 1))*2*N;
        }

        return calcResult;
    }

    double Perimeter()
    {
        return SideLength()*(pow(2, N) * N / 2) ;
    }

    int** GetPoints()
    {
        return Coords;
    }


    void AssignPoints(int N, int* Coords)
    {


        this->N = N / 2;
        int  isOk = 0;
        double intermediateResult=0;
        intermediateResult = abs(Coords[this->N] - Coords[0]);

            for (int i = 0; i < this->N; i++)
            {
                if (abs(Coords[i+ this->N] - Coords[i]) != intermediateResult)
                {
                    isOk = 1;
                    break;
                }
            }
            if (isOk == 0)
            {
                int d1index = 0;
                this->Coords[0] = new int[this->N];
                this->Coords[1] = new int[this->N];

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

    void DisplayProperties()
    {
        cout << "\nThe side length = " << SideLength() << "\nPerimeter = " << Perimeter() << "\nArea = " << Area() << endl;

    }

};





int main()
{


    int Cube4[] = { 1,1,1,1,2,2,2,2 };


    int* Cube3;
    int numb;
    cout << "Input number of elements (should be even):"<<endl;
    cin >> numb;

    Cube3 = new int[numb];
    cout << "Input elements (difference between elements of first and corresponding of second one should be equal):" << endl;
    for (int i = 0; i < numb; i++)
    {
        cout << "\nEl[" <<i<<"]=";
        cin >> Cube3[i];
   
    }

    Square Sq(row*2,Cube4);

    Sq.DisplayProperties();

    Sq.AssignPoints(numb, Cube3);

    Sq.DisplayProperties();


    Square Sqcpy;
    Sqcpy = Sq;

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << "Element[" << i << "][" << j << "]" << Sqcpy.GetPoints()[i][j] <<endl;
        }
    }

    delete[] Cube3;

    return 0;

}
