#include "gtgenerator.h"

GTGenerator::GTGenerator(QWidget *parent)
	: QMainWindow(parent)
{
	//Create Gui variable
	GTgui = new Ui_GTGeneratorClass();
	GTgui->setupUi(this);

	//------------------------------------------------------------------------------------
	//New project slots and initialization

	//Create NewProject Dialog
	newProject = new QDialog(this);
	ui_newProject = new Ui_newProject_dialog();
	ui_newProject->setupUi(newProject);

	connect(GTgui->actionNewProject, SIGNAL(triggered()), this, SLOT(showNewProjectDialog()));

	connect(ui_newProject->sourceVideo_button, SIGNAL(stateChanged()), this, SLOT(selectVideo()));

	//------------------------------------------------------------------------------------
}

GTGenerator::~GTGenerator()
{

}

void GTGenerator::showNewProjectDialog()
{
	//Show new project dialog
	newProject->exec();
}

void GTGenerator::selectVideo()
{

}

void GTGenerator::selectImageSeq()
{

}

void GTGenerator::loadSource()
{
	//Load video dialog
	if (flag_src == 1)
	{

	}

	//Load image sequence dialog
	if (flag_src == 2)
	{

	}
}
