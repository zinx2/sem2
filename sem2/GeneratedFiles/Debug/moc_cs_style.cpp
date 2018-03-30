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
struct qt_meta_stringdata_Font_t {
    QByteArrayData data[12];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Font_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Font_t qt_meta_stringdata_Font = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Font"
QT_MOC_LITERAL(1, 5, 12), // "largeChanged"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 13), // "midiumChanged"
QT_MOC_LITERAL(4, 33, 12), // "smallChanged"
QT_MOC_LITERAL(5, 46, 8), // "setLarge"
QT_MOC_LITERAL(6, 55, 1), // "m"
QT_MOC_LITERAL(7, 57, 9), // "setMidium"
QT_MOC_LITERAL(8, 67, 8), // "setSmall"
QT_MOC_LITERAL(9, 76, 5), // "large"
QT_MOC_LITERAL(10, 82, 6), // "midium"
QT_MOC_LITERAL(11, 89, 5) // "small"

    },
    "Font\0largeChanged\0\0midiumChanged\0"
    "smallChanged\0setLarge\0m\0setMidium\0"
    "setSmall\0large\0midium\0small"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Font[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       3,   56, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   47,    2, 0x0a /* Public */,
       7,    1,   50,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,

 // properties: name, type, flags
       9, QMetaType::Int, 0x00495103,
      10, QMetaType::Int, 0x00495103,
      11, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void Font::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Font *_t = static_cast<Font *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->largeChanged(); break;
        case 1: _t->midiumChanged(); break;
        case 2: _t->smallChanged(); break;
        case 3: _t->setLarge((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setMidium((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setSmall((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Font::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Font::largeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Font::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Font::midiumChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Font::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Font::smallChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Font *_t = static_cast<Font *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->large(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->midium(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->small(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Font *_t = static_cast<Font *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLarge(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setMidium(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setSmall(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject Font::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Font.data,
      qt_meta_data_Font,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Font::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Font::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Font.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Font::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Font::largeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Font::midiumChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Font::smallChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
struct qt_meta_stringdata_StyleBasic_t {
    QByteArrayData data[9];
    char stringdata0[73];
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
QT_MOC_LITERAL(4, 39, 8), // "setWidth"
QT_MOC_LITERAL(5, 48, 1), // "m"
QT_MOC_LITERAL(6, 50, 9), // "setHeight"
QT_MOC_LITERAL(7, 60, 5), // "width"
QT_MOC_LITERAL(8, 66, 6) // "height"

    },
    "StyleBasic\0widthChanged\0\0heightChanged\0"
    "setWidth\0m\0setHeight\0width\0height"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StyleBasic[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       2,   42, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   36,    2, 0x0a /* Public */,
       6,    1,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,

 // properties: name, type, flags
       7, QMetaType::Int, 0x00495103,
       8, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       1,

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
        case 2: _t->setWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setHeight((*reinterpret_cast< int(*)>(_a[1]))); break;
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
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        StyleBasic *_t = static_cast<StyleBasic *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->width(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->height(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        StyleBasic *_t = static_cast<StyleBasic *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWidth(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setHeight(*reinterpret_cast< int*>(_v)); break;
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
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
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
struct qt_meta_stringdata_Button_t {
    QByteArrayData data[6];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Button_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Button_t qt_meta_stringdata_Button = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Button"
QT_MOC_LITERAL(1, 7, 11), // "nameChanged"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "setName"
QT_MOC_LITERAL(4, 28, 1), // "m"
QT_MOC_LITERAL(5, 30, 4) // "name"

    },
    "Button\0nameChanged\0\0setName\0m\0name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Button[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       1,   28, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,

 // properties: name, type, flags
       5, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,

       0        // eod
};

void Button::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Button *_t = static_cast<Button *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nameChanged(); break;
        case 1: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Button::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Button::nameChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Button *_t = static_cast<Button *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Button *_t = static_cast<Button *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject Button::staticMetaObject = {
    { &StyleBasic::staticMetaObject, qt_meta_stringdata_Button.data,
      qt_meta_data_Button,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Button::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Button::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Button.stringdata0))
        return static_cast<void*>(this);
    return StyleBasic::qt_metacast(_clname);
}

int Button::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = StyleBasic::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Button::nameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_StyleMainSlide_t {
    QByteArrayData data[6];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StyleMainSlide_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StyleMainSlide_t qt_meta_stringdata_StyleMainSlide = {
    {
QT_MOC_LITERAL(0, 0, 14), // "StyleMainSlide"
QT_MOC_LITERAL(1, 15, 15), // "extendedChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "extend"
QT_MOC_LITERAL(4, 39, 1), // "m"
QT_MOC_LITERAL(5, 41, 8) // "extended"

    },
    "StyleMainSlide\0extendedChanged\0\0extend\0"
    "m\0extended"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StyleMainSlide[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       1,   28, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    4,

 // properties: name, type, flags
       5, QMetaType::Bool, 0x00495003,

 // properties: notify_signal_id
       0,

       0        // eod
};

void StyleMainSlide::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StyleMainSlide *_t = static_cast<StyleMainSlide *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->extendedChanged(); break;
        case 1: _t->extend((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StyleMainSlide::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StyleMainSlide::extendedChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        StyleMainSlide *_t = static_cast<StyleMainSlide *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->extended(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        StyleMainSlide *_t = static_cast<StyleMainSlide *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->extend(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject StyleMainSlide::staticMetaObject = {
    { &StyleBasic::staticMetaObject, qt_meta_stringdata_StyleMainSlide.data,
      qt_meta_data_StyleMainSlide,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StyleMainSlide::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StyleMainSlide::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StyleMainSlide.stringdata0))
        return static_cast<void*>(this);
    return StyleBasic::qt_metacast(_clname);
}

int StyleMainSlide::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = StyleBasic::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void StyleMainSlide::extendedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_StyleMainContent_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StyleMainContent_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StyleMainContent_t qt_meta_stringdata_StyleMainContent = {
    {
QT_MOC_LITERAL(0, 0, 16) // "StyleMainContent"

    },
    "StyleMainContent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StyleMainContent[] = {

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

void StyleMainContent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject StyleMainContent::staticMetaObject = {
    { &StyleBasic::staticMetaObject, qt_meta_stringdata_StyleMainContent.data,
      qt_meta_data_StyleMainContent,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StyleMainContent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StyleMainContent::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StyleMainContent.stringdata0))
        return static_cast<void*>(this);
    return StyleBasic::qt_metacast(_clname);
}

int StyleMainContent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = StyleBasic::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_StyleMainBody_t {
    QByteArrayData data[4];
    char stringdata0[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StyleMainBody_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StyleMainBody_t qt_meta_stringdata_StyleMainBody = {
    {
QT_MOC_LITERAL(0, 0, 13), // "StyleMainBody"
QT_MOC_LITERAL(1, 14, 13), // "initWidthBody"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 14) // "initHeightBody"

    },
    "StyleMainBody\0initWidthBody\0\0"
    "initHeightBody"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StyleMainBody[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void StyleMainBody::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StyleMainBody *_t = static_cast<StyleMainBody *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initWidthBody(); break;
        case 1: _t->initHeightBody(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject StyleMainBody::staticMetaObject = {
    { &StyleBasic::staticMetaObject, qt_meta_stringdata_StyleMainBody.data,
      qt_meta_data_StyleMainBody,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StyleMainBody::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StyleMainBody::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StyleMainBody.stringdata0))
        return static_cast<void*>(this);
    return StyleBasic::qt_metacast(_clname);
}

int StyleMainBody::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = StyleBasic::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_StyleMain_t {
    QByteArrayData data[10];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StyleMain_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StyleMain_t qt_meta_stringdata_StyleMain = {
    {
QT_MOC_LITERAL(0, 0, 9), // "StyleMain"
QT_MOC_LITERAL(1, 10, 15), // "initWidthHeader"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "initWidthFooter"
QT_MOC_LITERAL(4, 43, 6), // "header"
QT_MOC_LITERAL(5, 50, 16), // "StyleMainHeader*"
QT_MOC_LITERAL(6, 67, 4), // "body"
QT_MOC_LITERAL(7, 72, 14), // "StyleMainBody*"
QT_MOC_LITERAL(8, 87, 6), // "footer"
QT_MOC_LITERAL(9, 94, 16) // "StyleMainFooter*"

    },
    "StyleMain\0initWidthHeader\0\0initWidthFooter\0"
    "header\0StyleMainHeader*\0body\0"
    "StyleMainBody*\0footer\0StyleMainFooter*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StyleMain[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       6,    0,   42,    2, 0x0a /* Public */,
       8,    0,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 5,
    0x80000000 | 7,
    0x80000000 | 9,

       0        // eod
};

void StyleMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StyleMain *_t = static_cast<StyleMain *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initWidthHeader(); break;
        case 1: _t->initWidthFooter(); break;
        case 2: { StyleMainHeader* _r = _t->header();
            if (_a[0]) *reinterpret_cast< StyleMainHeader**>(_a[0]) = std::move(_r); }  break;
        case 3: { StyleMainBody* _r = _t->body();
            if (_a[0]) *reinterpret_cast< StyleMainBody**>(_a[0]) = std::move(_r); }  break;
        case 4: { StyleMainFooter* _r = _t->footer();
            if (_a[0]) *reinterpret_cast< StyleMainFooter**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
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
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
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
