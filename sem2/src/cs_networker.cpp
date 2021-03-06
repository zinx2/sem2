﻿#include "cs_networker.h"
#include <QMutexLocker>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "cs_model.h"
#include <QHttpMultiPart>
#include <QDir>
//#include "imageresponseprovider.h"

NetWorker* NetWorker::m_instance = nullptr;
NetWorker::NetWorker(QObject *parent) : QObject(parent)
{
    m = Model::instance();
    connect(this, SIGNAL(next()), this, SLOT(request()));
}
NetWorker::~NetWorker()
{
    //delete m_model;
}

void NetWorker::request()
{
    if (m_hosts.isEmpty())
        return;

    NetHost* host = m_hosts.front();
    QNetworkRequest req;

    if (!host->type().compare("post"))
    {
        QUrl url(DOMAIN_NAME + host->addr());
        QNetworkRequest req(url);
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=UTF-8");
        m_netReply = m_netManager.post(req, host->queries().toString(QUrl::FullyDecoded).toUtf8());
    }
    else if (!host->type().compare("get"))
    {
        req = createRequest(host->addr(), host->queries());
        m_netReply = m_netManager.get(req);
    }
    else if (!host->type().compare("file"))
    {
        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart imagePart;
        imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg")); /*jpeg*/
        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"" + host->file() + "\""));

        QFile *file = new QFile(host->file());
        file->open(QIODevice::ReadOnly);
        imagePart.setBodyDevice(file);
        file->setParent(multiPart);
        multiPart->append(imagePart);

        QUrl url(DOMAIN_NAME + host->addr());
        if (!host->queries().isEmpty())
            url.setQuery(host->queries());

        req.setUrl(url);
        m_netReply = m_netManager.post(req, multiPart);
        multiPart->setParent(m_netReply);

        /*QUrl url(DOMAIN_NAME + host->addr());
        QNetworkRequest req(url);
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=UTF-8");
        m_netReply = m_netManager.post(req, multiPart);
        multiPart->setParent(m_netReply);*/


    }
    else return;

    qDebug() << "########## NETWORK INFORMATION ##########";
    QString msg = DOMAIN_NAME + host->addr();
    QList<QPair<QString, QString>> qItems = host->queries().queryItems();
    int size = qItems.size();
    if (size > 0)
    {
        for(int i=0; i<size; i++)
        {
            QPair<QString, QString> p = qItems.at(i);
            msg  += "\n[" + QString::number(i + 1) + "] key: " + p.first  + ", value: " +  p.second;
        }
    }
    qDebug().noquote() << msg;
    qDebug() << "#########################################";

    connect(m_netReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, QOverload<QNetworkReply::NetworkError>::of(&NetWorker::httpError));
    connect(m_netReply, &QNetworkReply::finished, host->func());
    connect(m_netReply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(progress(qint64, qint64)));
    m_hosts.pop_front();
}

void NetWorker::done()
{
    qDebug() << "done";
    QMutexLocker locker(&m_mtx);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
    QJsonObject jsonObj = jsonDoc.object();
    bool isSuccess = jsonObj["is_success"].toBool();
    QString url = jsonObj["file_url"].toString();
    QString name = jsonObj["file_name"].toString();

    Notificator * nott = new Notificator(isSuccess, jsonObj["error_message"].toString(), url, name, Notificator::File);
    nott->showDialog(true);
    m->setNotificator(nott);
}
void NetWorker::progress(qint64 a, qint64 b)
{
    qDebug() << a << "/" << b;
}
QNetworkRequest NetWorker::createRequest(QString suffixUrl, QUrlQuery queries)
{
    QUrl url(DOMAIN_NAME + suffixUrl);
    if (!queries.isEmpty())
        url.setQuery(queries);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=UTF-8");

    queries.clear();
    return request;
}

