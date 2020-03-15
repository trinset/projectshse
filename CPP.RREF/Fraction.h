//
// Created by Олег Васютин on 2020-03-15.
//

#ifndef UNTITLED_FRACTION_H
#define UNTITLED_FRACTION_H

#include<iostream>
#include<cmath>
#include <ostream>
#include <stdexcept>
#include <string>

int gcd(int a, int b)
{
    if (b == 0)
    {
        return abs(a);
    }
    return gcd(b, a % b);
}

class Rational
{
public:
    Rational (int r = 0, int i = 1)
    {
        if (i) {
            if (gcd(r, i)) {
                numer = r / gcd(r, i);
                denomin = i / gcd(r, i);
            } else {
                numer = r;
                denomin = i;
            }
            if (denomin < 0)
            {
                numer *= (-1);
                denomin *= (-1);
            }
        }
        else
        {
            throw std::invalid_argument("received zero denominator");
        }
    }

    Rational operator+ (const Rational &rat) const;
    Rational operator+ (int &a) const;

    Rational operator- (const Rational &rat) const;
    Rational operator- (int &a) const;

    Rational operator* (const Rational &rat) const;
    Rational operator* (int &a) const;

    Rational operator/ (const Rational &rat) const;
    Rational operator/ (int &a) const;

    Rational& operator*= (const Rational &rat);
    Rational& operator*= (int &a);

    Rational& operator+= (const Rational &rat);
    Rational& operator+= (int &a);

    Rational& operator/= (const Rational &rat);
    Rational& operator/= (int &a) ;

    Rational& operator-= (const Rational &rat);
    Rational& operator-= (int &a);

    Rational& operator++ ();
    Rational operator++ (int);
    Rational& operator-- ();
    Rational operator-- (int);

    Rational operator+ () const;
    Rational operator- () const;

    bool operator== (const Rational &rat) const;
    bool operator== (int &a) const;

    bool operator!= (const Rational &rat) const;
    bool operator!= (int &a) const;

    int numerator() const
    {
        return numer;
    }
    int denominator() const
    {
        return denomin;
    }
private:

    int numer, denomin;

};


Rational Rational::operator+ (const Rational &rat) const
{
    return (Rational(numer * rat.denominator() + rat.numerator() * denomin, denomin * rat.denominator()));
}

Rational Rational::operator+ (int &a) const
{
    return (Rational(numer + a * denomin, denomin));
}

Rational operator+ (int a, const Rational &rat)
{
    return (rat + a);
}

Rational Rational::operator+ () const
{
    return (*this);
}

Rational Rational::operator- () const
{
    return (*this * (-1));
}

Rational Rational::operator- (const Rational &rat) const
{
    return (Rational(numer * rat.denominator() - rat.numerator() * denominator(), rat.denominator() * denomin));
}

Rational Rational::operator- (int &a) const
{
    return (Rational(numer - a * denomin, denomin));
}

Rational operator- (int a, const Rational &rat)
{
    return (Rational(-rat + a));
}

Rational Rational::operator* (const Rational &rat) const
{
    return (Rational(numer * rat.numerator(), denomin * rat.denominator()));
}

Rational Rational::operator* (int &a) const
{
    return (Rational(a * numer, denomin));
}

Rational operator* (int a, const Rational &rat)
{
    return rat * a;
}

Rational Rational::operator/ (const Rational &rat) const
{
    return (Rational(numer * rat.denominator(), denomin * rat.numerator()));
}

Rational Rational::operator/(int &a) const
{
    return (Rational(numer, denomin * a));
}

Rational operator/ (int a, const Rational &rat)
{
    return (Rational(a * rat.denominator(), rat.numerator()));
}

bool Rational::operator== (int &a) const
{
    return (numer == a && denomin == 1);
}

bool Rational::operator==(const Rational &rat) const
{
    return (numer == rat.numerator() && denomin == rat.denominator());
}

bool operator== (int a, const Rational &rat)
{
    return (rat == a);
}

bool Rational::operator!= (const Rational &rat) const
{

    return (!(*this == rat));
}

bool Rational::operator!= (int &a) const
{
    return (!(*this == a));
}

bool operator!= (int a, const Rational &rat)
{
    return (!(rat == a));
}

Rational& Rational::operator+=(const Rational &rat)
{
    *this = *this + rat;
    return (*this);
}

Rational& Rational::operator+= (int &a)
{
    *this = *this + a;
    return (*this);
}

Rational& Rational::operator-= (const Rational &rat)
{
    *this = *this - rat;
    return (*this);
}

Rational& Rational::operator-= (int &a)
{
    *this = *this - a;
    return (*this);
}

Rational& Rational::operator*= (const Rational &rat)
{
    *this = *this * rat;
    return (*this);
}

Rational& Rational::operator*= (int &a)
{
    *this = *this * a;
    return (*this);
}

Rational& Rational::operator/= (const Rational &rat)
{
    *this = *this / rat;
    return (*this);
}

Rational& Rational::operator/= (int &a)
{
    *this = *this / a;
    return (*this);
}

Rational& Rational::operator++()
{
    *this = *this + 1;
    return (*this);
}

Rational Rational::operator++(int)
{
    const Rational a(*this);
    *this = *this + 1;
    return (a);
}

Rational& Rational::operator--()
{
    *this = *this - 1;
    return (*this);
}

Rational Rational::operator--(int)
{
    Rational a(*this);
    *this = *this - 1;
    return (a);
}

std::ostream& operator<<(std::ostream& out, const Rational& b)
{
    if (b.numerator())
    {
        if (b.denominator() == 1)
        {
            out << b.numerator();
        }
        else
        {
            out << b.numerator() << '/' << b.denominator();
        }
    }
    else
    {
        out << 0;
    }
    return out;
}

std::istream& operator>> (std::istream& in, Rational& a)
{
    std::string str;
    std::string str1;
    in >> str;
    bool rat = false;
    int c = 0, b = 0;
    for (char el : str) {
        if (el == '/') {
            rat = true;
            c = std::stoi(str1);
            str1 = "";
        }
        else {
            str1 += el;
        }
    }
    if (rat)
    {
        b = std::stoi(str1);
    }
    else
    {
        c = std::stoi(str1);
        b = 1;
    }
    a = Rational(c, b);
    return in;
}

#endif //UNTITLED_FRACTION_H
