#ifndef __ValueConverter__
#define __ValueConverter__

#include <float.h>
#include <algorithm>    // std::max
#include <cmath>

//--------------------------------------------------------------------------------------
// convert values between UI and Faust. The UI side is described
// by a min and max value. The Faust side is described by a min and max value
// as well as a scale mode : lin, log or exp. Log and exp mappings are build on top of
// linear conversion.
//--------------------------------------------------------------------------------------
class ValueConverter 
{

 public:

	virtual ~ValueConverter() {}

	virtual double ui2faust(double x) = 0;

	virtual double faust2ui(double x) = 0;
};


class LinearValueConverter : public ValueConverter
{
	double	fUMin;
	double 	fUMax;
	double	fFMin;
	double	fFMax;
	double 	fUDelta;
	double	fFDelta;

 public:

	LinearValueConverter(double umin, double umax, double fmin, double fmax) :
		fUMin(umin), 
		fUMax((umax==umin) ? umax+DBL_MIN : umax), 
		fFMin(fmin), 
		fFMax((fmax==fmin) ? fmax+DBL_MIN : fmax) 
	{
		fUDelta = fUMax-fUMin;
		fFDelta = fFMax-fFMin;
	}

	virtual double ui2faust(double x) 
	{
		if (x >= fUMax) {
			return fFMax;
		} else if (x <= fUMin) {
			return fFMin;
		}
		return fFMin +  fFDelta * (x - fUMin)/fUDelta;
	}

	virtual double faust2ui(double x) 
	{
		if (x > fFMax) {
			x = fFMax;
		} else if (x < fFMin) {
			x = fFMin;
		}
		return fUMin +  fUDelta * (x - fFMin)/fFDelta;
	}
};

//--------------------------------------------------------------------------------------
// Logarithmic conversion between ui and faust values
//--------------------------------------------------------------------------------------
class LogValueConverter : public LinearValueConverter
{

 public:

	LogValueConverter(double umin, double umax, double fmin, double fmax) :
		LinearValueConverter(umin, umax, log(std::max(DBL_MIN,fmin)), log(std::max(DBL_MIN,fmax))) 
	{ }

	virtual double ui2faust(double x) 
	{
		return exp(LinearValueConverter::ui2faust(x));
	}

	virtual double faust2ui(double x) 
	{
		return LinearValueConverter::faust2ui(log(std::max(x, DBL_MIN)));
	}
};

//--------------------------------------------------------------------------------------
// Exponential conversion between ui and faust values
//--------------------------------------------------------------------------------------
class ExpValueConverter : public LinearValueConverter
{

 public:

	ExpValueConverter(double umin, double umax, double fmin, double fmax) :
		LinearValueConverter(umin, umax, exp(fmin), exp(fmax)) 
	{ }

	virtual double ui2faust(double x) 
	{
		return log(LinearValueConverter::ui2faust(x));
	}

	virtual double faust2ui(double x) 
	{
		return LinearValueConverter::faust2ui(exp(x));
	}
};

#endif
