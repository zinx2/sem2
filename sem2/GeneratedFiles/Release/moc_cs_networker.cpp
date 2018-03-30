/****************************************************************************
** Meta object code from reading C++ file 'cs_networker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/cs_networker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cs_networker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetHost_t {
    QByteArrayData data[10];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetHost_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetHost_t qt_meta_stringdata_NetHost = {
    {
QT_MOC_LITERAL(0, 0, 7), // "NetHost"
QT_MOC_LITERAL(1, 8, 7), // "setType"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 1), // "m"
QT_MOC_LITERAL(4, 19, 7), // "setAddr"
QT_MOC_LITERAL(5, 27, 10), // "setQueries"
QT_MOC_LITERAL(6, 38, 9), // "QUrlQuery"
QT_MOC_LITERAL(7, 48, 7), // "setFunc"
QT_MOC_LITERAL(8, 56, 4), // "FUNC"
QT_MOC_LITERAL(9, 61, 7) // "setFile"

    },
    "NetHost\0setType\0\0m\0setAddr\0setQueries\0"
    "QUrlQuery\0setFunc\0FUNC\0setFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetHost[] = {

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
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       5,    1,   45,    2, 0x0a /* Public */,
       7,    1,   48,    2, 0x0a /* Public */,
       9,    1,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 6,    3,
    QMetaType::Void, 0x80000000 | 8,    3,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void NetHost::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetHost *_t = static_cast<NetHost *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setType((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setAddr((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setQueries((*reinterpret_cast< const QUrlQuery(*)>(_a[1]))); break;
        case 3: _t->setFunc((*reinterpret_cast< const FUNC(*)>(_a[1]))); break;
        case 4: _t->setFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject NetHost::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NetHost.data,
      qt_meta_data_NetHost,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NetHost::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetHost::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetHost.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NetHost::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_NetWorker_t {
    QByteArrayData data[47];
    char stringdata0[464];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetWorker_t qt_meta_stringdata_NetWorker = {
    {
QT_MOC_LITERAL(0, 0, 9), // "NetWorker"
QT_MOC_LITERAL(1, 10, 4), // "next"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 6), // "update"
QT_MOC_LITERAL(4, 23, 6), // "result"
QT_MOC_LITERAL(5, 30, 6), // "upload"
QT_MOC_LITERAL(6, 37, 8), // "finished"
QT_MOC_LITERAL(7, 46, 7), // "request"
QT_MOC_LITERAL(8, 54, 9), // "httpError"
QT_MOC_LITERAL(9, 64, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(10, 92, 3), // "msg"
QT_MOC_LITERAL(11, 96, 8), // "progress"
QT_MOC_LITERAL(12, 105, 4), // "done"
QT_MOC_LITERAL(13, 110, 11), // "getUserList"
QT_MOC_LITERAL(14, 122, 10), // "NetWorker*"
QT_MOC_LITERAL(15, 133, 11), // "getPartList"
QT_MOC_LITERAL(16, 145, 13), // "getDeviceList"
QT_MOC_LITERAL(17, 159, 6), // "noPart"
QT_MOC_LITERAL(18, 166, 10), // "searchType"
QT_MOC_LITERAL(19, 177, 3), // "now"
QT_MOC_LITERAL(20, 181, 11), // "getRentList"
QT_MOC_LITERAL(21, 193, 12), // "borrowDevice"
QT_MOC_LITERAL(22, 206, 7), // "barcode"
QT_MOC_LITERAL(23, 214, 6), // "noUser"
QT_MOC_LITERAL(24, 221, 7), // "purpose"
QT_MOC_LITERAL(25, 229, 12), // "returnDevice"
QT_MOC_LITERAL(26, 242, 7), // "noAdmin"
QT_MOC_LITERAL(27, 250, 8), // "noDevice"
QT_MOC_LITERAL(28, 259, 9), // "isInitial"
QT_MOC_LITERAL(29, 269, 10), // "signBorrow"
QT_MOC_LITERAL(30, 280, 10), // "signReturn"
QT_MOC_LITERAL(31, 291, 9), // "addDevice"
QT_MOC_LITERAL(32, 301, 10), // "nameDevice"
QT_MOC_LITERAL(33, 312, 7), // "noAsset"
QT_MOC_LITERAL(34, 320, 5), // "price"
QT_MOC_LITERAL(35, 326, 4), // "date"
QT_MOC_LITERAL(36, 331, 4), // "memo"
QT_MOC_LITERAL(37, 336, 10), // "editDevice"
QT_MOC_LITERAL(38, 347, 12), // "removeDevice"
QT_MOC_LITERAL(39, 360, 18), // "uploadFileBorrowed"
QT_MOC_LITERAL(40, 379, 8), // "fileName"
QT_MOC_LITERAL(41, 388, 18), // "uploadFileReturned"
QT_MOC_LITERAL(42, 407, 10), // "uploadFile"
QT_MOC_LITERAL(43, 418, 6), // "expire"
QT_MOC_LITERAL(44, 425, 13), // "getDeviceInfo"
QT_MOC_LITERAL(45, 439, 20), // "searchDeviceReturned"
QT_MOC_LITERAL(46, 460, 3) // "mtx"

    },
    "NetWorker\0next\0\0update\0result\0upload\0"
    "finished\0request\0httpError\0"
    "QNetworkReply::NetworkError\0msg\0"
    "progress\0done\0getUserList\0NetWorker*\0"
    "getPartList\0getDeviceList\0noPart\0"
    "searchType\0now\0getRentList\0borrowDevice\0"
    "barcode\0noUser\0purpose\0returnDevice\0"
    "noAdmin\0noDevice\0isInitial\0signBorrow\0"
    "signReturn\0addDevice\0nameDevice\0noAsset\0"
    "price\0date\0memo\0editDevice\0removeDevice\0"
    "uploadFileBorrowed\0fileName\0"
    "uploadFileReturned\0uploadFile\0expire\0"
    "getDeviceInfo\0searchDeviceReturned\0"
    "mtx"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  184,    2, 0x06 /* Public */,
       3,    1,  185,    2, 0x06 /* Public */,
       5,    1,  188,    2, 0x06 /* Public */,
       6,    0,  191,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  192,    2, 0x0a /* Public */,
       8,    1,  193,    2, 0x0a /* Public */,
      11,    2,  196,    2, 0x0a /* Public */,
      12,    0,  201,    2, 0x0a /* Public */,
      13,    0,  202,    2, 0x0a /* Public */,
      15,    0,  203,    2, 0x0a /* Public */,
      16,    3,  204,    2, 0x0a /* Public */,
      16,    2,  211,    2, 0x2a /* Public | MethodCloned */,
      16,    1,  216,    2, 0x2a /* Public | MethodCloned */,
      16,    0,  219,    2, 0x2a /* Public | MethodCloned */,
      20,    2,  220,    2, 0x0a /* Public */,
      20,    1,  225,    2, 0x2a /* Public | MethodCloned */,
      20,    0,  228,    2, 0x2a /* Public | MethodCloned */,
      21,    3,  229,    2, 0x0a /* Public */,
      25,    4,  236,    2, 0x0a /* Public */,
      25,    3,  245,    2, 0x2a /* Public | MethodCloned */,
      29,    0,  252,    2, 0x0a /* Public */,
      30,    0,  253,    2, 0x0a /* Public */,
      31,    7,  254,    2, 0x0a /* Public */,
      31,    6,  269,    2, 0x2a /* Public | MethodCloned */,
      37,    8,  282,    2, 0x0a /* Public */,
      37,    7,  299,    2, 0x2a /* Public | MethodCloned */,
      38,    1,  314,    2, 0x0a /* Public */,
      39,    1,  317,    2, 0x0a /* Public */,
      41,    1,  320,    2, 0x0a /* Public */,
      42,    1,  323,    2, 0x0a /* Public */,
      43,    1,  326,    2, 0x0a /* Public */,
      44,    1,  329,    2, 0x0a /* Public */,
      45,    1,  332,    2, 0x0a /* Public */,
      46,    0,  335,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    2,    2,
    QMetaType::Void,
    0x80000000 | 14,
    0x80000000 | 14,
    0x80000000 | 14, QMetaType::Int, QMetaType::Int, QMetaType::Int,   17,   18,   19,
    0x80000000 | 14, QMetaType::Int, QMetaType::Int,   17,   18,
    0x80000000 | 14, QMetaType::Int,   17,
    0x80000000 | 14,
    0x80000000 | 14, QMetaType::Int, QMetaType::Int,   17,   19,
    0x80000000 | 14, QMetaType::Int,   17,
    0x80000000 | 14,
    0x80000000 | 14, QMetaType::QString, QMetaType::Int, QMetaType::QString,   22,   23,   24,
    0x80000000 | 14, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   22,   26,   27,   28,
    0x80000000 | 14, QMetaType::QString, QMetaType::Int, QMetaType::Int,   22,   26,   27,
    0x80000000 | 14,
    0x80000000 | 14,
    0x80000000 | 14, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   17,   32,   33,   22,   34,   35,   36,
    0x80000000 | 14, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   17,   32,   33,   22,   34,   35,
    0x80000000 | 14, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   27,   17,   32,   33,   22,   34,   35,   36,
    0x80000000 | 14, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   27,   17,   32,   33,   22,   34,   35,
    0x80000000 | 14, QMetaType::Int,   27,
    0x80000000 | 14, QMetaType::QString,   40,
    0x80000000 | 14, QMetaType::QString,   40,
    0x80000000 | 14, QMetaType::QString,   40,
    0x80000000 | 14, QMetaType::Int,   23,
    0x80000000 | 14, QMetaType::Int,   22,
    0x80000000 | 14, QMetaType::Int,   22,
    QMetaType::Void,

       0        // eod
};

void NetWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetWorker *_t = static_cast<NetWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->next(); break;
        case 1: _t->update((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->upload((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->finished(); break;
        case 4: _t->request(); break;
        case 5: _t->httpError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 6: _t->progress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 7: _t->done(); break;
        case 8: { NetWorker* _r = _t->getUserList();
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 9: { NetWorker* _r = _t->getPartList();
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 10: { NetWorker* _r = _t->getDeviceList((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 11: { NetWorker* _r = _t->getDeviceList((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 12: { NetWorker* _r = _t->getDeviceList((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 13: { NetWorker* _r = _t->getDeviceList();
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 14: { NetWorker* _r = _t->getRentList((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 15: { NetWorker* _r = _t->getRentList((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 16: { NetWorker* _r = _t->getRentList();
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 17: { NetWorker* _r = _t->borrowDevice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 18: { NetWorker* _r = _t->returnDevice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 19: { NetWorker* _r = _t->returnDevice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 20: { NetWorker* _r = _t->signBorrow();
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 21: { NetWorker* _r = _t->signReturn();
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 22: { NetWorker* _r = _t->addDevice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 23: { NetWorker* _r = _t->addDevice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 24: { NetWorker* _r = _t->editDevice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])),(*reinterpret_cast< QString(*)>(_a[8])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 25: { NetWorker* _r = _t->editDevice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 26: { NetWorker* _r = _t->removeDevice((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 27: { NetWorker* _r = _t->uploadFileBorrowed((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 28: { NetWorker* _r = _t->uploadFileReturned((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 29: { NetWorker* _r = _t->uploadFile((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 30: { NetWorker* _r = _t->expire((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 31: { NetWorker* _r = _t->getDeviceInfo((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 32: { NetWorker* _r = _t->searchDeviceReturned((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< NetWorker**>(_a[0]) = std::move(_r); }  break;
        case 33: _t->mtx(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NetWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NetWorker::next)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (NetWorker::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NetWorker::update)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (NetWorker::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NetWorker::upload)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (NetWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NetWorker::finished)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject NetWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NetWorker.data,
      qt_meta_data_NetWorker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NetWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NetWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    return _id;
}

// SIGNAL 0
void NetWorker::next()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void NetWorker::update(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NetWorker::upload(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NetWorker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
