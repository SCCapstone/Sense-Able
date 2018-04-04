/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../leddargui/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[47];
    char stringdata0[820];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "startCapture"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "stopCapture"
QT_MOC_LITERAL(4, 37, 11), // "startStream"
QT_MOC_LITERAL(5, 49, 10), // "stopStream"
QT_MOC_LITERAL(6, 60, 9), // "startRead"
QT_MOC_LITERAL(7, 70, 8), // "stopRead"
QT_MOC_LITERAL(8, 79, 11), // "startDetect"
QT_MOC_LITERAL(9, 91, 10), // "stopDetect"
QT_MOC_LITERAL(10, 102, 7), // "clicked"
QT_MOC_LITERAL(11, 110, 19), // "streamButtonClicked"
QT_MOC_LITERAL(12, 130, 12), // "passNotifier"
QT_MOC_LITERAL(13, 143, 14), // "vector<string>"
QT_MOC_LITERAL(14, 158, 10), // "setSigDist"
QT_MOC_LITERAL(15, 169, 20), // "setLeddarOrientation"
QT_MOC_LITERAL(16, 190, 25), // "on_readDataButton_clicked"
QT_MOC_LITERAL(17, 216, 7), // "checked"
QT_MOC_LITERAL(18, 224, 15), // "catchDataPoints"
QT_MOC_LITERAL(19, 240, 5), // "index"
QT_MOC_LITERAL(20, 246, 13), // "vector<float>"
QT_MOC_LITERAL(21, 260, 10), // "dataPoints"
QT_MOC_LITERAL(22, 271, 12), // "aOrientation"
QT_MOC_LITERAL(23, 284, 19), // "catchObjectDetected"
QT_MOC_LITERAL(24, 304, 6), // "string"
QT_MOC_LITERAL(25, 311, 10), // "objectName"
QT_MOC_LITERAL(26, 322, 23), // "on_streamButton_clicked"
QT_MOC_LITERAL(27, 346, 13), // "frameCaptured"
QT_MOC_LITERAL(28, 360, 8), // "cv::Mat*"
QT_MOC_LITERAL(29, 369, 5), // "frame"
QT_MOC_LITERAL(30, 375, 27), // "on_cancelButtonRead_clicked"
QT_MOC_LITERAL(31, 403, 29), // "on_settingsPageButton_clicked"
QT_MOC_LITERAL(32, 433, 28), // "on_actionMain_Menu_triggered"
QT_MOC_LITERAL(33, 462, 30), // "on_notificationsButton_clicked"
QT_MOC_LITERAL(34, 493, 29), // "on_readDataPageButton_clicked"
QT_MOC_LITERAL(35, 523, 21), // "on_backButton_clicked"
QT_MOC_LITERAL(36, 545, 23), // "on_backButtonGo_clicked"
QT_MOC_LITERAL(37, 569, 29), // "on_backButtonSettings_clicked"
QT_MOC_LITERAL(38, 599, 25), // "on_backButtonRead_clicked"
QT_MOC_LITERAL(39, 625, 23), // "on_changeCamera_clicked"
QT_MOC_LITERAL(40, 649, 23), // "on_changeOrient_clicked"
QT_MOC_LITERAL(41, 673, 21), // "on_QuitButton_clicked"
QT_MOC_LITERAL(42, 695, 15), // "on_Play_clicked"
QT_MOC_LITERAL(43, 711, 42), // "on_notificationDistanceSlider..."
QT_MOC_LITERAL(44, 754, 5), // "value"
QT_MOC_LITERAL(45, 760, 30), // "on_speechCheckBox_stateChanged"
QT_MOC_LITERAL(46, 791, 28) // "on_beepCheckBox_stateChanged"

    },
    "MainWindow\0startCapture\0\0stopCapture\0"
    "startStream\0stopStream\0startRead\0"
    "stopRead\0startDetect\0stopDetect\0clicked\0"
    "streamButtonClicked\0passNotifier\0"
    "vector<string>\0setSigDist\0"
    "setLeddarOrientation\0on_readDataButton_clicked\0"
    "checked\0catchDataPoints\0index\0"
    "vector<float>\0dataPoints\0aOrientation\0"
    "catchObjectDetected\0string\0objectName\0"
    "on_streamButton_clicked\0frameCaptured\0"
    "cv::Mat*\0frame\0on_cancelButtonRead_clicked\0"
    "on_settingsPageButton_clicked\0"
    "on_actionMain_Menu_triggered\0"
    "on_notificationsButton_clicked\0"
    "on_readDataPageButton_clicked\0"
    "on_backButton_clicked\0on_backButtonGo_clicked\0"
    "on_backButtonSettings_clicked\0"
    "on_backButtonRead_clicked\0"
    "on_changeCamera_clicked\0on_changeOrient_clicked\0"
    "on_QuitButton_clicked\0on_Play_clicked\0"
    "on_notificationDistanceSlider_valueChanged\0"
    "value\0on_speechCheckBox_stateChanged\0"
    "on_beepCheckBox_stateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  189,    2, 0x06 /* Public */,
       3,    0,  192,    2, 0x06 /* Public */,
       4,    0,  193,    2, 0x06 /* Public */,
       5,    0,  194,    2, 0x06 /* Public */,
       6,    1,  195,    2, 0x06 /* Public */,
       7,    0,  198,    2, 0x06 /* Public */,
       8,    0,  199,    2, 0x06 /* Public */,
       9,    0,  200,    2, 0x06 /* Public */,
      10,    0,  201,    2, 0x06 /* Public */,
      11,    0,  202,    2, 0x06 /* Public */,
      12,    1,  203,    2, 0x06 /* Public */,
      14,    1,  206,    2, 0x06 /* Public */,
      15,    1,  209,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,  212,    2, 0x08 /* Private */,
      16,    1,  213,    2, 0x08 /* Private */,
      18,    3,  216,    2, 0x08 /* Private */,
      23,    1,  223,    2, 0x08 /* Private */,
      26,    0,  226,    2, 0x08 /* Private */,
      27,    1,  227,    2, 0x08 /* Private */,
      30,    0,  230,    2, 0x08 /* Private */,
      31,    0,  231,    2, 0x08 /* Private */,
      32,    0,  232,    2, 0x08 /* Private */,
      33,    0,  233,    2, 0x08 /* Private */,
      34,    0,  234,    2, 0x08 /* Private */,
      35,    0,  235,    2, 0x08 /* Private */,
      36,    0,  236,    2, 0x08 /* Private */,
      37,    0,  237,    2, 0x08 /* Private */,
      38,    0,  238,    2, 0x08 /* Private */,
      39,    0,  239,    2, 0x08 /* Private */,
      40,    0,  240,    2, 0x08 /* Private */,
      41,    0,  241,    2, 0x08 /* Private */,
      42,    0,  242,    2, 0x08 /* Private */,
      43,    1,  243,    2, 0x08 /* Private */,
      45,    0,  246,    2, 0x08 /* Private */,
      46,    0,  247,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 20, QMetaType::Bool,   19,   21,   22,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startCapture((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->stopCapture(); break;
        case 2: _t->startStream(); break;
        case 3: _t->stopStream(); break;
        case 4: _t->startRead((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->stopRead(); break;
        case 6: _t->startDetect(); break;
        case 7: _t->stopDetect(); break;
        case 8: _t->clicked(); break;
        case 9: _t->streamButtonClicked(); break;
        case 10: _t->passNotifier((*reinterpret_cast< vector<string>(*)>(_a[1]))); break;
        case 11: _t->setSigDist((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->setLeddarOrientation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_readDataButton_clicked(); break;
        case 14: _t->on_readDataButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->catchDataPoints((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< vector<float>(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 16: _t->catchObjectDetected((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 17: _t->on_streamButton_clicked(); break;
        case 18: _t->frameCaptured((*reinterpret_cast< cv::Mat*(*)>(_a[1]))); break;
        case 19: _t->on_cancelButtonRead_clicked(); break;
        case 20: _t->on_settingsPageButton_clicked(); break;
        case 21: _t->on_actionMain_Menu_triggered(); break;
        case 22: _t->on_notificationsButton_clicked(); break;
        case 23: _t->on_readDataPageButton_clicked(); break;
        case 24: _t->on_backButton_clicked(); break;
        case 25: _t->on_backButtonGo_clicked(); break;
        case 26: _t->on_backButtonSettings_clicked(); break;
        case 27: _t->on_backButtonRead_clicked(); break;
        case 28: _t->on_changeCamera_clicked(); break;
        case 29: _t->on_changeOrient_clicked(); break;
        case 30: _t->on_QuitButton_clicked(); break;
        case 31: _t->on_Play_clicked(); break;
        case 32: _t->on_notificationDistanceSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->on_speechCheckBox_stateChanged(); break;
        case 34: _t->on_beepCheckBox_stateChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startCapture)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stopCapture)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startStream)) {
                *result = 2;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stopStream)) {
                *result = 3;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startRead)) {
                *result = 4;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stopRead)) {
                *result = 5;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startDetect)) {
                *result = 6;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stopDetect)) {
                *result = 7;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::clicked)) {
                *result = 8;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::streamButtonClicked)) {
                *result = 9;
            }
        }
        {
            typedef void (MainWindow::*_t)(vector<string> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::passNotifier)) {
                *result = 10;
            }
        }
        {
            typedef void (MainWindow::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::setSigDist)) {
                *result = 11;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::setLeddarOrientation)) {
                *result = 12;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 35)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 35;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::startCapture(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::stopCapture()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void MainWindow::startStream()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void MainWindow::stopStream()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void MainWindow::startRead(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::stopRead()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void MainWindow::startDetect()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void MainWindow::stopDetect()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void MainWindow::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void MainWindow::streamButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 9, Q_NULLPTR);
}

// SIGNAL 10
void MainWindow::passNotifier(vector<string> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MainWindow::setSigDist(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MainWindow::setLeddarOrientation(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_END_MOC_NAMESPACE
