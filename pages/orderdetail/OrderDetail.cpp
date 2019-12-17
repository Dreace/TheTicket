#include "OrderDetail.h"
#pragma execution_character_set("utf-8")

OrderDetail::OrderDetail(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QStringList  HStrList;
	HStrList.push_back(QString("������"));
	HStrList.push_back(QString("��������"));
	HStrList.push_back(QString("ʱ��"));
	HStrList.push_back(QString("����"));
	HStrList.push_back(QString("��λ"));
	int HlableCnt = HStrList.count();
	ui.orderlist->setRowCount(10);
	ui.orderlist->setColumnCount(HlableCnt);
	ui.orderlist->setHorizontalHeaderLabels(HStrList);
	ui.orderlist->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.orderlist->setShowGrid(true);
	/*ui.orderlist->resizeRowsToContents();*/
	ui.orderlist->setSpan(2, 2, 3, 2);
	ui.orderlist->setItem(0, 4, new QTableWidgetItem("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"));
}

OrderDetail::~OrderDetail()
{
}
