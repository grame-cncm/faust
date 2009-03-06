//#include <assert.h>
//#include <math.h>

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <stack>

#include <QApplication>
#include <QCheckBox>
#include <QColormap>
#include <QDial>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLayout>
#include <QMap>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QProgressBar>
#include <QPushButton>
#include <QRadialGradient>
#include <QSlider>
#include <QStyle>
#include <QTabWidget>
#include <QTimer>
#include <QToolTip>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QWidget>
#include <QtGui>

//----------------------------------

// for compatibility
#define minValue minimum
#define maxValue maximum


using namespace std;


//==============================BEGIN QSYNTHKNOB=====================================
//
//   qsynthknob and qsynthDialVokiStyle borrowed from qsynth-0.3.3 by Rui Nuno Capela
//   This widget is based on a design by Thorsten Wilms,
//   implemented by Chris Cannam in Rosegarden,
//   adapted for QSynth by Pedro Lopez-Cabanillas,
//   improved for Qt4 by David Garc�a Garzon.
//

#define DIAL_MIN      (0.25 * M_PI)
#define DIAL_MAX      (1.75 * M_PI)
#define DIAL_RANGE    (DIAL_MAX - DIAL_MIN)

class qsynthDialVokiStyle : public QCommonStyle
{
public:
	qsynthDialVokiStyle() {};
	virtual ~qsynthDialVokiStyle() {};
	
    virtual void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *widget = 0) const
	{
		if (cc != QStyle::CC_Dial)
		{
			QCommonStyle::drawComplexControl(cc, opt, p, widget);
			return;
		}
		
		const QStyleOptionSlider *dial = qstyleoption_cast<const QStyleOptionSlider *>(opt); 
		if (dial == NULL)
			return;
		
		double angle = DIAL_MIN // offset
			+ (DIAL_RANGE *
				(double(dial->sliderValue - dial->minimum) /
				(double(dial->maximum - dial->minimum))));
		int degrees = int(angle * 180.0 / M_PI);
		int side = dial->rect.width() < dial->rect.height() ? dial->rect.width() : dial->rect.height();
		int xcenter = dial->rect.width() / 2;
		int ycenter = dial->rect.height() / 2;
		int notchWidth   = 1 + side / 400;
		int pointerWidth = 2 + side / 30;
		int scaleShadowWidth = 1 + side / 100;
		int knobBorderWidth = 0;
		int ns = dial->tickInterval;
		int numTicks = 1 + (dial->maximum + ns - dial->minimum) / ns;
		int indent = int(0.15 * side) + 2;
		int knobWidth = side - 2 * indent;
		int shineFocus = knobWidth / 4;
		int shineCenter = knobWidth / 5;
		int shineExtension = shineCenter * 4;
		int shadowShift = shineCenter * 2;
		int meterWidth = side - 2 * scaleShadowWidth;
		
		QPalette pal = opt->palette;
		QColor knobColor = pal.mid().color();
		QColor borderColor = knobColor.light();
		QColor meterColor = (dial->state & State_Enabled) ? 
                            QColor("orange") : pal.mid().color();   
                         // pal.highlight().color() : pal.mid().color();
		QColor background = pal.window().color();

		p->save();
		p->setRenderHint(QPainter::Antialiasing, true);

		// The bright metering bit...

		QConicalGradient meterShadow(xcenter, ycenter, -90);
		meterShadow.setColorAt(0, meterColor.dark());
		meterShadow.setColorAt(0.5, meterColor);
		meterShadow.setColorAt(1.0, meterColor.light().light());
		p->setBrush(meterShadow);
		p->setPen(Qt::transparent);
		p->drawPie(xcenter - meterWidth / 2, ycenter - meterWidth / 2,
			meterWidth, meterWidth, (180 + 45) * 16, -(degrees - 45) * 16);

		// Knob projected shadow
		QRadialGradient projectionGradient(
			xcenter + shineCenter, ycenter + shineCenter,
			shineExtension,	xcenter + shadowShift, ycenter + shadowShift);
		projectionGradient.setColorAt(0, QColor(  0, 0, 0, 100));
		projectionGradient.setColorAt(1, QColor(200, 0, 0,  10));
		QBrush shadowBrush(projectionGradient);
		p->setBrush(shadowBrush);
		p->drawEllipse(xcenter - shadowShift, ycenter - shadowShift,
			knobWidth, knobWidth);

		// Knob body and face...

		QPen pen;
		pen.setColor(knobColor);
		pen.setWidth(knobBorderWidth);
		p->setPen(pen);

		QRadialGradient gradient(
			xcenter - shineCenter, ycenter - shineCenter,
			shineExtension,	xcenter - shineFocus, ycenter - shineFocus);
		gradient.setColorAt(0.2, knobColor.light().light());
		gradient.setColorAt(0.5, knobColor);
		gradient.setColorAt(1.0, knobColor.dark(150));
		QBrush knobBrush(gradient);
		p->setBrush(knobBrush);
		p->drawEllipse(xcenter - knobWidth / 2, ycenter - knobWidth / 2,
			knobWidth, knobWidth);

		// Tick notches...

		p->setBrush(Qt::NoBrush);

		if (dial->subControls & QStyle::SC_DialTickmarks)
		{
			pen.setColor(pal.dark().color());
			pen.setWidth(notchWidth);
			p->setPen(pen);
			double hyp = double(side - scaleShadowWidth) / 2.0;
			double len = hyp / 4;
			for (int i = 0; i < numTicks; ++i) {
				int div = numTicks;
				if (div > 1) --div;
				bool internal = (i != 0 && i != numTicks - 1);
				double angle = DIAL_MIN
					+ (DIAL_MAX - DIAL_MIN) * i / div;
				double dir = (internal ? -1 : len);
				double sinAngle = sin(angle);
				double cosAngle = cos(angle);
				double x0 = xcenter - (hyp - len) * sinAngle;
				double y0 = ycenter + (hyp - len) * cosAngle;
				double x1 = xcenter - (hyp + dir) * sinAngle;
				double y1 = ycenter + (hyp + dir) * cosAngle;
				p->drawLine(QLineF(x0, y0, x1, y1));
			}
		}

		// Shadowing...

		// Knob shadow...
		if (knobBorderWidth > 0) {
			QLinearGradient inShadow(xcenter - side / 4, ycenter - side / 4,
				xcenter + side / 4, ycenter + side / 4);
			inShadow.setColorAt(0.0, borderColor.light());
			inShadow.setColorAt(1.0, borderColor.dark());
			p->setPen(QPen(QBrush(inShadow), knobBorderWidth * 7 / 8));
			p->drawEllipse(xcenter - side / 2 + indent,
				ycenter - side / 2 + indent,
				side - 2 * indent, side - 2 * indent);
		}

		// Scale shadow...
		QLinearGradient outShadow(xcenter - side / 3, ycenter - side / 3,
			xcenter + side / 3, ycenter + side / 3);
		outShadow.setColorAt(0.0, background.dark().dark());
		outShadow.setColorAt(1.0, background.light().light());
		p->setPen(QPen(QBrush(outShadow), scaleShadowWidth));
		p->drawArc(xcenter - side / 2 + scaleShadowWidth / 2,
			ycenter - side / 2 + scaleShadowWidth / 2,
			side - scaleShadowWidth, side - scaleShadowWidth, -45 * 16, 270 * 16);

		// Pointer notch...

		double hyp = double(side) / 2.0;
		double len = hyp - indent - 1;

		double x = xcenter - len * sin(angle);
		double y = ycenter + len * cos(angle);

		QColor pointerColor = pal.dark().color();
		pen.setColor((dial->state & State_Enabled) ? pointerColor.dark(140) : pointerColor);
		pen.setWidth(pointerWidth + 2);
		p->setPen(pen);
		p->drawLine(QLineF(xcenter, ycenter, x, y));
		pen.setColor((dial->state & State_Enabled) ? pointerColor.light() : pointerColor.light(140));
		pen.setWidth(pointerWidth);
		p->setPen(pen);
		p->drawLine(QLineF(xcenter - 1, ycenter - 1, x - 1, y - 1));
		
		// done
		p->restore();
	}
	
};
//
//===============================END QSYNTHKNOB======================================


