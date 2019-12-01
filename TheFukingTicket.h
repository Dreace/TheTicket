#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TheFukingTicket.h"

class TheFukingTicket : public QMainWindow
{
	Q_OBJECT

public:
	TheFukingTicket(QWidget *parent = Q_NULLPTR);

private:
	Ui::TheFukingTicketClass ui;
};
