#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#pragma once

class ComplexNumber
{
public:
    ComplexNumber();
    ComplexNumber(const double& a, const double& b);

    ComplexNumber square() const;
    double radius() const;

    friend ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs);
    friend ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs);

    double real() const;
    double imag() const;

private:
    double x_;
    double y_;
};

#endif // COMPLEXNUMBER_H