void NetWorker::httpError(QNetworkReply::NetworkError msg)
{
    qDebug() << "[**] THE ERROR WAS OCCURED. " << msg;
}
NetWorker* NetWorker::join(QString id, QString pass, int noPart, int noUser)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("id", id);
	queries.addQueryItem("password", pass);
	queries.addQueryItem("part_no", QString("%1").arg(noPart));
	queries.addQueryItem("sem_user_no", QString("%1").arg(noUser));
	
	m_hosts.append(new NetHost("post", "/sem/joinManager", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		m_netReply->deleteLater();

		Notificator* noti = new Notificator();
		int noAdmin = 0;
		QString error = "";
		if (isSuccess)
			noAdmin = jsonObj["admin_no"].toInt();
		else
			error = jsonObj["error_message"].toString();

		noti->setResult(isSuccess);
		noti->setNo(noAdmin);
		noti->setType(Notificator::Join);
		noti->setMessage(error);		
		m->setNotificator(noti);

		m_netReply->deleteLater();
		emit next();
	}));
	return this;
}
NetWorker* NetWorker::login(QString id, QString pass)
{
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("id", id);
	queries.addQueryItem("password", pass);
	m->user()->setId(id);
	m->user()->setPass(pass);

	m_hosts.append(new NetHost("post", "/sem/loginManager", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		m_netReply->deleteLater();

		Notificator* noti = new Notificator();
		int noAdmin = 0;
		QString error = "";
		if (isSuccess)
		{
			m->user()->setNoAdmin(jsonObj["admin_no"].toInt());
			m->user()->setTypeAdmin(jsonObj["admin_type"].toInt());
			m->user()->setNoUser(jsonObj["user_no"].toInt());
			m->user()->setNameUser(jsonObj["user_name"].toString());
			m->user()->setNoPart(jsonObj["part_no"].toInt());
			m->user()->setNamePart(jsonObj["part_name"].toString());
			m->user()->setTypeAlarm(jsonObj["alarm_type"].toInt());
			m->user()->setTextAlarm(jsonObj["alarm_text"].toString());
			qDebug() << kr("관리자번호") <<jsonObj["admin_no"].toInt();
			qDebug() << kr("사용자이름") << jsonObj["user_name"].toString();
			qDebug() << kr("파트이름") << jsonObj["part_name"].toString();
			qDebug() << kr("파트번호") << jsonObj["part_no"].toInt();
			qDebug() << kr("관리자타입") << jsonObj["admin_type"].toInt();
		}
		else
			error = jsonObj["error_message"].toString();

		noti->setResult(isSuccess);
		noti->setNo(noAdmin);
		noti->setType(Notificator::Login);
		noti->setMessage(error);
		m->setNotificator(noti);
		m_netReply->deleteLater();
		emit next();
	}));
	return this;
}

