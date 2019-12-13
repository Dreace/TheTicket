#include <utils/network/network.h>
Network::Network() {
	manager = new QNetworkAccessManager(this);
}
QJsonDocument Network::get(QUrl& url) {
	QNetworkReply* reply = manager->get(QNetworkRequest(url));
	QEventLoop loop;
	connect(manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
	loop.exec();
	return toJson(reply);
}

QJsonDocument Network::post(QUrl& url, QUrlQuery& params) {
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	QNetworkReply* reply = manager->post(request, params.query().toUtf8());
	QEventLoop loop;
	connect(manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
	loop.exec();
	return toJson(reply);
}

QJsonDocument Network::toJson(QNetworkReply* reply) {
	QJsonParseError jsonError;
	if (reply->error()) {
		qDebug() << reply->errorString();
		return QJsonDocument();
	}
	QJsonDocument doucment = QJsonDocument::fromJson(reply->readAll(), &jsonError);
	reply->deleteLater();
	reply = nullptr;
	return doucment;
}
