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

	//Initialize player as paused
	play_state = false;
	video_loaded = false;

	//Tagging variables and functions------------------------
	GTplayerWidget->image_label->installEventFilter(this);

	//Project global variables
	data = GTProject_data::Instance();

	//Create ROI interpolator object
	ROI_interp = new ROI_interpolator();
}

playerWidget::~playerWidget()
{

}

void playerWidget::playerInitialization()
{
	//Initialize player variables
	data->frame_idx = 0;
	video_loaded = true;
	data->video_length = data->imgSeq_list.size();

	//Initialize play timer
	playTimer = new QTimer(this);
	playTimer->start(data->fps);

	//Load play and pause icons
	const QPixmap play_pixmap("D:/Documentos/VS-Codes/GTGeneratorQT5/GTGenerator_v1/Resources/play128.png");
	playIcon = new QIcon(play_pixmap);
	const QPixmap pause_pixmap("D:/Documentos/VS-Codes/GTGeneratorQT5/GTGenerator_v1/Resources/pause52.png");
	pauseIcon = new QIcon(pause_pixmap);

	//Set slider according image sequence length
	GTplayerWidget->progres_slider->setMinimum(0);
	GTplayerWidget->progres_slider->setMaximum(data->imgSeq_list.size());

	//Display first frame
	readFrame();

	//Enable play button and slider
	GTplayerWidget->play_button->setEnabled(true);
	GTplayerWidget->progres_slider->setEnabled(true);

	//Initialize ROI drawing state
	mouse_ROIstate = 0;
}

