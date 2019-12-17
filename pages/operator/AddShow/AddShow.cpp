#include "AddShow.h"
#include<qmessagebox.h>
AddShow::AddShow(QWidget *parent, QWidget *parentWindows)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(click_confirm_add_btn()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(click_cancel_add_btn()));
	connect(this, SIGNAL(refresh_list()), parentWindows, SLOT(refresh()));
}
void AddShow::click_confirm_add_btn() {
	QUrlQuery params;
	params.addQueryItem("session", session);
	params.addQueryItem("show_name", ui.lineEdit->text());
	params.addQueryItem("show_time",ui.dateTimeEdit->dateTime().toString());
	params.addQueryItem("show_price",ui.lineEdit_2->text());
	params.addQueryItem("show_seat_total", QString::number(ui.lineEdit_5->text().toInt()*ui.lineEdit_6->text().toInt()));
	params.addQueryItem("show_seat_avaliable", ui.lineEdit_4->text());
	params.addQueryItem("seat_max_row", ui.lineEdit_5->text());
	params.addQueryItem("seat_max_col", ui.lineEdit_6->text());
	QJsonDocument doucment = network.post(QString("Operator/AddShow"), params);
	QVariantMap result = doucment.toVariant().toMap();
	if (result["code"].toInt() == 0) {
		QMessageBox::warning(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("修改成功！"));
		emit(refresh_list());
	}
	else {
		QMessageBox::warning(this, QString::fromLocal8Bit("错误"), result["message"].toString());
	}
}
void AddShow::click_cancel_add_btn() {
	this->close();
}

AddShow::~AddShow()
{
}
