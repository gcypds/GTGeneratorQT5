#ifndef GTGENERATOR_H
#define GTGENERATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_gtgenerator.h"

class GTGenerator : public QMainWindow
{
	Q_OBJECT

public:
	GTGenerator(QWidget *parent = 0);
	~GTGenerator();

private:
	Ui::GTGeneratorClass ui;
};

#endif // GTGENERATOR_H
