#ifndef ROI_INTERPOLATOR_H
#define ROI_INTERPOLATOR_H


#include <iostream>
#include "GTProject_data.h"

class ROI_interpolator 
{

public:
	ROI_interpolator();
	~ROI_interpolator();

	void interpolateROI();

private:

	//Project global variables
	GTProject_data *data;

	//Delete ROI parameters
	int delID;
	int delFrame;

	//Functions
	bool validateNumber(const QString &Input);

	void interpolation(roi_info prev, roi_info curr, roi_info next, int Fidx);
};

#endif // ROI_INTERPOLATOR_H
