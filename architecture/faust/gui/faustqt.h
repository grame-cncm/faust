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

#if defined(HTTPCTRL) && defined(QRCODECTRL) 

#ifdef _WIN32
#include <winsock2.h>
#undef min
#undef max
#else
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include <QtNetwork>
#include <qrencode.h>

#endif

#include <QtGlobal>
#include <QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "faust/gui/GUI.h"
#include "faust/gui/ValueConverter.h"
#include "faust/gui/MetaDataUI.h"

#include <sstream>

// for compatibility
#define minValue minimum
#define maxValue maximum

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
        
		const QStyleOptionSlider* dial = qstyleoption_cast<const QStyleOptionSlider *>(opt);
		if (dial == NULL) return;
        
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
		QRadialGradient projectionGradient(xcenter + shineCenter, ycenter + shineCenter,
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
        
		QRadialGradient gradient(xcenter - shineCenter, ycenter - shineCenter,
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
        
		if (dial->subControls & QStyle::SC_DialTickmarks) {
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
    
protected:
    
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
    
protected:
    
    FAUSTFLOAT      fScaleMin;
    FAUSTFLOAT      fScaleMax;
    std::vector<int>     fLevel;
    std::vector<QBrush>  fBrush;
    
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
    
protected:
    
     QColor  fColor;
    
    /**
     * Draw the LED using a transparency depending of its value
     */
    virtual void paintEvent(QPaintEvent *)
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
    
protected:
    
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
    void paintContent(QPainter* painter) const
    {
        int     w = width();
        int     h = height();
        FAUSTFLOAT   v = (fValue-fMin)/(fMax-fMin);
        
        if (h > w) {
            // draw vertical rectangle
            painter->fillRect(0,(1-v)*h,w, v*h, fBrush);
        } else {
            // draw horizontal rectangle
            painter->fillRect(0, 0, v*w, h, fBrush);
        }
    }
    
    virtual void paintEvent(QPaintEvent *)
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
    
    virtual QSize sizeHint() const
    {
        return QSize(128, 16);
    }
};

/**
 * A dB Bargraph with a scale of colors
 */
class dbBargraph : public dbAbstractDisplay
{
    
protected:
    
    QBrush  fBackColor;
    
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
    void paintContent(QPainter* painter) const
    {
        int l = fLevel.size();
        
        FAUSTFLOAT p = -1;   // fake value indicates to start from border
        int n = 0;
        // paint all the full segments < fValue
        for (n = 0; (n < l) && (fValue > fLevel[n]); n++) {
            p = paintSegment(painter, p, fLevel[n], fBrush[n]);
        }
        // paint the last segment
        if (n == l) n = n-1;
        p=paintSegment(painter, p, fValue, fBrush[n]);
        
        painter->drawRect(0,0,width(),height());
    }
    
    virtual void paintEvent (QPaintEvent *)
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
    
    virtual QSize sizeHint() const
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
    int paintSegment(QPainter* painter, int pos, FAUSTFLOAT v, const QBrush& b) const
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

/******************************************************************************
 *******************************************************************************
 
 IMPLEMENTATION OF GUI ITEMS
 (QT 4.3 for FAUST)
 
 *******************************************************************************
 *******************************************************************************/


/**
 * A push button that controls/reflects the value (O/1)
 * of a zone.
 */
class uiButton : public QObject, public uiItem
{
    Q_OBJECT
    
public:
    
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


/**
 * A checkbox that controls/reflects the value (O/1)
 * of a zone.
 */
class uiCheckButton : public QObject, public uiItem
{
    Q_OBJECT
    
public:
    
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

/**
 * A slider that controls/reflects the value (min..max)
 * of a zone.
 */
class uiSlider : public QObject, public uiItem
{
    Q_OBJECT
    
protected:
    
    QAbstractSlider* 	fSlider;
    FAUSTFLOAT			fCur;
    FAUSTFLOAT			fMin;
    FAUSTFLOAT			fMax;
    FAUSTFLOAT			fStep;
	ValueConverter*		fConverter;
    
public:
    
    uiSlider (GUI* ui, FAUSTFLOAT* zone, QAbstractSlider* slider, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT step, MetaDataUI::Scale scale)
    : uiItem(ui, zone), fSlider(slider), fCur(cur), fMin(lo), fMax(hi), fStep(step)
    {
		// select appropriate converter according to scale mode
		if (scale == MetaDataUI::kLog) 			{ fConverter = new LogValueConverter(0, 10000, fMin, fMax); }
		else if (scale == MetaDataUI::kExp) 	{ fConverter = new ExpValueConverter(0, 10000, fMin, fMax); }
        else                                    { fConverter = new LinearValueConverter(0, 10000, fMin, fMax); }
        
        fSlider->setMinimum(0);
        fSlider->setMaximum(10000);
        fSlider->setValue(int(0.5+fConverter->faust2ui(fCur)));
        *fZone = fCur;
    }
    
	~uiSlider() 
	{
		if (fConverter) delete fConverter;
	}
    
    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        fSlider->setValue(int(0.5+fConverter->faust2ui(v)));
    }
    
    public slots :
    void setValue(int v)		{ modifyZone(fConverter->ui2faust(v)); }
};


/**
 * A zone setter, an object that sets a zone with a predefined value
 * every time the set(bool) method is called. The boolean parameter
 * is here for compatibility with some signals and is ignored.
 */
class ZoneSetter : public QObject
{
    Q_OBJECT
    
protected:
    
    FAUSTFLOAT  fValue;
    FAUSTFLOAT* fZone;
    
public:
    explicit ZoneSetter(FAUSTFLOAT v, FAUSTFLOAT* z, QObject *parent = 0):
    QObject(parent), fValue(v), fZone(z)
    {}
    
    public slots:
    void set(bool)
    {
        *fZone = fValue;
        //        qDebug() << "setting " << fValue << " --> " << fZone;
    }
};


/**
 * A set of mutually exclusive radio buttons vertically
 * layed out. The names and values used for the radio buttons
 * are described in the string mdescr with the following syntax
 * "{'foo':3.14; 'faa':-0.34; ... 'fii':10.5}"
 */
class uiRadioButtons : public QGroupBox, public uiItem
{
    Q_OBJECT
    
protected:
    
    vector<double>          fValues;
    vector<QRadioButton*>   fButtons;
    
public:
    
    uiRadioButtons (GUI* ui, FAUSTFLOAT* z, const char* label,
                    FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT /*step*/,
                    bool vertical, const char* mdescr, QWidget* parent)
    : QGroupBox(label, parent),  uiItem(ui, z)
    {
        vector<string>  names;
        vector<double>  values;
        
        if (parseMenuList(mdescr, names, values)) {
            
            QBoxLayout*    l;
            if (vertical) {
                l = new QVBoxLayout(this);
            } else {
                l = new QHBoxLayout(this);
            }
            l->setSpacing(5);
            
            QRadioButton*   defaultbutton = 0;
            double          mindelta = FLT_MAX;
            
            for (unsigned int i = 0; i < names.size(); i++) {
                double v = values[i];
                if ((v >= lo) && (v <= hi)) {
                    
                    // It is a valid value included in slider's range
                    QRadioButton*   b = new QRadioButton(QString(names[i].c_str()), this);
                    ZoneSetter*     s = new ZoneSetter(v,z,b);
                    fValues.push_back(v);
                    fButtons.push_back(b);
                    connect(b,SIGNAL(clicked(bool)), s, SLOT(set(bool)));
                    l->addWidget(b);
                    
                    // Check if this item is a good candidate to represent the current value
                    double delta = fabs(cur-v);
                    if (delta < mindelta) {
                        mindelta = delta;
                        defaultbutton = b;
                    }
                }
            }
            // check the best candidate to represent the current value
            if (defaultbutton) { defaultbutton->setChecked(true); }
            setLayout(l);
        }
        *fZone = cur;
    }
    
    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        
        // select closest value
        int             defaultitem = -1;
        double          mindelta = FLT_MAX;
        
        for (unsigned int i=0; i<fValues.size(); i++) {
            double delta = fabs(fValues[i]-v);
            if (delta < mindelta) {
                mindelta = delta;
                defaultitem = i;
            }
        }
        if (defaultitem > -1) { fButtons[defaultitem]->setChecked(true); }
    }
};

/**
 * A popup menu. The names and values used for the menu items
 * are described in the string mdescr with the following syntax
 * "{'foo':3.14; 'faa':-0.34; ... 'fii':10.5}"
 */
class uiMenu : public QComboBox, public uiItem
{
    Q_OBJECT
    
protected:
    
    vector<double>  fValues;
    
public:
    
    uiMenu (GUI* ui, FAUSTFLOAT* z, const char* /*label*/,
            FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT /*step*/,
            const char* mdescr, QWidget* parent)
    : QComboBox(parent),  uiItem(ui, z)
    {
        vector<string>  names;
        vector<double>  values;
        
        if (parseMenuList(mdescr, names, values)) {
            
            int     defaultitem = -1;
            double  mindelta = FLT_MAX;
            
            for (unsigned int i = 0; i < names.size(); i++) {
                double v = values[i];
                if ( (v >= lo) && (v <= hi) ) {
                    
                    // It is a valid value : add corresponding menu item
                    addItem(QString(names[i].c_str()), v);
                    fValues.push_back(v);
                    
                    // Check if this item is a good candidate to represent the current value
                    double delta = fabs(cur-v);
                    if (delta < mindelta) {
                        mindelta = delta;
                        defaultitem = count()-1;
                    }
                }
            }
            // check the best candidate to represent the current value
            if (defaultitem > -1) { setCurrentIndex(defaultitem); }
        }
        connect(this,SIGNAL(activated(int)), this, SLOT(updateZone(int)));
        *fZone = cur;
    }
    
    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        
        // search closest value
        int             defaultitem = -1;
        double          mindelta = FLT_MAX;
        
        for (unsigned int i=0; i<fValues.size(); i++) {
            double delta = fabs(fValues[i]-v);
            if (delta < mindelta) {
                mindelta = delta;
                defaultitem = i;
            }
        }
        if (defaultitem > -1) { setCurrentIndex(defaultitem); }
    }
    
    public slots :
    
    void updateZone(int)
    {
        double x = itemData(currentIndex()).toDouble();
        *fZone = x;
    }
};

/**
 * A bargraph representing the value of a zone
 */
class uiBargraph : public QObject, public uiItem
{
    Q_OBJECT
    
protected:
    
    AbstractDisplay*   fBar;
    
public:
    
    uiBargraph (GUI* ui, FAUSTFLOAT* zone, AbstractDisplay* bar, FAUSTFLOAT lo, FAUSTFLOAT hi)
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

/**
 * A numerical entry that controls/reflects the value (min..max)
 * of a zone.
 */
class uiNumEntry : public QObject, public uiItem
{
    Q_OBJECT
    
protected:
    
	QDoubleSpinBox* 	fNumEntry;
	FAUSTFLOAT			fCur;
	FAUSTFLOAT			fMin;
	FAUSTFLOAT			fMax;
	FAUSTFLOAT			fStep;
	int					fDecimals;
    
public:
    
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
    void setValue(double v)
    {
        modifyZone(FAUSTFLOAT(v));
    }
};

/******************************************************************************
 *******************************************************************************
 
 IMPLEMENTATION OF THE USER INTERFACE
 (QT 4.3 for FAUST)
 
 *******************************************************************************
 *******************************************************************************/

class QTGUI : public QWidget, public GUI, public MetaDataUI
{
    Q_OBJECT
    
protected:
    
	QTimer*                 fTimer;
    std::stack<QWidget* > 	fGroupStack;
    
    QMainWindow*            fMainWindow;
    QVBoxLayout*            fGeneralLayout;
    
    QPixmap                 fQrCode;
    
	bool isTabContext()
	{
		//return fGroupStack.empty() || ((!fGroupStack.empty()) && (dynamic_cast<QTabWidget*>(fGroupStack.top()) != 0));
		return ((!fGroupStack.empty()) && (dynamic_cast<QTabWidget*>(fGroupStack.top()) != 0));
	}
    
    /**
     * Insert a widget into the parent widget (the top of
     * the stack group). The label is used if this group is
     * a tab.
     */
    
    void insert(const char* label, QWidget* widget)
	{
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
     * Analyses a full label and activates the relevant options. Returns a simplified
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
    
    void openBox(const char* fulllabel, QLayout* layout)
	{
        std::map<std::string, std::string> metadata;
        std::string label;
        extractMetadata(fulllabel, label, metadata);
  		layout->setMargin(5);
		QWidget* box;
        
        label = startWith(label, "0x") ? "" : label;
        
        if (fGroupStack.empty()) {
            if (isTabContext()) {
                box = new QWidget(this);
                // set background color
                QPalette pal = box->palette();
                pal.setColor(box->backgroundRole(), QColor::fromRgb(150, 150, 150));
                box->setPalette(pal);
                
            } else if (label.size() > 0) {
                QGroupBox* group = new QGroupBox(this);
                group->setTitle(label.c_str());
                box = group;
                
            } else {
                // no label here we use simple widget
                layout->setMargin(0);
                box = new QWidget(this);
            }
            
            box->setLayout(layout);
            fGeneralLayout->addWidget(box);
            if (fGroupTooltip != "") {
                box->setToolTip(fGroupTooltip.c_str());
                fGroupTooltip = "";
            }
        } else {
            if (isTabContext()) {
                box = new QWidget();
                // set background color
                QPalette pal = box->palette();
                pal.setColor(box->backgroundRole(), QColor::fromRgb(150, 150, 150));
                box->setPalette(pal);
                
            } else  if (label.size()>0) {
                QGroupBox* group = new QGroupBox();
                group->setTitle(label.c_str());
                box = group;
                
            } else {
                // no label here we use simple widget
                layout->setMargin(0);
                box = new QWidget;
            }
            
            box->setLayout(layout);
            if (fGroupTooltip != "") {
                box->setToolTip(fGroupTooltip.c_str());
                fGroupTooltip = "";
            }
        }
        insert(label.c_str(), box);
        fGroupStack.push(box);
    }
    
	void openTab(const char* label)
	{
		QTabWidget* group;
        
        if (fGroupStack.empty()) {
            group = new QTabWidget(this);
            fGeneralLayout->addWidget(group);
        } else {
            group = new QTabWidget();
        }
        
		insert(label, group);
		fGroupStack.push(group);
	}
    
    public slots:
    
	void update()		
    {
        //std::cout << '.' << std::endl;
        //		updateAllZones();
		updateAllGuis();
	}
    
public:
    
    QTGUI(QWidget* parent) : QWidget(parent)
    {
        fGeneralLayout = new QVBoxLayout;
        setLayout(fGeneralLayout);
        QWidget::show();
        
        fMainWindow = NULL;        
        fTimer = 0;
    }

    QTGUI():QWidget()
    {
        fGeneralLayout = new QVBoxLayout;
        setLayout(fGeneralLayout);
        QWidget::show();

        fTimer = 0;

        fMainWindow = new QMainWindow;
        QScrollArea *sa = new QScrollArea( fMainWindow );
        
        sa->setWidgetResizable( true );
        sa->setWidget(this);
        
        fMainWindow->setCentralWidget(sa);
    }

	virtual ~QTGUI() 
    {
        delete fGeneralLayout;
    }

    QString styleSheet()
    {
        QString styleSheet("");
        QFile file(":/Grey.qss");
        
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            styleSheet = QLatin1String(file.readAll());
            file.close();
        }
        
        return styleSheet;
    }
    
    /**
     * Analyses the widget zone metadata declarations and takes
     * appropriate actions
     */
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* value)
    {
        MetaDataUI::declare(zone, key, value);
    }
    
#if defined(HTTPCTRL) && defined(QRCODECTRL)
    
    //
    // Returns the IP address of the machine (to be qrcoded)
    //
    QString extractIPnum()
    {
        QList<QHostAddress> ipAdresses = QNetworkInterface::allAddresses();
        QList<QHostAddress>::iterator it;
        QString localhost("localhost"); 
        
        for (it = ipAdresses.begin(); it != ipAdresses.end(); it++) {
            if ((*it).protocol() == QAbstractSocket::IPv4Protocol && (*it) != QHostAddress::LocalHost) {
                return it->toString();
            } else if((*it).protocol() == QAbstractSocket::IPv4Protocol && (*it) == QHostAddress::LocalHost) {
                localhost = it->toString();
            }
        }
        
        return localhost;
    }
    
    //
    // Used in HTTPD mode, display the QRCode of the URL of the application
    //
    void displayQRCode(int portnum)
    {
        QString url("http://");
        url += extractIPnum();
        url += ":";
        url += QString::number(portnum);
        displayQRCode(url, NULL);
    }
    
    void displayQRCode(const QString& url, QMainWindow* parent = NULL)
    {
        if (parent == NULL) {
            parent = new QMainWindow;
        }
        
        QWidget* centralWidget = new QWidget;
        parent->setCentralWidget(centralWidget);
        //    QTextEdit* httpdText = new QTextEdit(centralWidget);
        QTextBrowser* myBro = new QTextBrowser(centralWidget);
        
        //Construction of the flashcode
        const int padding = 5;
        QRcode* qrc = QRcode_encodeString(url.toLatin1().data(), 0, QR_ECLEVEL_H, QR_MODE_8, 1);
        
        //   qDebug() << "QRcode width = " << qrc->width;
        
        QRgb colors[2];
        colors[0] = qRgb(255, 255, 255); 	// 0 is white
        colors[1] = qRgb(0, 0, 0); 			// 1 is black
        
        // build the QRCode image
        QImage image(qrc->width+2*padding, qrc->width+2*padding, QImage::Format_RGB32);
        // clear the image
        for (int y = 0; y < qrc->width+2*padding; y++) {
            for (int x = 0; x < qrc->width+2*padding; x++) {
                image.setPixel(x, y, colors[0]);
            }
        }
        // copy the qrcode inside
        for (int y = 0; y < qrc->width; y++) {
            for (int x = 0; x < qrc->width; x++) {
                image.setPixel(x+padding, y+padding, colors[qrc->data[y*qrc->width+x]&1]);
            }
        }
        
        QImage big = image.scaledToWidth(qrc->width*8);
        QLabel* myLabel = new QLabel(centralWidget);
        
        fQrCode = QPixmap::fromImage(big);
        myLabel->setPixmap(fQrCode);
        
        //----Written Address
        
        QString sheet = QString::fromLatin1("a{ text-decoration: underline; color: white; font: Menlo; font-size: 14px }");
        //    myBro->document()->setDefaultStyleSheet(sheet);
        //    myBro->setStyleSheet("*{color: white; font: Menlo; font-size: 14px }");
        
        QString text("<br>Please connect to ");
        text += "<br><a href = " + url + ">"+ url+ "</a>";
        text += "<br>Or scan the QR code below";
        
        myBro->setOpenExternalLinks(true);
        myBro->setHtml(text);
        myBro->setAlignment(Qt::AlignCenter);
        myBro->setFixedWidth(qrc->width*8);
        //    myBro->setFixedHeight(myBro->minimumHeight());
        
        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(myBro, 0, 1);
        mainLayout->addWidget(myLabel, 1, 1);
        centralWidget->setLayout(mainLayout);
        centralWidget->show();
        centralWidget->adjustSize();
        parent->show();
    }
    
    bool toPNG(const QString& filename, QString& error)
    {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly)) {
            fQrCode.save(&file, "PNG");
            return true;
        } else {
            error = "Impossible to write file.";
            return false;
        }
    }
#endif
    
    virtual bool run()
    {
        if (fTimer == 0) {
            fTimer = new QTimer(this);
            QObject::connect(fTimer, SIGNAL(timeout()), this, SLOT(update()));
            fTimer->start(100);
        }

        if (fMainWindow) {
            fMainWindow->show();
        }
        return true;
    }
    
    virtual void stop()
	{
		if (fTimer != 0) {
            fTimer->stop();
            delete fTimer;
            fTimer = NULL;
		}
        
        GUI::stop();
	}
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // OPEN AND CLOSE GROUPS
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    virtual void openHorizontalBox(const char* label) 
    {
		openBox(label, new QHBoxLayout());
	}
    
	virtual void openVerticalBox(const char* label) 	
    {
        openBox(label, new QVBoxLayout());
    }
    
    virtual void openFrameBox(const char* )
    {}
    
	virtual void openTabBox(const char* label) 		
    { 
		openTab(label);
	}
    
	virtual void closeBox()
	{
		QWidget* group = fGroupStack.top();
		fGroupStack.pop();
		if (fGroupStack.empty()) {
            group->show();
            group->adjustSize();
        }
	}
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // ADD BUTTONS AND CHECKBOX
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone)
	{
		QAbstractButton* 	w = new QPushButton(label);
		w->setAttribute(Qt::WA_MacNoClickThrough);
		uiButton* 			c = new uiButton(this, zone, w);
        
		insert(label, w);
		QObject::connect(w, SIGNAL(pressed()), c, SLOT(pressed()));
		QObject::connect(w, SIGNAL(released()), c, SLOT(released()));
        checkForTooltip(zone, w);
        clearMetadata();
	}
    
    virtual void addToggleButton(const char*, FAUSTFLOAT*)
    {}
    
	virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
	{
		QCheckBox* w = new QCheckBox(label);
		uiCheckButton* c = new uiCheckButton(this, zone, w);
        
		insert(label, w);
		QObject::connect(w, SIGNAL(stateChanged(int)), c, SLOT(setState(int)));
        checkForTooltip(zone, w);
        clearMetadata();
	}
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // ADD NUMERICAL ENTRY
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    
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
        std::string suffix = " " + fUnit[zone];
        w->setSuffix(suffix.c_str());
        QObject::connect(w, SIGNAL(valueChanged(double)), c, SLOT(setValue(double)));
        if (label && label[0]) closeBox();
        checkForTooltip(zone, w);
        clearMetadata();
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
        uiNumEntry* c = new uiNumEntry(this, zone, w, init, min, max, step);
        insert(label, w);
        w->setButtonSymbols(QAbstractSpinBox::NoButtons);
        std::string suffix = " " + fUnit[zone];
        w->setSuffix(suffix.c_str());
        QObject::connect(w, SIGNAL(valueChanged(double)), c, SLOT(setValue(double)));
        if (label && label[0]) closeBox();
        checkForTooltip(zone, w);
        clearMetadata();
    }
    
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
    // ADD KNOBS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	virtual void addVerticalKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
	{
		openVerticalBox(label);
		QAbstractSlider* 	w = new QDial(); //qsynthKnob();
        uiSlider*	c = new uiSlider(this, zone, w, init, min, max, step, getScale(zone));
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
        clearMetadata();
	}
    
	virtual void addHorizontalKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
	{
		openHorizontalBox(label);
		QAbstractSlider* 	w = new QDial(); //new qsynthKnob();
        uiSlider*	c = new uiSlider(this, zone, w, init, min, max, step, getScale(zone));
		insert(label, w);
		w->setStyle(new qsynthDialVokiStyle());
		QObject::connect(w, SIGNAL(valueChanged(int)), c, SLOT(setValue(int)));
		addNumDisplay(0, zone, init, min, max, step);
		closeBox();
        checkForTooltip(zone, w);
        clearMetadata();
	}
    
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
    // ADD SLIDERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
	{
		if (isKnob(zone)) {
			addVerticalKnob(label, zone, init, min, max, step);
			return;
        } else if (isRadio(zone)) {
            addVerticalRadioButtons(label, zone, init, min, max, step, fRadioDescription[zone].c_str());
            return;
        } else if (isMenu(zone)) {
            addMenu(label, zone, init, min, max, step, fMenuDescription[zone].c_str());
            return;
        }
		openVerticalBox(label);
		QSlider* w = new QSlider(Qt::Vertical);
        w->setMinimumHeight(160);
        w->setMinimumWidth(34);
		//w->setTickPosition(QSlider::TicksBothSides);
 		uiSlider* c = new uiSlider(this, zone, w, init, min, max, step, getScale(zone));
		insert(label, w);
		QObject::connect(w, SIGNAL(valueChanged(int)), c, SLOT(setValue(int)));
		addNumDisplay(0, zone, init, min, max, step);
		closeBox();
        checkForTooltip(zone, w);
        clearMetadata();
	}
    
	virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
	{
		if (isKnob(zone)) {
			addHorizontalKnob(label, zone, init, min, max, step);
			return;
        } else if (isRadio(zone)) {
            addHorizontalRadioButtons(label, zone, init, min, max, step, fRadioDescription[zone].c_str());
            return;
        } else if (isMenu(zone)) {
            addMenu(label, zone, init, min, max, step, fMenuDescription[zone].c_str());
            return;
        }
		openHorizontalBox(label);
		QSlider* w = new QSlider(Qt::Horizontal);
        w->setMinimumHeight(34);
        w->setMinimumWidth(160);
		//w->setTickPosition(QSlider::TicksBothSides);
 		uiSlider* c = new uiSlider(this, zone, w, init, min, max, step, getScale(zone));
		insert(label, w);
		QObject::connect(w, SIGNAL(valueChanged(int)), c, SLOT(setValue(int)));
		addNumDisplay(0, zone, init, min, max, step);
		closeBox();
        checkForTooltip(zone, w);
        clearMetadata();
	}
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // ADD RADIO-BUTTONS AND MENUS
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    virtual void addVerticalRadioButtons(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                                         FAUSTFLOAT max, FAUSTFLOAT step, const char* mdescr)
    {
        uiRadioButtons* w = new uiRadioButtons(this,zone,label,init,min,max,step,true,mdescr,0);
        insert(label, w);
        checkForTooltip(zone, w);
        clearMetadata();
    }
    
    virtual void addHorizontalRadioButtons(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                                           FAUSTFLOAT max, FAUSTFLOAT step, const char* mdescr)
    {
        uiRadioButtons* w = new uiRadioButtons(this,zone,label,init,min,max,step,false,mdescr,0);
        insert(label, w);
        checkForTooltip(zone, w);
        clearMetadata();
    }
    
    virtual void addMenu(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                         FAUSTFLOAT max, FAUSTFLOAT step, const char* mdescr)
    {
        if (label && label[0]) openVerticalBox(label);
        uiMenu* w = new uiMenu(this,zone,label,init,min,max,step,mdescr,0);
        insert(label, w);
        checkForTooltip(zone, w);
        if (label && label[0]) closeBox();
        clearMetadata();
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // ADD BARGRAPHS
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    virtual void addHorizontalBargraph(const char* label , FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        openVerticalBox(label);
        if (isNumerical(zone)) {
			addNumDisplay(0, zone, min, min, max, (max-min)/100.0);
        } else {
            AbstractDisplay* bargraph;
            bool db = (fUnit[zone] == "dB");
            if (isLed(zone)) {
                if (db) {
                    bargraph = new dbLED(min, max);
                } else {
                    bargraph = new LED(min, max);
                }
            } else {
                if (db) {
                    bargraph = new dbHorizontalBargraph(min, max);
                } else {
                    bargraph = new linHorizontalBargraph(min, max);
                }
            }
            
            new uiBargraph(this, zone, bargraph, min, max);
			insert(label, bargraph);
            checkForTooltip(zone, bargraph);
        }
        closeBox();
        clearMetadata();
    }
    
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        openVerticalBox(label);
        if (isNumerical(zone)) {
			addNumDisplay(0, zone, min, min, max, (max-min)/100.0);
        } else {
            AbstractDisplay* bargraph;
            bool db = (fUnit[zone] == "dB");
            if (isLed(zone)) {
                if (db) {
                    bargraph = new dbLED(min, max);
                } else {
                    bargraph = new LED(min, max);
                }
            } else {
                if (db) {
                    bargraph = new dbVerticalBargraph(min, max);
                } else {
                    bargraph = new linVerticalBargraph(min, max);
                }
            }
            new uiBargraph(this, zone, bargraph, min, max);
			insert(label, bargraph);
			addNumDisplay(0, zone, min, min, max, (max-min)/100.0);
            checkForTooltip(zone, bargraph);
        }
        closeBox();
        clearMetadata();
    }
};

#endif

