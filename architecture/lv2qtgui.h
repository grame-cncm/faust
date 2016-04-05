#ifndef LV2QTGUI_H
#define LV2QTGUI_H

#include <QObject>
#include <faust/gui/faustqt.h>

class LV2PluginUI;
#ifdef OSCCTRL
class OSCUI;
#endif
#ifdef HTTPCTRL
class httpdUI;
#endif

struct ERect {
  short top, left, bottom, right;
};

class LV2QtGUI : public QObject {
  Q_OBJECT

  QScrollArea* widget;
  void *uidsp;
  QTGUI* qtinterface;
#ifdef OSCCTRL
  OSCUI* oscinterface;
#endif
#ifdef HTTPCTRL
  httpdUI *httpdinterface;
#endif

 public:
  LV2QtGUI(LV2PluginUI* plugui);
  ~LV2QtGUI();
  LV2PluginUI* plugui;

  // vector of all GUI controls, indexed by parameter indices
  QVector< QList<QObject*> > controls;
  // vector of all passive controls needing continuous update (this isn't used
  // right now, as all live updates are done through the controls vector, but
  // we keep it around for debugging purposes)
  QVector<QObject*> passive_controls;

  virtual QWidget* open();
  virtual void close();

  void updateQTGUI(QObject* object, float value);
  void updatePassiveControl(QObject* object, float value);

 protected:
  ERect rectangle;
  float voices_zone, tuning_zone;

 public slots:
  void updateUI_buttonPressed();
  void updateUI_buttonReleased();
  void updateUI_checkBox();
  void updateUI();

};

#endif // LV2QTGUI_H
