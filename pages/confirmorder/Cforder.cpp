#include "Cforder.h"
#include <QComboBox>
#pragma execution_character_set("utf-8")


Cforder::Cforder(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.name->setFocusPolicy(Qt::NoFocus);
	ui.time->setFocusPolicy(Qt::NoFocus);
	ui.total->setFocusPolicy(Qt::NoFocus);
	ui.cancelButton->setEnabled(true);
	ui.confirmButton->setEnabled(true);
	ui.num->setValue(0);
	ui.num->setMaximum(20);
	connect(ui.confirmButton, SIGNAL(clicked()), this, SLOT(clickConfirmButton()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(clickCancelButton()));
	connect(ui.num, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
	
}

void Cforder::clickCancelButton() {
	QString quantity = QString::number(ui.num->value());
	
}

void Cforder::receive_data(QVariantMap s) {
	ui.name->setText(s["showName"].toString());
	ui.time->setText(s["showTimestamp"].toString());
	showPrice = s["showPrice"].toInt();
}

void Cforder::clickConfirmButton() {
	
}

void Cforder::setValue(int){
	int total = 0;
	int num = ui.num->value();
	total = num * showPrice;
	ui.total->setText(QString::number(total));
}

Cforder::~Cforder(){}