//==============================BEGIN DISPLAYS===================================
//
// This section constains displays, passive QT widgets that displays values in
// different ways, in particular bargraphs
//

/**
 * An abstract widget that display a value in a range
 */
class AbstractDisplay : public QWidget
{
    protected :
        float           fMin;
        float           fMax;
        float           fValue;

    public:

        AbstractDisplay (float lo, float hi) : fMin(lo), fMax(hi), fValue(lo)
        {
        }

        /**
         * set the range of displayed values
         */
        virtual void setRange(float lo, float hi)
        {
            fMin = lo;
            fMax = hi;
        }

        /**
         * set the value to be displayed
         */
        virtual void setValue(float v)
        {
            if (v < fMin)       v = fMin;
            else if (v > fMax)  v = fMax;
            
            if (v != fValue) {
                fValue = v;
                update();
            }
        }
};


/**
 * Displays dB values using a scale of colors
 */
class dbAbstractDisplay : public AbstractDisplay
{
    protected :
    
        float           fScaleMin;
        float           fScaleMax;
        vector<int>     fLevel;
        vector<QBrush>  fBrush;


        /**
        * Convert a dB value into a scale between 0 and 1 (following IEC standard ?)
        */
        float dB2Scale ( float dB ) const
        {
            float fScale = 1.0f;

            /*if (dB < -70.0f)
                fScale = 0.0f;
            else*/ if (dB < -60.0f)
                fScale = (dB + 70.0f) * 0.0025f;
            else if (dB < -50.0f)
                fScale = (dB + 60.0f) * 0.005f + 0.025f;
            else if (dB < -40.0)
                fScale = (dB + 50.0f) * 0.0075f + 0.075f;
            else if (dB < -30.0f)
                fScale = (dB + 40.0f) * 0.015f + 0.15f;
            else if (dB < -20.0f)
                fScale = (dB + 30.0f) * 0.02f + 0.3f;
            else if (dB < -0.001f || dB > 0.001f)  /* if (dB < 0.0f) */
                fScale = (dB + 20.0f) * 0.025f + 0.5f;

            return fScale;
        }


        /**
         * Create the scale of colors used to paint the bargraph in relation to the levels
         * The parameter x indicates the direction of the gradient. x=1 means an horizontal
         * gradient typically used by a vertical bargraph, and x=0 a vertical gradient.
         */
        void initLevelsColors(int x)
        {
            int alpha = 200;
            { // level until -10 dB
                QColor c(40, 160, 40, alpha);
                QLinearGradient g(0,0,x,1-x);
                g.setCoordinateMode(QGradient::ObjectBoundingMode);
                g.setColorAt(0.0,   c.lighter());
                g.setColorAt(0.2,   c);
                g.setColorAt(0.8,   c);
                g.setColorAt(0.9,   c.darker(120));

                fLevel.push_back(-10);
                fBrush.push_back(QBrush(g));
            }
            
            { // level until -6 dB
                QColor c(160, 220, 20, alpha);
                QLinearGradient g(0,0,x,1-x);
                g.setCoordinateMode(QGradient::ObjectBoundingMode);
                g.setColorAt(0.0,   c.lighter());
                g.setColorAt(0.2,   c);
                g.setColorAt(0.8,   c);
                g.setColorAt(0.9,   c.darker(120));

                fLevel.push_back(-6);
                fBrush.push_back(QBrush(g));
            }

            { // level until -3 dB
                QColor c(220, 220, 20, alpha);
                QLinearGradient g(0,0,x,1-x);
                g.setCoordinateMode(QGradient::ObjectBoundingMode);
                g.setColorAt(0.0,   c.lighter());
                g.setColorAt(0.2,   c);
                g.setColorAt(0.8,   c);
                g.setColorAt(0.9,   c.darker(120));

                fLevel.push_back(-3);
                fBrush.push_back(QBrush(g));
            }

            { // level until -0 dB
                QColor c(240, 160, 20, alpha);
                QLinearGradient g(0,0,x,1-x);
                g.setCoordinateMode(QGradient::ObjectBoundingMode);
                g.setColorAt(0.0,   c.lighter());
                g.setColorAt(0.2,   c);
                g.setColorAt(0.8,   c);
                g.setColorAt(0.9,   c.darker(120));

                fLevel.push_back(0);
                fBrush.push_back(QBrush(g));
            }

            { // until 10 dB (and over because last one)
                QColor c(240,  0, 20, alpha);   // ColorOver
                QLinearGradient g(0,0,x,1-x);
                g.setCoordinateMode(QGradient::ObjectBoundingMode);
                g.setColorAt(0.0,   c.lighter());
                g.setColorAt(0.2,   c);
                g.setColorAt(0.8,   c);
                g.setColorAt(0.9,   c.darker(120));

                fLevel.push_back(+10);
                fBrush.push_back(QBrush(g));
            }

        }

    public:

        dbAbstractDisplay(float lo, float hi) : AbstractDisplay(lo,hi)
        {
        }

