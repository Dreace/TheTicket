#pragma execution_character_set("utf-8")
#include "ShowList.h"
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtablewidget.h>
#include <qlist.h>
#include <QHeaderView>
#include <qmessagebox.h>
#include <qvariant.h>
#include <qdatetime.h>
#include <Cforder.h>


ShowList::ShowList(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	ui.tableWidget->setColumnCount(5);
	/*ui.tableWidget->horizontalHeader()->setStretchLastSection(true);*/
	//ui.tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//�Զ������и�
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//�Զ������п�
	
	//ui.tableWidget->verticalHeader()->setVisible(true); // ����ˮƽheader,falseΪ����
	ui.tableWidget->setHorizontalHeaderLabels(QStringList() << "��Ŀ����" << "��Ŀʱ��" << "ʣ����λ" << "Ʊ��" << "Ԥ��");
	
	
	//��ȡ������Ϣ
	QJsonDocument doucment = network.get(QString("GetShow"));
	
	if (doucment.isObject()) {
		QVariantMap result = doucment.toVariant().toMap();
		if (result["code"].toInt() != 0) {
			QMessageBox::warning(this, QString::fromLocal8Bit("��¼ʧ��"), result["message"].toString());
		}
		else {
			resultList = result["data"].toList();
		}
	}
	ui.tableWidget->setRowCount(resultList.length());
	int cnt = 0;
	for (auto a : resultList) {
		QVariantMap s = a.toMap();
		ui.tableWidget->setItem(cnt, 0, new QTableWidgetItem(s["showName"].toString()));
		ui.tableWidget->setItem(cnt, 1, new QTableWidgetItem(QDateTime::fromTime_t(s["showTimestamp"].toInt()).toString()));
		/*qDebug() << s["showName"].toInt();*/
		ui.tableWidget->setItem(cnt, 2, new QTableWidgetItem(s["showSeatsAvailable"].toString()));
		ui.tableWidget->setItem(cnt, 3, new QTableWidgetItem(s["showPrice"].toString()));
		

		//��Ӱ�ť
		QPushButton *buy_btn = new QPushButton(this);
		buy_btn->setText("Ԥ��");
		ui.tableWidget->setCellWidget(cnt, 4, buy_btn);
		connect(buy_btn, SIGNAL(clicked()), this, SLOT(clickOrderButton()));
		buy_btn->setProperty("row", cnt);//����ÿ�а�ť������
		/*buy_btn->setFixedSize(55, 30);*/
		connect(buy_btn, SIGNAL(clicked()), this, SLOT(clickOrderButton()));
		++cnt;
	
	}

}

void ShowList::clickOrderButton() {
	
	Cforder *c = new Cforder();
	QPushButton *btn = (QPushButton *)sender();
	QVariantMap s = resultList.at(btn->property("row").toInt()).toMap();
	connect(this, SIGNAL(transmit_data(QVariantMap)), c, SLOT(receive_data(QVariantMap)));
	c->show();
	emit(transmit_data(s));
}

ShowList::~ShowList()
{

}


