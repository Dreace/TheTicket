#pragma once

#include <QWidget>
#include "ui_AddShow.h"
#include "utils/network/network.h"
class AddShow : public QWidget {
	Q_OBJECT

public:
	AddShow(QWidget* parent, QWidget*);
	~AddShow();
signals:
	void refresh_list();
public slots:
	void receiveSession(QString);
private slots:
	void click_confirm_add_btn();
	void click_cancel_add_btn();
	void rowTextChanged(QString);
	void colTextChanged(QString);
private:
	int row = 0, col = 0;
	Ui::AddShow ui;
	QString session;
	Network network;
};
