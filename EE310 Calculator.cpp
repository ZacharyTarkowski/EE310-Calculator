// EE310 Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
void quadratic(double* root1, double* root2, double a, double b, double c);
using namespace std;

int main()
{
    int command;
    int sp;
    bool cont =true;
    double entry;
    double entry2;
    double entry3;
    double a =0;
    double w = 0;
    double s1;
    double s2;
    double a1;
    double a2;

    while (cont)
    {
        cout << "What operation" << endl;
        cout << "1 for alpha and omega-not calculation" << endl;
        cout << "2 for A1 A2 calculation" << endl;
        
        cout << "9 for program exit" << endl;
        cin >> command;

        switch (command)
        {
        case 1:
            cout << "Enter 1 for series, 2 for parallel: ";
            cin >> sp;
            cout << "Enter R :";
            cin >> entry;
            cout << "Enter L :";
            cin >> entry2;
            cout << "Enter C :";
            cin >> entry3;
            if (sp == 1) { a = entry / (2 * entry2); }
            if (sp == 2) { a = 1 / (2 * entry * entry3); }
            w = 1 / sqrt(entry2 * entry3);
            cout << "\nAlpha = " << a;
            cout << "\nOmega-not = " << w << endl;
            if (w > a) { cout << "Omega-d = " << sqrt((w * w) - (a * a)) << "\n"<<endl; }
            cout << endl;
            break;
            
        case 2:
            cout << "Enter r(0+) :";
            cin >> entry;
            cout << "Enter dr/dt(0+) :";
            cin >> entry2;
            
            if (a > w )
            {
                quadratic(&s1, &s2, 1, a * 2, w * w);
                cout << "s1 is: " << s1 << " s2 is: " << s2 << endl;
                a1 = ((entry * s2) - entry2) / (s2 - s1);
                a2 = entry - a1;
                cout << "A1 = " << a1;
                cout << "\nA2 = " << a2 << endl;
            }

            if (a == w)
            {
                a2 = entry;
                a1 = entry2 + a * a2;
                cout << "A1 = " << a1;
                cout << "\nA2 = " << a2 << endl;
            }

            if (a < w)
            {
                a1 = entry;
                a2 = (entry2 + a * a1) / (sqrt((w * w) - (a * a)));
                cout << "A1 = " << a1;
                cout << "\nA2 = " << a2 << endl;
            }

            cout << endl;
            break;

        case 9:
            cont = false;
            break;

        default:
            cout << "Dont have it" << endl;
        }
    }
}

void quadratic(double *root1, double *root2, double a, double b, double c)
{
    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        *root1 = (-b + sqrt(discriminant)) / (2 * a);
        *root2 = (-b - sqrt(discriminant)) / (2 * a);
    }

    else if (discriminant == 0) {
        //*root1 = *root2 = (-b + sqrt(discriminant)) / (2 * a);
        cout << "Critically Damped" << endl;
    }

    else {
        //double realPart = -b / (2 * a);
        //double imaginaryPart = sqrt(-discriminant) / (2 * a);
        cout << "Underdamped" << endl;
    }

}

