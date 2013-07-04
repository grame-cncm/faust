/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
#ifndef __faustqt__
#define __faustqt__

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
#include <QCommonStyle>
#include <QDial>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLayout>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QProgressBar>
#include <QPushButton>
#include <QRadialGradient>
#include <QSlider>
#include <QStyle>
#include <QStyleOptionSlider>
#include <QTabWidget>
#include <QTimer>
#include <QToolTip>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QWidget>
#include <QtGui>

#include "faust/gui/GUI.h"

#ifdef QRCODECTRL
#include <sstream>
#include <QHostAddress>
#include <QTcpSocket>
#include <qrencode.h>
#include <QRegExp>
#endif

//----------------------------------

// for compatibility
#define minValue minimum
#define maxValue maximum


///using namespace std;


//==============================BEGIN QSYNTHKNOB=====================================
//
//   qsynthknob and qsynthDialVokiStyle borrowed from qsynth-0.3.3 by Rui Nuno Capela
//   This widget is based on a design by Thorsten Wilms,
//   implemented by Chris Cannam in Rosegarden,
//   adapted for QSynth by Pedro Lopez-Cabanillas,
//   improved for Qt4 by David Garcia Garzon.
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
    
        FAUSTFLOAT fMin;
        FAUSTFLOAT fMax;
        FAUSTFLOAT fValue;

    public:

        AbstractDisplay(FAUSTFLOAT lo, FAUSTFLOAT hi) : fMin(lo), fMax(hi), fValue(lo)
        {}

        /**
         * set the range of displayed values
         */
        virtual void setRange(FAUSTFLOAT lo, FAUSTFLOAT hi)
        {
            fMin = lo;
            fMax = hi;
        }

        /**
         * set the value to be displayed
         */
        virtual void setValue(FAUSTFLOAT v)
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

        FAUSTFLOAT      fScaleMin;
        FAUSTFLOAT      fScaleMax;
        std::vector<int>     fLevel;
        std::vector<QBrush>  fBrush;


        /**
        * Convert a dB value into a scale between 0 and 1 (following IEC standard ?)
        */
        FAUSTFLOAT dB2Scale(FAUSTFLOAT dB) const
        {
            FAUSTFLOAT fScale = 1.0;

            /*if (dB < -70.0f)
                fScale = 0.0f;
            else*/ if (dB < -60.0)
                fScale = (dB + 70.0) * 0.0025;
            else if (dB < -50.0)
                fScale = (dB + 60.0) * 0.005 + 0.025;
            else if (dB < -40.0)
                fScale = (dB + 50.0) * 0.0075 + 0.075;
            else if (dB < -30.0)
                fScale = (dB + 40.0) * 0.015 + 0.15;
            else if (dB < -20.0)
                fScale = (dB + 30.0) * 0.02 + 0.3;
            else if (dB < -0.001 || dB > 0.001)  /* if (dB < 0.0) */
                fScale = (dB + 20.0f) * 0.025 + 0.5;

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

        dbAbstractDisplay(FAUSTFLOAT lo, FAUSTFLOAT hi) : AbstractDisplay(lo, hi)
        {}

        /**
         * set the range of displayed values
         */
        virtual void setRange(FAUSTFLOAT lo, FAUSTFLOAT hi)
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
                FAUSTFLOAT a = (fValue-fMin)/(fLevel[0]-fMin);
                c.setAlphaF(a);
                painter.fillRect(rect(), c);

            } else {

                // find the minimal level > value
                int l = fLevel.size()-1; while (fValue < fLevel[l] && l > 0) l--;
                painter.fillRect(rect(), fBrush[l]);
            }
        }

    public:

        dbLED(FAUSTFLOAT lo, FAUSTFLOAT hi) : dbAbstractDisplay(lo,hi)
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
            FAUSTFLOAT a = (fValue-fMin)/(fMax-fMin);
            c.setAlphaF(a);
            painter.fillRect(rect(), c);
        }

    public:

        LED(FAUSTFLOAT lo, FAUSTFLOAT hi) : AbstractDisplay(lo,hi), fColor("yellow")
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
            FAUSTFLOAT   v = (fValue-fMin)/(fMax-fMin);

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

        linBargraph(FAUSTFLOAT lo, FAUSTFLOAT hi) : AbstractDisplay(lo,hi)
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

        linVerticalBargraph(FAUSTFLOAT lo, FAUSTFLOAT hi) : linBargraph(lo,hi)
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

        linHorizontalBargraph(FAUSTFLOAT lo, FAUSTFLOAT hi) : linBargraph(lo,hi)
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
        virtual void paintMark(QPainter* painter, FAUSTFLOAT v) const = 0;
        virtual int paintSegment (QPainter* painter, int pos, FAUSTFLOAT v, const QBrush& b) const = 0;

        /**
         * Draw the logarithmic scale
         */
        void paintScale(QPainter* painter) const
        {
            painter->fillRect(0,0,width(),height(), fBackColor);
            painter->save();
            painter->setPen(QColor(0x6699aa)); //0xffa500));
            for (FAUSTFLOAT v = -10; v > fMin; v -= 10) paintMark(painter, v);
            for (FAUSTFLOAT v = -6; v < fMax; v += 3) paintMark(painter, v);
            painter->restore();
        }

        /**
         * Draw the content using colored segments
         */
        void paintContent (QPainter* painter) const
        {
            int   l = fLevel.size();

            FAUSTFLOAT   p = -1;   // fake value indicates to start from border
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

        dbBargraph(FAUSTFLOAT lo, FAUSTFLOAT hi) : dbAbstractDisplay(lo,hi)
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
        FAUSTFLOAT dB2y(FAUSTFLOAT dB) const
        {
            FAUSTFLOAT s0 = fScaleMin;
            FAUSTFLOAT s1 = fScaleMax;
            FAUSTFLOAT sx = dB2Scale(dB);
            int    h = height();

            return h - h*(s0-sx)/(s0-s1);
        }

        /**
         * Paint a vertical graduation mark
         */
        virtual void paintMark(QPainter* painter, FAUSTFLOAT v) const
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
        virtual int paintSegment(QPainter* painter, int pos, FAUSTFLOAT v, const QBrush& b) const
        {
            if (pos == -1) pos = height();
            FAUSTFLOAT y = dB2y(v);
            painter->fillRect(0, y, width(), pos-y+1, b);
            return y;
        }


    public:

        dbVerticalBargraph(FAUSTFLOAT lo, FAUSTFLOAT hi) : dbBargraph(lo,hi)
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
        FAUSTFLOAT dB2x(FAUSTFLOAT dB) const
        {
            FAUSTFLOAT s0 = fScaleMin;
            FAUSTFLOAT s1 = fScaleMax;
            FAUSTFLOAT sx = dB2Scale(dB);
            int    w = width();

            return w - w*(s1-sx)/(s1-s0);
        }

        /**
         * Paint an horizontal graduation mark
         */
        void paintMark(QPainter* painter, FAUSTFLOAT v) const
        {
            int n = 10;
            int x = dB2x(v);
            QRect r(x-n,0,2*n, height());
            painter->drawText(r, Qt::AlignHCenter|Qt::AlignVCenter, QString::number(v));
        }

        /**
         * Paint a horizontal color segment
         */
        int paintSegment (QPainter* painter, int pos, FAUSTFLOAT v, const QBrush& b) const
        {
            if (pos == -1) pos = 0;
            FAUSTFLOAT x = dB2x(v);
            painter->fillRect(pos, 0, x-pos, height(), b);
            return x;
        }


    public:

        dbHorizontalBargraph(FAUSTFLOAT lo, FAUSTFLOAT hi) : dbBargraph(lo,hi)
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
static std::string rmWhiteSpaces(const std::string& s)
{
    size_t i = s.find_first_not_of(" \t");
    size_t j = s.find_last_not_of(" \t");
  	if ( (i != std::string::npos) && (j != std::string::npos) ) {
		return s.substr(i, 1+j-i);
	} else {
		return "";
	}
}

/**
 * Extracts metdata from a label : 'vol [unit: dB]' -> 'vol' + metadata(unit=dB)
 */
static void extractMetadata(const std::string& fulllabel, std::string& label, std::map<std::string, std::string>& metadata)
{
    enum {kLabel, kEscape1, kEscape2, kEscape3, kKey, kValue};
    int state = kLabel; int deep = 0;
    std::string key, value;

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
                std::cerr << "ERROR unrecognized state " << state << std::endl;
        }
    }
    label = rmWhiteSpaces(label);
}

