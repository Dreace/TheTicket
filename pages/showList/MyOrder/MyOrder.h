#pragma once

#include <QWidget>
#include "ui_MyOrder.h"
#include <utils/network/network.h>

class MyOrder : public QWidget
{
	Q_OBJECT

public:
	MyOrder(QWidget *parent = Q_NULLPTR);
	~MyOrder();
public slots:
	void receiveSession(QString);
private:
	Ui::MyOrder ui;
	QString session;
	Network network;
	void refresh();
};
