#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv
{
//------------------------------------------------------------------------------------------
// Missing operations. A default implementation is provided for the code to compile. A real implementation has to be
// provided.

interval interval_algebra::Nil()
{
    return interval(0);
}
interval interval_algebra::FixPointUpdate(const interval& x, const interval& y)
{
    return interval(0);
}
interval interval_algebra::Input(const interval& c)
{
    return interval(0);
}
interval interval_algebra::Output(const interval& c, const interval& y)
{
    return interval(0);
}
	/*interval interval_algebra::Button(const interval& name)
{
    return interval(0);
    }*/
	/*interval interval_algebra::Checkbox(const interval& name)
{
    return interval(0);
    }*/

interval interval_algebra::HBargraph(const interval& name, const interval& lo, const interval& hi)
{
    return interval(0);
}
interval interval_algebra::VBargraph(const interval& name, const interval& lo, const interval& hi)
{
    return interval(0);
}
interval interval_algebra::Attach(const interval& x, const interval& y)
{
    return interval(0);
}
interval interval_algebra::Highest(const interval& x)
{
    return interval(0);
}
interval interval_algebra::Lowest(const interval& x)
{
    return interval(0);
}
interval interval_algebra::BitCast(const interval& x)
{
    return interval(0);
}
interval interval_algebra::Select2(const interval& x, const interval& y, const interval& z)
{
    return interval(0);
}
interval interval_algebra::Prefix(const interval& x, const interval& y)
{
    return interval(0);
}
interval interval_algebra::RDTbl(const interval& wtbl, const interval& ri)
{
    return interval(0);
}
interval interval_algebra::WRTbl(const interval& n, const interval& g, const interval& wi, const interval& ws)
{
    return interval(0);
}
interval interval_algebra::Gen(const interval& x)
{
    return interval(0);
}

interval interval_algebra::SoundFile(const interval& label)
{
    return interval(0);
}
interval interval_algebra::SoundFileRate(const interval& sf, const interval& x)
{
    return interval(0);
}
interval interval_algebra::SoundFileLength(const interval& sf, const interval& x)
{
    return interval(0);
}
interval interval_algebra::SoundFileBuffer(const interval& sf, const interval& x, const interval& y, const interval& z)
{
    return interval(0);
}
interval interval_algebra::Waveform(const std::vector<interval>& w)
{
    return interval(0);
}

	/*interval interval_algebra::VSlider(const interval& name, const interval& init, const interval& lo, const interval& hi,
                                   const interval& step)
{
    return interval(0);
    }*/
	/*interval interval_algebra::HSlider(const interval& name, const interval& init, const interval& lo, const interval& hi,
                                   const interval& step)
{
    return interval(0);
    }*/
	/*interval interval_algebra::NumEntry(const interval& name, const interval& init, const interval& lo, const interval& hi,
                                    const interval& step)
{
    return interval(0);
    }*/

	/* interval interval_algebra::IntNum(int x)
{
    return interval(0);
    }*/
	/*interval interval_algebra::Int64Num(int64_t x)
{
    return interval(0);
    }*/
	/*interval interval_algebra::FloatNum(double x)
{
    return interval(0);
    }*/
	/*interval interval_algebra::Label(const std::string& x)
{
    return interval(0);
    }*/

// Foreign functions
interval interval_algebra::ForeignFunction(const std::vector<interval>& ff)
{
    return interval(0);
}
interval interval_algebra::ForeignVar(const interval& type, const interval& name, const interval& file)
{
    return interval(0);
}
interval interval_algebra::ForeignConst(const interval& type, const interval& name, const interval& file)
{
    return interval(0);
}

}  // namespace itv
