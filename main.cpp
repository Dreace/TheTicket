#include "pages/login/Login.h"
#include "pages/showList/ShowList.h"
#include "pages/confirmorder/Cforder.h"
#include <QtWidgets/QApplication>
#include "ModifyList.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Login w;
	w.show();
	return a.exec();
}