//
//============================= END GROUP LABEL METADATA===========================


/******************************************************************************
*******************************************************************************

							IMPLEMENTATION OF GUI ITEMS
							   (QT 4.3 for FAUST)

*******************************************************************************
*******************************************************************************/

class uiButton : public QObject, public uiItem
{
    Q_OBJECT

 public :
	QAbstractButton* 	fButton;

	uiButton (GUI* ui, FAUSTFLOAT* zone, QAbstractButton* b) : uiItem(ui, zone), fButton(b) {}


	virtual void reflectZone()
	{
		FAUSTFLOAT v = *fZone;
		fCache = v;
		fButton->setDown( v > 0.0 );
	}

 public slots :
	void pressed()		{ modifyZone(1.0); }
	void released()		{ modifyZone(0.0); }
};

class uiCheckButton : public QObject, public uiItem
{
    Q_OBJECT

 public :
	QCheckBox* 	fCheckBox;

	uiCheckButton (GUI* ui, FAUSTFLOAT* zone, QCheckBox* b) : uiItem(ui, zone), fCheckBox(b) {}

	virtual void reflectZone()
	{
		FAUSTFLOAT v = *fZone;
		fCache = v;
		fCheckBox->setCheckState( (v < 0.5) ? Qt::Unchecked : Qt::Checked );
	}

