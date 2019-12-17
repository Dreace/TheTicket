#include "pages/login/Login.h"
#include "pages/confirmorder/Cforder.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Login w;
	w.show();
	return a.exec();
}
