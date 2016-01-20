#ifndef GTGENERATOR_H
#define GTGENERATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_gtgenerator.h"
#include "ui_newProject.h"
#include "ui_saveProject.h"
#include <QFileDialog>
#include <qmessagebox.h>
#include <qdebug.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencvprocessor.h"
#include "playerwidget.h"

class GTGenerator : public QMainWindow
{
	Q_OBJECT

public:
	GTGenerator(QWidget *parent = 0);

	~GTGenerator();

	
	int fps;
	string imgSeq_path;
	QStringList imgSeq_list;

private:

	void load_videoSource();

	void load_imageSource();

	//Variables---------------

	//Main GT Gui
	Ui::GTGeneratorClass ui;
	Ui_GTGeneratorClass * GTgui;

	//New project Gui
	QDialog *newProject;
	Ui_newProject_dialog *ui_newProject;

	//Player widget 
	Ui_playerWidget *ui_GTplayerWidget;

	QString sourcePath;	//Path to load source
	QFileInfo videoFile;
	int flag_src;	//Data source flag (1: video, 2: image sequence)

	QProgressDialog *progressDialog;


public slots:

//New project dialog slots

void showNewProjectDialog();

void selectSource(bool state);

void loadSource();

void acceptSource_convertVideo();





};

#endif // GTGENERATOR_H
