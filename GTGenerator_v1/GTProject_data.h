#ifndef GTPROJECT_DATA_H
#define GTPROJECT_DATA_H

#include <qwidget.h>
#include <iostream>
#include <qtablewidget.h>

//Global structs
struct label_info
{
	QString name;
	QColor color;
	int ID;
};

struct roi_info
{
	bool empty;
	int frame;
	int top;
	int bot;
	int left;
	int right;
	int w;
	int h;
	QVector<int> states;
};

struct roi_register_info
{
	int ID;
	int lbl_ID;
	QVector<roi_info> frameROI_info;
};
//-----------------

//Global functions
int labelID_search(int ID, QVector<label_info> labels_reg);

int ROIID_search(int ID, QVector<roi_register_info> KeyROIs_reg);

class GTProject_data
{
public:
	static GTProject_data *Instance();

	QVector<label_info> labels_reg;			//Labels register
	QVector<roi_register_info> ROIs_reg;	//ROIs register
	QVector<roi_register_info> KeyROIs_reg;	//Key ROIs register

	int fps;							//Displayed FPS
	int currLabel_ID;					//Current selected label ID
	int currROI_ID;						//Current selected ROI ID
	bool ROI_selected;					//true: ROI is new, false: ROI is selected

	std::string imgSeq_path;			//Path to image sequence
	QStringList imgSeq_list;			//Frames list

	roi_info newKROI;					//New Key ROI

	int frame_idx;	
	int video_length;

	double ROIselection_thr;			//Threshold for select a drawn ROI (Relative to frame size)
	int ROIselection_thr_pix_w;			//Threshold in pixels for select a drawn ROI (width)
	int ROIselection_thr_pix_h;			//Threshold in pixels for select a drawn ROI (height)

	double ROIminsize_thr;				//Threshold for minimum size of a ROI (Relative to frame size)
	int ROImin_w;						//Threshold in pixels for minimum width of a ROI
	int ROImin_h;						//Threshold in pixels for minimum height of a ROI

	QTableWidget *currFrame_ROIs;		//ROIs of the current frame

private:

	GTProject_data();

	static GTProject_data * _instance;
};
#endif