        /**
         * set the range of displayed values
         */
        virtual void setRange(float lo, float hi)
        {
            AbstractDisplay::setRange(lo, hi);
            fScaleMin = dB2Scale(fMin);
            fScaleMax = dB2Scale(fMax);
        }
};


/**
 * Small rectangular LED display which color changes with the level in dB
 */
class dbLED : public dbAbstractDisplay
{
    protected:
         
        /**
         * Draw the LED using a color depending of its value in dB
         */
        virtual void paintEvent ( QPaintEvent *)
        {
            QPainter painter(this);
            painter.drawRect(rect());

            if (fValue <= fLevel[0]) {
            
                // interpolate the first color on the alpha channel
                QColor c(40, 160, 40) ;
                float a = (fValue-fMin)/(fLevel[0]-fMin);
                c.setAlphaF(a);
                painter.fillRect(rect(), c);
                
            } else {
                    
                // find the minimal level > value
                int l = fLevel.size()-1; while (fValue < fLevel[l] && l > 0) l--;
                painter.fillRect(rect(), fBrush[l]);
            }
        }

    public:

        dbLED(float lo, float hi) : dbAbstractDisplay(lo,hi)
        {
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            initLevelsColors(1);
       }

        virtual QSize sizeHint () const
        {
            return QSize(16, 8);
        }
};
/**
 * Small rectangular LED display which intensity (alpha channel) changes according to the value
 */
class LED : public AbstractDisplay
{
    QColor  fColor;
    
    protected:
         
        /**
         * Draw the LED using a transparency depending of its value
         */
        virtual void paintEvent ( QPaintEvent *)
        {
            QPainter painter(this);
            painter.drawRect(rect());
            // interpolate the first color on the alpha channel
            QColor c = fColor ;
            float a = (fValue-fMin)/(fMax-fMin);
            c.setAlphaF(a);
            painter.fillRect(rect(), c);
        }

    public:

        LED(float lo, float hi) : AbstractDisplay(lo,hi), fColor("yellow")
        {
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
       }

        virtual QSize sizeHint () const
        {
            return QSize(16, 8);
        }
};



/**
 * A simple bargraph that detect automatically its direction
 */
class linBargraph : public AbstractDisplay
{
    protected :
        QBrush  fBrush;
        
        /**
         * No scale implemented yet
         */
        void paintScale(QPainter* painter) const
        {
            painter->drawRect(0,0,width(),height());
        }
              
        /**
         * The length of the rectangle is proportional to the value
         */
        void paintContent (QPainter* painter) const
        {
            int     w = width();
            int     h = height();
            float   v = (fValue-fMin)/(fMax-fMin);
                
            if (h>w) {
                // draw vertical rectangle
                painter->fillRect(0,(1-v)*h,w, v*h, fBrush);
            } else {
                // draw horizontal rectangle
                painter->fillRect(0, 0, h, v*w, fBrush);
            }
                
        }
              
        virtual void paintEvent ( QPaintEvent *)
        {
            QPainter painter(this);
            paintContent(&painter);
            paintScale(&painter);
        }

    public:

        linBargraph(float lo, float hi) : AbstractDisplay(lo,hi)
        {
            // compute the brush that will be used to
            // paint the value
            QColor c(0xffa500);                 // orange
            int x = int(height() < width());    // gradient direction
            QLinearGradient g(0,0,x,1-x);
            g.setCoordinateMode(QGradient::ObjectBoundingMode);
            g.setColorAt(0.0,   c.lighter());
            g.setColorAt(0.2,   c);
            g.setColorAt(0.8,   c);
            g.setColorAt(0.9,   c.darker(120));
            fBrush = QBrush(g);
        }
};


/**
 * A simple vertical bargraph
 */
class linVerticalBargraph : public linBargraph
{
    public:

        linVerticalBargraph(float lo, float hi) : linBargraph(lo,hi)
        {
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        }

        virtual QSize sizeHint () const
        {
            return QSize(16, 128);
        }
};



/**
 * A simple horizontal bargraph
 */
class linHorizontalBargraph : public linBargraph
{
    public:

        linHorizontalBargraph(float lo, float hi) : linBargraph(lo,hi)
        {
            setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        }

        virtual QSize sizeHint () const
        {
            return QSize(128, 16);
        }
};




/**
 * A dB Bargraph with a scale of colors
 */
class dbBargraph : public dbAbstractDisplay
{
    QBrush  fBackColor;
    
    protected :

        // These two abstract methods are implemented
        // according to the vertical or horizontal direction
        // in dbVerticalBargraph and dbHorizontalBargraph
        virtual void paintMark(QPainter* painter, float v) const = 0;
        virtual int paintSegment (QPainter* painter, int pos, float v, const QBrush& b) const = 0;
        
        /**
         * Draw the logarithmic scale
         */
        void paintScale(QPainter* painter) const
        {
            painter->fillRect(0,0,width(),height(), fBackColor);
            painter->save();
            painter->setPen(QColor(0x6699aa)); //0xffa500));
            for (float v = -10; v > fMin; v -= 10) paintMark(painter, v);
            for (float v = -6; v < fMax; v += 3) paintMark(painter, v);
            painter->restore();
        }
        
        
        /**
         * Draw the content using colored segments
         */
        void paintContent (QPainter* painter) const
        {
            int   l = fLevel.size();

            float   p = -1;   // fake value indicates to start from border
            int     n = 0;
            // paint all the full segments < fValue
            for (n=0; (n < l) && (fValue > fLevel[n]); n++) {
                p = paintSegment(painter, p, fLevel[n], fBrush[n]);
            }
            // paint the last segment
            if (n == l) n = n-1;
            p=paintSegment(painter, p, fValue, fBrush[n]);

            painter->drawRect(0,0,width(),height());
       }
        

        virtual void paintEvent ( QPaintEvent *)
        {
            QPainter painter(this);
            paintScale(&painter);
            paintContent(&painter);
        }

    public:

        dbBargraph(float lo, float hi) : dbAbstractDisplay(lo,hi)
        {
        
            QFont f = this->font();
            f.setPointSize(6);
            this->setFont(f);

            fBackColor = QBrush(QColor(20,20,20));
        }
};


/**
 * Vertical dB Bargraph
 */
class dbVerticalBargraph : public dbBargraph
{
    protected:
        /**
         * Convert a dB value into a vertical position
         */
        float dB2y (float dB) const
        {
            float s0 = fScaleMin;
            float s1 = fScaleMax;
            float sx = dB2Scale(dB);
            int    h = height();

            return h - h*(s0-sx)/(s0-s1);
        }

