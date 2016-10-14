/****************************************************************************
** Meta object code from reading C++ file 'maincontroller.h'
**
** Created: Tue Sep 21 09:56:35 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "maincontroller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maincontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainController[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      24,   15,   15,   15, 0x0a,
      56,   48,   15,   15, 0x0a,
      77,   15,   15,   15, 0x0a,
     108,   15,   15,   15, 0x0a,
     127,   15,   15,   15, 0x0a,
     143,   15,   15,   15, 0x0a,
     160,   15,   15,   15, 0x0a,
     176,   15,   15,   15, 0x0a,
     193,   15,   15,   15, 0x0a,
     227,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainController[] = {
    "MainController\0\0fetch()\0handleRequestFinished()\0"
    "message\0handleError(QString)\0"
    "handleItemClicked(QModelIndex)\0"
    "handleItemClosed()\0handleLastDay()\0"
    "handleLastWeek()\0handleShowMap()\0"
    "handleShowList()\0positionUpdated(QGeoPositionInfo)\0"
    "addProxyObjects()\0"
};

const QMetaObject MainController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MainController,
      qt_meta_data_MainController, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainController::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainController))
        return static_cast<void*>(const_cast< MainController*>(this));
    return QObject::qt_metacast(_clname);
}

int MainController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: fetch(); break;
        case 1: handleRequestFinished(); break;
        case 2: handleError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: handleItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: handleItemClosed(); break;
        case 5: handleLastDay(); break;
        case 6: handleLastWeek(); break;
        case 7: handleShowMap(); break;
        case 8: handleShowList(); break;
        case 9: positionUpdated((*reinterpret_cast< const QGeoPositionInfo(*)>(_a[1]))); break;
        case 10: addProxyObjects(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
