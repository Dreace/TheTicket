#include "OrderDetail.h"
#pragma execution_character_set("utf-8")

OrderDetail::OrderDetail(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QStringList  HStrList;
	HStrList.push_back(QString("订单号"));
	HStrList.push_back(QString("表演名称"));
	HStrList.push_back(QString("时间"));
	HStrList.push_back(QString("数量"));
	HStrList.push_back(QString("座位"));
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
