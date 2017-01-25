
class Rational
{
public:
	Rational( int numerator = 0, int denominator = 1);
	int getNumerator() const;
	int getDenominator() const;
////	const Rational operator *(const Rational& rhs) const;

private:
	int numerator;
	int denominator;
};

int Rational::getNumerator() const
{
	return numerator;
}

int Rational::getDenominator() const
{
	return denominator;
}

// when non-explicit constructors are involved, explicit constructors can't be used 
// for implicit conversions; that's what explicit means. If Rational were defined like this: 
//class Rational {
//public:
//  explicit Rational(int numerator = 0,     // this ctor is
//                    int denominator = 1);  // now explicit
//  //...
//  const Rational operator*(const Rational& rhs) const;
//  ...
//};
//
// neither of these statements would compile: 
//
// result = oneHalf * 2;             // error!
// result = 2 * oneHalf;             // error!
// That would hardly qualify as support for mixed-mode arithmetic, 
// but at least the behavior of the two statements would be consistent. 

//
// implicit ctor
Rational::Rational( int numerator, int denominator)
{
	this->numerator = numerator;
	this->denominator = denominator;
}

///
/// in this case, operator * is defined as a member
/// it's OK if implicit conversions are supported (see ctor)
///
////const Rational Rational::operator *(const Rational& rhs) const
////{
////	Rational result = Rational(this->numerator * rhs.numerator,
////		this->denominator * rhs.denominator);
////
////	return result;
////}

/// alternative: have operator * be a non-member function
///
const Rational operator *(const Rational& lhs,
						  const Rational& rhs) 
{
	return Rational(lhs.getNumerator() * rhs.getNumerator(),
		lhs.getDenominator() * rhs.getDenominator() );
}