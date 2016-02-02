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
	GTplayerWidget->image_label->setMouseTracking(true);

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

	//Set ROI selection threshold
	data->ROIselection_thr_pix_w = int(ceil(data->ROIselection_thr*double(currFrame.size().width)));
	data->ROIselection_thr_pix_h = int(ceil(data->ROIselection_thr*double(currFrame.size().height)));

	//Set ROI minimum size thresholds
	data->ROImin_w = int(ceil(data->ROIminsize_thr*double(currFrame.size().width)));
	data->ROImin_h = int(ceil(data->ROIminsize_thr*double(currFrame.size().height)));

	//Enable play button and slider
	GTplayerWidget->play_button->setEnabled(true);
	GTplayerWidget->progres_slider->setEnabled(true);

	//Initialize ROI drawing state
	mouse_ROIstate = 0;

	//ROIs table interaction functions
	connect(data->currFrame_ROIs, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(currROI_change(QTableWidgetItem *)));
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
	
	//Draw ROIs from register and update ROIs table
	if (mouse_ROIstate == 0)
	{
		drawROI_currFrame();
		update_ROIsTable();
	}

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
					//Get mouse click coordinates
					const QMouseEvent* const me = static_cast<const QMouseEvent*>(event);
					ROI_left = me->pos().x();
					ROI_up = me->pos().y();

					//Scale coordinates from widget size to frame size
					ROI_left = int(floor(double(ROI_left)*(double(currFrame.size().width) / double(scaledFrame_width))));
					ROI_up = int(floor(double(ROI_up)*(double(currFrame.size().height) / double(scaledFrame_height))));

					//Check if mouse click selected a ROI
					mousePosition_ROIcheck(ROI_left, ROI_up);
					setMouseCursor(data->mouseROItype_sel, play_state, 1);

					if (data->ROI_selected)
					{
						//Highlight selected ROI
						highlightSelected_ROI(data->currROI_ID);						
					}	
					else
					{
						//Change mouse_ROIstate to "being drawn"
						mouse_ROIstate = 1;

						//Unselect row from ROIs table
						data->currFrame_ROIs->setFocus();
						data->currFrame_ROIs->clearSelection();
					}
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

				//Draw ROI in frame
				cv::Mat Frame_ROI = currFrame.clone();
				cv::Scalar CVcurrLbl_color = Scalar(currLbl_color.blue(), currLbl_color.green(), currLbl_color.red());
				cv::rectangle(Frame_ROI, cv::Point(ROI_left, ROI_up), cv::Point(ROI_right, ROI_down), CVcurrLbl_color, 2);

				//Display frame 
				displayFrame(Frame_ROI);
			}

			//Deselect rows from ROIs table
			if (!data->ROI_selected)
			{
				data->currFrame_ROIs->setFocus();
				data->currFrame_ROIs->clearSelection();
			}

			//Check if mouse click selected a ROI
			mousePosition_ROIcheck(ROI_right, ROI_down);
			setMouseCursor(data->mouseROItype_sel, play_state, 0);
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

				ROI_width = ROI_right - ROI_left;
				ROI_height = ROI_down - ROI_up;

				//Draw and save ROI if it surpass minimum size
				if (ROI_width >= data->ROImin_w && ROI_height >= data->ROImin_h)
				{
					//Get Label color
					int lbl_idx = labelID_search(data->currLabel_ID, data->labels_reg);
					QColor currLbl_color = data->labels_reg[lbl_idx].color;

					//Draw ROI in frame
					cv::Mat Frame_ROI = currFrame.clone();
					cv::Scalar CVcurrLbl_color = Scalar(currLbl_color.blue(), currLbl_color.green(), currLbl_color.red());
					cv::rectangle(Frame_ROI, cv::Point(ROI_left, ROI_up), cv::Point(ROI_right, ROI_down), CVcurrLbl_color, 2);

					//Change mouse_ROIstate to drawn
					mouse_ROIstate = 2;

					//Create new Key ROI
					createKROI();

					//Display frame 
					displayFrame(Frame_ROI);
				}
				else
				{
					//Display frame 
					displayFrame(currFrame);

					//Change mouse_ROIstate to not drawn
					mouse_ROIstate = 0;
				}
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
	data->newKROI.w = ROI_width;
	data->newKROI.h = ROI_height;
	data->newKROI.frame = data->frame_idx;

	//Set ROI states
	QVector<int> states;
	states.push_back(ROI_left);
	states.push_back(ROI_up);
	states.push_back(data->newKROI.w);
	states.push_back(data->newKROI.h);
	data->newKROI.states = states;

	//Reset mouse_ROIstate to ROI not drawn
	mouse_ROIstate = 0;

	//Increase current ROI ID
	data->currROI_ID = data->ROIs_reg.size();

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
			//Get label for ROI i
			currLbl = data->labels_reg[data->ROIs_reg[i].lbl_ID];

			//Get label color for ROI i
			currLbl_color = currLbl.color;
			CVcurrLbl_color  = Scalar(currLbl_color.blue(), currLbl_color.green(), currLbl_color.red());

			//Draw ROI i in current frame
			cv::rectangle(currFrame, cv::Point(ROIcurrFrame.left, ROIcurrFrame.top), cv::Point(ROIcurrFrame.right, ROIcurrFrame.bot), CVcurrLbl_color, 1);
		}
	}
}

