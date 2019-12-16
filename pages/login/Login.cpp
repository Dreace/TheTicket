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
		ui.registerButton->setText(QString::fromLocal8Bit("×¢²á"));
		ui.loginButton->setText(QString::fromLocal8Bit("È¥µÇÂ¼"));
		return;
	}
	QString uid = ui.uidInput->text();
	QString password = ui.passwordInput->text();
	if (uid.length() == 0 || password.length() == 0) {
		QMessageBox::warning(this, QString::fromLocal8Bit("´íÎó"), QString::fromLocal8Bit("ÕËºÅÃÜÂë²»ÄÜÎª¿Õ"));
	} else if (password != ui.repeatPasswordInput->text()) {
		QMessageBox::warning(this, QString::fromLocal8Bit("´íÎó"), QString::fromLocal8Bit("Á½´ÎÊäÈëµÄÃÜÂë²»Ò»ÖÂ"));
	} else {
		QUrlQuery params;
		params.addQueryItem("uid", uid);
		params.addQueryItem("password", password);
		QJsonDocument doucment = network.post(QString("Register"), params);
		if (doucment.isObject()) {
			QVariantMap result = doucment.toVariant().toMap();
			if (result["code"].toInt() != 0) {
				QMessageBox::warning(this, QString::fromLocal8Bit("×¢²áÊ§°Ü"), result["message"].toString());
			} else {
				QMessageBox::StandardButton reply;
				reply = QMessageBox::warning(this, QString::fromLocal8Bit("×¢²á³É¹¦"), QString::fromLocal8Bit("×ªµ½µÇÂ¼Ò³"));
				if (reply == QMessageBox::Ok) {
					ui.repeatPasswordInput->setVisible(false);
					ui.repeatPasswordLabel->setVisible(false);
					this->registering = false;
					ui.registerButton->setText(QString::fromLocal8Bit("È¥×¢²á"));
					ui.loginButton->setText(QString::fromLocal8Bit("µÇÂ¼"));
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
		ui.registerButton->setText(QString::fromLocal8Bit("È¥×¢²á"));
		ui.loginButton->setText(QString::fromLocal8Bit("µÇÂ¼"));
		return;
	}
	//QMessageBox::information(this, QString::fromLocal8Bit("²âÊÔ"), QString::fromLocal8Bit("µã»÷µÇÂ¼"));
	QString uid = ui.uidInput->text();
	QString password = ui.passwordInput->text();
	if (uid.length() == 0 || password.length() == 0) {
		QMessageBox::warning(this, QString::fromLocal8Bit("´íÎó"), QString::fromLocal8Bit("ÕËºÅÃÜÂë²»ÄÜÎª¿Õ"));
	} else {
		QUrlQuery params;
		params.addQueryItem("uid", uid);
		params.addQueryItem("password", password);
		QJsonDocument doucment = network.post(QString("Login"), params);
		if (doucment.isObject()) {
			QVariantMap result = doucment.toVariant().toMap();
			if (result["code"].toInt() != 0) {
				QMessageBox::warning(this, QString::fromLocal8Bit("µÇÂ¼Ê§°Ü"), result["message"].toString());
			}
		}
	}

}
Login::~Login() {}
