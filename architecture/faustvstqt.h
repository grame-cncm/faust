#ifndef FAUSTVSTQT_H
#define FAUSTVSTQT_H

#include <QObject>
#include <aeffeditor.h>
#include <faust/gui/faustqt.h>

class VSTWrapper;
#ifdef OSCCTRL
class OSCUI;
#endif
#ifdef HTTPCTRL
class httpdUI;
#endif

class VSTQtGUI : public QObject, public AEffEditor {
  Q_OBJECT

  VSTWrapper* effect;
  QScrollArea* widget;
  void *uidsp;
#ifdef OSCCTRL
  OSCUI* oscinterface;
#endif
#ifdef HTTPCTRL
  httpdUI *httpdinterface;
#endif
  QTGUI* qtinterface;

  // vector of all GUI controls, indexed by parameter indices
  QVector< QList<QObject*> > controls;
  // cached control values, so that we only update the GUI when needed
  float *control_values;
  // vector of all passive controls needing continuous update (this isn't used
  // right now, as all live updates are done through the controls vector, but
  // we keep it around for debugging purposes)
  QVector<QObject*> passive_controls;

public:
  VSTQtGUI(VSTWrapper* effect);
  ~VSTQtGUI();

  // open(): opens the GUI
  virtual bool open(void *ptr);
  // getRect(): determines the size of the GUI
  virtual bool getRect (ERect** rect);
  // idle(): event processing is done here
  virtual void idle ();
  // close(): closes the GUI
  virtual void close();

  float valueToVST(double value, double minimum, double maximum);
  void updateQTGUI(QObject* object, float value, bool init = true);
  void updatePassiveControl(QObject* object, float value);

protected:
  ERect rectangle;
  float voices_zone, tuning_zone;

public slots:
  void updateVST_buttonPressed();
  void updateVST_buttonReleased();
  void updateVST_checkBox();
  void updateVST();

};

#endif // FAUSTVSTQT_H