        /**
         * Paint a vertical graduation mark
         */
        virtual void paintMark(QPainter* painter, float v) const
        {
            int n = 10;
            int y = dB2y(v);
            QRect r(0,y-n,width()-1,2*n);
            if (v > 0.0) {
                painter->drawText(r, Qt::AlignRight|Qt::AlignVCenter, QString::number(v).prepend('+'));
            } else {
                painter->drawText(r, Qt::AlignRight|Qt::AlignVCenter, QString::number(v));
            }
        }
        
        /**
         * Paint a color segment
         */
        virtual int paintSegment (QPainter* painter, int pos, float v, const QBrush& b) const
        {
            if (pos == -1) pos = height();
            float y = dB2y(v);
            painter->fillRect(0, y, width(), pos-y, b);
            return y;
        }


    public:

        dbVerticalBargraph(float lo, float hi) : dbBargraph(lo,hi)
        {
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
            initLevelsColors(1);
        }

        virtual QSize sizeHint () const
        {
            return QSize(18, 256);
        }
};

/**
 * Horizontal dB Bargraph
 */
class dbHorizontalBargraph : public dbBargraph
{

    protected:

        /**
         * Convert a dB value into an horizontal position
         */
        float dB2x (float dB) const
        {
            float s0 = fScaleMin;
            float s1 = fScaleMax;
            float sx = dB2Scale(dB);
            int    w = width();

            return w - w*(s1-sx)/(s1-s0);
        }
    
        /**
         * Paint an horizontal graduation mark
         */
        void paintMark(QPainter* painter, float v) const
        {
            int n = 10;
            int x = dB2x(v);
            QRect r(x-n,0,2*n, height());
            painter->drawText(r, Qt::AlignHCenter|Qt::AlignVCenter, QString::number(v));
        }
            
        /**
         * Paint a horizontal color segment
         */
        int paintSegment (QPainter* painter, int pos, float v, const QBrush& b) const
        {
            if (pos == -1) pos = 0;
            float x = dB2x(v);
            painter->fillRect(pos, 0, x-pos, height(), b);
            return x;
        }


    public:

        dbHorizontalBargraph(float lo, float hi) : dbBargraph(lo,hi)
        {
            setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
            initLevelsColors(0);
        }

        virtual QSize sizeHint () const
        {
            return QSize(256, 18);
        }

};

//
//===============================END DISPLAYS====================================

//============================= BEGIN GROUP LABEL METADATA===========================
// Unlike widget's label, metadata inside group's label are not extracted directly by
// the Faust compiler. Therefore they must be extracted within the architecture file
//-----------------------------------------------------------------------------------
//

/**
 * rmWhiteSpaces(): Remove the leading and trailing white spaces of a string
 * (but not those in the middle of the string)
 */
static string rmWhiteSpaces(const string& s)
{
    unsigned int i = s.find_first_not_of(" \t");
    unsigned int j = s.find_last_not_of(" \t");

	if ( (i != string::npos) & (j != string::npos) ) {
		return s.substr(i, 1+j-i);
	} else {
		return "";
	}
}

/**
 * Extracts metdata from a label : 'vol [unit: dB]' -> 'vol' + metadata(unit=dB)
 */
static void extractMetadata(const string& fulllabel, string& label, map<string, string>& metadata)
{
    enum {kLabel, kEscape1, kEscape2, kEscape3, kKey, kValue};
    int state = kLabel; int deep = 0;
    string key, value;

    for (unsigned int i=0; i < fulllabel.size(); i++) {
        char c = fulllabel[i];
        switch (state) {
            case kLabel :
                assert (deep == 0);
                switch (c) {
                    case '\\' : state = kEscape1; break;
                    case '[' : state = kKey; deep++; break;
                    default : label += c;
                }
                break;

            case kEscape1 :
                label += c;
                state = kLabel;
                break;

            case kEscape2 :
                key += c;
                state = kKey;
                break;

            case kEscape3 :
                value += c;
                state = kValue;
                break;

            case kKey :
                assert (deep > 0);
                switch (c) {
                    case '\\' :  state = kEscape2;
                                break;

                    case '[' :  deep++;
                                key += c;
                                break;

                    case ':' :  if (deep == 1) {
                                    state = kValue;
                                } else {
                                    key += c;
                                }
                                break;
                    case ']' :  deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = "";
                                    state = kLabel;
                                    key="";
                                    value="";
                                } else {
                                    key += c;
                                }
                                break;
                    default :   key += c;
                }
                break;

            case kValue :
                assert (deep > 0);
                switch (c) {
                    case '\\' : state = kEscape3;
                                break;

                    case '[' :  deep++;
                                value += c;
                                break;

                    case ']' :  deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)]=rmWhiteSpaces(value);
                                    state = kLabel;
                                    key="";
                                    value="";
                                } else {
                                    value += c;
                                }
                                break;
                    default :   value += c;
                }
                break;

            default :
                cerr << "ERROR unrecognized state " << state << endl;
        }
    }
    label = rmWhiteSpaces(label);
}
//
//============================= END GROUP LABEL METADATA===========================



/******************************************************************************
*******************************************************************************

							  ABSTRACT DEFINITIONS
							   (QT 4.3 for FAUST)

*******************************************************************************
*******************************************************************************/

struct uiItem;
typedef void (*uiCallback)(float val, void* data);

/**
 * Graphic User Interface : abstract definition
 */

class UI : public QObject
{
	typedef list<uiItem*> clist;
	typedef map<float*, clist*> zmap;
	
 private:
 	static list<UI*>	fGuiList;
	zmap				fZoneMap;
	bool				fStopped;
	
 public:
		
	UI() : fStopped(false) {	
		fGuiList.push_back(this);
	}
	
	virtual ~UI() {
		// suppression de this dans fGuiList
	}

	// -- registerZone(z,c) : zone management
	
	void registerZone(float* z, uiItem* c)
	{
		if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
		fZoneMap[z]->push_back(c);
	} 	

	// -- saveState(filename) : save the value of every zone to a file
	
	void saveState(const char* filename)	
	{
		ofstream f(filename);
		
		for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++) { 
			f << *(i->first) << ' ';
		} 
		
