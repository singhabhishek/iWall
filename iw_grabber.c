
#include "iWall.h"

extern iw_input_stream* global;
/* It will retrive frames from camera */

int grab_frame_from_video()
{
	//Access data_global->pc-stream & data_global->wall_stream using cvCaptureFromCAM;
	global->wall_stream = cvCaptureFromCAM(0);
	
	//Exract frame using cvQueryFrame and set to data_global->data;
	
	return 0;
}