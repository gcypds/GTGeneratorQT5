#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <qwidget.h>
#include "ui_playerWidget.h"
#include <iostream>
#include "opencvprocessor.h"
#include <qtimer.h>

class playerWidget : public QWidget
{
	Q_OBJECT

public:
	explicit playerWidget(QWidget *parent = 0);

	~playerWidget();

	void playerInitialization();

	bool play_state;	//true:play, false:pause
	int fps;
	string imgSeq_path; 
	QStringList imgSeq_list;

	//playerWidget Gui
	Ui::playerWidget *GTplayerWidget;

private:
	//Frame info
	int frame_idx;
	cv::Mat currFrame;
	QImage Qim_currFrame;
	QPixmap Qpix_currFrame;
	QFileInfo frame_info;
	QString frame_name;
	string frame_path;

	//Timer
	QTimer *playTimer;

	bool slider_mov;	//true:slider moved by user, false:~

	//Play pause icons
	QIcon *playIcon;
	QIcon *pauseIcon;

	public slots:

	void on_playButton_clicked();

	void on_progressSlider_moved(int val);

	void on_progressSlider_released();

	void displayFrame();

};

#endif