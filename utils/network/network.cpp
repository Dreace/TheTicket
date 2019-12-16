#include <utils/network/network.h>
Network::Network() {
	manager = new QNetworkAccessManager(this);
	apiUrl = QString("http://dreace.top:105/");
}
QJsonDocument Network::get(QString& url) {
	QNetworkReply* reply = manager->get(QNetworkRequest(this->apiUrl + url));
	QEventLoop loop;
	connect(manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
	loop.exec();
	return toJson(reply);
}

QJsonDocument Network::post(QString& url, QUrlQuery& params) {
	QNetworkRequest request(this->apiUrl + url);
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
