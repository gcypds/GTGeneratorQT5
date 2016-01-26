#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <qwidget.h>
#include "ui_playerWidget.h"
#include "GTProject_data.h"
#include <iostream>
#include "opencvprocessor.h"
#include <qtimer.h>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "roi_interpolator.h"



class playerWidget : public QWidget
{
	Q_OBJECT

public:
	explicit playerWidget(QWidget *parent = 0);

	~playerWidget();

	void playerInitialization();

	//playerWidget Gui
	Ui::playerWidget *GTplayerWidget;

private:
	//Functions
	void displayFrame(cv::Mat Frame);

	void createKROI();

	void drawROI_currFrame();

	bool ROIclicked_check(int x, int y);

	void highlightSelected_ROI(int ROI_ID);

	void update_ROIsTable();

	//Project global variables
	GTProject_data *data;

	//Frame info
	cv::Mat currFrame;
	QImage Qim_currFrame;
	QPixmap Qpix_currFrame;
	QFileInfo frame_info;
	QString frame_name;
	string frame_path;

	//Timer
	QTimer *playTimer;

	bool play_state;	//true:play, false:pause
	bool video_loaded;

	//Play pause icons
	QIcon *playIcon;
	QIcon *pauseIcon;

	//ROI tagging 
	int ROI_up;
	int ROI_down;
	int ROI_left;
	int ROI_right;
	int ROI_width;
	int ROI_height;
	int mouse_ROIstate;	//0=ROI not drawn, 1=ROI being drawn, 2=ROI drawn

	int scaledFrame_width;
	int scaledFrame_height;	
	
	ROI_interpolator *ROI_interp;		//ROI registering and interpolation
	
protected:
	//Tagging functions-----------
	bool eventFilter(QObject *obj, QEvent *event);


	public slots:

	void on_playButton_clicked();

	void on_progressSlider_moved(int val);

	void on_progressSlider_released();
	
	void readFrame();
	
	void currROI_change(QTableWidgetItem *item);
};

#endif