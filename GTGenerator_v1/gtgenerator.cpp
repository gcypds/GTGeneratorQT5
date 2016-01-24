#include "gtgenerator.h"

GTGenerator::GTGenerator(QWidget *parent)
	: QMainWindow(parent)
{
	//Create Gui variable
	GTgui = new Ui_GTGeneratorClass();
	GTgui->setupUi(this);

	//Project global variables
	data = GTProject_data::Instance();

	//------------------------------------------------------------------------------------
	//New project Dialog slots and initialization

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

	//Cancel new project
	connect(ui_newProject->cancelNew_button, SIGNAL(clicked()), this, SLOT(cancel_newProject()));

	//------------------------------------------------------------------------------------
	//Create label Dialog slots and initialization

	//Create NewProject Dialog
	createLabel = new QDialog(this);
	ui_createLabel = new Ui_createLabel_Dialog();
	ui_createLabel->setupUi(createLabel);

	//Show create label dialog
	connect(GTgui->createLabel_button, SIGNAL(clicked()), this, SLOT(showCreateLabelDialog()));

	//Select color dialog
	connect(ui_createLabel->labelColor_button, SIGNAL(clicked()), this, SLOT(selectLabelColor()));

	//Accept new label
	connect(ui_createLabel->acceptLabel, SIGNAL(clicked()), this, SLOT(acceptNewLabel()));

	//Cancel new label
	connect(ui_createLabel->cancelLabel, SIGNAL(clicked()), this, SLOT(cancelNewLabel()));

	//Initialize labels table
	initialize_labelsTable();

	//Initialize labels ID register (0 default label)
	labelID_reg = 1;

	//------------------------------------------------------------------------------------
	//Labels table interaction functions

	connect(GTgui->labels_table, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(currLabel_change(QTableWidgetItem *)));
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
			data->imgSeq_path = sourcePath.toUtf8().constData();
			data->imgSeq_list = files;
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
		data->fps = openCVProcessor.saveFramesFromVideo(sourcePath, videoFramesDir.path());

		videoFramesDir.setFilter(QDir::Files | QDir::NoSymLinks);
		data->imgSeq_path = QimgSeq_path.toUtf8().constData();

		QStringList filters;
		filters << "*.png" << "*.jpg" << "*.jpeg";
		data->imgSeq_list = videoFramesDir.entryList(filters, QDir::Files | QDir::NoSymLinks);
	}	

	//Initialize player
	GTgui->GTplayerWidget->playerInitialization();
}

void GTGenerator::cancel_newProject()
{
	//Close new project dialog
	newProject->close();
}

void GTGenerator::showCreateLabelDialog()
{
	//Initialize createLabel button color with blue
	label_color = QColor(0, 0, 255, 255);

	QString s("background: #"
		+ QString(label_color.red() < 16 ? "0" : "") + QString::number(label_color.red(), 16)
		+ QString(label_color.green() < 16 ? "0" : "") + QString::number(label_color.green(), 16)
		+ QString(label_color.blue() < 16 ? "0" : "") + QString::number(label_color.blue(), 16) + ";");
	ui_createLabel->labelColor_button->setStyleSheet(s);
	ui_createLabel->labelColor_button->update();

	//Initialize label name
	ui_createLabel->labelName_input->setText("Person");

	//Display Dialog
	createLabel->show();
}

void GTGenerator::selectLabelColor()
{
	//Select color dialog
	label_color = QColorDialog::getColor();

	//Set the selected color to the createLabel button
	QString s("background: #"
		+ QString(label_color.red() < 16 ? "0" : "") + QString::number(label_color.red(), 16)
		+ QString(label_color.green() < 16 ? "0" : "") + QString::number(label_color.green(), 16)
		+ QString(label_color.blue() < 16 ? "0" : "") + QString::number(label_color.blue(), 16) + ";");
	ui_createLabel->labelColor_button->setStyleSheet(s);
	ui_createLabel->labelColor_button->update();
}