NetWorker* NetWorker::logout()
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("sem_admin_no", QString("%1").arg(m->user()->noAdmin()));

	m_hosts.append(new NetHost("post", "/sem/logout", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		m_netReply->deleteLater();

		Notificator* noti = new Notificator();
		int noAdmin = 0;
		QString error = "";
		if (!isSuccess)
			error = jsonObj["error_message"].toString();

		noti->setResult(isSuccess);
		noti->setType(Notificator::Logout);
		noti->setMessage(error);
		m->setNotificator(noti);

		m_netReply->deleteLater();
		emit next();
	}));
	return this;
}
NetWorker* NetWorker::getUserList()
{
    m_hosts.append(new NetHost("post", "/sem/getUserList",
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        if (!isSuccess) {
			m->request(false, Notificator::None, jsonObj["error_message"].toString());
            m_netReply->deleteLater();
            emit next(); return;
        }

        QList<Employee*> list;
        QJsonArray jsonArr = jsonObj["data_list"].toArray();
		qDebug() << "@@@ getUserList @@@";
        foreach(const QJsonValue &value, jsonArr)
        {
            QJsonObject obj = value.toObject();

            Employee* d = new Employee();
            d->setNoUser(obj["sem_user_no"].toInt());
            d->setNameUser(obj["sem_user_name"].toString());
            d->isManager(obj["sem_is_admin"].toInt());
            qDebug() << d->noUser() << "/" << d->nameUser() << "/" << d->manager();
            list.append(d);
        }
		qDebug() << "@@@@@@@@@@@@@@@@@@@";
        m->setEmployees(list);
        m_netReply->deleteLater();
        emit next();
    }));
    return this;
}
NetWorker* NetWorker::getPartList()
{
    m_hosts.append(new NetHost("post", "/sem/getPartList",
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        if (!isSuccess) {
			m->request(false, Notificator::None, jsonObj["error_message"].toString());
            m_netReply->deleteLater();
            emit next(); return;
        }

        QList<Part*> list;
        QJsonArray jsonArr = jsonObj["data_list"].toArray();
        foreach(const QJsonValue &value, jsonArr)
        {
            QJsonObject obj = value.toObject();

            Part* d = new Part();
            d->setNoPart(obj["part_no"].toInt());
            d->setNamePart(obj["part_name"].toString());
            d->isSystem(obj["is_system_part"].toInt());
            qDebug() << d->noPart() << "/" << d->namePart() << "/" << d->system();
            list.append(d);
        }
        m->setParts(list);
        m_netReply->deleteLater();
        emit next();
    }));
    return this;
}
NetWorker* NetWorker::getDeviceList(int searchType, int now)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("search_type", QString("%1").arg(searchType));
    queries.addQueryItem("now_page", QString("%1").arg(m->pageNumber()));
    qDebug() << m->pageNumber();

    m_hosts.append(new NetHost("post", "/sem/getDeviceList", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        qDebug() << m_netReply->readAll();
        bool isSuccess = jsonObj["is_success"].toBool();
        if (!isSuccess) {
			m->request(false, Notificator::None, jsonObj["error_message"].toString());
            m_netReply->deleteLater();
            emit next(); return;
        }
        int totalPage = jsonObj["total_page"].toInt();

        QList<Device*> list;
        QJsonArray jsonArr = jsonObj["data_list"].toArray();
        int count = 0;
        foreach(const QJsonValue &value, jsonArr)
        {
            QJsonObject obj = value.toObject();

            Device *d = new Device();
            d->setNoDevice(obj["sem_device_no"].toInt());
            d->setNameDevice(obj["device_name"].toString());
            d->setNoAsset(obj["asset_no"].toString());
            d->setBarcode(obj["barcode"].toString());
            d->setPrice(obj["get_money"].toInt());
            d->setDateTaked(obj["get_date"].toString());
            d->setMemo(obj["memo"].toString());
            d->borrow(obj["is_rented"].toInt());
            qDebug() << d->noDevice() << "/" << d->nameDevice() << d->noAsset() << "/" << d->barcode() << "/" << d->price() << "/" << d->dateTaked() << "/" << d->memo() << "/" << d->borrowed();
            list.append(d);
            count++;
        }
        m->setCountTotalDevice(totalPage);
        m->setCountCurrentDevice((m->pageNumber() - 1)*COUNT_PAGE + count);
        //m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVIList, false));
        //m->setPageNumber((m->countCurrentDevice() / COUNT_PAGE) + 1);

        m->setDevices(list);
        m_netReply->deleteLater(); emit next();
    }));
    return this;
}
NetWorker* NetWorker::getDeviceListForAdmin(int noPart, int searchType, int now)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("sem_part_no", QString("%1").arg(noPart));
	queries.addQueryItem("search_type", QString("%1").arg(searchType));
	queries.addQueryItem("now_page", QString("%1").arg(m->pageNumber()));

	m_hosts.append(new NetHost("post", "/sem/getDeviceListForAdmin", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		qDebug() << m_netReply->readAll();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess) {
			m->request(false, Notificator::None, jsonObj["error_message"].toString());
			m_netReply->deleteLater();
			emit next(); return;
		}
		int totalPage = jsonObj["total_page"].toInt();

		QList<Device*> list;
		QJsonArray jsonArr = jsonObj["data_list"].toArray();
		int count = 0;
		foreach(const QJsonValue &value, jsonArr)
		{
			QJsonObject obj = value.toObject();

			Device *d = new Device();
			d->setNoDevice(obj["sem_device_no"].toInt());
			d->setNameDevice(obj["device_name"].toString());
			d->setNoAsset(obj["asset_no"].toString());
			d->setBarcode(obj["barcode"].toString());
			d->setPrice(obj["get_money"].toInt());
			d->setDateTaked(obj["get_date"].toString());
			d->setMemo(obj["memo"].toString());
			d->borrow(obj["is_rented"].toInt());
			d->setNamePart(obj["part_name"].toString());
			qDebug() << d->noDevice() << "/" << d->nameDevice() << d->noAsset() << "/" << d->barcode() 
				<< "/" << d->price() << "/" << d->dateTaked() << "/" << d->memo() << "/" << d->borrowed()
				<< "/" << d->namePart();
			list.append(d);
			count++;
		}
		m->setCountTotalDevice(totalPage);
		m->setCountCurrentDevice((m->pageNumber() - 1)*COUNT_PAGE + count);
		//m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVIList, false));
		//m->setPageNumber((m->countCurrentDevice() / COUNT_PAGE) + 1);

		m->setDevices(list);
		m_netReply->deleteLater(); emit next();
	}));
	return this;
}
NetWorker* NetWorker::getRentList(int type, int year, int month)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

	if (type == 0)
	{
		year = 0; month = 0;
	}


    /********** SET URL QUERIES **********/
    QUrlQuery queries;
	queries.addQueryItem("search_type", QString("%1").arg(type));
    queries.addQueryItem("search_year", QString("%1").arg(year));
	queries.addQueryItem("search_month", QString("%1").arg(month));

    m_hosts.append(new NetHost("post", "/sem/getRentList", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        if (!isSuccess) {
			m->request(false, Notificator::None, jsonObj["error_message"].toString());
			qDebug() << jsonObj["error_message"].toString();
            m_netReply->deleteLater();
            emit next(); return;
        }
        int totalPage = jsonObj["total_page"].toInt();

        QList<Rent*> list;
        QJsonArray jsonArr = jsonObj["data_list"].toArray();
        int count = 0;
        foreach(const QJsonValue &value, jsonArr)
        {
            QJsonObject obj = value.toObject();
            Rent *d = new Rent();
            d->setNoRent(obj["rent_no"].toInt());
            d->setNameUser(obj["sem_user_name"].toString());
            d->setNoDevice(obj["sem_device_no"].toInt());
            d->setNameDevice(obj["device_name"].toString());
            d->setNoAsset(obj["asset_no"].toString());
            d->setDateBorrowed(obj["rent_date"].toString());
            QString confirmer = obj["confirm_user_name"].toString();
            QString dateReturned = confirmer.isEmpty() ? "" : obj["return_date"].toString();
            d->setNameAdmin(confirmer);
            d->setDateReturned(dateReturned);
            d->setSignUser(obj["signature"].toString());
            d->complete(obj["is_complete"].toInt() > 0 ? true : false);
            d->setSignAdmin(obj["confirm_signature"].toString());
            d->setPurpose(obj["purpose"].toString());
			d->setNoPart(obj["sem_part_no"].toInt());
			d->setNamePart(obj["sem_part_name"].toString());
            d->isInitial(obj["is_initial"].toInt());
            qDebug() << d->noRent() << "##/" << d->nameUser() << "/" << d->dateReturned();
            list.append(d);
            count++;
        }
        m->setCountTotalDevice(totalPage);
        m->setCountCurrentDevice((m->pageNumber() - 1)*COUNT_PAGE + count);
        m->setRents(list);
        m_netReply->deleteLater();
        emit next();
    }));
    return this;
}
NetWorker* NetWorker::getRentListForAdmin(int type, int year, int month)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("search_type", QString("%1").arg(type));
	queries.addQueryItem("search_year", QString("%1").arg(year));
	queries.addQueryItem("search_month", QString("%1").arg(month));
	queries.addQueryItem("sem_part_no", QString("%1").arg(0));

	m_hosts.append(new NetHost("post", "/sem/getRentListForAdmin", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess) {
			qDebug() << jsonObj["error_message"].toString();
			m->request(false, Notificator::None, jsonObj["error_message"].toString());
			m_netReply->deleteLater();
			emit next(); return;
		}
		int totalPage = jsonObj["total_count"].toInt();

		QList<Rent*> list;
		QJsonArray jsonArr = jsonObj["data_list"].toArray();
		int count = 0;
		foreach(const QJsonValue &value, jsonArr)
		{
			QJsonObject obj = value.toObject();
			Rent *d = new Rent();
			d->setNoRent(obj["rent_no"].toInt());
			d->setNameUser(obj["sem_user_name"].toString());
			d->setNoDevice(obj["sem_device_no"].toInt());
			d->setNameDevice(obj["device_name"].toString());
			d->setNoAsset(obj["asset_no"].toString());
			d->setDateBorrowed(obj["rent_date"].toString());
			QString confirmer = obj["confirm_user_name"].toString();
			QString dateReturned = confirmer.isEmpty() ? "" : obj["return_date"].toString();
			d->setNameAdmin(confirmer);
			d->setDateReturned(dateReturned);
			d->setSignUser(obj["signature"].toString());
			d->complete(obj["is_complete"].toInt());
			d->setSignAdmin(obj["confirm_signature"].toString());
			d->setPurpose(obj["purpose"].toString());
			d->setNoPart(obj["sem_part_no"].toInt());
			d->setNamePart(obj["origin_part_name"].toString());
			d->isInitial(obj["is_initial"].toInt());
			qDebug() << d->noRent() << "##/" << d->nameUser() << "/" << d->dateReturned();
			list.append(d);
			count++;
		}
		m->setCountTotalDevice(totalPage);
		m->setCountCurrentDevice((m->pageNumber() - 1)*COUNT_PAGE + count);
		m->setRents(list);
		m_netReply->deleteLater();
		emit next();
	}));
	return this;
}
NetWorker* NetWorker::getTotalRentListMonth(int year, int month)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("year", QString("%1").arg(year));
	queries.addQueryItem("month", QString("%1").arg(month));

	m_hosts.append(new NetHost("post", "/sem/getTotalRentListMonth", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess) {
			qDebug() << jsonObj["error_message"].toString();
			m->request(false, Notificator::None, jsonObj["error_message"].toString());
			m_netReply->deleteLater();
			emit next(); return;
		}
		int totalPage = jsonObj["total_count"].toInt();

		QList<Rent*> list;
		QJsonArray jsonArr = jsonObj["data_list1"].toArray();
		foreach(const QJsonValue &value, jsonArr)
		{
			QJsonObject obj = value.toObject();
			Rent *d = new Rent();
			d->setNoRent(obj["rent_no"].toInt());
			d->setNameUser(obj["sem_user_name"].toString());
			d->setNoDevice(obj["sem_device_no"].toInt());
			d->setNameDevice(obj["device_name"].toString());
			d->setNoAsset(obj["asset_no"].toString());
			d->setDateBorrowed(obj["rent_date"].toString());
			QString confirmer = obj["confirm_user_name"].toString();
			QString dateReturned = confirmer.isEmpty() ? "" : obj["return_date"].toString();
			d->setNameAdmin(confirmer);
			d->setDateReturned(dateReturned);
			d->setSignUser(obj["signature"].toString());
			d->complete(obj["is_complete"].toInt());
			d->setSignAdmin(obj["confirm_signature"].toString());
			d->setPurpose(obj["purpose"].toString());
			//d->setNoPart(obj["sem_part_no"].toInt());
			d->setNamePart(obj["sem_part_name"].toString());
			d->isInitial(obj["is_initial"].toInt());
			qDebug() << d->noRent() << "##/" << d->nameUser() << "/" << d->dateReturned() <<"/"<<d->namePart();
			list.append(d);
		}
		m->setRents(list);

		QList<Sign*> list2;
		QJsonArray jsonArr2 = jsonObj["data_list2"].toArray();
		foreach(const QJsonValue &value, jsonArr2)
		{
			QJsonObject obj = value.toObject();
			Sign *s = new Sign();
			s->setNoSign(obj["superior_sign_no"].toInt());
			s->setNamePart(obj["sem_part_name"].toString());
			s->setYear(obj["year"].toInt());
			s->setMonth(obj["month"].toInt());
			s->setTypeComplete(obj["is_complete"].toInt());
			qDebug() << s->noSign() << "@@/" << s->namePart() << "/" << s->year()
			<< s->month() << "/" << s->typeComplete();
			list2.append(s);
		}
		m->setSignatures(list2);
		m->request(true, Notificator::MNGList);
		m_netReply->deleteLater();
		emit next();
	}));
	return this;
}

