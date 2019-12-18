#include "ShowList.h"
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <QHeaderView>
#include <qmessagebox.h>
#include <qvariant.h>
#include <qdatetime.h>
#include <Cforder.h>
#include <Login.h>
#include <MyOrder.h>


ShowList::ShowList(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.action, SIGNAL(triggered()), this, SLOT(showMyOrder()));
	connect(ui.action_2, SIGNAL(triggered()), this, SLOT(logout()));
}

void ShowList::clickOrderButton() {
	Cforder *c = new Cforder(nullptr,this);
	QPushButton *btn = (QPushButton *)sender();
	QVariantMap s = resultList.at(btn->property("row").toInt()).toMap();
	connect(this, SIGNAL(transmit_data(QVariantMap, QString)), c, SLOT(receive_data(QVariantMap, QString)));
	c->show();
	emit(transmit_data(s,this->session));
}
void ShowList::refreshList() {
	QJsonDocument doucment = network.get(QString("GetShow"));
	if (doucment.isObject()) {
		QVariantMap result = doucment.toVariant().toMap();
		if (result["code"].toInt() != 0) {
			QMessageBox::warning(this, QString::fromLocal8Bit("发成错误"), result["message"].toString());
		} else {
			resultList = result["data"].toList();
			ui.tableWidget->setRowCount(resultList.length());
			int cnt = 0;
			for (auto a : resultList) {
				QVariantMap s = a.toMap();
				QDateTime show_time = QDateTime::fromTime_t(s["showTimestamp"].toInt());
				QString show_time_str = show_time.toString(QString::fromLocal8Bit("yyyy年MM月dd日 hh:mm"));
				ui.tableWidget->setItem(cnt, 0, new QTableWidgetItem(s["showName"].toString()));
				ui.tableWidget->setItem(cnt, 1, new QTableWidgetItem(show_time_str));
				/*qDebug() << s["showName"].toInt();*/
				ui.tableWidget->setItem(cnt, 2, new QTableWidgetItem(s["showSeatsAvailable"].toString()));
				ui.tableWidget->setItem(cnt, 3, new QTableWidgetItem(s["showPrice"].toString()));
				QPushButton* buy_btn = new QPushButton(this);
				buy_btn->setText(QString::fromLocal8Bit("预定"));
				ui.tableWidget->setCellWidget(cnt, 4, buy_btn);
				connect(buy_btn, SIGNAL(clicked()), this, SLOT(clickOrderButton()));
				buy_btn->setProperty("row", cnt);//设置每行按钮的属性
				++cnt;
			}
			ui.tableWidget->resizeColumnToContents(1);
		}
	}
}

void ShowList::receiveSession(QString session) {
	this->session = session;
	this->refreshList();
}
void ShowList::refresh() {
	this->refreshList();
}
void ShowList::showMyOrder() {
	MyOrder* w = new MyOrder();
	w->show();
	connect(this, SIGNAL(sendSession(QString)), w, SLOT(receiveSession(QString)));
	emit(sendSession(this->session));
}
void ShowList::logout() {
	Login *w = new Login();
	w->show();
	this->close();
}
ShowList::~ShowList()
{

}