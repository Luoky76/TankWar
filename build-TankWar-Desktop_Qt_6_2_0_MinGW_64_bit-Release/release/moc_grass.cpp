/****************************************************************************
** Meta object code from reading C++ file 'grass.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../TankWar/blockKinds/grass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'grass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Grass_t {
    const uint offsetsAndSize[2];
    char stringdata0[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Grass_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Grass_t qt_meta_stringdata_Grass = {
    {
QT_MOC_LITERAL(0, 5) // "Grass"

    },
    "Grass"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Grass[] = {

 // content:
      10,       // revision
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

void Grass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject Grass::staticMetaObject = { {
    QMetaObject::SuperData::link<GameBlock::staticMetaObject>(),
    qt_meta_stringdata_Grass.offsetsAndSize,
    qt_meta_data_Grass,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Grass_t
, QtPrivate::TypeAndForceComplete<Grass, std::true_type>



>,
    nullptr
} };


const QMetaObject *Grass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Grass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Grass.stringdata0))
        return static_cast<void*>(this);
    return GameBlock::qt_metacast(_clname);
}

int Grass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GameBlock::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
