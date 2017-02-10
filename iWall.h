#ifndef __IWALL_H__
#define __IWALL_H__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//#include <iostream>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
//#include <iostream>
//#include <sstream>
#include <math.h>

#include </usr/include/opencv/cv.h>
#include "/usr/include/opencv/highgui.h"
#include "/usr/include/opencv/cvaux.h"
#include "/usr/include/opencv/cvcompat.h"
#include "/usr/include/opencv/cvstreams.h"
#include "/usr/include/opencv/cxcore.h"
#include "/usr/include/opencv/cvwimage.h"
#include "/usr/include/opencv/cxtypes.h"

#define THRESHOLD 20

/*All structures are defined here*/

typedef struct struct_iw_input_stream                   //This structure will be globally defined.
{
	CvCapture	*pc_stream;
	CvCapture	*wall_stream;
	CvMoments 	*G_Moments;
}iw_input_stream;


typedef struct _iw_image_frame			//Image frame structure.
{
	CvSize sz;
	IplImage	*pc_image;
	IplImage	*wall_image;
	IplImage* hsv_image;
	IplImage* hsv_mask;
	CvScalar  hsv_min;    
	CvScalar  hsv_max ;
}iw_image_frame;


typedef struct _iw_centroid				//Structure of centroid coordinate
{
	int x,y;
}iw_centroid;


typedef struct _iw_cursor_boundary			//Structure of click/cursor movement decision making
{
	int i,flag,j;
	int tempx,tempy,minx,miny,maxx,maxy;
}iw_cursor_boundary;


typedef struct _iw_Moments				// Structure of moments	
{
	double moment10;
	double moment01;
	double area;
}iw_Moments;




int convert_to_hsv(iw_image_frame* frames);
int find_moments(iw_Moments* moments,iw_image_frame* frames);
int iw_get_centriod(iw_image_frame *frames,iw_centroid *center,iw_Moments *moments);
int check_mouse_threshold(iw_image_frame *frames,iw_centroid *center,iw_cursor_boundary *limit);
int mouse_click_event(int button);
int grab_frame_from_video();



#endif //__IWALL_H__