#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class complex
{
public:
    double real, imag;
    complex()
    {
        this->real = 0;
        this->imag = 0;
    }
    complex(double real, double imag)
    {
        this->real = real;
        this->imag = imag;
    }

    complex operator+(const complex &other)
    {
        return complex(this->real + other.real, this->imag + other.imag);
    }

    complex operator-(const complex &other)
    {
        return complex(this->real - other.real, this->imag - other.imag);
    }

    complex operator*(const complex &other)
    {
        return complex(
            (this->real * other.real) - (this->imag * other.imag),
            (this->real * other.imag) + (this->imag * other.real));
    }

    complex operator/(const complex &other)
    {
        return complex(
            ((this->real * other.real) + (this->imag * other.imag)) / (pow(other.real, 2) + pow(other.imag, 2)),
            ((this->imag * other.real) - (this->real * other.imag)) / (pow(other.real, 2) + pow(other.imag, 2)));
    }

    friend ostream &operator<<(ostream &out, const complex &c)
    {
        if (c.imag >= 0)
        {
            out << c.real << "+" << c.imag << "i";
        }
        else
        {
            out << c.real << "-" << -c.imag << "i";
        }

        return out;
    }

    friend istream &operator>>(istream &in, complex &c)
    {
        cout << "enter real part = ";
        in >> c.real;
        cout << "enter imaginary part = ";
        in >> c.imag;

        return in;
    }
};

int main()
{
    complex c1;
    complex c2;
    complex c3;

    cin >> c1;
    cin >> c2;

    c3 = c1 + c2;
    cout << "Addition = " << c3 << endl;

    c3 = c1 - c2;
    cout << "Substraction = " << c3 << endl;

    c3 = c1 * c2;
    cout << "Multiplication = " << c3 << endl;

    c3 = c1 / c2;
    cout << "Division = " << c3 << endl;

    return 0;
}