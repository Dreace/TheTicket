#include "pages/login/Login.h"
#include "pages/showList/ShowList.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	/*Login w;
	w.show();*/
	ShowList s;
	s.show();
	return a.exec();
}
