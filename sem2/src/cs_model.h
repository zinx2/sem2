﻿#pragma once
#include "cs_qheader.h"
#define DEVICE_LIST "devicelist"
#define DEVICE_MANAGE_LIST "devicemanagelist"
#define EMPLOYEE_MANAGE_LIST "employeemanagelist"
#define COUNT_PAGE 20

class Device : public QObject {
    Q_OBJECT
        Q_PROPERTY(int noDevice READ noDevice WRITE setNoDevice NOTIFY noDeviceChanged)
        Q_PROPERTY(int noPart READ noPart WRITE setNoPart NOTIFY noPartChanged)
        Q_PROPERTY(QString nameDevice READ nameDevice WRITE setNameDevice NOTIFY nameDeviceChanged)
        Q_PROPERTY(QString namePart READ namePart WRITE setNamePart NOTIFY namePartChanged)
        Q_PROPERTY(QString noAsset READ noAsset WRITE setNoAsset NOTIFY noAssetChanged)
        Q_PROPERTY(QString barcode READ barcode WRITE setBarcode NOTIFY barcodeChanged)
        Q_PROPERTY(int price READ price WRITE setPrice NOTIFY priceChanged)
        Q_PROPERTY(QString dateTaked READ dateTaked WRITE setDateTaked NOTIFY dateTakedChanged)
        Q_PROPERTY(QString memo READ memo WRITE setMemo NOTIFY memoChanged)
        Q_PROPERTY(bool borrowed READ borrowed WRITE borrow NOTIFY borrowedChanged)
public:
    int noDevice() const { return m_noDevice; }
    int noPart() const { return m_noPart; }
    QString nameDevice() const { return m_nameDevice; }
    QString namePart() const { return m_namePart; }
    QString noAsset() const { return m_noAsset; }
    QString barcode() const { return m_barcode; }
    int price() const { return m_price; }
    QString dateTaked() const { return m_dateTaked; }
    QString memo() const { return m_memo; }
    bool borrowed() const { return m_borrowed; }

    public slots:
    void setNoDevice(const int m) { m_noDevice = m; emit noDeviceChanged(); }
    void setNoPart(const int m) { m_noPart = m; emit noPartChanged(); }
    void setNameDevice(const QString &m) { m_nameDevice = m; emit nameDeviceChanged(); }
    void setNamePart(const QString &m) { m_namePart = m; emit namePartChanged(); }
    void setNoAsset(const QString &m) { m_noAsset = m; emit noAssetChanged(); }
    void setBarcode(const QString &m) { m_barcode = m; emit barcodeChanged(); }
    void setPrice(const int &m) { m_price = m; emit priceChanged(); }
    void setDateTaked(const QString &m) { m_dateTaked = m; emit dateTakedChanged(); }
    void setMemo(const QString &m) { m_memo = m; emit memoChanged(); }
    void borrow(bool m) { m_borrowed = m; emit borrowedChanged(); };

signals:
    void noDeviceChanged();
    void nameDeviceChanged();
    void namePartChanged();
    void userChanged();
    void noAssetChanged();
    void barcodeChanged();
    void priceChanged();
    void dateTakedChanged();
    void memoChanged();
    void borrowedChanged();
    void noPartChanged();

private:
    int m_noDevice = -1;
    int m_noPart = -1;
    QString m_nameDevice;
    QString m_namePart;
    QString m_noAsset;
    QString m_barcode;
    int m_price;
    QString m_dateTaked;
    QString m_memo;
    bool m_borrowed = false;
};

