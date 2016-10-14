/****************************************************************************
** Meta object code from reading C++ file 'mapitemwidget.h'
**
** Created: Tue Sep 21 09:56:36 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mapitemwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mapitemwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapItemWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      86,   15,   14,   14, 0x0a,
     151,  134,   14,   14, 0x0a,
     205,  185,   14,   14, 0x0a,
     243,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MapItemWidget[] = {
    "MapItemWidget\0\0"
    "sourceParent,sourceStart,sourceEnd,destinationParent,destinationColumn\0"
    "itemsMoved(QModelIndex,int,int,QModelIndex,int)\0"
    "parent,start,end\0itemsRemoved(QModelIndex,int,int)\0"
    "topLeft,bottomRight\0"
    "itemsChanged(QModelIndex,QModelIndex)\0"
    "itemsReset()\0"
};

const QMetaObject MapItemWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MapItemWidget,
      qt_meta_data_MapItemWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapItemWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapItemWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapItemWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapItemWidget))
        return static_cast<void*>(const_cast< MapItemWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MapItemWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itemsMoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QModelIndex(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 1: itemsRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: itemsChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 3: itemsReset(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
