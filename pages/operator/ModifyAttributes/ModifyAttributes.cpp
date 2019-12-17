#include "ModifyAttributes.h"
#include<qdatetime.h>
#include<qmessagebox.h>
ModifyAttributes::ModifyAttributes(QWidget *parent, QWidget *parentWindows)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(click_confirm_change_btn()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(click_cancel_change_btn()));
    connect(this, SIGNAL(refresh_list()), parentWindows, SLOT(refresh()));
}

void ModifyAttributes::receive_data(QVariantMap v) {
	this->v = v;
	ui.lineEdit->setText(v["showID"].toString().left(5));
	ui.lineEdit_2->setText(v["showName"].toString());
	QDateTime showTime = QDateTime::fromTime_t(v["showTimestamp"].toInt());
	ui.dateTimeEdit->setDateTime(showTime);
	ui.lineEdit_4->setText(v["showSeats"].toString());
	ui.lineEdit_5->setText(v["showPrice"].toString());
	ui.lineEdit_6->setText(v["showSeatsAvailable"].toString());
}
void ModifyAttributes::click_confirm_change_btn() {//从输入框获取修改过后的值
	QUrlQuery params;
	params.addQueryItem("session", session);
	params.addQueryItem("show_id", v["showID"].toString());
	params.addQueryItem("show_name",ui.lineEdit_2->text());
	params.addQueryItem("show_time",ui.dateTimeEdit->dateTime().toString());
	params.addQueryItem("show_price",ui.lineEdit_5->text());
	QJsonDocument doucment = network.post(QString("Operator/ModifyShow"), params);
	QVariantMap result = doucment.toVariant().toMap();
	if (result["code"].toInt() == 0) {
		emit(refresh_list());	
		QMessageBox::warning(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("修改成功！"));
	}
	else {
		QMessageBox::warning(this, QString::fromLocal8Bit("错误"), result["message"].toString());
	}
}
void ModifyAttributes::click_cancel_change_btn(){
	this->close();
}
ModifyAttributes::~ModifyAttributes()
{
}