class Rent : public QObject {
    Q_OBJECT
        Q_PROPERTY(int noRent READ noRent WRITE setNoRent NOTIFY noRentChanged)
        Q_PROPERTY(int noDevice READ noDevice WRITE setNoDevice NOTIFY noDeviceChanged)
		Q_PROPERTY(int noPart READ noPart WRITE setNoPart NOTIFY noPartChanged)
        Q_PROPERTY(QString noAsset READ noAsset WRITE setNoAsset NOTIFY noAssetChanged)
		Q_PROPERTY(QString namePart READ namePart WRITE setNamePart NOTIFY namePartChanged)
        Q_PROPERTY(QString nameDevice READ nameDevice WRITE setNameDevice NOTIFY nameDeviceChanged)
        Q_PROPERTY(QString nameUser READ nameUser WRITE setNameUser NOTIFY nameUserChanged)
        Q_PROPERTY(QString nameAdmin READ nameAdmin WRITE setNameAdmin NOTIFY nameAdminChanged)
        Q_PROPERTY(QString dateBorrowed READ dateBorrowed WRITE setDateBorrowed NOTIFY dateBorrowedChanged)
        Q_PROPERTY(QString dateReturned READ dateReturned WRITE setDateReturned NOTIFY dateReturnedChanged)
        Q_PROPERTY(QString signUser READ signUser WRITE setSignUser NOTIFY signUserChanged)
        Q_PROPERTY(QString signAdmin READ signAdmin WRITE setSignAdmin NOTIFY signAdminChanged)
        Q_PROPERTY(QString purpose READ purpose WRITE setPurpose NOTIFY purposeChanged)
        Q_PROPERTY(bool completed READ completed WRITE complete NOTIFY completedChanged)
        Q_PROPERTY(bool initial READ initial WRITE isInitial NOTIFY initialChanged)

public:
    int noRent() const { return m_noRent; }
    int noDevice() const { return m_noDevice; }
	int noPart() const { return m_noPart; }
    QString noAsset() const { return m_noAsset; }
	QString namePart() const { return m_namePart; }
    QString nameDevice() const { return m_nameDevice; }
    QString nameUser() const { return m_nameUser; }
    QString nameAdmin() const { return m_nameAdmin; }
    QString dateBorrowed() const { return m_dateBorrowed; }
    QString dateReturned() const { return m_dateReturned; }
    QString signUser() const { return m_signUser; }
    QString signAdmin() const { return m_signAdmin; }
    QString purpose() const { return m_purpose; }
    bool completed() const { return m_completed; }
    bool initial() const { return m_initial; }

    public slots:
	void setNoPart(const int m) { m_noPart = m; emit noPartChanged(); }
    void setNoRent(const int m) { m_noRent = m; emit noRentChanged(); }
    void setNoDevice(const int m) { m_noDevice = m; emit noAssetChanged(); }
    void setNoAsset(const QString &m) { m_noAsset = m; emit noDeviceChanged(); }
	void setNamePart(const QString &m) { m_namePart = m; emit namePartChanged(); }
    void setNameDevice(const QString &m) { m_nameDevice = m; emit nameDeviceChanged(); }
    void setNameUser(const QString &m) { m_nameUser = m; emit nameUserChanged(); }
    void setNameAdmin(const QString &m) { m_nameAdmin = m; emit nameAdminChanged(); }
    void setDateBorrowed(const QString &m) { m_dateBorrowed = m; emit dateBorrowedChanged(); }
    void setDateReturned(const QString &m) { m_dateReturned = m; emit dateReturnedChanged(); }
    void setSignUser(const QString &m) { m_signUser = m; emit signUserChanged(); }
    void setSignAdmin(const QString &m) { m_signAdmin = m; emit signAdminChanged(); }
    void setPurpose(const QString &m) { m_purpose = m; emit purposeChanged(); }
    void complete(bool m) { m_completed = m; emit completedChanged(); };
    void isInitial(bool m) { m_initial = m; emit initialChanged(); }

signals:
	void noPartChanged();
    void noRentChanged();
    void noAssetChanged();
    void noDeviceChanged();
	void namePartChanged();
    void nameDeviceChanged();
    void nameUserChanged();
    void nameAdminChanged();
    void dateBorrowedChanged();
    void dateReturnedChanged();
    void signUserChanged();
    void signAdminChanged();
    void completedChanged();
    void purposeChanged();
    void initialChanged();

private:
	int m_noPart = -1;
    int m_noRent = -1;
    int m_noDevice = -1;
    QString m_noAsset;
	QString m_namePart;
    QString m_nameDevice;
    QString m_nameUser;
    QString m_nameAdmin;
    QString m_dateBorrowed;
    QString m_dateReturned;
    QString m_signUser;
    QString m_signAdmin;
    QString m_purpose;
    bool m_completed = false;
    bool m_initial = false;
};

