#ifndef GTGENERATOR_H
#define GTGENERATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_gtgenerator.h"
#include "ui_newProject.h"
#include "ui_saveProject.h"
#include <QtMultimediaWidgets>

class GTGenerator : public QMainWindow
{
	Q_OBJECT

public:
	GTGenerator(QWidget *parent = 0);
	~GTGenerator();

private:

	//Variables---------------

	//Main GT Gui
	Ui::GTGeneratorClass ui;
	Ui_GTGeneratorClass * GTgui;

	//New project Gui
	QDialog *newProject;
	Ui_newProject_dialog *ui_newProject;


	int flag_src;	//Data source flag (1: video, 2: image sequence)

public slots:

//New project dialog slots

void showNewProjectDialog();

void selectVideo();

void selectImageSeq();

void loadSource();



};

#endif // GTGENERATOR_H
