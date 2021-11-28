/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2014-2016 Albert Graef <aggraef@gmail.com>
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as
 published by the Free Software Foundation; either version 3 of the
 License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with the GNU C Library; if not, write to the Free
 Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 02111-1307 USA.
 ************************************************************************
 ************************************************************************/

#ifndef FAUSTVSTQT_H
#define FAUSTVSTQT_H

#include <QObject>
#include <aeffeditor.h>
#include <faust/gui/QTUI.h>

class dsp;
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
  dsp* uidsp;
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
  virtual bool getRect(ERect** rect);
  // idle(): event processing is done here
  virtual void idle();
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