class Part : public QObject {
    Q_OBJECT
        Q_PROPERTY(int noPart READ noPart WRITE setNoPart NOTIFY noPartChanged)
        Q_PROPERTY(QString namePart READ namePart WRITE setNamePart NOTIFY namePartChanged)
        Q_PROPERTY(bool system READ system WRITE isSystem NOTIFY systemChanged)
public:
    int noPart() const { return m_noPart; }
    QString namePart() const { return m_namePart; }
    bool system() const { return m_system; }

    public slots :
    void setNoPart(const int m) { m_noPart = m; emit noPartChanged(); }
    void setNamePart(const QString &m) { m_namePart = m; emit namePartChanged(); }
    void isSystem(const bool m) { m_system = m; emit systemChanged(); }

signals:
    void noPartChanged();
    void namePartChanged();
    void systemChanged();

private:
    int m_noPart = -1;
    QString m_namePart;
    bool m_system = false;
};

class User : public QObject
{
	Q_OBJECT
		Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
		Q_PROPERTY(QString pass READ pass WRITE setPass NOTIFY passChanged)
		Q_PROPERTY(int noAdmin READ noAdmin WRITE setNoAdmin NOTIFY noAdminChanged)
		Q_PROPERTY(int typeAdmin READ typeAdmin WRITE setTypeAdmin NOTIFY typeAdminChanged)
		Q_PROPERTY(int noUser READ noUser WRITE setNoUser NOTIFY noUserChanged)
		Q_PROPERTY(QString nameUser READ nameUser WRITE setNameUser NOTIFY nameUserChanged)
		Q_PROPERTY(int noPart READ noPart WRITE setNoPart NOTIFY noPartChanged)
		Q_PROPERTY(QString namePart READ namePart WRITE setNamePart NOTIFY namePartChanged)
		Q_PROPERTY(int typeAlarm READ typeAlarm WRITE setTypeAlarm NOTIFY typeAlarmChanged)
		Q_PROPERTY(QString textAlarm READ textAlarm WRITE setTextAlarm NOTIFY textAlarmChanged)

public:
	enum UserType { None, PartManager, PartChair, SpecialList, SystemAdmin};

	int noAdmin() { return m_noAdmin; }
	int typeAdmin() { return m_typeAdmin; }
	int noUser() { return m_noUser; }
	QString nameUser() { return m_nameUser; }
	QString id() { return m_id; }
	QString pass() { return m_pass; }
	int noPart() { return m_noPart; }
	QString namePart() { return m_namePart; }
	int typeAlarm() { return m_typeAlarm; }
	QString textAlarm() { return m_textAlarm; }

	public slots:
	void setNoAdmin(int m) { m_noAdmin = m; }
	void setTypeAdmin(int m) { m_typeAdmin = m; }
	void setNoUser(int m) { m_noUser = m; }
	void setNameUser(QString m) { m_nameUser = m; }
	void setNoPart(int m) { m_noPart = m; }
	void setNamePart(QString m) { m_namePart = m; }
	void setTypeAlarm(int m) { m_typeAlarm = m; }
	void setTextAlarm(QString m) { m_textAlarm = m; }
	void setId(QString m) { m_id = m; }
	void setPass(QString m) { m_pass = m; }

	void clear()
	{
		m_noAdmin = 0;
		m_typeAdmin = 0;
		m_noUser = 0;
		m_nameUser = "";
		m_noPart = 0;
		m_namePart = "";
		m_typeAlarm = 0;
		m_textAlarm = "";
		m_id = "";
		m_pass = "";
	}

signals:
	void noAdminChanged();
	void typeAdminChanged();
	void noUserChanged();
	void nameUserChanged();
	void noPartChanged();
	void namePartChanged();
	void typeAlarmChanged();
	void textAlarmChanged();
	void idChanged();
	void passChanged();

private:
	int m_noAdmin = 0;
	int m_typeAdmin = 0;
	int m_noUser = 0;
	QString m_nameUser = "";
	int m_noPart = 0;
	QString m_namePart = "";
	int m_typeAlarm = 0;
	QString m_textAlarm = "";
	QString m_id = "";
	QString m_pass = "";
};