		f << endl;
		f.close();
	}

	// -- recallState(filename) : load the value of every zone from a file
	
	void recallState(const char* filename)	
	{
		ifstream f(filename);
		if (f.good()) {
			for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++) { 
				f >> *(i->first);
			} 
		}
		f.close();
	}
	
	void updateAllZones();
	
	void updateZone(float* z);
	
	static void updateAllGuis()
	{
		list<UI*>::iterator g;
		for (g = fGuiList.begin(); g != fGuiList.end(); g++) {
			(*g)->updateAllZones();
		}
	}
	
	
	// debut remplacement '= 0;' par '{}'
	// -- active widgets
	
	virtual void addButton(const char*, float*) = 0;
	virtual void addCheckButton(const char*, float*) = 0;
	virtual void addVerticalSlider(const char*, float*, float, float, float, float) = 0;
	virtual void addHorizontalSlider(const char*, float*, float, float, float, float) = 0;
	virtual void addNumEntry(const char*, float*, float, float, float, float) = 0;
	
	// -- passive widgets
	
	virtual void addHorizontalBargraph(const char*, float*, float, float) = 0;
	virtual void addVerticalBargraph(const char*, float*, float, float) = 0;
	
	// -- widget's layouts
	
	virtual void openTabBox(const char*) = 0;
	virtual void openHorizontalBox(const char*) = 0;
	virtual void openVerticalBox(const char*) = 0;
	virtual void closeBox() = 0;
	
	virtual void run() = 0;
	
	// fin remplacement

	void stop()		{ fStopped = true; }
	bool stopped() 	{ return fStopped; }

    virtual void declare(float*, const char*, const char*) {}
};


/**
 * A User Interface Item that can reflect and modify a floating point zone
 */

class uiItem : public QObject
{
  protected :
		  
	UI*			fGUI;
	float*		fZone;
	float		fCache;
	
	uiItem (UI* ui, float* zone) : fGUI(ui), fZone(zone), fCache(-123456.654321) 
	{ 
		ui->registerZone(zone, this); 
	}
	
	
  public :
	
	void modifyZone(float v) 	
	{ 
		fCache = v;
		if (*fZone != v) {
			*fZone = v;
			fGUI->updateZone(fZone);
		}
	}
		  	
	float			cache()			{ return fCache; }
	virtual void 	reflectZone() 	= 0;	
};


/**
 * Update all user items reflecting zone z
 */

inline void UI::updateZone(float* z)
{
	float 	v = *z;
	clist* 	l = fZoneMap[z];
	for (clist::iterator c = l->begin(); c != l->end(); c++) {
		if ((*c)->cache() != v) (*c)->reflectZone();
	}
}


/**
 * Update all user items not up to date
 */

inline void UI::updateAllZones()
{
	for (zmap::iterator m = fZoneMap.begin(); m != fZoneMap.end(); m++) {
		float* 	z = m->first;
		clist*	l = m->second;
		float	v = *z;
		for (clist::iterator c = l->begin(); c != l->end(); c++) {
			if ((*c)->cache() != v) (*c)->reflectZone();
		}
	}
}



/******************************************************************************
*******************************************************************************

							IMPLEMENTATION OF UI ITEMS
							   (QT 4.3 for FAUST)

*******************************************************************************
*******************************************************************************/


class uiButton : public uiItem
{
    Q_OBJECT
			
 public :
	QAbstractButton* 	fButton;
	
	uiButton (UI* ui, float* zone, QAbstractButton* b) : uiItem(ui, zone), fButton(b) {}
	

	virtual void reflectZone() 	
	{ 
		float v = *fZone;
		fCache = v; 
		fButton->setDown( v > 0.0 );
	}
	
 public slots :
	void pressed()		{ modifyZone(1.0); }	 
	void released()		{ modifyZone(0.0); }
};


class uiCheckButton : public uiItem
{
    Q_OBJECT
			
 public :
	QCheckBox* 	fCheckBox;
	
	uiCheckButton (UI* ui, float* zone, QCheckBox* b) : uiItem(ui, zone), fCheckBox(b) {}
	
	virtual void reflectZone() 	
	{ 
		float v = *fZone;
		fCache = v; 
		fCheckBox->setCheckState( (v < 0.5) ? Qt::Unchecked : Qt::Checked );
	}
	
 public slots :
	void setState(int v)		{ modifyZone(float(v>0)); }	 
};


class uiSlider : public uiItem
{
    Q_OBJECT

	int		faust2qt(float x) 	{ return int(0.5 + (x-fMin)/fStep); }
	float	qt2faust (int v)	{ return fMin + v*fStep; }
	int		optimalTick()		{ 
				float x=fStep; 
				while((fMax-fMin)/x > 50) x*=10; 
				while((fMax-fMin)/x < 10) x/=2; 
				return faust2qt(fMin+x); 
			}
			
 public :
	QSlider* 	fSlider;
	float		fCur;
	float		fMin;
	float		fMax;
	float		fStep;

	uiSlider (UI* ui, float* zone, QSlider* slider, float cur, float lo, float hi, float step) 
		: uiItem(ui, zone), fSlider(slider), fCur(cur), fMin(lo), fMax(hi), fStep(step) 
	{
		fSlider->setMinimum(0);
		fSlider->setMaximum(faust2qt(fMax)); 
		fSlider->setValue(faust2qt(fCur));
		fSlider->setTickInterval(optimalTick());
		*fZone = fCur;
	}
	
	virtual void reflectZone() 	
	{ 
		float 	v = *fZone;
		fCache = v; 
		fSlider->setValue(faust2qt(v));
	}
	
 public slots :
	void setValue(int v)		{ modifyZone(qt2faust(v)); }	 
};


class uiKnob : public uiItem
{
    Q_OBJECT

	int		faust2qt(float x) 	{ return int(0.5 + (x-fMin)/fStep); }
	float	qt2faust (int v)	{ return fMin + v*fStep; }
	int		optimalTick()		{ 
				float x=fStep; 
				while((fMax-fMin)/x > 50) x*=10; 
				while((fMax-fMin)/x < 10) x/=2; 
				return faust2qt(fMin+x); 
			}
			
 public :
	QAbstractSlider* 	fSlider;
	float				fCur;
	float				fMin;
	float				fMax;
	float				fStep;

	uiKnob (UI* ui, float* zone, QAbstractSlider* slider, float cur, float lo, float hi, float step) 
		: uiItem(ui, zone), fSlider(slider), fCur(cur), fMin(lo), fMax(hi), fStep(step) 
	{
		fSlider->setMinimum(0);
		fSlider->setMaximum(faust2qt(fMax)); 
		fSlider->setValue(faust2qt(fCur));
		//fSlider->setTickInterval(optimalTick());
		*fZone = fCur;
	}
	
	virtual void reflectZone() 	
	{ 
		float 	v = *fZone;
		fCache = v; 
		fSlider->setValue(faust2qt(v));
	}
	
 public slots :
	void setValue(int v)		{ modifyZone(qt2faust(v)); }	 
};


class uiBargraph : public uiItem
{
    Q_OBJECT

