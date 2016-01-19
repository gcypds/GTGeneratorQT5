#include "playerwidget.h"

playerWidget::playerWidget(QWidget *parent) :
QWidget(parent),
GTplayerWidget(new Ui::playerWidget)
{
	GTplayerWidget->setupUi(this);
	
	//Initializw player variables
	play_state = true;
	frame_idx = 0;

	//Connect when play button is clicked
	connect(GTplayerWidget->play_button, SIGNAL(clicked()), this, SLOT(on_playButton_clicked()));


}

playerWidget::~playerWidget()
{

}

void playerWidget::on_playButton_clicked()
{
	//Play video
	if (play_state)
	{
		QFileInfo frame_info;
		string frame_path;
		for (int i = frame_idx; i < imgSeq_files.size(); i++)
		{
			frame_idx = i;
			frame_info = imgSeq_files.at(i);
			frame_path = imgSeq_path + frame_info.fileName().toUtf8().constData();
			currFrame = cv::imread(frame_path);

			OpenCVProcessor openCVProcessor = OpenCVProcessor();

			QcurrFrame = openCVProcessor.cvMatToQImage(currFrame);

			GTplayerWidget->image_label->setPixmap(QPixmap());
			GTplayerWidget->image_label->adjustSize();
		}
	}
	//Pause video
	else
	{

	}
}

void playerWidget::getFrame()
{
	//imgSeq_path.
	//cv::imread()
}

