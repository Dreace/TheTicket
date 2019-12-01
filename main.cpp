#include "TheFukingTicket.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TheFukingTicket w;
	w.show();
	return a.exec();
}
