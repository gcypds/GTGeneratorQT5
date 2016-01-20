#include "gtgenerator.h"

#define Default_FPS 15

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

	//Show new project dialog
	connect(GTgui->actionNewProject, SIGNAL(triggered()), this, SLOT(showNewProjectDialog()));

	//Change source flag if user changes source buttons 
	connect(ui_newProject->sourceVideo_button, SIGNAL(toggled(bool)), this, SLOT(selectSource(bool)));

	//Load source according to source flag
	connect(ui_newProject->browsePath_button, SIGNAL(clicked()), this, SLOT(loadSource()));

	//Accept new project and convert video to image sequence if video is the selected source
	connect(ui_newProject->acceptNew_button, SIGNAL(clicked()), this, SLOT(acceptSource_convertVideo()));

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

void GTGenerator::selectSource(bool state)
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
			fps = Default_FPS;
			imgSeq_path = sourcePath.toUtf8().constData();
			imgSeq_list = files;
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


void GTGenerator::acceptSource_convertVideo()
{
	//Close new project dialog
	newProject->close();

	//Convert video to image sequence and save to directory
	if (flag_src==1)
	{
		QString QimgSeq_path = videoFile.dir().path() + "/" + videoFile.baseName().section(".", 0, 0) + "_video_frames";

		QDir videoFramesDir = QDir(QimgSeq_path);

		if (!videoFramesDir.exists()) {
			QDir().mkdir(videoFramesDir.path());
		}

		OpenCVProcessor openCVProcessor = OpenCVProcessor();
		progressDialog = new QProgressDialog(this);
		progressDialog->setFixedSize(QSize(400, 100));
		openCVProcessor.setProgressDialog(progressDialog);
		fps = openCVProcessor.saveFramesFromVideo(sourcePath, videoFramesDir.path());

		videoFramesDir.setFilter(QDir::Files | QDir::NoSymLinks);
		imgSeq_path = QimgSeq_path.toUtf8().constData();

		QStringList filters;
		filters << "*.png" << "*.jpg" << "*.jpeg";
		imgSeq_list = videoFramesDir.entryList(filters, QDir::Files | QDir::NoSymLinks);
	}	

	//Copy variables to playerWidget class
	GTgui->GTplayerWidget->fps = fps;
	GTgui->GTplayerWidget->imgSeq_path = imgSeq_path;
	GTgui->GTplayerWidget->imgSeq_list = imgSeq_list;

	//Initialize player
	GTgui->GTplayerWidget->playerInitialization();
}