class Employee : public QObject {
    Q_OBJECT
        Q_PROPERTY(int noUser READ noUser WRITE setNoUser NOTIFY noUserChanged)
        Q_PROPERTY(QString nameUser READ nameUser WRITE setNameUser NOTIFY nameUserChanged)
        Q_PROPERTY(bool manager READ manager WRITE isManager NOTIFY isManagerChanged)
public:
    int noUser() const { return m_noUser; }
    QString nameUser() const { return m_nameUser; }
    bool manager() const { return m_manager; }

    public slots :
    void setNoUser(const int m) { m_noUser = m; emit noUserChanged(); }
    void setNameUser(const QString &m) { m_nameUser = m; emit nameUserChanged(); }
    void isManager(const bool m) { m_manager = m; emit isManagerChanged(); }

signals:
    void noUserChanged();
    void nameUserChanged();
    void isManagerChanged();

private:
    int m_noUser = -1;
    QString m_nameUser;
    bool m_manager = false;
};

class Sign : public QObject
{
	Q_OBJECT
		Q_PROPERTY(int noSign READ noSign WRITE setNoSign NOTIFY noSignChanged)
		Q_PROPERTY(QString namePart READ namePart WRITE setNamePart NOTIFY namePartChanged)
		Q_PROPERTY(int year READ year WRITE setYear NOTIFY yearChanged)
		Q_PROPERTY(int month READ month WRITE setMonth NOTIFY monthChanged)
		Q_PROPERTY(int typeComplete READ typeComplete WRITE setTypeComplete NOTIFY typeCompleteChanged)

public:
	int noSign() const { return m_noSign; }
	QString namePart() const { return m_namePart; }
	int year() const { return m_year; }
	int month() const { return m_month; }
	int typeComplete() const { return m_typeComplete; }

	public slots :
	void setNoSign(const int m) { m_noSign = m; emit noSignChanged(); }
	void setNamePart(const QString m) { m_namePart = m; emit namePartChanged(); }
	void setYear(const int m) { m_year = m; emit yearChanged(); }
	void setMonth(const int m) { m_month = m; emit monthChanged(); }
	void setTypeComplete(const int m) { m_typeComplete = m; emit typeCompleteChanged(); }

signals:
	void noSignChanged();
	void namePartChanged();
	void yearChanged();
	void monthChanged();
	void typeCompleteChanged();

private:
	int m_noSign = -1;
	QString m_namePart = "";
	int m_year = -1;
	int m_month = -1;
	int m_typeComplete = -1;
};

