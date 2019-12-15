#include "Login.h"
#include <qmessagebox.h>
Login::Login(QWidget* parent)
	: QWidget(parent) {
	ui.setupUi(this);
	connect(ui.loginButton, SIGNAL(clicked()), this, SLOT(clickLoginButton()));
	connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(clickExitButton()));
}
void Login::clickExitButton() {
	this->close();
}
void Login::clickLoginButton() {
	//QMessageBox::information(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�����¼"));
	QString uid = ui.uidInput->text();
	QString password = ui.passwordInput->text();
	if (uid.length() == 0 || password.length() == 0) {
		QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�˺����벻��Ϊ��"));
	} else {
		QUrlQuery params;
		params.addQueryItem("uid", uid);
		params.addQueryItem("password", password);
		QJsonDocument doucment = network.post(QString("Login"), params);
		if (doucment.isObject()) {
			QVariantMap result = doucment.toVariant().toMap();
			if (result["code"].toInt() != 0) {
				QMessageBox::warning(this, QString::fromLocal8Bit("��¼ʧ��"), result["message"].toString());
			}
		}
	}

}
Login::~Login() {}