    int     faust2qt(float x)   { return int(0.5 + (x-fMin)/(fMax-fMin)*fStep); }
            
 public :
    QProgressBar*   fBar;
    float           fMin;
    float           fMax;
    int             fStep;

    uiBargraph (UI* ui, float* zone, QProgressBar* bar, float lo, float hi) 
        : uiItem(ui, zone), fBar(bar), fMin(lo), fMax(hi), fStep(1024) 
    {
        fBar->setRange(0, fStep);
        fBar->setValue(0);
        *fZone = 0;
    }
    
    virtual void reflectZone()  
    { 
        float   v = *fZone;
        fCache = v;
        int x = faust2qt(v);
        //std::cout << "update *" << fBar << " = " << x << std::endl;
        fBar->setValue(x);
    }
};


class uiBargraph2 : public uiItem
{
    Q_OBJECT
            
 public :
    AbstractDisplay*   fBar;

    uiBargraph2 (UI* ui, float* zone, AbstractDisplay* bar, float lo, float hi)
        : uiItem(ui, zone), fBar(bar)
    {
        fBar->setRange(lo, hi);
        fBar->setValue(lo);
        *fZone = lo;
    }
    
    virtual void reflectZone()  
    { 
        float   v = *fZone;
        fCache = v;
        fBar->setValue(v);
    }
};



class uiNumEntry : public uiItem
{
    Q_OBJECT

 public :
	QDoubleSpinBox* 	fNumEntry;
	float				fCur;
	float				fMin;
	float				fMax;
	float				fStep;
	int					fDecimals;

	uiNumEntry (UI* ui, float* zone, QDoubleSpinBox* numEntry, float cur, float lo, float hi, float step) 
		: uiItem(ui, zone), fNumEntry(numEntry), fCur(cur), fMin(lo), fMax(hi), fStep(step) 
	{
		fDecimals = (fStep >= 1.0) ? 0 : int(0.5+log10(1.0/fStep));

		fNumEntry->setMinimum(fMin);
		fNumEntry->setMaximum(fMax); 
		fNumEntry->setSingleStep(fStep);
		fNumEntry->setDecimals(fDecimals);
		fNumEntry->setValue(fCur);
		*fZone = fCur;
	}
	

	virtual void reflectZone() 	
	{ 
		float 	v = *fZone;
		fCache = v; 
		fNumEntry->setValue(v);
	}
	
 public slots :
	void setValue(double v)		{ 
		modifyZone(float(v)); 
	}	 
};




/******************************************************************************
*******************************************************************************

						IMPLEMENTATION OF THE USER INTERFACE
							   (QT 4.3 for FAUST)

*******************************************************************************
*******************************************************************************/


class QTGUI : public UI
{
    Q_OBJECT
	QApplication		fAppl;
	QTimer*				fTimer;
	QStyle*			 	fStyle;
	stack<QWidget* > 	fGroupStack;

    static map<float*, float>           fGuiSize;       // map widget zone with widget size coef
    static map<float*, string>          fTooltip;       // map widget zone with tooltip strings
    static map<float*, string>          fUnit;          // map widget zone to unit string (i.e. "dB")
    static set<float*>                  fKnobSet;       // set of widget zone to be knobs
    static set<float*>                  fLedSet;        // set of widget zone to be LEDs


    /**
    * Analyses the widget zone metadata declarations and takes
    * appropriate actions
    */
    virtual void declare(float* zone, const char* key, const char* value)
    {
        if (strcmp(key,"size")==0) {
            fGuiSize[zone]=atof(value);
        }
        else if (strcmp(key,"tooltip")==0) {
            fTooltip[zone] = value ;
        }
        else if (strcmp(key,"unit")==0) {
            fUnit[zone] = value ;
        }
        else if (strcmp(key,"style")==0) {
            if (strcmp(value,"knob") == 0) {
				fKnobSet.insert(zone);
			} else if (strcmp(value,"led") == 0) {
                fLedSet.insert(zone);
            }
        }
    }

	bool isTabContext()
	{
		return fGroupStack.empty() || ((!fGroupStack.empty()) && (dynamic_cast<QTabWidget*>(fGroupStack.top()) != 0));
	}

	void insert(const char* label, QWidget* widget)
	{
		if (fStyle) widget->setStyle(fStyle);
		if (!fGroupStack.empty()) {
			QWidget* mother = fGroupStack.top();
			QTabWidget*	tab = dynamic_cast<QTabWidget*>(mother);
			if (tab) {
				tab->addTab(widget,label);
			} else {
				widget->setParent(mother);
				mother->layout()->addWidget(widget);
			}
		}
	}

    /**
    * Analyses a full label and activates the relevant options. returns a simplified
    * label (without options) and an amount of stack adjustement (in case additional
    * containers were pushed on the stack).
    */

    int checkLabelOptions(QWidget* widget, const string& fullLabel, string& simplifiedLabel)
    {   
        map<string, string> metadata;
        extractMetadata(fullLabel, simplifiedLabel, metadata);

        if (metadata.count("tooltip")) {
            widget->setToolTip(metadata["tooltip"].c_str());
        }
        if (metadata["option"] == "detachable") {
            //openHandleBox(simplifiedLabel.c_str());
            return 1;
        }

        // no adjustement of the stack needed
        return 0;
    }

    /**
    * Check if a tooltip is associated to a zone and add it to the corresponding widget
    */
    void checkForTooltip(float* zone, QWidget* widget)
    {
        if (fTooltip.count(zone)) {
            widget->setToolTip(fTooltip[zone].c_str());
        }
    }


    /**
    * Check if a knob is required
    */
    bool isKnob(float* zone)
    {
        return fKnobSet.count(zone) > 0;
    }


	void openBox(const char* fulllabel, QLayout* layout)
	{
        map<string, string> metadata;
        string label;
        extractMetadata(fulllabel, label, metadata);

		layout->setMargin(5);
		QWidget* box;
		if (isTabContext()) {
			box = new QWidget();
            // set background color
            QPalette pal = box->palette();
            pal.setColor(box->backgroundRole(), QColor::fromRgb(150, 150, 150) );
            box->setPalette(pal);

		} else  if (label.size()>0) {
			QGroupBox* group = new QGroupBox();
			group->setTitle(label.c_str());
			box = group;
		} else {
			// no label here we use simple widget
			layout->setMargin(0);
			box = new QWidget();
		}
		box->setLayout(layout);

        if (metadata.count("tooltip")) {
            box->setToolTip(metadata["tooltip"].c_str());
        }

		insert(label.c_str(), box);
		fGroupStack.push(box);
	}

