#pragma once

#include <QWidget>
#include "ui_Cforder.h"
#include <utils/network/network.h>
class Cforder : public QWidget
{
	Q_OBJECT

public:
	Cforder(QWidget *parent = Q_NULLPTR);
	~Cforder();

private:
	Ui::Cforder ui;
	Network network;
	int showPrice;
	QString showid;
	QString session;

private slots:
	void clickConfirmButton();
	void clickCancelButton();
	void setValue(int);

	void receive_data(QVariantMap s);
};


