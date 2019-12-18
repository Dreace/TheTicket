#include "MyOrder.h"
#include <QtWidgets\qmessagebox.h>
#include <qtablewidget.h>

MyOrder::MyOrder(QWidget* parent)
	: QWidget(parent) {
	ui.setupUi(this);
}
void MyOrder::refresh() {
	QString path = QString("/User/GetOrder?session=") + this->session;
	QJsonDocument doucment = network.get(path);
	if (doucment.isObject()) {
		QVariantMap result = doucment.toVariant().toMap();
		if (result["code"].toInt() != 0) {
			QMessageBox::warning(this, QString::fromLocal8Bit("发生错误"), result["message"].toString());
		} else {
			QVariantList resultList = result["data"].toList();
			ui.tableWidget->setRowCount(resultList.length());
			int cnt = 0;
			for (auto a : resultList) {
				QVariantMap s = a.toMap();
				QString tickets;
				int i = 0;
				QString r = QString::fromLocal8Bit("排");
				QString c = QString::fromLocal8Bit("列 ");
				for (auto ticket : s["tickets"].toList()) {
					auto t = ticket.toMap();
					tickets.append(t["row"].toString() + r + t["col"].toString() + c);
					++i;
					if (i && i % 2 == 0) {
						tickets.append("\n");
					}
				}
				tickets = tickets.left(tickets.length() - 1);
				QDateTime order_time = QDateTime::fromTime_t(s["timestamp"].toInt());
				QString order_time_str = order_time.toString(QString::fromLocal8Bit("yyyy年MM月dd日 hh:mm"));
				QDateTime show_time = QDateTime::fromTime_t(s["showTime"].toInt());
				QString show_time_str = show_time.toString(QString::fromLocal8Bit("yyyy年MM月dd日 hh:mm"));
				ui.tableWidget->setItem(cnt, 0, new QTableWidgetItem(s["orderID"].toString().left(5)));
				ui.tableWidget->setItem(cnt, 1, new QTableWidgetItem(order_time_str));
				ui.tableWidget->setItem(cnt, 2, new QTableWidgetItem(s["ticketsNum"].toString()));
				ui.tableWidget->setItem(cnt, 3, new QTableWidgetItem(tickets));
				ui.tableWidget->setItem(cnt, 4, new QTableWidgetItem(s["showName"].toString()));
				ui.tableWidget->setItem(cnt, 5, new QTableWidgetItem(show_time_str));
				++cnt;
			}
			ui.tableWidget->resizeColumnToContents(1);
			ui.tableWidget->resizeColumnToContents(2);
			ui.tableWidget->resizeColumnToContents(5);
			ui.tableWidget->resizeRowsToContents();
		}
	}
}
void MyOrder::receiveSession(QString session) {
	this->session = session;
	this->refresh();
}
MyOrder::~MyOrder() {}
