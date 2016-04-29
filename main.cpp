#include "Image.h"
#include <iostream> 
#include "commons.h"
#include <stdlib.h>
#include "star.h"
using namespace std; 
int main() {

	//string imageName = "measure_PSF_test_back_0.0_e_0.23_PA_130.fits"; 
	string imageName = "N1_test_image.fits"; 
	Image* image = new Image(imageName); 

	image->printImageInfo(); 
	//image->cropStamp(1013, 2038, 1040, 2061, "stamp_test.fits"); 


	int stampRegion[4] = {0, 0, 300, 300}; 

	//double background = 0; 
	//getEllipticity(stampRegion,image, background); 


	string dataCatalogName = "dataCatalog.txt"; 
	string cmd = "/usr/local/bin/sex -c data.sex " + imageName 
		+ " -CATALOG_NAME " + dataCatalogName; 
	int status = system(cmd.c_str()); 

	Star starList("N1", dataCatalogName); 
	starList.printStarListInfo(); 

	delete image; 


}



