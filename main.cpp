#include "pages/login/Login.h"
#include "pages/confirmorder/Cforder.h"
#include "pages/orderdetail/OrderDetail.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	/*Login w;
	w.show();*/
	/*Cforder c;
	c.show();*/
	OrderDetail o;
	o.show();
	return a.exec();
}
