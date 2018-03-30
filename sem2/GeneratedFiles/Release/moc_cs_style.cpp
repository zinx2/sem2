/****************************************************************************
** Meta object code from reading C++ file 'cs_style.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/cs_style.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cs_style.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StyleBasic_t {
    QByteArrayData data[18];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StyleBasic_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StyleBasic_t qt_meta_stringdata_StyleBasic = {
    {
QT_MOC_LITERAL(0, 0, 10), // "StyleBasic"
QT_MOC_LITERAL(1, 11, 12), // "widthChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 13), // "heightChanged"
QT_MOC_LITERAL(4, 39, 12), // "largeChanged"
QT_MOC_LITERAL(5, 52, 13), // "midiumChanged"
QT_MOC_LITERAL(6, 66, 12), // "smallChanged"
QT_MOC_LITERAL(7, 79, 8), // "setWidth"
QT_MOC_LITERAL(8, 88, 1), // "m"
QT_MOC_LITERAL(9, 90, 9), // "setHeight"
QT_MOC_LITERAL(10, 100, 8), // "setLarge"
QT_MOC_LITERAL(11, 109, 9), // "setMidium"
QT_MOC_LITERAL(12, 119, 8), // "setSmall"
QT_MOC_LITERAL(13, 128, 5), // "width"
QT_MOC_LITERAL(14, 134, 6), // "height"
QT_MOC_LITERAL(15, 141, 5), // "large"
QT_MOC_LITERAL(16, 147, 6), // "midium"
QT_MOC_LITERAL(17, 154, 5) // "small"

    },
    "StyleBasic\0widthChanged\0\0heightChanged\0"
    "largeChanged\0midiumChanged\0smallChanged\0"
    "setWidth\0m\0setHeight\0setLarge\0setMidium\0"
    "setSmall\0width\0height\0large\0midium\0"
    "small"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StyleBasic[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       6,   84, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,
       6,    0,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   69,    2, 0x0a /* Public */,
       9,    1,   72,    2, 0x0a /* Public */,
      10,    1,   75,    2, 0x0a /* Public */,
      11,    1,   78,    2, 0x0a /* Public */,
      12,    1,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,

 // properties: name, type, flags
      13, QMetaType::Int, 0x00495103,
      14, QMetaType::Int, 0x00495103,
      14, QMetaType::Int, 0x00495103,
      15, QMetaType::Int, 0x00495103,
      16, QMetaType::Int, 0x00495103,
      17, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       1,
       2,
       3,
       4,

       0        // eod
};