class Notificator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
        Q_PROPERTY(int no READ no WRITE setNo NOTIFY noChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(bool result READ result WRITE setResult NOTIFY resultChanged)
    Q_PROPERTY(bool dialog READ dialog WRITE showDialog NOTIFY dialogChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    enum UpdateType{
        None, File, Login, RequestLogin, Join, Logout, Exit, LogoutRequest,
        DVIList, DVIModified, DVISearch, DVIReturnedSearch,
        DVIBorrowed, DVIReturned,
        MNGList, MNGModified,
        EMPList, RequestPartsList,
		ErrorNoLogined, ErrorNoBarcode,
		OpenFromBorrow, OpenFromReturn,
		ErrorNoFile, ErrorNoSaveFile, ErrorNoRent, //ConfirmedRent
		Signed, SignForMonth
    };

    Notificator() { }
    Notificator(bool result, QString message, int type = UpdateType::None, bool dialog = true)
        : m_result(result), m_message(message), m_type(type), m_dialog(dialog) { }
    Notificator(bool result, QString message, QString url, QString name, int type = UpdateType::None)
        : m_result(result), m_message(message), m_type(type), m_url(url), m_name(name) { }
	Notificator(bool result, int type = UpdateType::None, QString message="")
		: m_result(result), m_type(type), m_message(message) {  }

    int type() const { return m_type; }
    int no() const { return m_no; }
    QString message() const { return m_message; }
    bool result() const { return m_result; }
    bool dialog() const { return m_dialog; }
    QString url() const { return m_url; }
    QString name() const { return m_name; }

    public slots :
    Notificator* setType(const int m) { m_type = m; emit typeChanged(); return this; }
    Notificator* setMessage(const QString &m) { m_message = m; emit messageChanged(); return this; }
    void setResult(const bool m) { m_result = m; emit resultChanged(); }
    Notificator* showDialog(const bool m) { m_dialog = m; emit dialogChanged(); return this; }
    Notificator* setUrl(const QString &m) { m_url = m; emit urlChanged(); return this; }
    Notificator* setName(const QString &m) { m_name = m; emit nameChanged(); return this; }
    void setNo(const int m) { m_no = m; emit noChanged(); }

signals:
    void typeChanged();
    void messageChanged();
    void resultChanged();
    void dialogChanged();
    void urlChanged();
    void nameChanged();
    void noChanged();

private:
    int m_type = -1;
    int m_no = -1;
    QString m_message = "";
    bool m_result = false;
    bool m_dialog = false;
    QString m_url = "";
    QString m_name = "";
};

class Model : public QObject {
    Q_OBJECT
        Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
        Q_PROPERTY(int selectedItem READ selectedItem WRITE selectItem NOTIFY itemSelected)
        Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
        Q_PROPERTY(QString dir READ dir WRITE setDir NOTIFY dirChanged)
        Q_PROPERTY(QString log READ log WRITE setLog NOTIFY logChanged)
        Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged)
        Q_PROPERTY(QString currentPage READ currentPage WRITE setCurrentPage NOTIFY pageChanged)
        Q_PROPERTY(bool full READ full WRITE setFull NOTIFY fullChanged)
        Q_PROPERTY(bool pressedCtrl READ pressedCtrl WRITE pressCtrl NOTIFY pressedCtrlChanged)
        Q_PROPERTY(bool modal READ modal WRITE setModal NOTIFY modalChanged)

        Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
        Q_PROPERTY(int scaledItemWidth READ scaledItemWidth WRITE setScaledItemWidth NOTIFY scaledItemWidthChanged)
        Q_PROPERTY(int scaledItemHeight READ scaledItemHeight WRITE setScaledItemHeight NOTIFY scaledItemHeightChanged)
        Q_PROPERTY(int itemFixedWidth READ itemFixedWidth WRITE setItemFixedWidth NOTIFY itemFixedWidthChanged)
        Q_PROPERTY(int itemFixedHeight READ itemFixedHeight WRITE setItemFixedHeight NOTIFY itemFixedHeightChanged)

        Q_PROPERTY(QList<Device*> devices READ devices WRITE setDevices NOTIFY devicesChanged)
        Q_PROPERTY(QList<Part*> parts READ parts WRITE setParts NOTIFY partsChanged)
        Q_PROPERTY(QList<Employee*> employees READ employees WRITE setEmployees NOTIFY employeesChanged)
        Q_PROPERTY(QList<Rent*> rents READ rents WRITE setRents NOTIFY rentsChanged)
		Q_PROPERTY(QList<Sign*> signatures READ signatures WRITE setSignatures NOTIFY signaturesChanged)

        Q_PROPERTY(bool alarmed READ alarmed WRITE alarm NOTIFY alarmedChanged)

        Q_PROPERTY(int countTotalDevice READ countTotalDevice WRITE setCountTotalDevice NOTIFY countTotalDeviceChanged)
        Q_PROPERTY(int countCurrentDevice READ countCurrentDevice WRITE setCountCurrentDevice NOTIFY countCurrentDeviceChanged)
        Q_PROPERTY(int pageNumber READ pageNumber WRITE setPageNumber NOTIFY pageNumberChanged)

        Q_PROPERTY(Device* searchedDevice READ searchedDevice WRITE setSearchedDevice NOTIFY searchedDeviceChanged)
        Q_PROPERTY(Rent* searchedRent READ searchedRent WRITE setSearchedRent NOTIFY searchedRentChanged)
		Q_PROPERTY(User* user READ user WRITE setUser NOTIFY userChanged)

        Q_PROPERTY(QString fileUrl READ fileUrl WRITE setFileUrl NOTIFY fileUrlChanged)


        Q_PROPERTY(int messageInt READ messageInt WRITE setMessageInt NOTIFY messageIntChanged)
private:
    Model()
    {
        m_notificator = new Notificator();
		m_user = new User();
    }
    static Model* m_instance;
public:
    static Model* instance() {
        if (m_instance == nullptr)
        {
            m_instance = new Model();
        }
        return m_instance;
    }

    QList<Device*> devices() { return m_devices; }
    int countDevice() { return m_devices.size(); }

    int countTotalDevice() { return m_countTotalDevice; }
    int countCurrentDevice() { return m_countCurrentDevice; }

    QList<Part*> parts() { return m_parts; }
    int countPart() { return m_parts.size(); }

    QList<Employee*> employees() { return m_employees; }
    int countEmployee() { return m_employees.size(); }

    QList<Rent*> rents() { return m_rents; }
    int countRent() { return m_rents.size(); }

	QList<Sign*> signatures() { return m_signatures; }
	int countSignatures() { return m_signatures.size(); }

    QString message() const { return m_message; }
    int selectedItem() const { return m_selectedItem; }
    QString path() const { return m_path; }
    QString dir() const { return m_dir; }
    QString log() const { return m_log; }
    QString date() const { return m_date; }
    bool full() const { return m_full; }
    bool pressedCtrl() const { return m_pressedCtrl; }
    bool modal() const { return m_modal; }
	bool checkedAuto() { return m_checkedAuto; }

    qreal scale() const { return m_scale; }
    int scaledItemWidth() const { return m_scaledItemWidth; }
    int scaledItemHeight() const { return m_scaledItemHeight; }
    int itemFixedWidth() const { return m_itemFixedWidth; }
    int itemFixedHeight() const { return m_itemFixedHeight; }
    QString currentPage() const { return m_currentPage;  }

    bool alarmed() const { return m_alarmed; }
    Notificator* notificator() { return m_notificator; }
    int pageNumber() const { return m_pageNumber; }

    Device* searchedDevice() { return m_searchedDevice;  }
    Rent* searchedRent() { return m_searchedRent; }
	User* user() { return m_user; }
    QString fileUrl() { QString tmp = m_fileUrl; m_fileUrl = ""; return tmp; }

    int messageInt() {
        int tmp = m_messageInt;
        m_messageInt = -1;
        return tmp;
    }

	Notificator::UpdateType messageUpdateType() 
	{
		Notificator::UpdateType tmp = m_messageUpdateType;
		m_messageUpdateType = Notificator::None;
		return tmp;
	}
	bool isLogined() { return m_logined; }
    public slots:
    void setDevices(QList<Device*> m) { m_devices.clear(); m_devices = m; emit devicesChanged(); }
    void setParts(QList<Part*> m) { m_parts.clear();  m_parts = m; emit partsChanged(); }
    void setEmployees(QList<Employee*> m) { m_employees.clear();  m_employees = m; emit employeesChanged(); }
    void setRents(QList<Rent*> m) { m_rents.clear();  m_rents = m; emit rentsChanged(); }
	void setSignatures(QList<Sign*> m) { 
		m_signatures.clear();  
		m_signatures = m; 
		emit signaturesChanged(); }
    void setMessage(QString m) { m_message = m; emit messageChanged(); }
    void selectItem(int m) { m_selectedItem = m; emit itemSelected(); }
    void setPath(QString m) { m_path = m; emit pathChanged(); }
    void setDir(QString m) { m_dir = m; emit dirChanged(); }
    void setLog(QString m) { m_log = m; emit logChanged(); }
    void setDate(QString m) { m_date = m; emit dateChanged(); }
    void setFull(bool m) { m_full = m; emit fullChanged(); }
    void pressCtrl(bool m) { m_pressedCtrl = m; emit pressedCtrlChanged(); }
    void setModal(bool m) { m_modal = m; emit modalChanged(); }

    void setScale(qreal m) { m_scale = m; emit scaleChanged(); }
    void setScaledItemWidth(int m) { m_scaledItemWidth = m; emit scaledItemWidthChanged(); }
    void setScaledItemHeight(int m) { m_scaledItemHeight = m; emit scaledItemHeightChanged(); }
    void setItemFixedWidth(int m) { m_itemFixedWidth = m; emit itemFixedWidthChanged(); }
    void setItemFixedHeight(int m) { m_itemFixedHeight = m; emit itemFixedHeightChanged(); }
    void setCurrentPage(QString &m) { m_currentPage = m; emit pageChanged(); }

    void alarm(bool m) { m_alarmed = m; emit alarmedChanged(); }
    void setNotificator(Notificator* m) { m_notificator = m; alarm(true); }

    void setCountTotalDevice(int m) { m_countTotalDevice = m; emit countTotalDeviceChanged(); }
    void setCountCurrentDevice(int m) { m_countCurrentDevice = m; emit countCurrentDeviceChanged(); }
    void setPageNumber(int m) { m_pageNumber = m; emit pageNumberChanged(); }

    void setSearchedDevice(Device* m) { m_searchedDevice = m; emit searchedDeviceChanged(); }
    void setSearchedRent(Rent* m) { m_searchedRent = m; emit searchedRentChanged(); }
    void setFileUrl(QString &m) { m_fileUrl = m; emit fileUrlChanged(); }
    void setMessageInt(int m) { m_messageInt = m; emit messageIntChanged(); }
	void setUser(User* m) { m_user = m; emit userChanged(); }
	void checkAuto(bool m) { m_checkedAuto = m; }
	void login(bool m) { m_logined = m; }

	void request(bool result, Notificator::UpdateType type, QString message="")
	{
		setNotificator(new Notificator(result, type, message));
	}
signals:
    void messageChanged();
    void itemSelected();
    void pathChanged();
    void dirChanged();
    void logChanged();
    void dateChanged();
    void dirRemove();
    void dirRefresh();
    void logClear();
    void zoomIn();
    void zoomOut();
    void fullChanged();
    void pressedCtrlChanged();
    void modalChanged();
    void scaleChanged();
    void scaledItemWidthChanged();
    void scaledItemHeightChanged();
    void itemFixedWidthChanged();
    void itemFixedHeightChanged();

    void devicesChanged();
    void partsChanged();
    void employeesChanged();
    void rentsChanged();
    void pageChanged();

    void alarmedChanged();

    void countTotalDeviceChanged();
    void countCurrentDeviceChanged();
    void pageNumberChanged();

    void searchedDeviceChanged();
    void searchedRentChanged();

    void fileUrlChanged();
    void messageIntChanged();
	void userChanged();
	void signaturesChanged();

private:
    QList<Device*> m_devices;
    QList<Part*> m_parts;
    QList<Employee*> m_employees;
    QList<Rent*> m_rents;
	QList<Sign*> m_signatures;
    QString m_message;
    int m_selectedItem;
    QString m_path;
    QString m_dir;
    QString m_log;
    QString m_date;
    QString m_currentPage;
    bool m_full = false;
    bool m_pressedCtrl = false;
    bool m_modal = false;
	bool m_checkedAuto = false;
	bool m_logined = false;
	
    qreal m_scale = 1;
    int m_scaledItemWidth = 720;
    int m_scaledItemHeight = 1080;
    int m_itemFixedWidth = 720;
    int m_itemFixedHeight = 1280;

    bool m_alarmed = false;
    Notificator* m_notificator;

    int m_countTotalDevice = 0;
    int m_countCurrentDevice = 0;
    int m_pageNumber = 1;

    Device* m_searchedDevice = nullptr;
    Rent* m_searchedRent = nullptr;

    QString m_fileUrl = "";
    int m_messageInt = -1;
	Notificator::UpdateType m_messageUpdateType = Notificator::None;

	User* m_user;
};
