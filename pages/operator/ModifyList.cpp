#include "ModifyList.h"
#include<qmessagebox.h>
#include<qlayout.h>
#include"pages/operator/AddShow/AddShow.h"
#include "pages/operator/ModifyAttributes/ModifyAttributes.h"
ModifyList::ModifyList(QWidget* parent)
	: QWidget(parent) {
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(click_add_btn()));
	Refresh();
}
void ModifyList::Refresh() {
	QJsonDocument doucment = network.get(QString("GetShow/All"));
	if (doucment.isObject()) {
		QVariantMap result = doucment.toVariant().toMap();
		if (result["code"].toInt() != 0) {
			QMessageBox::warning(this, QString::fromLocal8Bit("演出信息获取失败"), result["message"].toString());
		} else {
			resultList = result["data"].toList();
		}
		ui.tableWidget->setRowCount(resultList.size());
		int cnt = 0;
		for (auto a : resultList) {
			QVariantMap s = a.toMap();
			ui.tableWidget->setItem(cnt, 0, new QTableWidgetItem(s["showID"].toString().left(5)));
			ui.tableWidget->setItem(cnt, 1, new QTableWidgetItem(s["showName"].toString()));
			ui.tableWidget->setItem(cnt, 2, new QTableWidgetItem(QDateTime::fromTime_t(s["showTimestamp"].toInt()).toString(QString::fromLocal8Bit("yyyy年MM月dd hh:mm"))));
			ui.tableWidget->setItem(cnt, 3, new QTableWidgetItem(s["showPrice"].toString()));
			ui.tableWidget->setItem(cnt, 4, new QTableWidgetItem(s["showSeats"].toString()));
			ui.tableWidget->setItem(cnt, 5, new QTableWidgetItem(s["showSeatsAvailable"].toString()));
			QWidget* itemWidget = new QWidget();
			QHBoxLayout* itemHLayout = new QHBoxLayout(itemWidget);
			alter_btn = new QPushButton(QString::fromLocal8Bit("修改"), itemWidget);
			delete_btn = new QPushButton(QString::fromLocal8Bit("删除"), itemWidget);
			connect(alter_btn, SIGNAL(clicked()), this, SLOT(click_alter_btn()));
			connect(delete_btn, SIGNAL(clicked()), this, SLOT(click_delete_btn()));
			itemHLayout->addWidget(alter_btn);
			itemHLayout->addWidget(delete_btn);
			itemWidget->setLayout(itemHLayout);
			itemHLayout->setContentsMargins(0, 0, 0, 0);
			alter_btn->setFixedSize(55, 30);
			alter_btn->setProperty("row", cnt);
			delete_btn->setFixedSize(55, 30);
			delete_btn->setProperty("row", cnt);
			ui.tableWidget->setCellWidget(cnt, 6, itemWidget);
			++cnt;
		}
		ui.tableWidget->resizeColumnToContents(0);
		ui.tableWidget->resizeColumnToContents(2);
		ui.tableWidget->resizeColumnToContents(6);
	}
}
void ModifyList::click_alter_btn() {
	ModifyAttributes* modify_attributes = new ModifyAttributes(nullptr, this);
	QPushButton* btn = (QPushButton*)sender();
	QVariantMap s = resultList.at(btn->property("row").toInt()).toMap();
	connect(this, SIGNAL(transmit_data(QVariantMap, QString)), modify_attributes, SLOT(receive_data(QVariantMap, QString)));
	modify_attributes->show();
	emit(transmit_data(s, this->session));
}
void ModifyList::click_delete_btn() {
	QPushButton* btn = (QPushButton*)sender();
	QVariantMap s = resultList.at(btn->property("row").toInt()).toMap();
	QMessageBox::StandardButton reply;
	reply = QMessageBox::warning(this, QString::fromLocal8Bit("警告！"), QString::fromLocal8Bit("确认删除？"), QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes) {
		QUrlQuery params;
		params.addQueryItem("session", session);
		params.addQueryItem("show_id", s["showID"].toString());
		QJsonDocument doucment = network.post(QString("Operator/DeleteShow"), params);
		QVariantMap result = doucment.toVariant().toMap();
		if (result["code"].toInt() == 0) {
			QMessageBox::warning(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("删除成功！"));
			Refresh();
		} else {
			QMessageBox::warning(this, QString::fromLocal8Bit("提示"), result["message"].toString());
		}
	}
}
void ModifyList::receiveSession(QString session) {
	this->session = session;
}
void ModifyList::click_add_btn() {
	AddShow* add_show = new AddShow(nullptr, this);
	add_show->show();
	connect(this, SIGNAL(sendSession(QString)), add_show, SLOT(receiveSession(QString)));
	emit(sendSession(this->session));
}
void ModifyList::refresh() {
	Refresh();
}
ModifyList::~ModifyList() {}