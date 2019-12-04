#pragma once

#include <QWidget>
#include "ui_Fuck.h"

class Fuck : public QWidget
{
	Q_OBJECT

public:
	Fuck(QWidget *parent = Q_NULLPTR);
	~Fuck();

private:
	Ui::Fuck ui;
};