void playerWidget::on_playButton_clicked()
{
	//Play video
	if (!play_state)
	{
		//Set player timer
		playTimer->start(data->fps);

		//Connect timer with readFrame function
		connect(playTimer, SIGNAL(timeout()), this, SLOT(readFrame()));

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

void playerWidget::readFrame()
{
	if (data->frame_idx < data->imgSeq_list.size())
	{
		//Read frame
		frame_name = data->imgSeq_list.at(data->frame_idx);
		frame_path = data->imgSeq_path + "/" + frame_name.toUtf8().constData();
		currFrame = cv::imread(frame_path);

		//Display frame
		displayFrame(currFrame);

		//Increase index and move slider
		data->frame_idx++;
		GTplayerWidget->progres_slider->setValue(data->frame_idx);
	}
}

void playerWidget::displayFrame(cv::Mat Frame)
{
	OpenCVProcessor player_openCVProcessor = OpenCVProcessor();
	
	//PLOT ROIS FROM XML HERE-----
	if (mouse_ROIstate == 0)
		drawROI_currFrame();

	//----------------------------

	//Convert cv::Mat to Qpixmap 
	Qpix_currFrame = player_openCVProcessor.cvMatToQPixmap(Frame);

	//Display image
	GTplayerWidget->image_label->setPixmap(Qpix_currFrame);
	GTplayerWidget->image_label->setScaledContents(true);
	scaledFrame_width = GTplayerWidget->image_label->width();
	scaledFrame_height = GTplayerWidget->image_label->height();
}

void playerWidget::on_progressSlider_moved(int val)
{
	//Get slider value set by user
	data->frame_idx = val;

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
	readFrame();
	displayFrame(currFrame);
}

bool playerWidget::eventFilter(QObject *obj, QEvent *event)
{
	bool event_flag = false;

	//If video is loaded hear mouse events
	if (video_loaded)
	{
		//-------Mouse click on video-------
		if (event->type() == QEvent::MouseButtonPress)
		{
			//If mouse clicked and video is playing -> pause video
			if (play_state)
			{
				//Stop timer
				playTimer->stop();

				//Change player state to "pause"
				play_state = false;

				//Change icon to "pause"
				GTplayerWidget->play_button->setIcon(*playIcon);
			}
			//If mouse clicked and video is paused -> start to draw ROI
			else
			{
				if (mouse_ROIstate == 0)
				{
					std::cout << std::endl << "ams:" << mouse_ROIstate;

					//Get mouse click coordinates
					const QMouseEvent* const me = static_cast<const QMouseEvent*>(event);
					ROI_left = me->pos().x();
					ROI_up = me->pos().y();

					//Scale coordinates from widget size to frame size
					ROI_left = int(floor(double(ROI_left)*(double(currFrame.size().width) / double(scaledFrame_width))));
					ROI_up = int(floor(double(ROI_up)*(double(currFrame.size().height) / double(scaledFrame_height))));

					//Change mouse_ROIstate to "being drawn"
					mouse_ROIstate = 1;
				}				
			}
			event_flag = true;
		}
		//-------Mouse moved on video-------
		if (event->type() == QEvent::MouseMove)
		{
			//Continue drawing ROI
			if (mouse_ROIstate == 1)
			{
				//Get mouse coordinates
				const QMouseEvent* const me = static_cast<const QMouseEvent*>(event);
				ROI_right = me->pos().x();
				ROI_down = me->pos().y();	

				//Scale coordinates from widget size to frame size
				ROI_right = int(floor(double(ROI_right)*(double(currFrame.size().width) / double(scaledFrame_width))));
				ROI_down = int(floor(double(ROI_down)*(double(currFrame.size().height) / double(scaledFrame_height))));

				//Get Label color
				int lbl_idx = labelID_search(data->currLabel_ID, data->labels_reg);
				QColor currLbl_color = data->labels_reg[lbl_idx].color;

				std::cout << std::endl << "bms:" << mouse_ROIstate << " lbl:" << data->currLabel_ID<< " lbl_idx:"<< lbl_idx;

				//Draw ROI in frame
				cv::Mat Frame_ROI = currFrame.clone();
				cv::Scalar CVcurrLbl_color = Scalar(currLbl_color.blue(), currLbl_color.green(), currLbl_color.red());
				cv::rectangle(Frame_ROI, cv::Point(ROI_left, ROI_up), cv::Point(ROI_right, ROI_down), CVcurrLbl_color, 2);

				//Display frame 
				displayFrame(Frame_ROI);
			}
		}
		//-------Mouse released on video-------
		if (event->type() == QEvent::MouseButtonRelease)
		{
			//Continue drawing ROI
			if (mouse_ROIstate == 1)
			{
				//Get mouse coordinates
				const QMouseEvent* const me = static_cast<const QMouseEvent*>(event);
				ROI_right = me->pos().x();
				ROI_down = me->pos().y();

				//Scale coordinates from widget size to frame size
				ROI_right = int(floor(double(ROI_right)*(double(currFrame.size().width) / double(scaledFrame_width))));
				ROI_down = int(floor(double(ROI_down)*(double(currFrame.size().height) / double(scaledFrame_height))));

				//Get Label color
				int lbl_idx = labelID_search(data->currLabel_ID, data->labels_reg);
				QColor currLbl_color = data->labels_reg[lbl_idx].color;

				//Draw ROI in frame
				cv::Mat Frame_ROI = currFrame.clone();
				cv::Scalar CVcurrLbl_color = Scalar(currLbl_color.blue(), currLbl_color.green(), currLbl_color.red());
				cv::rectangle(Frame_ROI, cv::Point(ROI_left, ROI_up), cv::Point(ROI_right, ROI_down), CVcurrLbl_color, 2);

				//Display frame 
				displayFrame(Frame_ROI);

				//Change mouse_ROIstate to drawn
				mouse_ROIstate = 2;

				std::cout << std::endl << "cms:" << mouse_ROIstate;

				//Create new Key ROI
				createKROI();

				std::cout << std::endl << "dms:" << mouse_ROIstate;
				std::cout << std::endl << "reg:" << data->ROIs_reg.size();
			}
		}
	}	
	return event_flag;
}

void playerWidget::createKROI()
{
	//Set ROI information
	data->newKROI.empty = false;
	data->newKROI.top = ROI_up;
	data->newKROI.bot = ROI_down;
	data->newKROI.left = ROI_left;
	data->newKROI.right = ROI_right;
	data->newKROI.w = ROI_right-ROI_left;
	data->newKROI.h = ROI_down - ROI_up;
	data->newKROI.frame = data->frame_idx;

	//Set ROI states
	QVector<int> states;
	states.push_back(ROI_left);
	states.push_back(ROI_up);
	states.push_back(data->newKROI.w);
	states.push_back(data->newKROI.h);
	data->newKROI.states = states;

	//Increase current ROI ID
	data->currROI_ID++;

	//Reset mouse_ROIstate to ROI not drawn
	mouse_ROIstate = 0;

	//Register new ROI and interpolate
	ROI_interp->interpolateROI();
}

void playerWidget::drawROI_currFrame()
{
	roi_info ROIcurrFrame;
	cv::Scalar CVcurrLbl_color; 
	QColor currLbl_color;
	label_info currLbl;


	//Draw ROIs of current frame
	for (int i = 0; i < data->ROIs_reg.size(); i++)
	{
		//Get ROI i for frame_idx
		ROIcurrFrame = data->ROIs_reg[i].frameROI_info[data->frame_idx];

		if (!ROIcurrFrame.empty)
		{
			std::cout << std::endl << "ROI:" << i << " lbl:" << data->ROIs_reg[i].lbl_ID;

			//Get label for ROI i
			currLbl = data->labels_reg[data->ROIs_reg[i].lbl_ID];

			//Get label color for ROI i
			currLbl_color = currLbl.color;
			CVcurrLbl_color  = Scalar(currLbl_color.blue(), currLbl_color.green(), currLbl_color.red());

			//Draw ROI i in current frame
			cv::rectangle(currFrame, cv::Point(ROI_left, ROI_up), cv::Point(ROI_right, ROI_down), CVcurrLbl_color, 1);
		}
	}
}

