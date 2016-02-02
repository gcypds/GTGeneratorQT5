#include "GTProject_data.h"

GTProject_data* GTProject_data::_instance = 0;

GTProject_data::GTProject_data()
{
	//Default FPS if not given
	fps = 30; 

	//Initialize labels register with empty label 
	label_info default_label;
	default_label.name = "Empty Label";
	default_label.color = QColor(200, 250, 250);
	default_label.ID = 0;
	labels_reg.push_back(default_label);

	//Iniitalize current label with default label
	currLabel_ID = 0;

	//Initialize current ROI ID as empty
	currROI_ID = 0;

	//Initialize ROI selection flag as not selected
	ROI_selected = false;

	ROIselection_thr = 0.003;

	ROIminsize_thr = 0.02;

	//Initialize mouseROItype_sel as not ROI selected
	mouseROItype_sel = 0;
}

GTProject_data* GTProject_data::Instance() {
	if (!_instance)
		_instance = new GTProject_data;

	return _instance;
}

int labelID_search(int ID, QVector<label_info> labels_reg)
{
	int lbl_idx;

	for (int i = 0; i < labels_reg.size(); i++)
	{
		if (labels_reg[i].ID == ID)
		{
			lbl_idx = i;
			break;
		}
	}
	return lbl_idx;
}

int ROIID_search(int ID, QVector<roi_register_info> KeyROIs_reg)
{
	int lbl_idx;

	for (int i = 0; i < KeyROIs_reg.size(); i++)
	{
		if (KeyROIs_reg[i].ID == ID)
		{
			lbl_idx = i;
			break;
		}
	}
	return lbl_idx;
}

