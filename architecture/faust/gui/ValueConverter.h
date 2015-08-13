#ifndef __ValueConverter__
#define __ValueConverter__

/***************************************************************************************
								ValueConverter.h
							    (GRAME, © 2015)

Set of conversion objects used to map user interface values (for example a gui slider 
delivering values between 0 and 1) to faust values (for example a vslider between
20 and 20000) using a log scale.

-- Utilities

Range(lo,hi) : clip a value x between lo and hi
Interpolator(lo,hi,v1,v2) : Maps a value x between lo and hi to a value y between v1 and v2
Interpolator3pt(lo,mi,hi,v1,vm,v2) : Map values between lo mid hi to values between v1 vm v2

-- Value Converters

ValueConverter::ui2faust(x)
ValueConverter::faust2ui(x)

-- ValueConverters used for sliders depending of the scale

LinearValueConverter(umin, umax, fmin, fmax)
LogValueConverter(umin, umax, fmin, fmax)
ExpValueConverter(umin, umax, fmin, fmax)

-- ValueConverters used for accelerometers based on 3 points

AccUpConverter(amin, amid, amax, fmin, fmid, fmax)		-- curve 0
AccDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 1
AccUpDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 2
AccDownUpConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 3

-- lists of ZoneControl are used to implement accelerometers metadata for each axes

ZoneControl(zone, valueConverter) : a zone with an accelerometer data converter 

****************************************************************************************/


#include <float.h>
#include <algorithm>    // std::max
#include <cmath>


//--------------------------------------------------------------------------------------
// Range(lo,hi) clip a value between lo and hi
//--------------------------------------------------------------------------------------
class Range
{
    
  private:
    
	double	fLo;
	double 	fHi;

  public:
    
	Range(double x, double y) : fLo(std::min(x,y)), fHi(std::max(x,y)) {}
	double operator()(double x) { return (x<fLo) ? fLo : (x>fHi) ? fHi : x; }
};


//--------------------------------------------------------------------------------------
// Interpolator(lo,hi,v1,v2) 
// Maps a value x between lo and hi to a value y between v1 and v2
// y = v1 + (x-lo)/(hi-lo)*(v2-v1)
// y = v1 + (x-lo) * coef   		with coef = (v2-v1)/(hi-lo)
// y = v1 + x*coef - lo*coef
// y = v1 - lo*coef + x*coef
// y = offset + x*coef				with offset = v1 - lo*coef
//--------------------------------------------------------------------------------------
class Interpolator
{
    
  private:
    
	Range	fRange;
	double 	fCoef;
	double 	fOffset;

  public:
    
	Interpolator(double lo, double hi, double v1, double v2) : fRange(lo,hi)
	{ 
		if (hi != lo) { 
			// regular case
			fCoef = (v2-v1)/(hi-lo); 
			fOffset = v1 - lo*fCoef; 
		} else {
			// degenerate case, avoids division by zero
			fCoef = 0;
			fOffset = (v1+v2)/2;
		}
	}
	double operator()(double v) 
	{
		double x = fRange(v);
		return  fOffset + x*fCoef;
	}
};


//--------------------------------------------------------------------------------------
// Interpolator3pt(lo,mi,hi,v1,vm,v2) 
// Map values between lo mid hi to values between v1 vm v2
//--------------------------------------------------------------------------------------
class Interpolator3pt
{

  private:
    
	Interpolator 	fSegment1;
	Interpolator	fSegment2;
	double 			fMid;
    
  public:
    
	Interpolator3pt(double lo, double mi, double hi, double v1, double vm, double v2) :
		fSegment1(lo, mi, v1, vm),
		fSegment2(mi, hi, vm, v2),
		fMid(mi) {}
	double operator()(double x) { return  (x < fMid) ? fSegment1(x) : fSegment2(x); }
};


//--------------------------------------------------------------------------------------
// Abstract ValueConverter class. Converts values between UI and Faust representations
//--------------------------------------------------------------------------------------
class ValueConverter 
{
    
 public:
    
	virtual ~ValueConverter() {}
	virtual double ui2faust(double x) = 0;
	virtual double faust2ui(double x) = 0;
};


