#pragma once

#include <qmainwindow.h>
#include "ui_ShowList.h"
#include <qstringlistmodel.h>
#include <qstandarditemmodel.h>
#include <utils/network/network.h>


class ShowList : public QMainWindow
{
	Q_OBJECT

public:
	ShowList(QWidget *parent = Q_NULLPTR);
	~ShowList();
private:
	Ui::ShowList ui;
	Network network;
	QVariantList resultList;
	QString session;
	void refreshList();
signals:
	void transmit_data(QVariantMap,QString);
	void sendSession(QString);
private slots:
	void clickOrderButton();
	void logout();
	void showMyOrder();
public slots:
	void refresh();
	void receiveSession(QString);
};


