#include "roi_interpolator.h"


ROI_interpolator::ROI_interpolator()
{
	//Project global variables
	data = GTProject_data::Instance();
}

ROI_interpolator::~ROI_interpolator()
{

}

void ROI_interpolator::interpolateROI()
{
	bool ID_found = false;

	//Create new Key ROI register
	if (!data->ROI_selected)
	{
		roi_register_info newKeyROI;
		newKeyROI.ID = data->currROI_ID;
		newKeyROI.lbl_ID = data->currLabel_ID;
		QVector<roi_info> newKeyROI_reg;
		newKeyROI_reg.push_back(data->newKROI);
		newKeyROI.frameROI_info = newKeyROI_reg;

		data->KeyROIs_reg.push_back(newKeyROI);
	}

	roi_info KROI_prev, KROI_next;
	int mindif = 100000;
	int mindif_idx;
	int Fidx;

	//If ROI flag is selected then interpolate
	if (data->ROI_selected)
	{
		//Find index in register of current ROI with the ID
		Fidx = ROIID_search(data->currROI_ID, data->KeyROIs_reg);

		//Selected ROI
		roi_register_info SelKROI = data->KeyROIs_reg[Fidx];

		//Number of key rois saved for selected ROI
		int currROI_Nframes = SelKROI.frameROI_info.size();

		//Search frames to select interpolation
		for (int i = 0; i < currROI_Nframes; i++)
		{
			//Get frame of analysis
			int currFr = SelKROI.frameROI_info[i].frame;

			int dif = data->frame_idx - currFr;

			if (abs(dif) < abs(mindif))
			{
				mindif = dif;
				mindif_idx = i;
			}
		}

		//Find values for interpolation (KROI_prev, KROI_next)

		//Current indexed ROI's frame is greater than a previous one
		if (mindif > 0)
		{
			KROI_prev = SelKROI.frameROI_info[mindif_idx];

			if (mindif_idx + 1 < SelKROI.frameROI_info.size())
			{
				KROI_next = SelKROI.frameROI_info[mindif_idx + 1];
			}

			//Insert new KROI
			SelKROI.frameROI_info.insert(mindif_idx + 1, data->newKROI);
		}

		//Current indexed ROI's frame is less than a previous one
		if (mindif < 0)
		{
			KROI_next = SelKROI.frameROI_info[mindif_idx];

			if (mindif_idx - 1 >= 0)
			{
				KROI_prev = SelKROI.frameROI_info[mindif_idx - 1];
			}

			//Insert new KROI
			SelKROI.frameROI_info.insert(mindif_idx, data->newKROI);
		}

		//Current indexed ROI's frame is equal to a previous one
		if (mindif == 0)
		{
			if (mindif_idx - 1 >= 0)
			{
				KROI_prev = SelKROI.frameROI_info[mindif_idx - 1];
			}

			if (mindif_idx + 1 < SelKROI.frameROI_info.size())
			{
				KROI_next = SelKROI.frameROI_info[mindif_idx + 1];
			}

			//Replace KROI
			SelKROI.frameROI_info[mindif_idx] = data->newKROI;
		}
	}

	interpolation(KROI_prev, data->newKROI, KROI_next, Fidx);
}

