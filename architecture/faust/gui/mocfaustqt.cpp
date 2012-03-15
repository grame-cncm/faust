/****************************************************************************
** Meta object code from reading C++ file 'faustqt.h'
**
** Created: Fri Feb 25 08:07:38 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "faustqt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'faustqt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_uiButton[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      20,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_uiButton[] = {
    "uiButton\0\0pressed()\0released()\0"
};

const QMetaObject uiButton::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_uiButton,
      qt_meta_data_uiButton, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &uiButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *uiButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *uiButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_uiButton))
        return static_cast<void*>(const_cast< uiButton*>(this));
    if (!strcmp(_clname, "uiItem"))
        return static_cast< uiItem*>(const_cast< uiButton*>(this));
    return QObject::qt_metacast(_clname);
}

int uiButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pressed(); break;
        case 1: released(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_uiCheckButton[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_uiCheckButton[] = {
    "uiCheckButton\0\0v\0setState(int)\0"
};

const QMetaObject uiCheckButton::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_uiCheckButton,
      qt_meta_data_uiCheckButton, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &uiCheckButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *uiCheckButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *uiCheckButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_uiCheckButton))
        return static_cast<void*>(const_cast< uiCheckButton*>(this));
    if (!strcmp(_clname, "uiItem"))
        return static_cast< uiItem*>(const_cast< uiCheckButton*>(this));
    return QObject::qt_metacast(_clname);
}

int uiCheckButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setState((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_uiSlider[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   10,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_uiSlider[] = {
    "uiSlider\0\0v\0setValue(int)\0"
};

const QMetaObject uiSlider::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_uiSlider,
      qt_meta_data_uiSlider, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &uiSlider::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *uiSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *uiSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_uiSlider))
        return static_cast<void*>(const_cast< uiSlider*>(this));
    if (!strcmp(_clname, "uiItem"))
        return static_cast< uiItem*>(const_cast< uiSlider*>(this));
    return QObject::qt_metacast(_clname);
}

int uiSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_uiKnob[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    8,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_uiKnob[] = {
    "uiKnob\0\0v\0setValue(int)\0"
};

const QMetaObject uiKnob::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_uiKnob,
      qt_meta_data_uiKnob, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &uiKnob::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *uiKnob::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *uiKnob::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_uiKnob))
        return static_cast<void*>(const_cast< uiKnob*>(this));
    if (!strcmp(_clname, "uiItem"))
        return static_cast< uiItem*>(const_cast< uiKnob*>(this));
    return QObject::qt_metacast(_clname);
}

int uiKnob::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_uiBargraph[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_uiBargraph[] = {
    "uiBargraph\0"
};

const QMetaObject uiBargraph::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_uiBargraph,
      qt_meta_data_uiBargraph, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &uiBargraph::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *uiBargraph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *uiBargraph::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_uiBargraph))
        return static_cast<void*>(const_cast< uiBargraph*>(this));
    if (!strcmp(_clname, "uiItem"))
        return static_cast< uiItem*>(const_cast< uiBargraph*>(this));
    return QObject::qt_metacast(_clname);
}

int uiBargraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_uiBargraph2[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_uiBargraph2[] = {
    "uiBargraph2\0"
};

const QMetaObject uiBargraph2::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_uiBargraph2,
      qt_meta_data_uiBargraph2, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &uiBargraph2::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *uiBargraph2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *uiBargraph2::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_uiBargraph2))
        return static_cast<void*>(const_cast< uiBargraph2*>(this));
    if (!strcmp(_clname, "uiItem"))
        return static_cast< uiItem*>(const_cast< uiBargraph2*>(this));
    return QObject::qt_metacast(_clname);
}

int uiBargraph2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_uiNumEntry[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_uiNumEntry[] = {
    "uiNumEntry\0\0v\0setValue(double)\0"
};

const QMetaObject uiNumEntry::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_uiNumEntry,
      qt_meta_data_uiNumEntry, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &uiNumEntry::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *uiNumEntry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *uiNumEntry::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_uiNumEntry))
        return static_cast<void*>(const_cast< uiNumEntry*>(this));
    if (!strcmp(_clname, "uiItem"))
        return static_cast< uiItem*>(const_cast< uiNumEntry*>(this));
    return QObject::qt_metacast(_clname);
}

int uiNumEntry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_QTGUI[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QTGUI[] = {
    "QTGUI\0\0update()\0"
};

const QMetaObject QTGUI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QTGUI,
      qt_meta_data_QTGUI, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QTGUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QTGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QTGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTGUI))
        return static_cast<void*>(const_cast< QTGUI*>(this));
    if (!strcmp(_clname, "UI"))
        return static_cast< UI*>(const_cast< QTGUI*>(this));
    return QObject::qt_metacast(_clname);
}

int QTGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: update(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
