#include "gtgenerator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GTGenerator w;
	w.show();
	return a.exec();
}