void ROI_interpolator::interpolation(roi_info prev, roi_info curr, roi_info next, int Fidx)
{
	//Test
	/*std::cout << std::endl << "New interpolation:" << std::endl;
	if (std::get<1>(prev).size() != 0)
		std::cout << "Prev=" << " f:" << std::get<0>(prev) << " x:" << std::get<1>(prev)[0] << " y:" << std::get<1>(prev)[1] << " w:" << std::get<1>(prev)[2] << " h:" << std::get<1>(prev)[3] << std::endl;
	std::cout << "Curr=" << " f:" << std::get<0>(curr) << " x:" << std::get<1>(curr)[0] << " y:" << std::get<1>(curr)[1] << " w:" << std::get<1>(curr)[2] << " h:" << std::get<1>(curr)[3] << std::endl;
	if (std::get<1>(next).size() != 0)
		std::cout << "Next=" << " f:" << std::get<0>(next) << " x:" << std::get<1>(next)[0] << " y:" << std::get<1>(next)[1] << " w:" << std::get<1>(next)[2] << " h:" << std::get<1>(next)[3] << std::endl;
	*///-----

	QVector<roi_info> interpROI_states;
	int xc_int, yc_int, w_int, h_int;
	int x0, y0, x1, y1;
	double slope_x, slope_y, slope_w, slope_h;
	
	//Replicate input states until last
	if (prev.states.size() == 0 && next.states.size() == 0)
	{
		for (int i = 0; i < data->video_length; i++)
		{
			//New ROI to save at frame i
			roi_info newROI;
			newROI = data->newKROI;
			newROI.frame = i;

			if (i < data->frame_idx)
			{
				newROI.empty = true;
				interpROI_states.append(newROI);
			}
			else
			{				
				interpROI_states.append(newROI);
			}
		}
		//Save in global ROIs register for plotting
		roi_register_info newKROI_reg;
		newKROI_reg.ID = data->currROI_ID;
		newKROI_reg.lbl_ID = data->currLabel_ID;
		newKROI_reg.frameROI_info = interpROI_states;
		data->ROIs_reg.append(newKROI_reg);
	}

	//Linear interpolation until next or last
	if (prev.states.size() != 0)
	{
		//slope for x coordinate
		y0 = prev.left;
		y1 = curr.left;
		x0 = prev.frame;
		x1 = curr.frame;
		slope_x = double(y1 - y0) / double(x1 - x0);

		//slope for y coordinate
		y0 = prev.top;
		y1 = curr.top;
		x0 = prev.frame;
		x1 = curr.frame;
		slope_y = double(y1 - y0) / double(x1 - x0);

		//slope for width
		y0 = prev.w;
		y1 = curr.w;
		x0 = prev.frame;
		x1 = curr.frame;
		slope_w = double(y1 - y0) / double(x1 - x0);

		//slope for height
		y0 = prev.h;
		y1 = curr.h;
		x0 = prev.frame;
		x1 = curr.frame;
		slope_h = double(y1 - y0) / double(x1 - x0);
		
		//Get superior limit to replicate linear interpolation values
		int lim_sup;
		if (next.states.size() == 0)
			lim_sup = curr.frame;
		else
			lim_sup = next.frame;

		for (int i = 0; i < data->video_length; i++)
		{
			if (i > prev.frame && i < lim_sup)
			{
				//Interpolate x coordinate
				y0 = prev.left;
				xc_int = y0 + int(std::floor(double(i - x0)*slope_x));

				//Interpolate y coordinate
				y0 = prev.top;
				yc_int = y0 + int(std::floor(double(i - x0)*slope_y));

				//Interpolate width
				y0 = prev.w;
				w_int = y0 + int(std::floor(double(i - x0)*slope_w));

				//Interpolate height
				y0 = prev.h;
				h_int = y0 + int(std::floor(double(i - x0)*slope_h));

				QVector<int> st;
				st.append(xc_int);
				st.append(yc_int);
				st.append(w_int);
				st.append(h_int);

				//Store new states according interpolation
				roi_info newROI;
				newROI.empty = false;
				newROI.left = xc_int;
				newROI.top = yc_int;
				newROI.right = xc_int + w_int;
				newROI.bot = yc_int + h_int;
				newROI.w = w_int;
				newROI.h = h_int;
				newROI.frame = i;
				newROI.states = st;			

				data->ROIs_reg[Fidx].frameROI_info[i] = newROI;
			}

			//Keep last KeyROI until end
			if (i >= lim_sup && (next.states.size() == 0))
			{
				//Store new states according interpolation
				data->ROIs_reg[Fidx].frameROI_info[i] = curr;
			}
		}
	}

	//Linear interpolation from current to next
	if (next.states.size() != 0)
	{
		//slope for x coordinate
		y0 = curr.left;
		y1 = next.left;
		x0 = curr.frame;
		x1 = next.frame;
		slope_x = double(y1 - y0) / double(x1 - x0);

		//slope for y coordinate
		y0 = curr.top;
		y1 = next.top;
		x0 = curr.frame;
		x1 = next.frame;
		slope_y = double(y1 - y0) / double(x1 - x0);

		//slope for width
		y0 = curr.w;
		y1 = next.w;
		x0 = curr.frame;
		x1 = next.frame;
		slope_w = double(y1 - y0) / double(x1 - x0);

		//slope for height
		y0 = curr.h;
		y1 = next.h;
		x0 = curr.frame;
		x1 = next.frame;
		slope_h = double(y1 - y0) / double(x1 - x0);

		for (int i = 0; i < data->video_length; i++)
		{
			if (i >= curr.frame && i < next.frame)
			{
				//Interpolate x coordinate
				y0 = curr.left;
				xc_int = y0 + int(std::floor(double(i - x0)*slope_x));

				//Interpolate y coordinate
				y0 = curr.top;
				yc_int = y0 + int(std::floor(double(i - x0)*slope_y));

				//Interpolate width
				y0 = curr.w;
				w_int = y0 + int(std::floor(double(i - x0)*slope_w));

				//Interpolate height
				y0 = curr.h;
				h_int = y0 + int(std::floor(double(i - x0)*slope_h));

				QVector<int> st;
				st.append(xc_int);
				st.append(yc_int);
				st.append(w_int);
				st.append(h_int);

				//Store new states according interpolation
				roi_info newROI;
				newROI.empty = false;
				newROI.left = xc_int;
				newROI.top = yc_int;
				newROI.right = xc_int + w_int;
				newROI.bot = yc_int + h_int;
				newROI.w = w_int;
				newROI.h = h_int;
				newROI.frame = i;
				newROI.states = st;

				data->ROIs_reg[Fidx].frameROI_info[i] = newROI;
			}
		}
	}
}