	void openTab(const char* label) 
	{
		QTabWidget* group = new QTabWidget();
		if (fStyle) group->setStyle(fStyle);
		insert(label, group);
		fGroupStack.push(group);
	}

	
  public slots :
	void update()		{
        //std::cout << '.' << std::endl;
		updateAllZones();
	}	 

  public:

	QTGUI(int argc, char* argv[], QStyle* style = 0) : fAppl(argc, argv), fTimer(0), fStyle(style){
        //fGroupStack.push(new QMainWindow());
    }
	
	virtual ~QTGUI() {}

	virtual void run()
	{
		if (fTimer == 0) {
			fTimer = new QTimer(this);
     		QObject::connect(fTimer, SIGNAL(timeout()), this, SLOT(update()));
     		fTimer->start(100);
		}
#if 1
        fAppl.setStyleSheet(

// BUTTONS
                        "QPushButton {"
                                    "background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,"
                                                                    "stop: 0 #B0B0B0, stop: 1 #404040);"
                                    "border: 2px solid grey;"
                                    "border-radius: 6px;"
                                    "margin-top: 1ex;"
                                 "}"

                 "QPushButton:hover {"
                                    "border: 2px solid orange;"
                                 "}"

                 "QPushButton:pressed {"
                                    //"border: 1px solid orange;"
                                    "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                                        "stop: 0 #404040, stop: 1 #B0B0B0);"
                                 "}"
// GROUPS
                       "QGroupBox {"
                                    "background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,"
                                                                    "stop: 0 #A0A0A0, stop: 1 #202020);"
                                    "border: 2px solid gray;"
                                    "border-radius: 5px;"
                                    "margin-top: 1ex;"
                                    "font-size:7pt;"
                                    "font-weight:bold;"
                                  //"color: dark grey;"
                                    "color: white;"
                                 "}"

                "QGroupBox::title {"
                                    "subcontrol-origin: margin;"
                                    "subcontrol-position: top center;" /* position at the top center */
                                    "padding: 0 5px;"
                                 "}"
// SLIDERS
                    // horizontal sliders
                    "QSlider::groove:vertical {"
                        "background: red;"
                        "position: absolute;" /* absolutely position 4px from the left and right of the widget. setting margins on the widget should work too... */
                        "left: 13px; right: 13px;"
                    "}"

                    "QSlider::handle:vertical {"
                        "height: 40px;"
                        "width: 30px;"
                        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                          "stop: 0 #AAAAAA, stop : 0.05 #0A0A0A, stop: 0.3 #101010, stop : 0.90 #AAAAAA, stop: 0.91 #000000);"
                        "margin: 0 -5px; /* expand outside the groove */"
                        "border-radius: 5px;"
                    "}"

                    "QSlider::add-page:vertical {"
                        "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,"
                                                          "stop: 0 yellow, stop : 0.5 orange);"
                    "}"

                    "QSlider::sub-page:vertical {"
                        "background: grey;"
                    "}"

                    // horizontal sliders

                    "QSlider::groove:horizontal {"
                        "background: red;"
                        "position: absolute;" /* absolutely position 4px from the left and right of the widget. setting margins on the widget should work too... */
                        "top: 14px; bottom: 14px;"
                    "}"

                    "QSlider::handle:horizontal {"
                        "width: 40px;"
                        "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,"
                                                          "stop: 0 #AAAAAA, stop : 0.05 #0A0A0A, stop: 0.3 #101010, stop : 0.90 #AAAAAA, stop: 0.91 #000000);"
                        "margin: -5px 0; /* expand outside the groove */"
                        "border-radius: 5px;"
                    "}"

                    "QSlider::sub-page:horizontal {"
                        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                          "stop: 0 yellow, stop : 0.5 orange);"
                    "}"

                    "QSlider::add-page:horizontal {"
                        "background: grey;"
                    "}"

// TABS
                    //TabWidget and TabBar
                    "QTabWidget::pane {" /* The tab widget frame */
                        //"border-top: 2px solid #C2C7CB;"
                        "border-top: 2px solid orange;"
                        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                        "stop: 0 #A0A0A0, stop: 1 #202020);"
                    "}"

                    "QTabWidget::tab-bar {"
                        "left: 5px;" /* move to the right by 5px */
                    "}"

                    /* Style the tab using the tab sub-control. Note that
                        it reads QTabBar _not_ QTabWidget */
                    "QTabBar::tab {"
                        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                    "stop: 0 #909090, stop: 0.4 #888888,"
                                                    "stop: 0.5 #808080, stop: 1.0 #909090);"
                        "border: 2px solid #808080;"
                        //"border-bottom-color: #C2C7CB;" /* same as the pane color */
                        "border-bottom-color: orange;" /* same as the pane color */
                        "border-top-left-radius: 4px;"
                        "border-top-right-radius: 4px;"
                        "min-width: 8ex;"
                        "padding: 2px;"
                    "}"

                    "QTabBar::tab:selected, QTabBar::tab:hover {"
                        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                    "stop: 0 #D0D0D0, stop: 0.4 #A0A0A0,"
                                                    "stop: 0.5 #808080, stop: 1.0 #A0A0A0);"
                                                    //"stop: 0.5 #A0A0A0, stop: 1.0 #C0C0C0);"
                                                    //"stop: 0 #fafafa, stop: 0.4 #f4f4f4,"
                                                    //"stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);"
                        //"border-bottom-color: orange;" /* same as the pane color */
                    "}"

                    "QTabBar::tab:selected {"
                        "border-color: orange;"
                        "border-bottom-color: #A0A0A0;" /* same as pane color */
                    "}"

                    "QTabBar::tab:!selected {"
                    "    margin-top: 2px;" /* make non-selected tabs look smaller */
                    "}"
                            );
#endif
		fAppl.exec();
		stop();

	}


	// ------------------------- Groups -----------------------------------

	virtual void openHorizontalBox(const char* label) { openBox(label, new QHBoxLayout()); }

	virtual void openVerticalBox(const char* label) 	{ openBox(label, new QVBoxLayout()); }

	virtual void openTabBox(const char* label) 		{ openTab(label); }

	virtual void closeBox()
	{
		QWidget* group = fGroupStack.top(); 
		fGroupStack.pop();
		if (fGroupStack.empty()) { group->show(); }
	}

	// ------------------------- active widgets -----------------------------------

	virtual void addButton(const char* label , float* zone)
	{
		QAbstractButton* 	w = new QPushButton(label);
		uiButton* 			c = new uiButton(this, zone, w);

		insert(label, w);	
		QObject::connect(w, SIGNAL(pressed()), c, SLOT(pressed()));
		QObject::connect(w, SIGNAL(released()), c, SLOT(released()));
        checkForTooltip(zone, w);
	}

