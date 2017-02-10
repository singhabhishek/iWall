
#include "iWall.h"

extern iw_input_stream* global;
/*Here is the code for centroid point calculation of the image */

int iw_get_centriod(iw_image_frame *frames,iw_centroid *center,iw_Moments* moments)
{
	
 	center->x = 2.5*moments->moment10/moments->area;
	center->y = 2.5*moments->moment01/moments->area;
	return 0;
}
