#pragma once

#include <QWidget>
#include "ui_ModifyAttributes.h"
#include "utils/network/network.h"
class ModifyAttributes : public QWidget
{
	Q_OBJECT

public:
	ModifyAttributes(QWidget *parent , QWidget*);
	~ModifyAttributes();
private:
	Ui::ModifyAttributes ui;
	Network network;
	QString session;
	QVariantMap v;
signals:
	void refresh_list();
private slots:
	void click_cancel_change_btn();
	void click_confirm_change_btn();
public slots:
	void receive_data(QVariantMap,QString);
};