	virtual void addCheckButton(const char* label , float* zone)
	{
		QCheckBox* 	w = new QCheckBox(label);
		uiCheckButton* 	c = new uiCheckButton(this, zone, w);

		insert(label, w);	
		QObject::connect(w, SIGNAL(stateChanged(int)), c, SLOT(setState(int)));
        checkForTooltip(zone, w);
	}

    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
    {
        if (isKnob(zone)) {
            addVerticalKnob(label, zone, init, min, max, step);
            return;
        }
        //insert(label, new QDoubleSpinBox());
        if (label && label[0]) openVerticalBox(label);
        QDoubleSpinBox*     w = new QDoubleSpinBox();
        uiNumEntry*         c = new uiNumEntry(this, zone, w, init, min, max, step);
        insert(label, w);
        w->setSuffix(fUnit[zone].c_str());
        QObject::connect(w, SIGNAL(valueChanged(double)), c, SLOT(setValue(double)));
        if (label && label[0]) closeBox();
        checkForTooltip(zone, w);
    }

    // special num entry without buttons
    virtual void addNumDisplay(const char* label, float* zone, float init, float min, float max, float step)
    {
        //insert(label, new QDoubleSpinBox());
        if (label && label[0]) openVerticalBox(label);
        QDoubleSpinBox*     w = new QDoubleSpinBox();
        w->setAlignment(Qt::AlignHCenter);
#if 1
        w->setStyleSheet(
                  "QDoubleSpinBox {"
                                    "border: 2px solid orange;"
                                    "border-radius: 5px;"
                                 "}"
        );
#endif
        uiNumEntry*         c = new uiNumEntry(this, zone, w, init, min, max, step);
        insert(label, w);
        w->setButtonSymbols(QAbstractSpinBox::NoButtons);
        w->setSuffix(fUnit[zone].c_str());
        QObject::connect(w, SIGNAL(valueChanged(double)), c, SLOT(setValue(double)));
        if (label && label[0]) closeBox();
        checkForTooltip(zone, w);
    }


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// KNOBS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void addVerticalKnob(const char* label , float* zone, float init, float min, float max, float step)
	{
		openVerticalBox(label);
		QAbstractSlider* 	w = new QDial(); //qsynthKnob();
		uiKnob*	c = new uiKnob(this, zone, w, init, min, max, step);
		insert(label, w);
		w->setStyle(new qsynthDialVokiStyle());
		QObject::connect(w, SIGNAL(valueChanged(int)), c, SLOT(setValue(int)));
		addNumDisplay(0, zone, init, min, max, step);

        // compute the size of the knob+display
        int width  = int(64*pow(2,fGuiSize[zone]));
        int height = int(100*pow(2,fGuiSize[zone]));
        fGroupStack.top()->setMinimumSize(width,height);
        fGroupStack.top()->setMaximumSize(width,height);

		closeBox();
        checkForTooltip(zone, w);
	}

	virtual void addHorizontalKnob(const char* label , float* zone, float init, float min, float max, float step)
	{
		openHorizontalBox(label);
		QAbstractSlider* 	w = new QDial(); //new qsynthKnob();
		uiKnob*	c = new uiKnob(this, zone, w, init, min, max, step);
		insert(label, w);
		w->setStyle(new qsynthDialVokiStyle());
		QObject::connect(w, SIGNAL(valueChanged(int)), c, SLOT(setValue(int)));
		addNumDisplay(0, zone, init, min, max, step);
		closeBox();
        checkForTooltip(zone, w);
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// SLIDERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void addVerticalSlider(const char* label , float* zone, float init, float min, float max, float step)
	{
		if (isKnob(zone)) {
			addVerticalKnob(label, zone, init, min, max, step);
			return;
		}
		openVerticalBox(label);
		QSlider* 	w = new QSlider(Qt::Vertical);
        w->setMinimumHeight(160);
        w->setMinimumWidth(34);
		//w->setTickPosition(QSlider::TicksBothSides);
		uiSlider*	c = new uiSlider(this, zone, w, init, min, max, step);
		insert(label, w);
		QObject::connect(w, SIGNAL(valueChanged(int)), c, SLOT(setValue(int)));
		addNumDisplay(0, zone, init, min, max, step);
		closeBox();
        checkForTooltip(zone, w);
	}

	virtual void addHorizontalSlider(const char* label , float* zone, float init, float min, float max, float step)
	{
		if (isKnob(zone)) {
			addHorizontalKnob(label, zone, init, min, max, step);
			return;
		}
		openHorizontalBox(label);
		QSlider* 	w = new QSlider(Qt::Horizontal);
        w->setMinimumHeight(34);
        w->setMinimumWidth(160);
		//w->setTickPosition(QSlider::TicksBothSides);
		uiSlider*	c = new uiSlider(this, zone, w, init, min, max, step);
		insert(label, w);
		QObject::connect(w, SIGNAL(valueChanged(int)), c, SLOT(setValue(int)));
		addNumDisplay(0, zone, init, min, max, step);
		closeBox();
        checkForTooltip(zone, w);
	}



	// ------------------------- passive widgets -----------------------------------

    
    virtual void addHorizontalBargraph(const char* label , float* zone, float min, float max)
    {
        AbstractDisplay*  bargraph;
        openVerticalBox(label);
        bool db = (fUnit[zone] == "dB");
        
        if (fLedSet.count(zone)) {
            if (db) {
                bargraph = new dbLED(min, max);
            } else {
                bargraph = new LED(min,max);
            }
        } else {
            if (db) {
                bargraph = new dbHorizontalBargraph(min, max);
            } else {
                bargraph = new linHorizontalBargraph(min, max);
            }
        }
        
        new uiBargraph2(this, zone, bargraph, min, max);
        insert(label, bargraph);
        closeBox();
        checkForTooltip(zone, bargraph);
    }

    virtual void addVerticalBargraph(const char* label , float* zone, float min, float max)
    {
        AbstractDisplay*  bargraph;
        openVerticalBox(label);
        bool db = (fUnit[zone] == "dB");
        
        if (fLedSet.count(zone)) {
            if (db) {
                bargraph = new dbLED(min, max);
            } else {
                bargraph = new LED(min,max);
            }
        } else {
            if (db) {
                bargraph = new dbVerticalBargraph(min, max);
            } else {
                bargraph = new linVerticalBargraph(min, max);
            }
        }
        new uiBargraph2(this, zone, bargraph, min, max);
        insert(label, bargraph);
        closeBox();
        checkForTooltip(zone, bargraph);
    }



};


