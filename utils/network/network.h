#pragma once
#include <QtNetwork>
class Network :QObject {
	Q_OBJECT
public:
	Network();
	QJsonDocument get(QString&);
	QJsonDocument post(QString&, QUrlQuery&);
private:
	QString apiUrl;
	QNetworkAccessManager* manager;
	QJsonDocument toJson(QNetworkReply*);
};