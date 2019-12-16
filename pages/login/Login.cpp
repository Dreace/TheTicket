#include "Login.h"
#include <qmessagebox.h>
Login::Login(QWidget* parent)
	: QWidget(parent) {
	ui.setupUi(this);
	connect(ui.loginButton, SIGNAL(clicked()), this, SLOT(clickLoginButton()));
	connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(clickExitButton()));
	connect(ui.registerButton, SIGNAL(clicked()), this, SLOT(clickRegisterButton()));
	ui.repeatPasswordInput->setVisible(false);
	ui.repeatPasswordLabel->setVisible(false);
}
void Login::clickExitButton() {
	this->close();
}
void Login::clickRegisterButton() {
	if (!this->registering) {
		ui.repeatPasswordInput->setVisible(true);
		ui.repeatPasswordLabel->setVisible(true);
		this->registering = true;
		ui.registerButton->setText(QString::fromLocal8Bit("ע��"));
		ui.loginButton->setText(QString::fromLocal8Bit("ȥ��¼"));
		return;
	}
	QString uid = ui.uidInput->text();
	QString password = ui.passwordInput->text();
	if (uid.length() == 0 || password.length() == 0) {
		QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�˺����벻��Ϊ��"));
	} else if (password != ui.repeatPasswordInput->text()) {
		QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("������������벻һ��"));
	} else {
		QUrlQuery params;
		params.addQueryItem("uid", uid);
		params.addQueryItem("password", password);
		QJsonDocument doucment = network.post(QString("Register"), params);
		if (doucment.isObject()) {
			QVariantMap result = doucment.toVariant().toMap();
			if (result["code"].toInt() != 0) {
				QMessageBox::warning(this, QString::fromLocal8Bit("ע��ʧ��"), result["message"].toString());
			} else {
				QMessageBox::StandardButton reply;
				reply = QMessageBox::warning(this, QString::fromLocal8Bit("ע��ɹ�"), QString::fromLocal8Bit("ת����¼ҳ"));
				if (reply == QMessageBox::Ok) {
					ui.repeatPasswordInput->setVisible(false);
					ui.repeatPasswordLabel->setVisible(false);
					this->registering = false;
					ui.registerButton->setText(QString::fromLocal8Bit("ȥע��"));
					ui.loginButton->setText(QString::fromLocal8Bit("��¼"));
				}
			}
		}
	}
}
void Login::clickLoginButton() {
	if (this->registering) {
		ui.repeatPasswordInput->setVisible(false);
		ui.repeatPasswordLabel->setVisible(false);
		this->registering = false;
		ui.registerButton->setText(QString::fromLocal8Bit("ȥע��"));
		ui.loginButton->setText(QString::fromLocal8Bit("��¼"));
		return;
	}
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
