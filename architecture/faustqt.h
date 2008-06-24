#include <stack>
#include <list>
#include <map>
#include <iostream>
#include <fstream>

#include <math.h>

#include <QObject>
#include <QTimer>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QSlider>
#include <QGroupBox>
#include <QTabWidget>
#include <QStyle>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QDial>
#include <QProgressBar>


using namespace std;




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
	
	void saveState(char* filename)	
	{
		ofstream f(filename);
		
		for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++) { 
			f << *(i->first) << ' ';
		} 
		
		f << endl;
		f.close();
	}

	// -- recallState(filename) : load the value of every zone from a file
	
	void recallState(char* filename)	
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
	
	virtual void addButton(char*, float*) = 0;
	virtual void addCheckButton(char*, float*) = 0;
	virtual void addVerticalSlider(char*, float*, float, float, float, float) = 0;
	virtual void addHorizontalSlider(char*, float*, float, float, float, float) = 0;
	virtual void addNumEntry(char*, float*, float, float, float, float) = 0;
	
	// -- passive widgets
	
	virtual void addHorizontalBargraph(char*, float*, float, float) = 0;
	virtual void addVerticalBargraph(char*, float*, float, float) = 0;
	
	// -- widget's layouts
	
	virtual void openTabBox(char*) = 0;
	virtual void openHorizontalBox(char*) = 0;
	virtual void openVerticalBox(char*) = 0;
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


class uiBargraph : public uiItem
{
    Q_OBJECT

	int		faust2qt(float x) 	{ return int(0.5 + (x-fMin)/(fMax-fMin)*fStep); }
			
 public :
	QProgressBar* 	fBar;
	float			fMin;
	float			fMax;
	int				fStep;

	uiBargraph (UI* ui, float* zone, QProgressBar* bar, float lo, float hi) 
		: uiItem(ui, zone), fBar(bar), fMin(lo), fMax(hi), fStep(1024) 
	{
		fBar->setRange(0, fStep);
		fBar->setValue(0);
		*fZone = 0;
	}
	
	virtual void reflectZone() 	
	{ 
		float 	v = *fZone;
		fCache = v; 
		fBar->setValue(faust2qt(v));
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

	bool isTabContext()
	{
		return fGroupStack.empty() || (!fGroupStack.empty()) && (dynamic_cast<QTabWidget*>(fGroupStack.top()) != 0);
	}

	void insert(char* label, QWidget* widget)
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

	void openBox(char* label, QLayout* layout) 
	{
		layout->setMargin(5);
		QWidget* box;
		if (isTabContext()) {
			box = new QWidget();
		} else  if (label && label[0]) {
			QGroupBox* group = new QGroupBox();
			group->setTitle(label);
			box = group;
		} else {
			// no label here we use simple widget
			layout->setMargin(0);
			box = new QWidget();
		}
		box->setLayout(layout);
			
		insert(label, box);
		fGroupStack.push(box);
	}

	void openTab(char* label) 
	{
		QTabWidget* group = new QTabWidget();
		if (fStyle) group->setStyle(fStyle);
		insert(label, group);
		fGroupStack.push(group);
	}

	
  public slots :
	void update()		{ 
		updateAllZones();
	}	 

  public:

	QTGUI(int argc, char *argv[], QStyle* style = 0) : fAppl(argc, argv), fTimer(0), fStyle(style){}
	
	virtual ~QTGUI() {}

	virtual void run()
	{
		if (fTimer == 0) {
			fTimer = new QTimer(this);
     		QObject::connect(fTimer, SIGNAL(timeout()), this, SLOT(update()));
     		fTimer->start(50);
		}
		fAppl.exec();
		stop();

	}


	// ------------------------- Groups -----------------------------------

	virtual void openHorizontalBox(char* label) { openBox(label, new QHBoxLayout()); }

	virtual void openVerticalBox(char* label) 	{ openBox(label, new QVBoxLayout()); }

	virtual void openTabBox(char* label) 		{ openTab(label); }

	virtual void closeBox()
	{
		QWidget* group = fGroupStack.top(); 
		fGroupStack.pop();
		if (fGroupStack.empty()) { group->show(); }
	}

	// ------------------------- active widgets -----------------------------------

	virtual void addButton(char* label , float* zone)
	{
		QAbstractButton* 	w = new QPushButton(label);
		uiButton* 			c = new uiButton(this, zone, w);

		insert(label, w);	
		QObject::connect(w, SIGNAL(pressed()), c, SLOT(pressed()));
		QObject::connect(w, SIGNAL(released()), c, SLOT(released()));
	}

	virtual void addCheckButton(char* label , float* zone)
	{
		QCheckBox* 	w = new QCheckBox(label);
		uiCheckButton* 	c = new uiCheckButton(this, zone, w);

		insert(label, w);	
		QObject::connect(w, SIGNAL(stateChanged(int)), c, SLOT(setState(int)));
	}

	virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step)
	{
		//insert(label, new QDoubleSpinBox());
		if (label && label[0]) openVerticalBox(label);
		QDoubleSpinBox* 	w = new QDoubleSpinBox();
		uiNumEntry*			c = new uiNumEntry(this, zone, w, init, min, max, step);
		insert(label, w);
		QObject::connect(w, SIGNAL(valueChanged(double)), c, SLOT(setValue(double)));
		if (label && label[0]) closeBox();
	}

	virtual void addVerticalSlider(char* label , float* zone, float init, float min, float max, float step)
	{
		openVerticalBox(label);
//		addNumEntry(0, zone, init, min, max, step);
		QSlider* 	w = new QSlider(Qt::Vertical);
		w->setTickPosition(QSlider::TicksBothSides);
		uiSlider*	c = new uiSlider(this, zone, w, init, min, max, step);
		insert(label, w);
		QObject::connect(w, SIGNAL(valueChanged(int)), c, SLOT(setValue(int)));
		addNumEntry(0, zone, init, min, max, step);
		closeBox();
	}

	virtual void addHorizontalSlider(char* label , float* zone, float init, float min, float max, float step)
	{
		openHorizontalBox(label);
		QSlider* 	w = new QSlider(Qt::Horizontal);
		w->setTickPosition(QSlider::TicksBothSides);
		uiSlider*	c = new uiSlider(this, zone, w, init, min, max, step);
		insert(label, w);
		QObject::connect(w, SIGNAL(valueChanged(int)), c, SLOT(setValue(int)));
		addNumEntry(0, zone, init, min, max, step);
		closeBox();
	}


	// ------------------------- passive widgets -----------------------------------

	virtual void addHorizontalBargraph(char* label , float* zone, float min, float max)
	{
		openHorizontalBox(label);
		QProgressBar* bargraph = new QProgressBar();
		bargraph->setMinimumSize(64,8);
		bargraph->setTextVisible(false);
		bargraph->setOrientation(Qt::Horizontal);
		new uiBargraph(this, zone, bargraph, min, max);
		insert(label, bargraph);
		closeBox();
	}

	virtual void addVerticalBargraph(char* label , float* zone, float min, float max)
	{
		openVerticalBox(label);
		QProgressBar* bargraph = new QProgressBar();
		bargraph->setOrientation(Qt::Vertical);
		bargraph->setMinimumSize(8,64);
		bargraph->setTextVisible(false);
		new uiBargraph(this, zone, bargraph, min, max);
		insert(label, bargraph);
		closeBox();
	}



}; 
