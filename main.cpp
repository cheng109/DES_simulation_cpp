#include "Image.h"
#include <iostream> 
#include "commons.h"
#include <stdlib.h>
#include "Star.h"
#include "des_catalogGenerate.h"
using namespace std; 


int main() {

	//string imageName = "pa_90.fits"; 
	vector<string> CHIPS; 

    CHIPS.push_back("S1");      CHIPS.push_back("S2");      CHIPS.push_back("S3");      CHIPS.push_back("S4");      CHIPS.push_back("S5");      CHIPS.push_back("S6");  
    CHIPS.push_back("S8");      CHIPS.push_back("S9");      CHIPS.push_back("S10");     CHIPS.push_back("S11");     CHIPS.push_back("S12");     CHIPS.push_back("S13"); 
    CHIPS.push_back("S14");     CHIPS.push_back("S15");     CHIPS.push_back("S16");     CHIPS.push_back("S17");     CHIPS.push_back("S18");     CHIPS.push_back("S19"); 
    CHIPS.push_back("S20");     CHIPS.push_back("S21");     CHIPS.push_back("S22");     CHIPS.push_back("S23");     CHIPS.push_back("S24");     CHIPS.push_back("S25"); 
    CHIPS.push_back("S26");     CHIPS.push_back("S27");     CHIPS.push_back("S28");     CHIPS.push_back("S29");     CHIPS.push_back("S30");     CHIPS.push_back("S31"); 
    CHIPS.push_back("N1");      CHIPS.push_back("N2");      CHIPS.push_back("N3");      CHIPS.push_back("N4");      CHIPS.push_back("N5");      CHIPS.push_back("N6");      CHIPS.push_back("N7");      CHIPS.push_back("N8"); 
    CHIPS.push_back("N9");      CHIPS.push_back("N10");     CHIPS.push_back("N11");     CHIPS.push_back("N12");     CHIPS.push_back("N13");     CHIPS.push_back("N14");     CHIPS.push_back("N15");     CHIPS.push_back("N16"); 
    CHIPS.push_back("N17");     CHIPS.push_back("N18");     CHIPS.push_back("N19");     CHIPS.push_back("N20");     CHIPS.push_back("N21");     CHIPS.push_back("N22");     CHIPS.push_back("N23");     CHIPS.push_back("N24"); 
    CHIPS.push_back("N25");     CHIPS.push_back("N26");     CHIPS.push_back("N27");     CHIPS.push_back("N28");     CHIPS.push_back("N29");     CHIPS.push_back("N31"); 

	 
	string dataDIR = "dataCatalog/"; 
	string simuDIR = "simuCatalog/"; 
if(0) {
   	for(int i=0; i<CHIPS.size(); ++i) {
   		string dataImageName = dataDIR + CHIPS[i] +  "_test_image.fits";
   		if(!ifstream(dataImageName)) 
			continue; 
		
		string dataCatalogName = dataDIR + CHIPS[i] + "_dataCatalog.txt"; 
		
		string dataCMD = "/usr/local/bin/sex -c data.sex " + dataImageName + " -CATALOG_NAME " + dataCatalogName; 

		int status = system(dataCMD.c_str()); 

	} 
}


string fileNameTail = "_x_0.0_y_-1.0_z_0.0_phi_-216000_psi_0.0_theta_0.0_seeing_0.7.fits"; 

if(0) {
	for(int i=0; i<CHIPS.size(); ++i) {

		string simuImageName = simuDIR + "Images_" + CHIPS[i] +  fileNameTail;
		if(!ifstream(simuImageName)) 
			continue; 
		string simuCatalogName = simuDIR + CHIPS[i] + "_simuCatalog.txt"; 
		
		string simuCMD = "/usr/local/bin/sex -c sim.sex  " + simuImageName + " -CATALOG_NAME " + simuCatalogName; 
		int status = system(simuCMD.c_str()); 
	}
}

/*
	for(int i=0; i<CHIPS.size(); ++i) {
		cout << CHIPS[i] << endl; 
		string dataCatalogName = dataDIR + CHIPS[i] + "_dataCatalog.txt"; 
		string simuCatalogName = simuDIR + CHIPS[i] + "_simuCatalog.txt"; 
		
		if(!ifstream(dataCatalogName) or !ifstream(simuCatalogName)) 
			continue; 
		string dataImageName = dataDIR + CHIPS[i] +  "_test_image.fits";
		string simuImageName = simuDIR + "Images_" + CHIPS[i] +  fileNameTail;

		Image* dataImage = new Image(dataImageName); 
		Image* simuImage = new Image(simuImageName); 

		Star *dataStarList = new Star(CHIPS[i], dataCatalogName); 
		Star *simuStarList = new Star(CHIPS[i], simuCatalogName); 
		
		dataStarList->updateEllipticity(dataImage); 
		simuStarList->updateEllipticity(simuImage); 
		dataStarList->matchObj(simuStarList); 
		dataStarList->writeTxt(simuStarList, simuDIR + CHIPS[i] + "_output_test.txt");  // data on the left; simu on the right; 
		delete dataImage, simuImage, dataStarList, simuStarList;  
	}

*/


	catalogGenerator("N10"); 

}



