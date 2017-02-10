make
gcc -I/usr/include/opencv -lcv -lhighgui -lcvaux -lml -lcxcore iWall.o iw_cent.o iw_grabber.o iw_image_processing.o iw_mouse_click.o -o iWallService
