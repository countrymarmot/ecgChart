/****************************************************************************
** Meta object code from reading C++ file 'QtApp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtApp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtApp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtApp_t {
    QByteArrayData data[8];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtApp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtApp_t qt_meta_stringdata_QtApp = {
    {
QT_MOC_LITERAL(0, 0, 5), // "QtApp"
QT_MOC_LITERAL(1, 6, 10), // "ConnectCOM"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 13), // "filter_result"
QT_MOC_LITERAL(4, 32, 10), // "const int*"
QT_MOC_LITERAL(5, 43, 12), // "filterResult"
QT_MOC_LITERAL(6, 56, 4), // "size"
QT_MOC_LITERAL(7, 61, 11) // "receiveInfo"

    },
    "QtApp\0ConnectCOM\0\0filter_result\0"
    "const int*\0filterResult\0size\0receiveInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtApp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    2,   30,    2, 0x0a /* Public */,
       7,    0,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    5,    6,
    QMetaType::Void,

       0        // eod
};

void QtApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtApp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ConnectCOM(); break;
        case 1: _t->filter_result((*reinterpret_cast< const int*(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: _t->receiveInfo(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtApp::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_QtApp.data,
    qt_meta_data_QtApp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtApp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtApp.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QtApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
