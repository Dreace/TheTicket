#include "Cforder.h"
#include "utils/network/network.h"
#include <QComboBox>
#include <qmessagebox.h>


Cforder::Cforder(QWidget *parent, QWidget *realParent)
	: QWidget(parent) {
	ui.setupUi(this);
	ui.name->setFocusPolicy(Qt::NoFocus);
	ui.time->setFocusPolicy(Qt::NoFocus);
	ui.total->setFocusPolicy(Qt::NoFocus);
	ui.cancelButton->setEnabled(true);
	ui.confirmButton->setEnabled(true);
	ui.num->setValue(0);
	ui.num->setMaximum(100);
	connect(ui.confirmButton, SIGNAL(clicked()), this, SLOT(clickConfirmButton()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(clickCancelButton()));
	connect(ui.num, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
	connect(this, SIGNAL(refresh_list()), realParent, SLOT(refresh()));
}

void Cforder::clickCancelButton() {
	this->close();
}

void Cforder::receive_data(QVariantMap s, QString session) {
	this->session = session;
	ui.name->setText(s["showName"].toString());
	QDateTime show_time = QDateTime::fromTime_t(s["showTimestamp"].toInt());
	QString show_time_str = show_time.toString(QString::fromLocal8Bit("yyyy年MM月dd hh:mm"));
	ui.time->setText(show_time_str);
	showPrice = s["showPrice"].toInt();
	showid = s["showID"].toString();
}

void Cforder::clickConfirmButton() {
	if (ui.num->value() == 0) {
		QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("购票数不能为0"));
	} else {
		QString quantity = QString::number(ui.num->value());
		QUrlQuery params;
		params.addQueryItem("session", session);
		params.addQueryItem("show_id", showid);
		params.addQueryItem("quantity", quantity);
		QJsonDocument doucment = network.post(QString("User/Buy"), params);
		if (doucment.isObject()) {
			QVariantMap result = doucment.toVariant().toMap();
			if (result["code"].toInt() != 0) {
				QMessageBox::information(this, QString::fromLocal8Bit("错误"), result["message"].toString());
			} else {
				QMessageBox::information(this, QString::fromLocal8Bit("成功"), QString::fromLocal8Bit("购买成功"));
				emit(refresh_list());
			}
		}
	}

}

void Cforder::setValue(int) {
	int total = 0;
	int num = ui.num->value();
	total = num * showPrice;
	ui.total->setText(QString::number(total));
}

Cforder::~Cforder() {}
