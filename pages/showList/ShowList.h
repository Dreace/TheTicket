#pragma once

#include <QWidget>
#include "ui_ShowList.h"
#include <qstringlistmodel.h>
#include <qstandarditemmodel.h>
#include <utils/network/network.h>


class ShowList : public QWidget
{
	Q_OBJECT

public:
	ShowList(QWidget *parent = Q_NULLPTR);
	~ShowList();
private:
	Ui::ShowList ui;
	Network network;
	QVariantList resultList;
public:
	

private slots:
	void clickOrderButton();
		
	
	
};