NetWorker* NetWorker::borrowDevice(QString barcode, int noUser, QString purpose)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("barcode", QString("%1").arg(barcode));
    queries.addQueryItem("sem_user_no", QString("%1").arg(noUser));
    queries.addQueryItem("purpose", purpose);

    m_hosts.append(new NetHost("post", "/sem/rentDevice", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        m_netReply->deleteLater();
        if (isSuccess)
        {
            int noRent = jsonObj["rent_no"].toInt();
            m->setMessageInt(noRent);
			uploadFileBorrowed("tmp.jpg")->request();
        }
		else
		{
			m->request(false, Notificator::None, jsonObj["error_message"].toString());
		}

        /*emit next();*/
    }));
    return this;
}
NetWorker* NetWorker::addDevice(int noPart, QString nameDevice, QString noAsset, QString barcode, QString price, QString date, QString memo)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("part_no", QString("%1").arg(noPart));
    queries.addQueryItem("device_name", nameDevice);
    queries.addQueryItem("asset_no", noAsset);
    queries.addQueryItem("barcode", barcode);
    queries.addQueryItem("get_money", price);
    queries.addQueryItem("get_date", date);
    queries.addQueryItem("memo", memo);

    m_hosts.append(new NetHost("post", "/sem/setDevice", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
		if (isSuccess)
		{
			int total = m->countTotalDevice() + 1;
			int pageNumber = total / COUNT_PAGE;
			m->setPageNumber(pageNumber + 1);
		}

        m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVIList));
        m_netReply->deleteLater();


    }));
    return this;
}
NetWorker* NetWorker::editDevice(int noDevice, int noPart, QString nameDevice, QString noAsset, QString barcode, QString price, QString date, QString memo) 
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("sem_device_no", QString("%1").arg(noDevice));
    queries.addQueryItem("part_no", QString("%1").arg(noPart));
    queries.addQueryItem("device_name", nameDevice);
    queries.addQueryItem("asset_no", noAsset);
    queries.addQueryItem("barcode", barcode);
    queries.addQueryItem("get_money", price);
    queries.addQueryItem("get_date", date);
    queries.addQueryItem("memo", memo);

    m_hosts.append(new NetHost("post", "/sem/updateDevice", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVIList));
        m_netReply->deleteLater();
    }));
    return this;
}
NetWorker* NetWorker::removeDevice(int noDevice)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("sem_device_no", QString("%1").arg(noDevice));

    m_hosts.append(new NetHost("post", "/sem/deleteDevice", queries,
        [=]()-> void {
        QMutexLocker locker(&m_mtx);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
		if ((m->countCurrentDevice() - 1) % COUNT_PAGE == 0)
		{
			if (m->pageNumber() > 1)
				m->setPageNumber(m->pageNumber() - 1);
		}
        m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVIList));
        m_netReply->deleteLater();        
    }));
    return this;
}
NetWorker* NetWorker::signBorrow()
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}
	QString fileUrl = m->fileUrl();
	if (fileUrl.isEmpty())
	{
		m->request(false, Notificator::ErrorNoFile);
		return this;
	}
	int noRent = m->messageInt();
	if (noRent < 0)
	{
		m->request(false, Notificator::ErrorNoRent);
		return this;
	}

    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("sig_url", fileUrl);
    queries.addQueryItem("rent_no", QString("%1").arg(noRent));

    m_hosts.append(new NetHost("post", "/sem/setSign", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        m_netReply->deleteLater();
        m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVIList));
        emit next();
    }));
    return this;
}
NetWorker* NetWorker::signReturn()
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}
	QString fileUrl = m->fileUrl();
	if (fileUrl.isEmpty())
	{
		m->request(false, Notificator::ErrorNoFile);
		return this;
	}
	int noRent = m->messageInt();
	if (noRent < 0)
	{
		m->request(false, Notificator::ErrorNoRent);
		return this;
	}

    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("sig_url", fileUrl);
    queries.addQueryItem("rent_no", QString("%1").arg(noRent));

    m_hosts.append(new NetHost("post", "/sem/setReturnSign", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        m_netReply->deleteLater();
        m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVIList));
        emit next();
    }));
    return this;
}
NetWorker* NetWorker::signForMonth()
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}
	QString fileUrl = m->fileUrl();
	if (fileUrl.isEmpty())
	{
		m->request(false, Notificator::ErrorNoFile);
		return this;
	}
	int noSign = m->messageInt();
	if (noSign < 0)
	{
		m->request(false, Notificator::ErrorNoRent);
		return this;
	}
	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("superior_sign_no", QString("%1").arg(noSign));
	queries.addQueryItem("sign_url", QString("%1").arg(fileUrl));
	m->setMessageInt(noSign);

	m_hosts.append(new NetHost("post", "/sem/setSignForMonth", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (isSuccess)
		{
			int noSign = m->messageInt();
			foreach(Sign* s, m->signatures())
			{
				if (s->noSign() == noSign) s->setTypeComplete(s->typeComplete() + 1);
			}
		}
		m->request(isSuccess, Notificator::Signed, jsonObj["error_message"].toString());
		m_netReply->deleteLater();
		emit next();
	}));
	return this;
}
NetWorker* NetWorker::returnDevice(QString barcode, bool isInitial)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("barcode", barcode);
    //queries.addQueryItem("confirm_user_no", QString("%1").arg(noAdmin));
    //queries.addQueryItem("sem_device_no", QString("%1").arg(noDevice));
    queries.addQueryItem("is_initial", QString("%1").arg(isInitial));

    m_hosts.append(new NetHost("post", "/sem/returnDevice", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        m_netReply->deleteLater();
        if (isSuccess)
        {
            int noRent = jsonObj["rent_no"].toInt();
			if (noRent == 0)
			{
				m->request(false, Notificator::None, kr("장비 정보를 확인할 수 없습니다."));
				return;
			}
            m->setMessageInt(noRent);
			uploadFileReturned("tmp.jpg")->request();
        }
		else
		{
			m->request(false, Notificator::None, jsonObj["error_message"].toString());
		}

        /*emit next();*/
    }));
    return this;
}
NetWorker* NetWorker::uploadFileBorrowed(QString fileName)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}
	if (fileName.isEmpty())
	{
		m->request(false, Notificator::ErrorNoFile);
		return this;
	}
    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("file_name", fileName);

    m_hosts.append(new NetHost("file", "/uploadMissionAnswerFile", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        QString url = jsonObj["file_url"].toString();
        QString name = jsonObj["file_name"].toString();
        m_netReply->deleteLater();
        m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::File, false));
        m->setFileUrl(url);
        signBorrow()->request();
        //emit next();
    }, fileName));
    return this;
}
NetWorker* NetWorker::uploadFileReturned(QString fileName)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}
	if (fileName.isEmpty())
	{
		m->request(false, Notificator::ErrorNoFile);
		return this;
	}

    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("file_name", fileName);

    m_hosts.append(new NetHost("file", "/uploadMissionAnswerFile", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        QString url = jsonObj["file_url"].toString();
        QString name = jsonObj["file_name"].toString();
        m_netReply->deleteLater();
        m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::File, false));
        m->setFileUrl(url);
        signReturn()->request();
        //emit next();
    }, fileName));
    return this;
}
NetWorker* NetWorker::uploadFileSignForMonth(QString fileName)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}
	if (fileName.isEmpty())
	{
		m->request(false, Notificator::ErrorNoFile);
		return this;
	}

	/********** SET URL QUERIES **********/
	QUrlQuery queries;
	queries.addQueryItem("file_name", fileName);

	m_hosts.append(new NetHost("file", "/uploadMissionAnswerFile", queries,
		[&]()-> void {
		QMutexLocker locker(&m_mtx);

		QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
		QJsonObject jsonObj = jsonDoc.object();
		bool isSuccess = jsonObj["is_success"].toBool();
		if (!isSuccess)
		{
			m->request(false, Notificator::None, jsonObj["error_message"].toString());
			m_netReply->deleteLater();
			return;
		}
		else
		{
			QString url = jsonObj["file_url"].toString();
			QString name = jsonObj["file_name"].toString();
			m->setFileUrl(url);
			m->request(false, Notificator::SignForMonth, jsonObj["error_message"].toString());
		}
		m_netReply->deleteLater();
		//emit next();
	}, fileName));
	return this;
}
NetWorker* NetWorker::uploadFile(QString fileName)
{
    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("file_name", fileName);

    m_hosts.append(new NetHost("file", "/uploadMissionAnswerFile", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        QString url = jsonObj["file_url"].toString();
        QString name = jsonObj["file_name"].toString();
        m_netReply->deleteLater();
        m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::File, false));
        m->setFileUrl(url);

        //emit next();
    }, fileName));
    return this;
}
NetWorker* NetWorker::expire(int noUser)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("sem_user_no", QString("%1").arg(noUser));

    m_hosts.append(new NetHost("post", "/sem/deleteUser", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());

        qDebug() << QString(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::EMPList));
    }));
    return this;
}

