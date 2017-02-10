// iWall.cpp : Defines the entry point for the console application.
//

#include "iWall.h"
//#include <iostream>
//#include <sstream>

iw_input_stream *global=NULL;
CvCapture *pc_stream=NULL;
CvCapture *wall_stream=NULL;
CvMoments *G_Moments = NULL;	

using namespace std;
using namespace cv;

int main()
{
	//Main Logic will be defined here.
	
	global=(iw_input_stream *)malloc(sizeof(iw_input_stream ));
	if(!global)
	{
		printf("Error!! Cannot allocate global\n");
	}
	
	iw_image_frame *frames = (iw_image_frame*)malloc(sizeof(iw_image_frame));

	global->G_Moments=(CvMoments *)malloc(sizeof(CvMoments ));

	grab_frame_from_video();

	frames->sz= cvGetSize(cvQueryFrame( global->wall_stream));
	frames->pc_image=NULL;
	frames->wall_image=cvCreateImage( frames->sz, 8, 3 );
	frames->hsv_image=cvCreateImage( frames->sz, 8, 3 );
	frames->hsv_mask=cvCreateImage( frames->sz, 8, 1 );
	frames->hsv_min = cvScalar(25, 100, 100,0);    
	frames->hsv_max = cvScalar(60, 255, 255,0);
	
	
	iw_Moments *moments=(iw_Moments*)malloc(sizeof(iw_Moments));
	moments->moment10=0;
	moments->moment01=0;
	moments->area=0;
	
	iw_cursor_boundary *limit=(iw_cursor_boundary*)malloc(sizeof(iw_cursor_boundary));		
	limit->i=0;
	limit->flag=0;
	limit->j=0;
	limit->tempx=0;
	limit->tempy=0;
	limit->minx=0;
	limit->miny=0;
	limit->maxx=0;
	limit->maxy=0;
	
	iw_centroid *center=(iw_centroid*)malloc(sizeof(iw_centroid));
	center->x=0;
	center->y=0;
	
	while(1)
	{
		frames->wall_image=cvQueryFrame( global->wall_stream);
		convert_to_hsv(frames);
		find_moments(moments,frames);
		iw_get_centriod(frames,center,moments);
		check_mouse_threshold(frames,center,limit);
	}
	cvReleaseCapture( &global->wall_stream);
	return 0;
}