void playerWidget::mousePosition_ROIcheck(int x, int y)
{
	roi_info ROIcurrFrame;

	int thr_x = data->ROIselection_thr_pix_w;
	int thr_y = data->ROIselection_thr_pix_h;

	//Edge conditions
	bool edge_left, edge_right, edge_top, edge_bot;

	//Inside conditions
	bool in_width, in_height;

	//Initialize mouse state as not ROI selected
	data->mouseROItype_sel = 0;

	//Initialize ROI selection as false
	data->ROI_selected = false;

	for (int i = 0; i < data->ROIs_reg.size(); i++)
	{
		//Get ROI i for frame_idx
		ROIcurrFrame = data->ROIs_reg[i].frameROI_info[data->frame_idx];

		if (!ROIcurrFrame.empty)
		{
			//Check if mouse coordinates are inside a ROI
			in_width = (x > ROIcurrFrame.left + thr_x) && (x < ROIcurrFrame.right - thr_x);
			in_height = (y > ROIcurrFrame.top + thr_y) && (y < ROIcurrFrame.bot - thr_y);

			if (in_width || in_height)
			{
				//Select ROI to highlight and change mouse_state to edge selection
				data->mouseROItype_sel = 1;
				data->currROI_ID = data->ROIs_reg[i].ID;

				//Set ROI selection as true
				data->ROI_selected = true;
			}

			//Check if mouse coordinates are near to ROI edges
			edge_left = (x <= ROIcurrFrame.left + thr_x) && (x >= ROIcurrFrame.left - thr_x) && (y <= ROIcurrFrame.bot + thr_y) && (y >= ROIcurrFrame.top - thr_y);
			edge_right = (x <= ROIcurrFrame.right + thr_x) && (x >= ROIcurrFrame.right - thr_x) && (y <= ROIcurrFrame.bot + thr_y) && (y >= ROIcurrFrame.top - thr_y);
			edge_top = (y <= ROIcurrFrame.top + thr_y) && (y >= ROIcurrFrame.top - thr_y) && (x <= ROIcurrFrame.right + thr_x) && (x >= ROIcurrFrame.left - thr_x);
			edge_bot = (y <= ROIcurrFrame.bot + thr_y) && (y >= ROIcurrFrame.bot - thr_y) && (x <= ROIcurrFrame.right + thr_x) && (x >= ROIcurrFrame.left - thr_x);

			//Vertical edge
			if (edge_left || edge_right)
			{
				data->mouseROItype_sel = 2;
			}

			//Horizontal edge
			if (edge_left || edge_right)
			{
				data->mouseROItype_sel = 3;
			}

			if (edge_left || edge_right || edge_top || edge_bot)
			{
				//Select ROI to highlight and change mouse_state to edge selection
				data->currROI_ID = data->ROIs_reg[i].ID;

				//Set ROI selection as true
				data->ROI_selected = true;
			}
		}
	}
}

void playerWidget::highlightSelected_ROI(int ROI_ID)
{
	//Get Label color
	roi_info selROI = data->ROIs_reg[ROI_ID].frameROI_info[data->frame_idx];
	int ROI_lblID = data->ROIs_reg[ROI_ID].lbl_ID;
	QColor currLbl_color = data->labels_reg[ROI_lblID].color;

	//Draw ROI in frame
	cv::Mat Frame_ROI = currFrame.clone();
	cv::Scalar CVcurrLbl_color = Scalar(currLbl_color.blue(), currLbl_color.green(), currLbl_color.red());
	cv::rectangle(Frame_ROI, cv::Point(selROI.left, selROI.top), cv::Point(selROI.right, selROI.bot), CVcurrLbl_color, 2);

	//Display frame 
	displayFrame(Frame_ROI);

	//Highlight ROI row in ROIs table
	data->currFrame_ROIs->setFocus();
	data->currFrame_ROIs->selectRow(ROI_ID);
}


