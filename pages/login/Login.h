#pragma once

#include <QWidget>
#include "ui_Login.h"
#include "utils/network/network.h"
class Login : public QWidget
{
	Q_OBJECT

public:
	Login(QWidget *parent = Q_NULLPTR);
	~Login();

private:
	Ui::Login ui;
	Network network;
	bool registering = false;
signals:
	void sendSession(QString);
private slots:
	void clickLoginButton();
	void clickExitButton();
	void clickRegisterButton();

};
