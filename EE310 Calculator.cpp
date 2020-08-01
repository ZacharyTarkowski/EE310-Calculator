// EE310 Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
#include <windows.h>
#include <shellapi.h>
void quadratic(double* root1, double* root2, double a, double b, double c);
void quadratic2(double a, double b, double c);
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
        //changes: 1 for parallel/series rlc
        //2: roots of a characteristic equation
        //3: complex to phasor / phasor to complex
        //4: complex arithmatic? no, go to symbolab
        cout << "What operation" << endl;
        cout << "1 for series/parallel calculations" << endl;
        cout << "2 for roots of a characteristic equation " << endl;
        cout << "3 for impedance calculation" << endl;
        cout << "4 for complex conversions" << endl; //polar to rect a lil broken
        
        cout << "8 for websites" << endl;
        
        cout << "9 for program exit" << endl;
        cin >> command;

        switch (command)
        {
        case 1:
            cout << "Enter 1 for series, 2 for parallel: "; // add in r(inf)
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

            //A1 and A2
            cout << "Enter r(0+) :";
            cin >> entry;
            cout << "Enter dr/dt(0+) :";
            cin >> entry2;
            cout << "Enter r(infinity) :";
            cin >> entry3;
            
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
            
        case 2:
            cout << "Enter a: ";
            cin >> entry;
            cout << "Enter b: ";
            cin >> entry2;
            cout << "Enter c: ";
            cin >> entry3;
            cout << endl;
            quadratic2(entry, entry2, entry3);
            break;

        case 3:
            cout << "1 for Capacitor, 2 for Inductor: ";
            cin >> entry;
            if (entry == 1)
            {
                cout << "Enter w: ";
                cin >> entry2;
                cout << "Enter capacitance: ";
                cin >> entry3;
                cout << "Impedance = -j" << 1 / (entry3 * entry2) << endl;
            }
            if (entry == 2)
            {
                cout << "Enter w: ";
                cin >> entry2;
                cout << "Enter inductance: ";
                cin >> entry3;
                cout << "Impedance = j" <<(entry3 * entry2) << endl;
            }
            break;

        case 4:
            cout << "1 for polar to rectangular, 2 for rectangular to polar: ";
            cin >> entry;

            if (entry == 1)
            {
                cout << "Enter magnitude: ";
                cin >> entry2;
                cout << "Enter phase angle: ";
                cin >> entry3;
                cout << "Converted to " << entry2 * cos(entry3) << " + j" << entry2 * sin(entry3) << endl;
            }
            if (entry == 2)
            {
                cout << "Enter real part: ";
                cin >> entry2;
                cout << "Enter imaginary part: ";
                cin >> entry3;
                double angle = atan(abs(entry3) / abs(entry2)) * 180 / 3.14159;
                if (entry2 < 0 && entry3 > 0) { angle = 180 - angle; }
                if (entry2 < 0 && entry3 < 0) { angle -= 180; }
                if (entry2 > 0 && entry3 < 0) { angle = -1*angle; }
                cout << "Converted to " << sqrt(entry2*entry2 + entry3*entry3) << " angle " << angle << endl;
            }
            break;

        case 8:
            cout << "Enter 1 for symbolab, 2 for complex converter: ";
            cin >> entry;
            if (entry == 1) { ShellExecute(0, 0, L"https://www.symbolab.com/", 0, 0, SW_SHOW); }
            if (entry == 2) { ShellExecute(0, 0, L"https://ejl.neocities.org/", 0, 0, SW_SHOW); }
            break;

        case 9:
            cont = false;
            break;

        default:
            cout << "Dont have it" << endl;
        }
        cout << endl;
    }
}

void quadratic(double *root1, double *root2, double a, double b, double c)
{
    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        *root1 = (-b + sqrt(discriminant)) / (2 * a);
        *root2 = (-b - sqrt(discriminant)) / (2 * a);
    }
    /*
    if (root1 == 0 && root2 == 0)
    {
        cout << "Overdamped" << endl;
        cout << "Roots are " << (-b + sqrt(discriminant)) / (2 * a)<<" and "<< (-b - sqrt(discriminant)) / (2 * a) << endl;
    }

    else if (discriminant == 0) {
        //*root1 = *root2 = (-b + sqrt(discriminant)) / (2 * a);
        cout << "Critically Damped" << endl;
        cout << "Root is " << (-b + sqrt(discriminant)) / (2 * a) << endl;
    }

    else {
        double realPart = -b / (2 * a);
        double imaginaryPart = sqrt(-discriminant) / (2 * a);
        cout << "Underdamped" << endl;
        cout << "Roots are: " << realPart << " +/- j" << imaginaryPart << endl;
    }
    */
}

void quadratic2( double a, double b, double c)
{
    double discriminant = b * b - 4 * a * c;

    if (discriminant>0)
    {
        cout << "Overdamped" << endl;
        cout << "Roots are " << (-b + sqrt(discriminant)) / (2 * a) << " and " << (-b - sqrt(discriminant)) / (2 * a) << endl;
    }

    else if (discriminant == 0) {
        //*root1 = *root2 = (-b + sqrt(discriminant)) / (2 * a);
        cout << "Critically Damped" << endl;
        cout << "Root is " << (-b + sqrt(discriminant)) / (2 * a) << endl;
    }

    else {
        double realPart = -b / (2 * a);
        double imaginaryPart = sqrt(-discriminant) / (2 * a);
        cout << "Underdamped" << endl;
        cout << "Roots are: " << realPart << " +/- j" << imaginaryPart << endl;
    }
    cout << endl;
}

