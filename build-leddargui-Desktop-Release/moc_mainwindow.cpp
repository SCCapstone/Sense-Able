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
    QByteArrayData data[53];
    char stringdata0[988];
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
QT_MOC_LITERAL(3, 25, 6), // "string"
QT_MOC_LITERAL(4, 32, 20), // "emitStartVideoRecord"
QT_MOC_LITERAL(5, 53, 11), // "stopCapture"
QT_MOC_LITERAL(6, 65, 11), // "startStream"
QT_MOC_LITERAL(7, 77, 10), // "stopStream"
QT_MOC_LITERAL(8, 88, 9), // "startRead"
QT_MOC_LITERAL(9, 98, 8), // "stopRead"
QT_MOC_LITERAL(10, 107, 21), // "emitStartLeddarRecord"
QT_MOC_LITERAL(11, 129, 20), // "setLeddarOrientation"
QT_MOC_LITERAL(12, 150, 11), // "startDetect"
QT_MOC_LITERAL(13, 162, 10), // "stopDetect"
QT_MOC_LITERAL(14, 173, 10), // "setSigDist"
QT_MOC_LITERAL(15, 184, 12), // "passNotifier"
QT_MOC_LITERAL(16, 197, 14), // "vector<string>"
QT_MOC_LITERAL(17, 212, 7), // "clicked"
QT_MOC_LITERAL(18, 220, 19), // "streamButtonClicked"
QT_MOC_LITERAL(19, 240, 25), // "on_readDataButton_clicked"
QT_MOC_LITERAL(20, 266, 7), // "checked"
QT_MOC_LITERAL(21, 274, 15), // "catchDataPoints"
QT_MOC_LITERAL(22, 290, 5), // "index"
QT_MOC_LITERAL(23, 296, 13), // "vector<float>"
QT_MOC_LITERAL(24, 310, 10), // "dataPoints"
QT_MOC_LITERAL(25, 321, 12), // "aOrientation"
QT_MOC_LITERAL(26, 334, 19), // "catchDetectedObject"
QT_MOC_LITERAL(27, 354, 6), // "object"
QT_MOC_LITERAL(28, 361, 23), // "on_streamButton_clicked"
QT_MOC_LITERAL(29, 385, 13), // "frameCaptured"
QT_MOC_LITERAL(30, 399, 8), // "cv::Mat*"
QT_MOC_LITERAL(31, 408, 5), // "frame"
QT_MOC_LITERAL(32, 414, 27), // "on_cancelButtonRead_clicked"
QT_MOC_LITERAL(33, 442, 29), // "on_settingsPageButton_clicked"
QT_MOC_LITERAL(34, 472, 28), // "on_actionMain_Menu_triggered"
QT_MOC_LITERAL(35, 501, 30), // "on_notificationsButton_clicked"
QT_MOC_LITERAL(36, 532, 29), // "on_readDataPageButton_clicked"
QT_MOC_LITERAL(37, 562, 21), // "on_backButton_clicked"
QT_MOC_LITERAL(38, 584, 23), // "on_backButtonGo_clicked"
QT_MOC_LITERAL(39, 608, 29), // "on_backButtonSettings_clicked"
QT_MOC_LITERAL(40, 638, 25), // "on_backButtonRead_clicked"
QT_MOC_LITERAL(41, 664, 23), // "on_changeCamera_clicked"
QT_MOC_LITERAL(42, 688, 23), // "on_changeOrient_clicked"
QT_MOC_LITERAL(43, 712, 21), // "on_QuitButton_clicked"
QT_MOC_LITERAL(44, 734, 15), // "on_Play_clicked"
QT_MOC_LITERAL(45, 750, 42), // "on_notificationDistanceSlider..."
QT_MOC_LITERAL(46, 793, 5), // "value"
QT_MOC_LITERAL(47, 799, 30), // "on_speechCheckBox_stateChanged"
QT_MOC_LITERAL(48, 830, 28), // "on_beepCheckBox_stateChanged"
QT_MOC_LITERAL(49, 859, 33), // "on_go_ReadFromFile_button_cli..."
QT_MOC_LITERAL(50, 893, 37), // "on_go_StreamFromDevice_button..."
QT_MOC_LITERAL(51, 931, 27), // "on_go_Record_button_clicked"
QT_MOC_LITERAL(52, 959, 28) // "on_go_StopAll_button_clicked"

    },
    "MainWindow\0startCapture\0\0string\0"
    "emitStartVideoRecord\0stopCapture\0"
    "startStream\0stopStream\0startRead\0"
    "stopRead\0emitStartLeddarRecord\0"
    "setLeddarOrientation\0startDetect\0"
    "stopDetect\0setSigDist\0passNotifier\0"
    "vector<string>\0clicked\0streamButtonClicked\0"
    "on_readDataButton_clicked\0checked\0"
    "catchDataPoints\0index\0vector<float>\0"
    "dataPoints\0aOrientation\0catchDetectedObject\0"
    "object\0on_streamButton_clicked\0"
    "frameCaptured\0cv::Mat*\0frame\0"
    "on_cancelButtonRead_clicked\0"
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
    "on_beepCheckBox_stateChanged\0"
    "on_go_ReadFromFile_button_clicked\0"
    "on_go_StreamFromDevice_button_clicked\0"
    "on_go_Record_button_clicked\0"
    "on_go_StopAll_button_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      41,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  219,    2, 0x06 /* Public */,
       4,    2,  222,    2, 0x06 /* Public */,
       5,    0,  227,    2, 0x06 /* Public */,
       6,    0,  228,    2, 0x06 /* Public */,
       7,    0,  229,    2, 0x06 /* Public */,
       8,    1,  230,    2, 0x06 /* Public */,
       9,    0,  233,    2, 0x06 /* Public */,
      10,    1,  234,    2, 0x06 /* Public */,
      11,    1,  237,    2, 0x06 /* Public */,
      12,    0,  240,    2, 0x06 /* Public */,
      13,    0,  241,    2, 0x06 /* Public */,
      14,    1,  242,    2, 0x06 /* Public */,
      15,    1,  245,    2, 0x06 /* Public */,
      17,    0,  248,    2, 0x06 /* Public */,
      18,    0,  249,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    0,  250,    2, 0x08 /* Private */,
      19,    1,  251,    2, 0x08 /* Private */,
      21,    3,  254,    2, 0x08 /* Private */,
      26,    1,  261,    2, 0x08 /* Private */,
      28,    0,  264,    2, 0x08 /* Private */,
      29,    1,  265,    2, 0x08 /* Private */,
      32,    0,  268,    2, 0x08 /* Private */,
      33,    0,  269,    2, 0x08 /* Private */,
      34,    0,  270,    2, 0x08 /* Private */,
      35,    0,  271,    2, 0x08 /* Private */,
      36,    0,  272,    2, 0x08 /* Private */,
      37,    0,  273,    2, 0x08 /* Private */,
      38,    0,  274,    2, 0x08 /* Private */,
      39,    0,  275,    2, 0x08 /* Private */,
      40,    0,  276,    2, 0x08 /* Private */,
      41,    0,  277,    2, 0x08 /* Private */,
      42,    0,  278,    2, 0x08 /* Private */,
      43,    0,  279,    2, 0x08 /* Private */,
      44,    0,  280,    2, 0x08 /* Private */,
      45,    1,  281,    2, 0x08 /* Private */,
      47,    0,  284,    2, 0x08 /* Private */,
      48,    0,  285,    2, 0x08 /* Private */,
      49,    0,  286,    2, 0x08 /* Private */,
      50,    0,  287,    2, 0x08 /* Private */,
      51,    0,  288,    2, 0x08 /* Private */,
      52,    0,  289,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 23, QMetaType::Bool,   22,   24,   25,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 30,   31,
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
    QMetaType::Void, QMetaType::Int,   46,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        case 0: _t->startCapture((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 1: _t->emitStartVideoRecord((*reinterpret_cast< string(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2]))); break;
        case 2: _t->stopCapture(); break;
        case 3: _t->startStream(); break;
        case 4: _t->stopStream(); break;
        case 5: _t->startRead((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 6: _t->stopRead(); break;
        case 7: _t->emitStartLeddarRecord((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 8: _t->setLeddarOrientation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->startDetect(); break;
        case 10: _t->stopDetect(); break;
        case 11: _t->setSigDist((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->passNotifier((*reinterpret_cast< vector<string>(*)>(_a[1]))); break;
        case 13: _t->clicked(); break;
        case 14: _t->streamButtonClicked(); break;
        case 15: _t->on_readDataButton_clicked(); break;
        case 16: _t->on_readDataButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->catchDataPoints((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< vector<float>(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 18: _t->catchDetectedObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->on_streamButton_clicked(); break;
        case 20: _t->frameCaptured((*reinterpret_cast< cv::Mat*(*)>(_a[1]))); break;
        case 21: _t->on_cancelButtonRead_clicked(); break;
        case 22: _t->on_settingsPageButton_clicked(); break;
        case 23: _t->on_actionMain_Menu_triggered(); break;
        case 24: _t->on_notificationsButton_clicked(); break;
        case 25: _t->on_readDataPageButton_clicked(); break;
        case 26: _t->on_backButton_clicked(); break;
        case 27: _t->on_backButtonGo_clicked(); break;
        case 28: _t->on_backButtonSettings_clicked(); break;
        case 29: _t->on_backButtonRead_clicked(); break;
        case 30: _t->on_changeCamera_clicked(); break;
        case 31: _t->on_changeOrient_clicked(); break;
        case 32: _t->on_QuitButton_clicked(); break;
        case 33: _t->on_Play_clicked(); break;
        case 34: _t->on_notificationDistanceSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->on_speechCheckBox_stateChanged(); break;
        case 36: _t->on_beepCheckBox_stateChanged(); break;
        case 37: _t->on_go_ReadFromFile_button_clicked(); break;
        case 38: _t->on_go_StreamFromDevice_button_clicked(); break;
        case 39: _t->on_go_Record_button_clicked(); break;
        case 40: _t->on_go_StopAll_button_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startCapture)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)(string , string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::emitStartVideoRecord)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stopCapture)) {
                *result = 2;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startStream)) {
                *result = 3;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stopStream)) {
                *result = 4;
            }
        }
        {
            typedef void (MainWindow::*_t)(string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startRead)) {
                *result = 5;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stopRead)) {
                *result = 6;
            }
        }
        {
            typedef void (MainWindow::*_t)(string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::emitStartLeddarRecord)) {
                *result = 7;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::setLeddarOrientation)) {
                *result = 8;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startDetect)) {
                *result = 9;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stopDetect)) {
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
            typedef void (MainWindow::*_t)(vector<string> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::passNotifier)) {
                *result = 12;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::clicked)) {
                *result = 13;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::streamButtonClicked)) {
                *result = 14;
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
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 41)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 41;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::startCapture(string _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::emitStartVideoRecord(string _t1, string _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::stopCapture()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void MainWindow::startStream()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void MainWindow::stopStream()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void MainWindow::startRead(string _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::stopRead()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void MainWindow::emitStartLeddarRecord(string _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainWindow::setLeddarOrientation(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MainWindow::startDetect()
{
    QMetaObject::activate(this, &staticMetaObject, 9, Q_NULLPTR);
}

// SIGNAL 10
void MainWindow::stopDetect()
{
    QMetaObject::activate(this, &staticMetaObject, 10, Q_NULLPTR);
}

// SIGNAL 11
void MainWindow::setSigDist(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MainWindow::passNotifier(vector<string> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MainWindow::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 13, Q_NULLPTR);
}

// SIGNAL 14
void MainWindow::streamButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 14, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
