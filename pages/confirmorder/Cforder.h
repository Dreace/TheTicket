#pragma once

#include <QWidget>
#include "ui_Cforder.h"

class Cforder : public QWidget
{
	Q_OBJECT

public:
	Cforder(QWidget *parent = Q_NULLPTR);
	~Cforder();

private:
	Ui::Cforder ui;
	int showPrice;

private slots:
	void clickConfirmButton();
	void clickCancelButton();
	void setValue(int);

	void receive_data(QVariantMap s);
};