//void ROI_interpolator::accept_deleteROI()
//{
//	QVector<int> st(4, 0);
//
//	//Delete delFrame ROI and subsequent ROIs from ALLROIs
//	if (delete_ROI->delAll_radioButton->isChecked())
//	{
//		for (int i = delFrame; i < vid_length; i++)
//		{
//			std::get<2>(AllROIs[ID])[i] = std::make_tuple(i, st);
//		}
//
//		//Delete Key ROIs with frame bigger than delete point
//		for (int i = 0; i < KeyROIs.size(); i++)
//		{
//			if (std::get<0>(KeyROIs[i]) == delID)
//			{
//				for (int j = 0; j < std::get<2>(KeyROIs[i]).size(); j++)
//				{
//					if (std::get<0>(std::get<2>(KeyROIs[i])[j]) >= delFrame)
//						std::get<2>(KeyROIs[i]).erase(std::get<2>(KeyROIs[i]).begin() + j);
//				}
//				break;
//			}
//		}
//	}	
//	
//	//Delete only delFrame ROI from ALLROIs
//	if (delete_ROI->delCurr_radioButton->isChecked())
//	{
//		std::get<2>(AllROIs[ID])[frame] = std::make_tuple(frame, st);
//
//		//Delete Key ROI if found any in delFrame
//		for (int i = 0; i < KeyROIs.size(); i++)
//		{
//			if (std::get<0>(KeyROIs[i]) == delID)
//			{
//				for (int j = 0; j < std::get<2>(KeyROIs[i]).size(); j++)
//				{
//					if (std::get<0>(std::get<2>(KeyROIs[i])[j]) == delFrame)
//						std::get<2>(KeyROIs[i]).erase(std::get<2>(KeyROIs[i]).begin()+j);
//				}
//				break;
//			}
//		}
//	}
//
//	deleteROI_dialog->close();
//	updateTable();
//}


bool ROI_interpolator::validateNumber(const QString &Input)
{
	//convert qstring to string
	std::string Instr = Input.toLocal8Bit().constData();

	//iterate through string checking for no numbers
	return !Instr.empty() && std::find_if(Instr.begin(),
		Instr.end(), [](char c) { return !isdigit(c); }) == Instr.end();
}

