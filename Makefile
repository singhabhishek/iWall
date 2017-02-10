# Define the symbols we might want to change
CXX	:= g++
CXXFLAGS := -I/usr/include/opencv -lcv -lhighgui -lcvaux -lml -lcxcore
OBJECTS	:= iWall.o iw_grabber.o iw_image_processing.o iw_cent.o iw_mouse_click.o

all:$(OBJECTS)

clean:
	rm -f $(OBJECTS)

iWallService: $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) -o iWallService

iWall.o: iWall.c
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c iWall.c -o iWall.o

iw_grabber.o: iw_grabber.c
	$(CXX) $(CXXFLAGS) -c iw_grabber.c -o iw_grabber.o

iw_image_processing.o: iw_image_processing.c
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c iw_image_processing.c -o iw_image_processing.o

iw_cent.o: iw_cent.c
	$(CXX) $(CXXFLAGS) -c iw_cent.c -o iw_cent.o

iw_mouse_click.o: iw_mouse_click.c
	$(CXX) $(CXXFLAGS) -c iw_mouse_click.c -o iw_mouse_click.o	
