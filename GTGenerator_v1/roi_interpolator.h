#ifndef ROI_INTERPOLATOR_H
#define ROI_INTERPOLATOR_H


#include <iostream>
#include "GTProject_data.h""

class ROI_interpolator 
{

public:
	ROI_interpolator();
	~ROI_interpolator();

private:

	//Project global variables
	GTProject_data *data;

	int vid_length;
	int NROI;
	
	//Delete ROI parameters
	int delID;
	int delFrame;

	//Functions
	void addNewROI();

	bool validateNumber(const QString &Input);

	void interpolateROI();

	void interpolation(roi_info prev, roi_info curr, roi_info next, int Fidx);
};

#endif // ROI_INTERPOLATOR_H
