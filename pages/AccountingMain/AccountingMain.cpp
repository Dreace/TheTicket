#include "AccountingMain.h"
#include <qmessagebox.h>
#include <qvariant.h>
#include <qtablewidget.h>
AccountingMain::AccountingMain(QWidget* parent)
	: QWidget(parent) {
	ui.setupUi(this);
}
void AccountingMain::refreshList() {
	QJsonDocument doucment = network.get(QString("GetShow/All"));
	if (doucment.isObject()) {
		QVariantMap result = doucment.toVariant().toMap();
		if (result["code"].toInt() != 0) {
			QMessageBox::warning(this, QString::fromLocal8Bit("发生异常"), result["message"].toString());
		} else {
			QVariantList list = result["data"].toList();
			ui.tableWidget->setRowCount(list.length());
			int cnt = 0;
			for (auto item : list) {
				auto item_map = item.toMap();
				int sold_seat = item_map["showSeats"].toInt() - item_map["showSeatsAvailable"].toInt();
				double price = item_map["showPrice"].toDouble();
				QDateTime show_time = QDateTime::fromTime_t(item_map["showTimestamp"].toInt());
				QString show_time_str = show_time.toString(QString::fromLocal8Bit("yyyy年MM月dd hh:mm"));
				ui.tableWidget->setItem(cnt, 0, new QTableWidgetItem(item_map["showID"].toString().mid(0, 5)));
				ui.tableWidget->setItem(cnt, 1, new QTableWidgetItem(item_map["showName"].toString()));
				ui.tableWidget->setItem(cnt, 2, new QTableWidgetItem(show_time_str));
				ui.tableWidget->setItem(cnt, 3, new QTableWidgetItem(item_map["showSeats"].toString()));
				ui.tableWidget->setItem(cnt, 4, new QTableWidgetItem(QString::number(sold_seat)));
				ui.tableWidget->setItem(cnt, 5, new QTableWidgetItem(QString::number(price)));
				ui.tableWidget->setItem(cnt, 6, new QTableWidgetItem(QString::number(price * sold_seat)));
				cnt++;
			}
			ui.tableWidget->resizeColumnToContents(2);
		}
	}
}
void AccountingMain::receiveSession(QString session) {
	this->session = session;
	this->refreshList();
}
AccountingMain::~AccountingMain() {}