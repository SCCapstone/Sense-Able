/****************************************************************************
** Meta object code from reading C++ file 'leddarmain.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../leddargui/leddarmain.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'leddarmain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LeddarStream_t {
    QByteArrayData data[16];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LeddarStream_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LeddarStream_t qt_meta_stringdata_LeddarStream = {
    {
QT_MOC_LITERAL(0, 0, 12), // "LeddarStream"
QT_MOC_LITERAL(1, 13, 8), // "finished"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 14), // "sendDataPoints"
QT_MOC_LITERAL(4, 38, 5), // "index"
QT_MOC_LITERAL(5, 44, 13), // "vector<float>"
QT_MOC_LITERAL(6, 58, 10), // "dataPoints"
QT_MOC_LITERAL(7, 69, 7), // "running"
QT_MOC_LITERAL(8, 77, 7), // "stopped"
QT_MOC_LITERAL(9, 85, 11), // "StartReplay"
QT_MOC_LITERAL(10, 97, 8), // "fileName"
QT_MOC_LITERAL(11, 106, 10), // "StopReplay"
QT_MOC_LITERAL(12, 117, 11), // "StartStream"
QT_MOC_LITERAL(13, 129, 10), // "StopStream"
QT_MOC_LITERAL(14, 140, 8), // "doReplay"
QT_MOC_LITERAL(15, 149, 8) // "doStream"

    },
    "LeddarStream\0finished\0\0sendDataPoints\0"
    "index\0vector<float>\0dataPoints\0running\0"
    "stopped\0StartReplay\0fileName\0StopReplay\0"
    "StartStream\0StopStream\0doReplay\0"
    "doStream"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LeddarStream[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    2,   65,    2, 0x06 /* Public */,
       7,    0,   70,    2, 0x06 /* Public */,
       8,    0,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   72,    2, 0x0a /* Public */,
      11,    0,   75,    2, 0x0a /* Public */,
      12,    0,   76,    2, 0x0a /* Public */,
      13,    0,   77,    2, 0x0a /* Public */,
      14,    1,   78,    2, 0x08 /* Private */,
      15,    0,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    4,    6,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,

       0        // eod
};

void LeddarStream::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LeddarStream *_t = static_cast<LeddarStream *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->sendDataPoints((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< vector<float>(*)>(_a[2]))); break;
        case 2: _t->running(); break;
        case 3: _t->stopped(); break;
        case 4: _t->StartReplay((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->StopReplay(); break;
        case 6: _t->StartStream(); break;
        case 7: _t->StopStream(); break;
        case 8: _t->doReplay((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->doStream(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LeddarStream::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LeddarStream::finished)) {
                *result = 0;
            }
        }
        {
            typedef void (LeddarStream::*_t)(int , vector<float> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LeddarStream::sendDataPoints)) {
                *result = 1;
            }
        }
        {
            typedef void (LeddarStream::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LeddarStream::running)) {
                *result = 2;
            }
        }
        {
            typedef void (LeddarStream::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LeddarStream::stopped)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject LeddarStream::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LeddarStream.data,
      qt_meta_data_LeddarStream,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LeddarStream::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LeddarStream::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LeddarStream.stringdata0))
        return static_cast<void*>(const_cast< LeddarStream*>(this));
    return QObject::qt_metacast(_clname);
}

int LeddarStream::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void LeddarStream::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void LeddarStream::sendDataPoints(int _t1, vector<float> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LeddarStream::running()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void LeddarStream::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