NetWorker* NetWorker::getDeviceInfo(int barcode)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("barcode", QString("%1").arg(barcode));

    m_hosts.append(new NetHost("post", "/sem/getDeviceInfo", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        if (isSuccess)
        {
            Device *d = new Device();
            d->setNoPart(jsonObj["sem_part_no"].toInt());
            d->setNamePart(jsonObj["sem_part_name"].toString());
            d->setNameDevice(jsonObj["device_name"].toString());
            d->setNoAsset(jsonObj["asset_no"].toString());
            d->setBarcode(jsonObj["barcode"].toString());
            d->setPrice(jsonObj["get_money"].toInt());
            d->setDateTaked(jsonObj["get_date"].toString());
            d->setMemo(jsonObj["memo"].toString());
            d->borrow(jsonObj["is_rented"].toInt());
            m->setSearchedDevice(d);
            qDebug() << d->namePart() << "/" << d->nameDevice() << "/" << d->noAsset() << "/" << d->price() << "/" << d->borrowed();
        }
        m->setNotificator(new Notificator(isSuccess, jsonObj["error_message"].toString(), Notificator::DVISearch, false));
        m_netReply->deleteLater();
    }));
    return this;
}

NetWorker* NetWorker::searchDeviceReturned(QString barcode)
{
	if (!m->isLogined())
	{
		m->request(false, Notificator::ErrorNoLogined);
		return this;
	}

	if (barcode.isEmpty())
	{
		m->request(false, Notificator::ErrorNoBarcode);
		return this;
	}

    /********** SET URL QUERIES **********/
    QUrlQuery queries;
    queries.addQueryItem("barcode", QString("%1").arg(barcode));
    m_hosts.append(new NetHost("post", "/sem/returnDeviceInfo", queries,
        [&]()-> void {
        QMutexLocker locker(&m_mtx);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_netReply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        bool isSuccess = jsonObj["is_success"].toBool();
        if (isSuccess)
        {
            Rent *r = new Rent();
            r->setNoRent(jsonObj["rent_no"].toInt());
            r->setNameDevice(jsonObj["device_name"].toString());
            r->setNameUser(jsonObj["user_name"].toString());
            r->setNoAsset(jsonObj["asset_no"].toString());
            r->setPurpose(jsonObj["purpose"].toString());
            r->setDateBorrowed(jsonObj["rent_date"].toString());
            m->setSearchedRent(r);
			//m->request(true, Notificator::ConfirmedRent);
            qDebug() << r->noRent() << "/" << r->nameDevice() << "/" << r->noAsset() << "/" << r->purpose();
        }
		else
			m->request(false, Notificator::None, jsonObj["error_message"].toString());

        m_netReply->deleteLater();
    }));
    return this;
}
