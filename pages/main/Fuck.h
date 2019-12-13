#pragma once

#include <QWidget>
#include <utils/network/network.h>
#include "ui_Fuck.h"

class Fuck : public QWidget {
	Q_OBJECT

public:
	Fuck(QWidget* parent = Q_NULLPTR);
	~Fuck();

private:
	Network network;
	Ui::Fuck ui;
};
