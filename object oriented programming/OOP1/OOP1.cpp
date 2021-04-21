#include <iostream>
#include <cmath>
using namespace std;

class Square
{
private:
    int PointAx, PointAy, PointCx,PointCy;
public:
    Square() 
    {
        PointAx = 1; PointAy = 2; 
    }
    Square(int Ax, int Ay, int Cx, int Cy)
    {
        SetPoints(Ax, Ay, Cx,Cy);
    }

    ~Square()
    {
        cout <<endl<<"This object is going to be destroyed."<<endl;
    }

    float SideLength() 
    {
      
        return sqrt(pow((PointCx - PointAx), 2));
    }
    
    float Area() 
    {
        return pow(SideLength(), 2);
    }

    float Perimeter()
    {
        return SideLength() * 4;
    }

    void GetPoints(int* PointerAx, int* PointerAy, int* PointerCx, int* PointerCy)
    {
        *PointerAx = PointAx; *PointerAy = PointAy;
        *PointerCx = PointCx; *PointerCy = PointCy;
    }



    void SetPoints(int Ax, int Ay, int Cx, int Cy)
    {
        if (abs(Cx-Ax) != abs(Cy-Ay))
        {
            cout << endl<< "Point A & C should have equal projections on X & Y ordinates in order to create a square." << endl;
            PointAx = 0;
            PointCx = 0;
        }
        else
        {
            PointAx = Ax; PointAy = Ay;
            PointCx = Cx; PointCy = Cy;
        }
    }

    void DisplayProperties() 
    {
        if ((PointAx==0 )&& (PointCx == 0))
        {
            cout << endl << "Failed to create a square."<<endl;
        }
        else
        {
            cout << endl << "Lenght of a side =" << SideLength() << endl << "Area of a Sqaure =" << Area() << endl << "Perimeter of a square =" << Perimeter() << endl;
        }
            
    }

};


int main()
{
    int x1,y1,x2,y2;

    cout << "Please, input four different coordinates of a  points creating diagonal of a square." << endl;
    cout << "Ax= ";
    cin >> x1;
    cout << "Ay= ";
    cin >> y1;
    cout << "Cx= ";
    cin >> x2;
    cout << "Cy= ";
    cin >> y2;
    Square Sq(x1, y1,x2,y2);

    Sq.DisplayProperties();

    x1 = 0; y1 = 0; x2 = 0; y2 = 0;

    Sq.GetPoints(&x1, &y1, &x2, &y2);

    cout << "pointA Ax = " << x1 << " point Ay = " << y1<<endl;

    cout << "pointC Cx = " << x2 << " point Cy = " << y2<<endl;

    Sq.SetPoints(1, 2,4,4);

      Sq.DisplayProperties();

 
    return 0;
}

