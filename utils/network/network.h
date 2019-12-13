#pragma once
#include <QtNetwork>
class Network :QObject {
	Q_OBJECT
public:
	Network();
	QJsonDocument get(QUrl&);
	QJsonDocument post(QUrl&, QUrlQuery&);
private:
	QNetworkAccessManager* manager;
	QJsonDocument toJson(QNetworkReply*);
};