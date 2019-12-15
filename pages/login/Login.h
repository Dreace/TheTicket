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
private slots:
	void clickLoginButton();
	void clickExitButton();
};
