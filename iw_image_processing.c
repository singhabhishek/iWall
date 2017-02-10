#include "iWall.h"

extern iw_input_stream* global;

/* Image processing modulue is defined in this file*/

int convert_to_hsv(iw_image_frame *frames)
{
	/*Access frames->pc_image & frames->wall_image
	Set threshold value for hsv
	Rgb value is converted into hsv & is set to frames->hsv_image	
	Thresholded image will be set to frames->hsv_mask
	Edge detection will be applied & set to frames->hsv_mask
	*/


	

	cvCvtColor(frames->wall_image, frames->hsv_image,CV_BGR2HSV);

	cvInRangeS (frames->hsv_image,frames-> hsv_min,frames->	hsv_max, frames->hsv_mask);

	//cvSmooth( frames->hsv_mask, frames->hsv_mask, CV_MEDIAN,27, 0, 0, 0 );

	return 0;
}

int find_moments(iw_Moments* moments,iw_image_frame* frames)
{
	cvMoments(frames->hsv_mask, global->G_Moments, 1);
    // The actual moment values
	moments->moment10 = cvGetSpatialMoment(global->G_Moments, 1, 0);
	moments->moment01 = cvGetSpatialMoment(global->G_Moments, 0, 1);
	moments->area = cvGetCentralMoment(global->G_Moments, 0, 0);
	return 0;
}


