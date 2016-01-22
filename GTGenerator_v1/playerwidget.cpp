#include "playerwidget.h"

playerWidget::playerWidget(QWidget *parent) :
QWidget(parent),
GTplayerWidget(new Ui::playerWidget)
{
	GTplayerWidget->setupUi(this);
	
	//Connect when play button is clicked
	connect(GTplayerWidget->play_button, SIGNAL(clicked()), this, SLOT(on_playButton_clicked()));

	//Connect when slider is moved
	connect(GTplayerWidget->progres_slider, SIGNAL(sliderMoved(int)), this, SLOT(on_progressSlider_moved(int)));

	//Connect when slider is released
	connect(GTplayerWidget->progres_slider, SIGNAL(sliderReleased()), this, SLOT(on_progressSlider_released()));

	//Disable play button and slider until a video is loaded
	GTplayerWidget->play_button->setEnabled(false);
	GTplayerWidget->progres_slider->setEnabled(false);
}

playerWidget::~playerWidget()
{

}

void playerWidget::playerInitialization()
{
	//Initialize player variables
	play_state = false;
	frame_idx = 0;

	//Load play and pause icons
	const QPixmap play_pixmap("D:/Documentos/VS-Codes/GTGeneratorQT5/GTGenerator_v1/Resources/play128.png");
	playIcon = new QIcon(play_pixmap);
	const QPixmap pause_pixmap("D:/Documentos/VS-Codes/GTGeneratorQT5/GTGenerator_v1/Resources/pause52.png");
	pauseIcon = new QIcon(pause_pixmap);

	//Set slider according image sequence length
	GTplayerWidget->progres_slider->setMinimum(0);
	GTplayerWidget->progres_slider->setMaximum(imgSeq_list.size());

	//Display first frame
	displayFrame();

	//Enable play button and slider
	GTplayerWidget->play_button->setEnabled(true);
	GTplayerWidget->progres_slider->setEnabled(true);

	//Initialize slider_mov flag 
	slider_mov = false;
}

void playerWidget::on_playButton_clicked()
{
	//Play video
	if (!play_state)
	{
		//Set player timer
		playTimer = new QTimer(this);
		playTimer->start(fps);

		//Connect timer with displayFrame function
		connect(playTimer, SIGNAL(timeout()), this, SLOT(displayFrame()));

		//Change player state to "play"
		play_state = true;

		//Change icon to "pause"
		GTplayerWidget->play_button->setIcon(*pauseIcon);
	}
	//Pause video
	else
	{
		//Stop timer
		playTimer->stop();

		//Change player state to "pause"
		play_state = false;

		//Change icon to "pause"
		GTplayerWidget->play_button->setIcon(*playIcon);
	}
}

void playerWidget::displayFrame()
{
	OpenCVProcessor player_openCVProcessor = OpenCVProcessor();

	if (frame_idx < imgSeq_list.size())
	{
		//Read current frame
		frame_name = imgSeq_list.at(frame_idx);
		frame_path = imgSeq_path + "/" + frame_name.toUtf8().constData();
		currFrame = cv::imread(frame_path);

		//Convert cv::Mat to Qpixmap 
		Qpix_currFrame = player_openCVProcessor.cvMatToQPixmap(currFrame);

		//Display image
		GTplayerWidget->image_label->setPixmap(Qpix_currFrame);
		GTplayerWidget->image_label->setScaledContents(true);

		//Increase frame index and progress slider
		if (!slider_mov)
		{
			frame_idx++;
			GTplayerWidget->progres_slider->setValue(frame_idx);
		}
	}
}

void playerWidget::on_progressSlider_moved(int val)
{
	
	//Get slider value set by user
	frame_idx = val;

	//Stop timer
	playTimer->stop();

	//Change player state to "pause"
	play_state = false;

	//Change icon to "pause"
	GTplayerWidget->play_button->setIcon(*playIcon);
}

void playerWidget::on_progressSlider_released()
{
	//Display frame when slider is released
	displayFrame();
}

