#pragma once

#include <QWidget>
#include "ui_ShowList.h"
#include <qstringlistmodel.h>
#include <qstandarditemmodel.h>
#include <utils/network/network.h>


class ShowList : public QWidget
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

private slots:
	void clickOrderButton();
public slots:
	void refresh();
	void receiveSession(QString);
};


