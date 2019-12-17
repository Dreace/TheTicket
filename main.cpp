#include "pages/login/Login.h"
#include <QtWidgets/QApplication>
#include "ModifyList.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Login w;
	w.show();
	return a.exec();
}