//--------------------------------------------------------------------------------------
// Linear conversion between ui and faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter : public ValueConverter
{
    
 private:
    
	Interpolator	fUI2F;
	Interpolator	fF2UI;
    
  public:
    
	LinearValueConverter(double umin, double umax, double fmin, double fmax) :
		fUI2F(umin,umax,fmin,fmax), fF2UI(fmin,fmax,umin,umax)
	{}
    
    LinearValueConverter() :
		fUI2F(0.,0.,0.,0.), fF2UI(0.,0.,0.,0.)
	{}
	virtual double ui2faust(double x) {	return fUI2F(x); }
	virtual double faust2ui(double x) {	return fF2UI(x); }

};


//--------------------------------------------------------------------------------------
// Logarithmic conversion between ui and faust values
//--------------------------------------------------------------------------------------
class LogValueConverter : public LinearValueConverter
{
    
 public:

	LogValueConverter(double umin, double umax, double fmin, double fmax) :
		LinearValueConverter(umin, umax, log(std::max(DBL_MIN,fmin)), log(std::max(DBL_MIN,fmax))) 
	{}

	virtual double ui2faust(double x) 	{ return exp(LinearValueConverter::ui2faust(x)); }
	virtual double faust2ui(double x)	{ return LinearValueConverter::faust2ui(log(std::max(x, DBL_MIN))); }
};


//--------------------------------------------------------------------------------------
// Exponential conversion between ui and faust values
//--------------------------------------------------------------------------------------
class ExpValueConverter : public LinearValueConverter
{
    
 public:

	ExpValueConverter(double umin, double umax, double fmin, double fmax) :
		LinearValueConverter(umin, umax, exp(fmin), exp(fmax)) 
	{}

	virtual double ui2faust(double x) { return log(LinearValueConverter::ui2faust(x)); }
	virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(exp(x)); }
};


//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up curve (curve 0)
//--------------------------------------------------------------------------------------
class AccUpConverter : public ValueConverter
{
    
 private:
    
	Interpolator3pt	fA2F;
	Interpolator3pt	fF2A;

 public:

	AccUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
		fA2F(amin,amid,amax,fmin,fmid,fmax),
		fF2A(fmin,fmid,fmax,amin,amid,amax)
	{}

	virtual double ui2faust(double x)	{ return fA2F(x); }
	virtual double faust2ui(double x)	{ return fF2A(x); }
};


//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down curve (curve 1)
//--------------------------------------------------------------------------------------
class AccDownConverter : public ValueConverter
{
    
 private:
    
	Interpolator3pt	fA2F;
	Interpolator3pt	fF2A;

 public:

	AccDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
		fA2F(amin,amid,amax,fmax,fmid,fmin),
		fF2A(fmin,fmid,fmax,amax,amid,amin)
	{}

	virtual double ui2faust(double x)	{ return fA2F(x); }
	virtual double faust2ui(double x)	{ return fF2A(x); }
};


//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up-Down curve (curve 2)
//--------------------------------------------------------------------------------------
class AccUpDownConverter : public ValueConverter
{
    
 private:
    
	Interpolator3pt	fA2F;
	Interpolator	fF2A;

 public:

	AccUpDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
		fA2F(amin,amid,amax,fmin,fmax,fmin),
		fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotone function 
	{}

	virtual double ui2faust(double x)	{ return fA2F(x); }
	virtual double faust2ui(double x)	{ return fF2A(x); }
};


//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down-Up curve (curve 3)
//--------------------------------------------------------------------------------------
class AccDownUpConverter : public ValueConverter
{
    
 private:
    
	Interpolator3pt	fA2F;
	Interpolator	fF2A;

 public:

	AccDownUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
		fA2F(amin,amid,amax,fmax,fmin,fmax),
		fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotone function 
	{}

	virtual double ui2faust(double x)	{ return fA2F(x); }
	virtual double faust2ui(double x)	{ return fF2A(x); }
};


//--------------------------------------------------------------------------------------
// Association of a zone and a value converter. Useful to implement accelerometers 
// metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class ZoneControl
{
    
  private:
    
	FAUSTFLOAT*			fZone;
	ValueConverter*		fValueConverter;
    
  public:
    
	ZoneControl(FAUSTFLOAT* zone, ValueConverter* valueConverter) : fZone(zone), fValueConverter(valueConverter) {}
    virtual ~ZoneControl() { delete fValueConverter; } // Assuming fValueConverter is not kept elsewhere...
	void update(double v) { *fZone = fValueConverter->ui2faust(v); }
    
    FAUSTFLOAT* getZone() { return fZone; }
    ValueConverter* getConverter() { return fValueConverter; }
};

#endif
