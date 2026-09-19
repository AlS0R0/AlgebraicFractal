#include "complexnumber.h"

ComplexNumber::ComplexNumber() : x_(0.0), y_(0.0) {}
ComplexNumber::ComplexNumber(const double& a, const double& b) : x_(a), y_(b) {}

ComplexNumber ComplexNumber::square() const
{
    ComplexNumber res = (*this) * (*this);
    return res;
}

double ComplexNumber::radius() const
{
    double res = (x_ * x_ + y_ * y_);
    return res;
}
ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
    ComplexNumber res = ComplexNumber(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
    return res;
}

ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
    ComplexNumber res = ComplexNumber(lhs.x_ * rhs.x_ - lhs.y_ * rhs.y_,
                                      lhs.x_ * rhs.y_ + lhs.y_ * rhs.x_);
    return res;
}

double ComplexNumber::real() const
{
    return x_;
}

double ComplexNumber::imag() const
{
    return y_;
}