void GTGenerator::acceptNewLabel()
{
	//Get label name
	label_name = ui_createLabel->labelName_input->text();

	//Construct new label struct
	label_info new_label_struct;
	new_label_struct.color = label_color;
	new_label_struct.name = label_name;

	//Check if new labels information is not already used in labels_reg
	bool valid_lbl = validate_newLabel(new_label_struct);

	if (valid_lbl)
	{
		//Assign ID
		new_label_struct.ID = labelID_reg;
		labelID_reg++;

		//Save new label in labels register
		data->labels_reg.push_back(new_label_struct);

		//Close Dialog
		createLabel->close();

		//Update Labels table
		update_labelsTable();
	}	
}

void GTGenerator::cancelNewLabel()
{
	//Close Dialog
	createLabel->close();
}

void GTGenerator::initialize_labelsTable()
{
	QTableWidget *LabelsTable = GTgui->labels_table;
	LabelsTable->setColumnCount(2);
	LabelsTable->setRowCount(0);

	QStringList column_names;
	column_names << "Name" << "Color";
	LabelsTable->setHorizontalHeaderLabels(column_names);
	LabelsTable->setColumnWidth(0, 270);

	LabelsTable->verticalHeader()->setVisible(false);
	LabelsTable->horizontalHeader()->setStretchLastSection(true);
}

bool GTGenerator::validate_newLabel(label_info new_label)
{
	QMessageBox errorBox;
	bool valid = true;

	for (int i = 0; i < data->labels_reg.size(); i++)
	{
		//Validate color in labels reg
		if (new_label.color == data->labels_reg[i].color)
		{
			errorBox.setWindowTitle("Error");
			errorBox.setIcon(QMessageBox::Icon::Critical);
			errorBox.setText("Label color already taken, please select another color");
			errorBox.setDefaultButton(QMessageBox::Ok);
			errorBox.exec();
			valid = false;
		}
		//Validate name in labels reg
		if (new_label.name == data->labels_reg[i].name)
		{
			errorBox.setWindowTitle("Error");
			errorBox.setIcon(QMessageBox::Icon::Critical);
			errorBox.setText("Label name already taken, please use another name");
			errorBox.setDefaultButton(QMessageBox::Ok);
			errorBox.exec();
			valid = false;
		}
	}

	return valid;
}

void GTGenerator::update_labelsTable()
{
	QTableWidget *LabelsTable = GTgui->labels_table;
	int newLabel_row = data->labels_reg.size() - 2;
	LabelsTable->setRowCount(newLabel_row+1);

	for (int i = 0; i <= newLabel_row; i++)
	{
		//Input label name in table
		QTableWidgetItem * name_item = new QTableWidgetItem(data->labels_reg[i+1].name);
		name_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		LabelsTable->setItem(i, 0, name_item);

		//Paint table cell with the selected label color
		QWidget *pWidget = new QWidget();
		QString s("background: #"
			+ QString(data->labels_reg[i + 1].color.red() < 16 ? "0" : "") + QString::number(data->labels_reg[i + 1].color.red(), 16)
			+ QString(data->labels_reg[i + 1].color.green() < 16 ? "0" : "") + QString::number(data->labels_reg[i + 1].color.green(), 16)
			+ QString(data->labels_reg[i + 1].color.blue() < 16 ? "0" : "") + QString::number(data->labels_reg[i + 1].color.blue(), 16) + ";");
		pWidget->setStyleSheet(s);
		LabelsTable->setCellWidget(i, 1, pWidget);
		QTableWidgetItem * color_item = new QTableWidgetItem();
		color_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		LabelsTable->setItem(i, 1, color_item);
	}
	LabelsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	LabelsTable->setSelectionMode(QAbstractItemView::SingleSelection);
	LabelsTable->selectRow(newLabel_row);

	//Get current label ID
	data->currLabel_ID = data->labels_reg[LabelsTable->currentIndex().row()].ID;
}

void GTGenerator::currLabel_change(QTableWidgetItem *item)
{
	QTableWidget *LabelsTable = GTgui->labels_table;

	//Get current label ID
	data->currLabel_ID = data->labels_reg[LabelsTable->currentIndex().row()+1].ID;
}