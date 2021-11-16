/****************************************************************************
** Meta object code from reading C++ file 'gameblock.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../TankWar/blockKinds/gameblock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameblock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameBlock_t {
    const uint offsetsAndSize[10];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_GameBlock_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_GameBlock_t qt_meta_stringdata_GameBlock = {
    {
QT_MOC_LITERAL(0, 9), // "GameBlock"
QT_MOC_LITERAL(10, 8), // "newBlock"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 10), // "GameBlock*"
QT_MOC_LITERAL(31, 9) // "gameBlock"

    },
    "GameBlock\0newBlock\0\0GameBlock*\0gameBlock"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameBlock[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void GameBlock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameBlock *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newBlock((*reinterpret_cast< GameBlock*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< GameBlock* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameBlock::*)(GameBlock * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameBlock::newBlock)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject GameBlock::staticMetaObject = { {
    QMetaObject::SuperData::link<VisibleObject::staticMetaObject>(),
    qt_meta_stringdata_GameBlock.offsetsAndSize,
    qt_meta_data_GameBlock,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GameBlock_t
, QtPrivate::TypeAndForceComplete<GameBlock, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<GameBlock *, std::false_type>



>,
    nullptr
} };


const QMetaObject *GameBlock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameBlock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameBlock.stringdata0))
        return static_cast<void*>(this);
    return VisibleObject::qt_metacast(_clname);
}

int GameBlock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VisibleObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void GameBlock::newBlock(GameBlock * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
