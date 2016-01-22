#ifndef GTGENERATOR_H
#define GTGENERATOR_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <qmessagebox.h>
#include <qdebug.h>
#include <qcolordialog.h>

#include "ui_gtgenerator.h"
#include "ui_newProject.h"
#include "ui_saveProject.h"
#include "ui_createLabel.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "opencvprocessor.h"
#include "playerwidget.h"

//Global structs
//struct label_info
//{
//	QString name;
//	QColor color;
//	int ID;
//};
//-----------------

class GTGenerator : public QMainWindow
{
	Q_OBJECT

public:
	GTGenerator(QWidget *parent = 0);

	~GTGenerator();
	
	//Global variables
	int fps;
	string imgSeq_path;
	QStringList imgSeq_list;
	QVector<label_info> labels_reg;		//Labels register
	int currLabel_ID;
	//----------------

private:

	//Functions---------------
	void load_videoSource();

	void load_imageSource();

	void update_labelsTable();

	void initialize_labelsTable();

	bool validate_newLabel(label_info new_label);

	//Variables---------------

	//Main GT Gui
	Ui::GTGeneratorClass ui;
	Ui_GTGeneratorClass * GTgui;

	//New project Dialog
	QDialog *newProject;
	Ui_newProject_dialog *ui_newProject;

	//Player widget 
	Ui_playerWidget *ui_GTplayerWidget;

	//Create label Dialog
	QDialog *createLabel;
	Ui_createLabel_Dialog *ui_createLabel;

	QString sourcePath;	//Path to load source
	QFileInfo videoFile;
	int flag_src;	//Data source flag (1: video, 2: image sequence)

	QProgressDialog *progressDialog;

	//Create label information
	QColor label_color;
	QString label_name;
	int labelID_reg;

public slots:

//New project dialog slots

void showNewProjectDialog();

void selectSource(bool state);

void loadSource();

void acceptSource_convertVideo();

void cancel_newProject();

//Create label slots

void showCreateLabelDialog();

void selectLabelColor();

void acceptNewLabel();

void cancelNewLabel();

void currLabel_change(QTableWidgetItem *item);

};

#endif // GTGENERATOR_H
