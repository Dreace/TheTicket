#pragma once

#include <QWidget>
#include "ui_OrderDetail.h"

class OrderDetail : public QWidget
{
	Q_OBJECT

public:
	OrderDetail(QWidget *parent = Q_NULLPTR);
	~OrderDetail();

private:
	Ui::OrderDetail ui;
};
