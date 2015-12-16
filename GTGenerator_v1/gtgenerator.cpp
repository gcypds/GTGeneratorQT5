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

	connect(ui_newProject->sourceVideo_button, SIGNAL(toggled(bool)), this, SLOT(selectVideo(bool)));

	connect(ui_newProject->browsePath_button, SIGNAL(clicked()), this, SLOT(loadSource()));

	//------------------------------------------------------------------------------------
}

GTGenerator::~GTGenerator()
{

}

void GTGenerator::showNewProjectDialog()
{
	//Default set checked video source
	ui_newProject->sourceVideo_button->setChecked(true);
	ui_newProject->sourceImage_button->setChecked(false);
	flag_src = 1;

	//Show new project dialog
	newProject->exec();
}

void GTGenerator::selectVideo(bool state)
{
	if (state)
		flag_src = 1;	//Select video
	else
		flag_src = 2;	//Select image sequence
}


void GTGenerator::loadSource()
{
	//Load video dialog
	if (flag_src == 1)
	{
		load_videoSource();
	}

	//Load image sequence dialog
	if (flag_src == 2)
	{
		load_imageSource();
	}
}

void GTGenerator::load_videoSource()
{
	sourcePath = QFileDialog::getOpenFileName(this, tr("Select video:"), "D:/Videos", tr("Video Files (*.avi *.flv *.mp4)"));
	videoFile = QFileInfo(sourcePath);

	if (!sourcePath.isEmpty())
	{
		ui_newProject->sourcePath_edit->setText(sourcePath);

		//Convert video to image sequence and save to directory
		QDir currentDir = QDir(sourcePath);
		qDebug() << "currentDir: " << videoFile.dir().path() << endl;
		qDebug() << "currentFile: " << videoFile.fileName() << endl;

		QDir videoFramesDir = QDir(videoFile.dir().path() + "\\" + videoFile.baseName().section(".", 0, 0) + "_video_frames\\");

		qDebug() << "videoFramesDir" << videoFramesDir.path() << endl;

		if (!videoFramesDir.exists()) {
			QDir().mkdir(videoFramesDir.path());
		}

		

		OpenCVProcessor openCVProcessor = OpenCVProcessor();
		openCVProcessor.setProgressDialog(progressDialog);
		double fps = openCVProcessor.saveFramesFromVideo(sourcePath, videoFramesDir.path());

		currentDir = QDir(videoFramesDir.path());
	}
}

void GTGenerator::load_imageSource()
{
	sourcePath = QFileDialog::getExistingDirectory(this, tr("Select directory:"), "D:/Documentos/Challenge_Surveillance");

	if (!sourcePath.isEmpty())
	{
		QDir currentDir = QDir(sourcePath);

		QStringList files;
		QStringList filters;
		filters << "*.png" << "*.jpg" << "*.jpeg";
		files = currentDir.entryList(filters, QDir::Files | QDir::NoSymLinks);

		if (!files.isEmpty())
		{
			ui_newProject->sourcePath_edit->setText(sourcePath);
		}
		else
		{
			QMessageBox errorBox;
			errorBox.setWindowTitle("Error");
			errorBox.setIcon(QMessageBox::Icon::Critical);
			errorBox.setText("Not a valid image sequence in the selected directory (.png, .jpg, .jpeg)");
			errorBox.setDefaultButton(QMessageBox::Ok);
			errorBox.exec();
		}
	}
}
