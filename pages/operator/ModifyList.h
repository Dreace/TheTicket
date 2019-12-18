#pragma once

#include <QWidget>
#include <qmainwindow.h>
#include "ui_ModifyList.h"
#include"utils/network/network.h"
#include <qpushbutton.h>
class ModifyList : public QMainWindow {
	Q_OBJECT

public:
	ModifyList(QWidget* parent = Q_NULLPTR);
	~ModifyList();
signals:
	void transmit_data(QVariantMap, QString);
	void sendSession(QString);
private slots:
	void click_alter_btn();
	void click_delete_btn();
	void logout();
	void addShow();
public slots:
	void receiveSession(QString);
	void refresh();
private:
	Ui::ModifyList ui;
	QString session;
	Network network;
	QVariantList resultList;
	QPushButton* alter_btn;
	QPushButton* delete_btn;
	void Refresh();
};
