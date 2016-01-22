#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <qwidget.h>
#include "ui_playerWidget.h"
#include <iostream>
#include "opencvprocessor.h"
#include <qtimer.h>
#include <QGraphicsScene>
#include <QMouseEvent>

//Global structs
struct label_info
{
	QString name;
	QColor color;
	int ID;
};
//-----------------

class playerWidget : public QWidget
{
	Q_OBJECT

public:
	explicit playerWidget(QWidget *parent = 0);

	~playerWidget();

	void playerInitialization();

	//Global variables
	bool play_state;	//true:play, false:pause
	int fps;
	string imgSeq_path; 
	QStringList imgSeq_list;
	QVector<label_info> labels_reg;		//Labels register
	int currLabel_ID;
	//-----------------

	//playerWidget Gui
	Ui::playerWidget *GTplayerWidget;

private:
	void displayFrame(cv::Mat Frame);

	//GLobal functions
	int labelID_search(int ID, QVector<label_info> labels_reg);
	//-----------------

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

	bool video_loaded;

	//Play pause icons
	QIcon *playIcon;
	QIcon *pauseIcon;

	//ROI tagging 
	int ROI_up;
	int ROI_down;
	int ROI_left;
	int ROI_right;
	int mouse_ROIstate;	//0=ROI not drawn, 1=ROI being drawn, 2=ROI drawn

	int scaledFrame_width;
	int scaledFrame_height;
	
protected:
	//Tagging functions-----------
	bool eventFilter(QObject *obj, QEvent *event);


	public slots:

	void on_playButton_clicked();

	void on_progressSlider_moved(int val);

	void on_progressSlider_released();
	
	void readFrame();
	

};

#endif