void playerWidget::update_ROIsTable()
{
	QTableWidget *ROIsTable = data->currFrame_ROIs;
	
	roi_register_info currROI_reg;
	roi_info currROI;
	QColor currLbl_color;
	Scalar CVcurrLbl_color;
	QTableWidgetItem *ROItable_item;

	int NROI_frame = 0;

	for (int i = 0; i < data->ROIs_reg.size(); i++)
	{
		currROI_reg = data->ROIs_reg[i];

		//If not empty display ROI in table
		if (!currROI_reg.frameROI_info[data->frame_idx].empty)
		{
			//Add a row to the table
			NROI_frame++;
			ROIsTable->setRowCount(NROI_frame);

			//Get ROI
			currROI = currROI_reg.frameROI_info[data->frame_idx];

			//ROI ID
			ROItable_item = new QTableWidgetItem(QString::number(currROI_reg.ID));
			ROItable_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ROIsTable->setItem(i, 0, ROItable_item);

			//ROI lbl color: paint table cell
			currLbl_color = data->labels_reg[currROI_reg.lbl_ID].color;	//ROI lbl color
			QWidget *pWidget = new QWidget();
			QString s("background: #"
				+ QString(currLbl_color.red() < 16 ? "0" : "") + QString::number(currLbl_color.red(), 16)
				+ QString(currLbl_color.green() < 16 ? "0" : "") + QString::number(currLbl_color.green(), 16)
				+ QString(currLbl_color.blue() < 16 ? "0" : "") + QString::number(currLbl_color.blue(), 16) + ";");
			pWidget->setStyleSheet(s);
			ROIsTable->setCellWidget(i, 1, pWidget);
			ROItable_item = new QTableWidgetItem(QString::number(1));
			ROItable_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ROIsTable->setItem(i, 1, ROItable_item);

			//ROI x
			ROItable_item = new QTableWidgetItem(QString::number(currROI.left));
			ROItable_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ROIsTable->setItem(i, 2, ROItable_item);

			//ROI y
			ROItable_item = new QTableWidgetItem(QString::number(currROI.top));
			ROItable_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ROIsTable->setItem(i, 3, ROItable_item);

			//ROI w
			ROItable_item = new QTableWidgetItem(QString::number(currROI.w));
			ROItable_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ROIsTable->setItem(i, 4, ROItable_item);

			//ROI h
			ROItable_item = new QTableWidgetItem(QString::number(currROI.h));
			ROItable_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ROIsTable->setItem(i, 5, ROItable_item);
		}		
	}
	ROIsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ROIsTable->setSelectionMode(QAbstractItemView::SingleSelection);

	//Highlight new ROI row
	ROIsTable->setFocus();
	ROIsTable->selectRow(NROI_frame-1);
}

void playerWidget::currROI_change(QTableWidgetItem *item)
{
	//Get current ROI ID
	data->currROI_ID = data->ROIs_reg[data->currFrame_ROIs->currentIndex().row()].ID;

	//Highlight in widget the selected ROI
	highlightSelected_ROI(data->currROI_ID);
}

void playerWidget::setMouseCursor(int typeSel, bool play_State, int mouseEventType)
{
	//typesel = 0: Not selected; 1: Inside a ROI; 2: On vertical ROI boundary; 3: On horizontal ROI boundary
	//4: draw ROI
	//play_State = true: play; false: pause
	//mouseEventType = 0: Move; 1: Click; 2: Release

	if (typeSel == 0)
	{
		if (mouseEventType == 0)
		{
			if (play_State)
				this->setCursor(Qt::ArrowCursor);
			else
				this->setCursor(Qt::CrossCursor);
		}

		if (mouseEventType == 1)
		{
			if (play_State)
				this->setCursor(Qt::CrossCursor);
			else
			{
				this->setCursor(Qt::SizeAllCursor);
			}
		}
	}

	if (typeSel == 1)
	{
		if (mouseEventType == 0)
		{
			if (!play_State)
				this->setCursor(Qt::OpenHandCursor);
		}

		if (mouseEventType == 1)
		{
			if (!play_State)
				this->setCursor(Qt::ClosedHandCursor);
		}
	}

	if (typeSel == 5)
	{
		if (mouseEventType == 0)
		{
			if (!play_State)
				this->setCursor(Qt::SizeAllCursor);
		}

		if (mouseEventType == 2)
		{
			if (!play_State)
				this->setCursor(Qt::CrossCursor);
		}
	}
}