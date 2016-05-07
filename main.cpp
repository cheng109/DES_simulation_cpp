#include "Image.h"
#include <iostream> 
#include "commons.h"
#include <stdlib.h>
#include "star.h"
using namespace std; 
int main() {

	//string imageName = "pa_90.fits"; 
	string imageName = "N7_test_image.fits"; 
	Image* image = new Image(imageName); 

	image->printImageInfo(); 
	//image->cropStamp(1013, 2038, 1040, 2061, "stamp_test.fits"); 


	int stampRegion[4] = {0, 0, 300, 300}; 

	double background = 0; 
	//getEllipticity(stampRegion,image, background); 


	Shape shape("ellipse", 1936.9799,3976.332,100.80637,200.70004,45); 
	//Shape shape("box", 801.4,1893.8,145.2,140.4,60); 

	
	//image->cropStamp(&shape, "test_stamp_ell.fits"); 



	/*
	string dataCatalogName = "dataCatalog.txt"; 
	string cmd = "/usr/local/bin/sex -c data.sex " + imageName 
		+ " -CATALOG_NAME " + dataCatalogName; 
	int status = system(cmd.c_str()); 

	Star starList("N1", dataCatalogName); 
	starList.printStarListInfo(); 
	*/
	
	delete image; 


}