void StyleBasic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StyleBasic *_t = static_cast<StyleBasic *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->widthChanged(); break;
        case 1: _t->heightChanged(); break;
        case 2: _t->largeChanged(); break;
        case 3: _t->midiumChanged(); break;
        case 4: _t->smallChanged(); break;
        case 5: _t->setWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setHeight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setLarge((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setMidium((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setSmall((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StyleBasic::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StyleBasic::widthChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (StyleBasic::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StyleBasic::heightChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (StyleBasic::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StyleBasic::largeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (StyleBasic::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StyleBasic::midiumChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (StyleBasic::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StyleBasic::smallChanged)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        StyleBasic *_t = static_cast<StyleBasic *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->width(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->height(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->height(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->large(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->midium(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->small(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        StyleBasic *_t = static_cast<StyleBasic *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWidth(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setHeight(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setHeight(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setLarge(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setMidium(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setSmall(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject StyleBasic::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StyleBasic.data,
      qt_meta_data_StyleBasic,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StyleBasic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StyleBasic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StyleBasic.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int StyleBasic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void StyleBasic::widthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void StyleBasic::heightChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void StyleBasic::largeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void StyleBasic::midiumChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void StyleBasic::smallChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
struct qt_meta_stringdata_StyleMain_t {
    QByteArrayData data[1];
    char stringdata0[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StyleMain_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StyleMain_t qt_meta_stringdata_StyleMain = {
    {
QT_MOC_LITERAL(0, 0, 9) // "StyleMain"

    },
    "StyleMain"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StyleMain[] = {

 // content:
       7,       // revision
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

void StyleMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject StyleMain::staticMetaObject = {
    { &StyleBasic::staticMetaObject, qt_meta_stringdata_StyleMain.data,
      qt_meta_data_StyleMain,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StyleMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StyleMain::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StyleMain.stringdata0))
        return static_cast<void*>(this);
    return StyleBasic::qt_metacast(_clname);
}

int StyleMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = StyleBasic::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_Style_t {
    QByteArrayData data[32];
    char stringdata0[417];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Style_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Style_t qt_meta_stringdata_Style = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Style"
QT_MOC_LITERAL(1, 6, 18), // "widthWindowChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 19), // "heightWindowChanged"
QT_MOC_LITERAL(4, 46, 16), // "widthMenuChanged"
QT_MOC_LITERAL(5, 63, 17), // "heightMenuChanged"
QT_MOC_LITERAL(6, 81, 16), // "widthPageChanged"
QT_MOC_LITERAL(7, 98, 17), // "heightPageChanged"
QT_MOC_LITERAL(8, 116, 16), // "widthUtilChanged"
QT_MOC_LITERAL(9, 133, 17), // "heightUtilChanged"
QT_MOC_LITERAL(10, 151, 21), // "heightTitleBarChanged"
QT_MOC_LITERAL(11, 173, 2), // "pt"
QT_MOC_LITERAL(12, 176, 5), // "pixel"
QT_MOC_LITERAL(13, 182, 14), // "setWidthWindow"
QT_MOC_LITERAL(14, 197, 1), // "m"
QT_MOC_LITERAL(15, 199, 15), // "setHeightWindow"
QT_MOC_LITERAL(16, 215, 12), // "setWidthMenu"
QT_MOC_LITERAL(17, 228, 13), // "setHeightMenu"
QT_MOC_LITERAL(18, 242, 12), // "setWidthPage"
QT_MOC_LITERAL(19, 255, 13), // "setHeightPage"
QT_MOC_LITERAL(20, 269, 12), // "setWidthUtil"
QT_MOC_LITERAL(21, 282, 13), // "setHeightUtil"
QT_MOC_LITERAL(22, 296, 17), // "setHeightTitleBar"
QT_MOC_LITERAL(23, 314, 11), // "widthWindow"
QT_MOC_LITERAL(24, 326, 12), // "heightWindow"
QT_MOC_LITERAL(25, 339, 9), // "widthMenu"
QT_MOC_LITERAL(26, 349, 10), // "heightMenu"
QT_MOC_LITERAL(27, 360, 9), // "widthPage"
QT_MOC_LITERAL(28, 370, 10), // "heightPage"
QT_MOC_LITERAL(29, 381, 9), // "widthUtil"
QT_MOC_LITERAL(30, 391, 10), // "heightUtil"
QT_MOC_LITERAL(31, 402, 14) // "heightTitleBar"

    },
    "Style\0widthWindowChanged\0\0heightWindowChanged\0"
    "widthMenuChanged\0heightMenuChanged\0"
    "widthPageChanged\0heightPageChanged\0"
    "widthUtilChanged\0heightUtilChanged\0"
    "heightTitleBarChanged\0pt\0pixel\0"
    "setWidthWindow\0m\0setHeightWindow\0"
    "setWidthMenu\0setHeightMenu\0setWidthPage\0"
    "setHeightPage\0setWidthUtil\0setHeightUtil\0"
    "setHeightTitleBar\0widthWindow\0"
    "heightWindow\0widthMenu\0heightMenu\0"
    "widthPage\0heightPage\0widthUtil\0"
    "heightUtil\0heightTitleBar"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Style[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       9,  148, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x06 /* Public */,
       3,    0,  110,    2, 0x06 /* Public */,
       4,    0,  111,    2, 0x06 /* Public */,
       5,    0,  112,    2, 0x06 /* Public */,
       6,    0,  113,    2, 0x06 /* Public */,
       7,    0,  114,    2, 0x06 /* Public */,
       8,    0,  115,    2, 0x06 /* Public */,
       9,    0,  116,    2, 0x06 /* Public */,
      10,    0,  117,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,  118,    2, 0x0a /* Public */,
      13,    1,  121,    2, 0x0a /* Public */,
      15,    1,  124,    2, 0x0a /* Public */,
      16,    1,  127,    2, 0x0a /* Public */,
      17,    1,  130,    2, 0x0a /* Public */,
      18,    1,  133,    2, 0x0a /* Public */,
      19,    1,  136,    2, 0x0a /* Public */,
      20,    1,  139,    2, 0x0a /* Public */,
      21,    1,  142,    2, 0x0a /* Public */,
      22,    1,  145,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Int, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,

 // properties: name, type, flags
      23, QMetaType::Int, 0x00495103,
      24, QMetaType::Int, 0x00495103,
      25, QMetaType::Int, 0x00495103,
      26, QMetaType::Int, 0x00495103,
      27, QMetaType::Int, 0x00495103,
      28, QMetaType::Int, 0x00495103,
      29, QMetaType::Int, 0x00495103,
      30, QMetaType::Int, 0x00495103,
      31, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,

       0        // eod
};

void Style::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Style *_t = static_cast<Style *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->widthWindowChanged(); break;
        case 1: _t->heightWindowChanged(); break;
        case 2: _t->widthMenuChanged(); break;
        case 3: _t->heightMenuChanged(); break;
        case 4: _t->widthPageChanged(); break;
        case 5: _t->heightPageChanged(); break;
        case 6: _t->widthUtilChanged(); break;
        case 7: _t->heightUtilChanged(); break;
        case 8: _t->heightTitleBarChanged(); break;
        case 9: { int _r = _t->pt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->setWidthWindow((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 11: _t->setHeightWindow((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 12: _t->setWidthMenu((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 13: _t->setHeightMenu((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 14: _t->setWidthPage((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 15: _t->setHeightPage((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 16: _t->setWidthUtil((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 17: _t->setHeightUtil((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 18: _t->setHeightTitleBar((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Style::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Style::widthWindowChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Style::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Style::heightWindowChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Style::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Style::widthMenuChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Style::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Style::heightMenuChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Style::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Style::widthPageChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Style::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Style::heightPageChanged)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Style::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Style::widthUtilChanged)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Style::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Style::heightUtilChanged)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (Style::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Style::heightTitleBarChanged)) {
                *result = 8;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Style *_t = static_cast<Style *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->widthWindow(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->heightWindow(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->widthMenu(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->heightMenu(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->widthPage(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->heightPage(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->widthUtil(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->heightUtil(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->heightTitleBar(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Style *_t = static_cast<Style *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWidthWindow(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setHeightWindow(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setWidthMenu(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setHeightMenu(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setWidthPage(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setHeightPage(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setWidthUtil(*reinterpret_cast< int*>(_v)); break;
        case 7: _t->setHeightUtil(*reinterpret_cast< int*>(_v)); break;
        case 8: _t->setHeightTitleBar(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject Style::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Style.data,
      qt_meta_data_Style,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Style::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Style::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Style.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Style::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Style::widthWindowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Style::heightWindowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Style::widthMenuChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Style::heightMenuChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Style::widthPageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Style::heightPageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Style::widthUtilChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Style::heightUtilChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Style::heightTitleBarChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