 public slots :
	void setState(int v)		{ modifyZone(FAUSTFLOAT(v>0)); }
};

class uiSlider : public QObject, public uiItem
{
    Q_OBJECT

	int		faust2qt(FAUSTFLOAT x) 	{ return int(0.5 + (x-fMin)/fStep); }
	FAUSTFLOAT	qt2faust (int v)	{ return fMin + v*fStep; }
	int		optimalTick()		{
				FAUSTFLOAT x = fStep;
				while ((fMax-fMin)/x > 50) x*=10;
				while ((fMax-fMin)/x < 10) x/=2;
				return faust2qt(fMin+x);
			}

 public :
	QSlider* 	fSlider;
	FAUSTFLOAT	fCur;
	FAUSTFLOAT	fMin;
	FAUSTFLOAT	fMax;
	FAUSTFLOAT	fStep;

	uiSlider (GUI* ui, FAUSTFLOAT* zone, QSlider* slider, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT step)
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
		FAUSTFLOAT v = *fZone;
		fCache = v;
		fSlider->setValue(faust2qt(v));
	}

 public slots :
	void setValue(int v)		{ modifyZone(qt2faust(v)); }
};

class uiKnob : public QObject, public uiItem
{
    Q_OBJECT

	int		faust2qt(FAUSTFLOAT x) 	{ return int(0.5 + (x-fMin)/fStep); }
	FAUSTFLOAT	qt2faust (int v)	{ return fMin + v*fStep; }
	int		optimalTick()		{
				FAUSTFLOAT x = fStep;
				while ((fMax-fMin)/x > 50) x*=10;
				while ((fMax-fMin)/x < 10) x/=2;
				return faust2qt(fMin+x);
			}

 public :
	QAbstractSlider* 	fSlider;
	FAUSTFLOAT			fCur;
	FAUSTFLOAT			fMin;
	FAUSTFLOAT			fMax;
	FAUSTFLOAT			fStep;

	uiKnob (GUI* ui, FAUSTFLOAT* zone, QAbstractSlider* slider, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT step)
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
		FAUSTFLOAT v = *fZone;
		fCache = v;
		fSlider->setValue(faust2qt(v));
	}

 public slots :
	void setValue(int v)		{ modifyZone(qt2faust(v)); }
};

class uiBargraph : public QObject, public uiItem
{
    Q_OBJECT

    int     faust2qt(FAUSTFLOAT x)   { return int(0.5 + (x-fMin)/(fMax-fMin)*fStep); }

 public :
    QProgressBar*   fBar;
    FAUSTFLOAT      fMin;
    FAUSTFLOAT      fMax;
    int             fStep;

    uiBargraph (GUI* ui, FAUSTFLOAT* zone, QProgressBar* bar, FAUSTFLOAT lo, FAUSTFLOAT hi)
        : uiItem(ui, zone), fBar(bar), fMin(lo), fMax(hi), fStep(1024)
    {
        fBar->setRange(0, fStep);
        fBar->setValue(0);
        *fZone = 0;
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        int x = faust2qt(v);
        //std::cout << "update *" << fBar << " = " << x << std::endl;
        fBar->setValue(x);
    }
};

class uiBargraph2 : public QObject, public uiItem
{
    Q_OBJECT

 public :
    AbstractDisplay*   fBar;

    uiBargraph2 (GUI* ui, FAUSTFLOAT* zone, AbstractDisplay* bar, FAUSTFLOAT lo, FAUSTFLOAT hi)
        : uiItem(ui, zone), fBar(bar)
    {
        fBar->setRange(lo, hi);
        fBar->setValue(lo);
        *fZone = lo;
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        fBar->setValue(v);
    }
};

