#include "Fuck.h"
#include <qmessagebox.h>

Fuck::Fuck(QWidget* parent) : QWidget(parent) {
	ui.setupUi(this);
	//QJsonDocument doucment = network.get(QUrl("http://127.0.0.1:100/CardBalance?name=1707004548"));

	QUrlQuery params;
	params.addQueryItem("uid", "test");
	params.addQueryItem("password", "123");
	QJsonDocument doucment = network.post(QUrl("http://192.168.137.1:100/ToiCal"), params);
	if (doucment.isObject()) {
		QVariantMap result = doucment.toVariant().toMap();
		qDebug() << result["message"].toString();
		QMessageBox::information(this, QString::fromLocal8Bit("²âÊÔ"), result["message"].toString());
	}

}

Fuck::~Fuck() {}
