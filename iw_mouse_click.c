#include "iWall.h"

extern iw_input_stream* global;

int check_mouse_threshold(iw_image_frame *frames,iw_centroid *center,iw_cursor_boundary *limit)
{

	if(limit->i==0)
	{
		//	printf("\n Enter 1st loop \n");
			limit->tempx=center->x;
			limit->tempy=center->y;
			limit->minx=(limit->tempx<THRESHOLD)?limit->tempx:limit->tempx-THRESHOLD;
			limit->maxx=limit->tempx+THRESHOLD;
			limit->miny=(limit->tempy<THRESHOLD)?limit->tempy:limit->tempy-THRESHOLD;
			limit->maxy=limit->tempy+THRESHOLD;
			(limit->i)++;
	}
		
	else
	{
		if((limit->minx<center->x && center->x<limit->maxx) && (limit->miny<center->y && center->y<limit->maxy))
		{
			//printf("position (%d,%d,%d),(%d, %d, %d)\n", minx,posX,maxx, miny,posY,maxy);
			limit->flag=0;
			(limit->j)++;
		
			(limit->i)++;
			limit->minx=(limit->tempx<THRESHOLD)?limit->tempx:limit->tempx-THRESHOLD;
			limit->maxx=limit->tempx+THRESHOLD;
			limit->miny=(limit->tempy<THRESHOLD)?limit->tempy:limit->tempy-THRESHOLD;
			limit->maxy=limit->tempy+THRESHOLD;				
			//	printf("updated %d \n",j);
		}
		else
		{
			//printf("\n Enter loop 2 \n");
			limit->tempx=center->x;
			limit->tempy=center->y;
			limit->flag=1;
			limit->j=0;
			limit->i=1;
			limit->minx=(limit->tempx<THRESHOLD)?limit->tempx:limit->tempx-THRESHOLD;
			limit->maxx=limit->tempx+THRESHOLD;
			limit->miny=(limit->tempy<THRESHOLD)?limit->tempy:limit->tempy-THRESHOLD;
			limit->maxy=limit->tempy+THRESHOLD;
		}
	}

		
	if (limit->j==3)
	{
		printf("Mouse Clicked\n");
		mouse_click_event(Button1);
		limit->j=0;
		limit->i=0;
	}
	else
	{
		mouse_click_event(Button5);

	}
		
	Display *display = XOpenDisplay(0);

	Window root = DefaultRootWindow(display);
	XWarpPointer(display, None, root, 0, 0, 0, 0, center->x, center->y);
	//mouse_click_event(Button5);
	XFlush(display);
	XCloseDisplay(display);
	
	
		 
	/*
	// Release the thresholded image+moments... we need no memory leaks.. please
	cvReleaseImage(&imgYellowThresh);
	delete moments;
	*/
}
		


int mouse_click_event(int button)
{
	Display *display = XOpenDisplay(NULL);

	XEvent event;

	if (display == NULL) {
		fprintf(stderr, "Errore nell'apertura del Display !!!\n");
		exit(EXIT_FAILURE);
	}

	memset(&event, 0x00, sizeof(event));

	event.type = ButtonPress;
	event.xbutton.button = button;
	event.xbutton.same_screen = False;

	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

	event.xbutton.subwindow = event.xbutton.window;

	while (event.xbutton.subwindow) {
		event.xbutton.window = event.xbutton.subwindow;

		XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	}

	if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

	XFlush(display);

	usleep(100000);

	event.type = ButtonRelease;
	event.xbutton.state = 0x100;

	if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

	XFlush(display);

	XCloseDisplay(display);
}


		