class uiNumEntry : public QObject, public uiItem
{
    Q_OBJECT

 public :
	QDoubleSpinBox* 	fNumEntry;
	FAUSTFLOAT			fCur;
	FAUSTFLOAT			fMin;
	FAUSTFLOAT			fMax;
	FAUSTFLOAT			fStep;
	int					fDecimals;

	uiNumEntry (GUI* ui, FAUSTFLOAT* zone, QDoubleSpinBox* numEntry, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT step)
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
		FAUSTFLOAT v = *fZone;
		fCache = v;
		fNumEntry->setValue(v);
	}

 public slots :
	void setValue(double v)		{
		modifyZone(FAUSTFLOAT(v));
	}
};

/******************************************************************************
*******************************************************************************

						IMPLEMENTATION OF THE USER INTERFACE
							   (QT 4.3 for FAUST)

*******************************************************************************
*******************************************************************************/

class QTGUI : public QObject, public GUI
{
    Q_OBJECT
	QApplication            fAppl;
	QTimer*                 fTimer;
	QStyle*                 fStyle;
    std::string				gGroupTooltip;
    std::stack<QWidget* > 	fGroupStack;

    std::map<FAUSTFLOAT*, FAUSTFLOAT>      fGuiSize;       // map widget zone with widget size coef
    std::map<FAUSTFLOAT*, std::string>     fTooltip;       // map widget zone with tooltip strings
    std::map<FAUSTFLOAT*, std::string>     fUnit;          // map widget zone to unit string (i.e. "dB")
    std::set<FAUSTFLOAT*>                  fKnobSet;       // set of widget zone to be knobs
    std::set<FAUSTFLOAT*>                  fLedSet;        // set of widget zone to be LEDs


    /**
    * Format tooltip string by replacing some white spaces by
	* return characters so that line width doesn't exceed n.
	* Limitation : long words exceeding n are not cut
    */
	virtual std::string formatTooltip(int n, const std::string& tt)
	{
		std::string  ss = tt;	// ss string we are going to format
		int	lws = 0;	// last white space encountered
		int 	lri = 0;	// last return inserted
		for (int i=0; i< (int)tt.size(); i++) {
			if (tt[i] == ' ') lws = i;
			if (((i-lri) >= n) && (lws > lri)) {
				// insert return here
				ss[lws] = '\n';
				lri = lws;
			}
		}
		return ss;
	}

