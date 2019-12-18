#include "AddShow.h"
#include<qmessagebox.h>
AddShow::AddShow(QWidget* parent, QWidget* parentWindows)
	: QWidget(parent) {
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(click_confirm_add_btn()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(click_cancel_add_btn()));
	connect(ui.lineEdit_5, SIGNAL(textChanged(QString)), this, SLOT(rowTextChanged(QString)));
	connect(ui.lineEdit_6, SIGNAL(textChanged(QString)), this, SLOT(colTextChanged(QString)));
	connect(this, SIGNAL(refresh_list()), parentWindows, SLOT(refresh()));
	QRegExp regx("[1-9][0-9]+$");
	QValidator* validator = new QRegExpValidator(regx);
	ui.lineEdit_2->setValidator(validator);
	ui.lineEdit_5->setValidator(validator);
	ui.lineEdit_6->setValidator(validator);
	ui.dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}
void AddShow::click_confirm_add_btn() {
	QUrlQuery params;
	if (ui.lineEdit->text().trimmed().length() < 1) {
		QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("演出名称不能为空"));
		return;
	}
	if (ui.lineEdit_2->text().length() < 1) {
		QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("票价不能为空"));
		return;
	}
	if (ui.lineEdit_5->text().length() < 1) {
		QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("座位行数不能为空"));
		return;
	}
	if (ui.lineEdit_6->text().length() < 1) {
		QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("座位列数不能为空"));
		return;
	}
	params.addQueryItem("session", session);
	params.addQueryItem("show_name", ui.lineEdit->text().trimmed());
	params.addQueryItem("show_time", QString::number(ui.dateTimeEdit->dateTime().toTime_t()));
	params.addQueryItem("show_price", ui.lineEdit_2->text());
	params.addQueryItem("show_seat_total", ui.lineEdit_3->text());
	params.addQueryItem("show_seat_available", ui.lineEdit_4->text());
	params.addQueryItem("seat_max_row", ui.lineEdit_5->text());
	params.addQueryItem("seat_max_col", ui.lineEdit_6->text());
	QJsonDocument doucment = network.post(QString("Operator/AddShow"), params);
	QVariantMap result = doucment.toVariant().toMap();
	if (result["code"].toInt() == 0) {
		QMessageBox::warning(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("添加成功"));
		emit(refresh_list());
		this->close();
	} else {
		QMessageBox::warning(this, QString::fromLocal8Bit("错误"), result["message"].toString());
	}
}
void AddShow::click_cancel_add_btn() {
	this->close();
}
void AddShow::receiveSession(QString session) {
	this->session = session;
}
void AddShow::rowTextChanged(QString rowText) {
	if (rowText.length() > 0) {
		this->row = rowText.toInt();
		if (this->col != 0) {
			ui.lineEdit_3->setText(QString::number(this->col * this->row));
			ui.lineEdit_4->setText(QString::number(this->col * this->row));
		}
	}
}
void AddShow::colTextChanged(QString colText) {
	if (colText.length() > 0) {
		this->col = colText.toInt();
		if (this->row != 0) {
			ui.lineEdit_3->setText(QString::number(this->col * this->row));
			ui.lineEdit_4->setText(QString::number(this->col * this->row));
		}
	}
}
AddShow::~AddShow() {}
