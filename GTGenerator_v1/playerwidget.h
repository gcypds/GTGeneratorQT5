#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <qwidget.h>
#include "ui_playerWidget.h"
#include <iostream>
#include "opencvprocessor.h"

class playerWidget : public QWidget
{
	Q_OBJECT

public:
	explicit playerWidget(QWidget *parent = 0);

	~playerWidget();

	bool play_state;	//true:play, false:pause
	int fps;
	string imgSeq_path; 
	QFileInfoList imgSeq_files;	//List of image sequence files

private:

	//playerWidget Gui
	Ui::playerWidget *GTplayerWidget;

	int frame_idx;
	
	void getFrame();

	public slots:

	void on_playButton_clicked();

	cv::Mat currFrame;
	QImage QcurrFrame;

};

#endif