    /**
    * Analyses the widget zone metadata declarations and takes
    * appropriate actions
    */
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* value)
    {
		if (zone == 0) {
			// special zone 0 means group metadata
			if (strcmp(key,"tooltip")==0) {
				// only group tooltip are currently implemented
				gGroupTooltip = formatTooltip(30, value);
			}
		} else {
			if (strcmp(key,"size")==0) {
				fGuiSize[zone]=atof(value);
			}
			else if (strcmp(key,"tooltip")==0) {
				fTooltip[zone] = formatTooltip(30, value) ;
			}
			else if (strcmp(key,"unit")==0) {
				fUnit[zone] = value ;
			}
			else if (strcmp(key,"style")==0) {
			// else if ((strcmp(key,"style")==0) || (strcmp(key,"type")==0)) {
				if (strcmp(value,"knob") == 0) {
					fKnobSet.insert(zone);
				} else if (strcmp(value,"led") == 0) {
					fLedSet.insert(zone);
				}
			}
		}
	}

	bool isTabContext()
	{
		//return fGroupStack.empty() || ((!fGroupStack.empty()) && (dynamic_cast<QTabWidget*>(fGroupStack.top()) != 0));
		return ((!fGroupStack.empty()) && (dynamic_cast<QTabWidget*>(fGroupStack.top()) != 0));
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

    int checkLabelOptions(QWidget* widget, const std::string& fullLabel, std::string& simplifiedLabel)
    {
        std::map<std::string, std::string> metadata;
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
    void checkForTooltip(FAUSTFLOAT* zone, QWidget* widget)
    {
        if (fTooltip.count(zone)) {
            widget->setToolTip(fTooltip[zone].c_str());
        }
    }

    /**
    * Check if a knob is required
    */
    bool isKnob(FAUSTFLOAT* zone)
    {
        return fKnobSet.count(zone) > 0;
    }

	void openBox(const char* fulllabel, QLayout* layout)
	{
		std::map<std::string, std::string> metadata;
        std::string label;
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
/*        if (metadata.count("tooltip")) {
            box->setToolTip(metadata["tooltip"].c_str());
        }*/
        if (gGroupTooltip != std::string()) {
			box->setToolTip(gGroupTooltip.c_str());
			gGroupTooltip = std::string();
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

	QTGUI(int& argc, char* argv[], QStyle* style = 0) : fAppl(argc, argv), fTimer(0), fStyle(style){
        //fGroupStack.push(new QMainWindow());
    }

	virtual ~QTGUI() {}

#ifdef HTTPCTRL
#ifdef QRCODECTRL
   
   	//
	// Extract the IP number of the machine http
 	//

    QString extractIPnum(int portnum)
	{
        QString     result;
        QTcpSocket  sock;
        
        sock.connectToHost("8.8.8.8", 53); // google DNS, or somethingelse reliable
        if (sock.waitForConnected()) {
            QHostAddress IP = sock.localAddress();
            result = IP.toString(); 
        } else {
            result = "localhost";
        }
        std::stringstream ss; ss << portnum;
        return result + ":" + ss.str().c_str();;
    }

    //
    // Used in HTTPD mode, display the QRCode of the URL of the application
    //
    void displayQRCode(int portnum)
    {
        const int padding = 5;
    	QString url = extractIPnum(portnum);
        QRcode* qrc = QRcode_encodeString(url.toStdString().c_str(), 0, QR_ECLEVEL_H, QR_MODE_8, 1);

        qDebug() << "url to encode = " << url;
        qDebug() << "QRcode width  = " << qrc->width;

		QRgb colors[2];
		colors[0] = qRgb(255, 255, 255); 	// 0 is white
		colors[1] = qRgb(0, 0, 0); 			// 1 is black

        // build the QRCode image
        QImage image(qrc->width+2*padding, qrc->width+2*padding, QImage::Format_RGB32);
        // clear the image
        for (int y=0; y<qrc->width+2*padding; y++) {
            for (int x=0; x<qrc->width+2*padding; x++) {
                image.setPixel(x, y, colors[0]);
            }
        }
        // copy the qrcode inside
        for (int y=0; y<qrc->width; y++) {
            for (int x=0; x<qrc->width; x++) {
                image.setPixel(x+padding, y+padding, colors[qrc->data[y*qrc->width+x]&1]);
            }
        }

        QImage big = image.scaledToWidth(qrc->width*5);
        QLabel* myLabel = new QLabel();
        myLabel->setPixmap(QPixmap::fromImage(big));
        myLabel->setWindowTitle(url);
        myLabel->show();

    }
#endif
#endif

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
                                    "margin-top: 3ex;"
                                    "font-size:10pt;"
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

	virtual void openHorizontalBox(const char* label) { 
		openBox(label, new QHBoxLayout());
	}

	virtual void openVerticalBox(const char* label) 	{
        openBox(label, new QVBoxLayout());
    }

    virtual void openFrameBox(const char* ) 		{ }
	virtual void openTabBox(const char* label) 		{ 
		openTab(label);
	}

	virtual void closeBox()
	{
		QWidget* group = fGroupStack.top();
		fGroupStack.pop();
		if (fGroupStack.empty()) { group->show(); group->adjustSize();}
	}

	// ------------------------- active widgets -----------------------------------

	virtual void addButton(const char* label, FAUSTFLOAT* zone)
	{
		QAbstractButton* 	w = new QPushButton(label);
		uiButton* 			c = new uiButton(this, zone, w);

		insert(label, w);
		QObject::connect(w, SIGNAL(pressed()), c, SLOT(pressed()));
		QObject::connect(w, SIGNAL(released()), c, SLOT(released()));
        checkForTooltip(zone, w);
	}

    virtual void addToggleButton(const char*, FAUSTFLOAT*)
    {}

	virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
	{
		QCheckBox* 	w = new QCheckBox(label);
		uiCheckButton* 	c = new uiCheckButton(this, zone, w);

		insert(label, w);
		QObject::connect(w, SIGNAL(stateChanged(int)), c, SLOT(setState(int)));
        checkForTooltip(zone, w);
	}

    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
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
    virtual void addNumDisplay(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
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
                                    "font-size: 8pt;"
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

	virtual void addVerticalKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
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

	virtual void addHorizontalKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
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

	virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
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

	virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
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

    virtual void addNumDisplay(const char*, FAUSTFLOAT*, int)
    {}

	virtual void addTextDisplay(const char*, FAUSTFLOAT*, const char* [], FAUSTFLOAT, FAUSTFLOAT)
    {}

    virtual void addHorizontalBargraph(const char* label , FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
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

    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
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

#endif
