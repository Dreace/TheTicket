#pragma once

#include <QWidget>
#include <qmainwindow.h>
#include "ui_AccountingMain.h"
#include "utils/network/network.h"

class AccountingMain : public QMainWindow
{
	Q_OBJECT

public:
	AccountingMain(QWidget *parent = Q_NULLPTR);
	~AccountingMain();

private:
	Network network;
	QString session;
	Ui::AccountingMain ui;
	void refreshList();
public slots:
	void receiveSession(QString);
	void logout();
};
