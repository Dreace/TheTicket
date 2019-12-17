#include "pages/login/Login.h"
#include "pages/showList/ShowList.h"
#include "pages/confirmorder/Cforder.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Login w;
	w.show();
	/*Cforder c;
	c.show();*/
	return a.exec();
}
