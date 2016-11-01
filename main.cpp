#include "Image.h"
#include <iostream> 
#include "commons.h"
#include <stdlib.h>
#include "Star.h"
#include "des_catalogGenerate.h"
using namespace std; 


int main() {

	//string imageName = "pa_90.fits"; 
	// vector<string> CHIPS =     {"S1","S2","S3","S4","S5","S6","S8","S9","S10","S11","S12","S13","S14",
 //        						"S15","S16","S17","S18","S19","S20","S21","S22","S23","S24","S25","S26",
 //        						"S27","S28","S29","S30","S31","N1","N2","N3","N4","N5","N6","N7","N8",
 //        						"N9","N10","N11","N12","N13","N14","N15","N16","N17","N18","N19","N20",
 //        						"N21","N22","N23","N24","N25","N26","N27","N28","N29","N31"}; 

	vector<string> CHIPS = {"S25"}; 

    Conf conf("conf.txt"); 
    conf.updateShiftCorrection(); 

	/*****************   SEXATCTIR *****************/
    if(conf.extractData) {
	   	for(auto & chip: CHIPS) {
	   		string dataImageName = conf.dataDIR + chip +  "_test_image.fits";
	   		if(!ifstream(dataImageName)) continue; 
			string dataCatalogName = conf.dataDIR + chip + "_dataCatalog.txt"; 
			string dataCMD = "/usr/local/bin/sex -c data.sex " + dataImageName + " -CATALOG_NAME " + dataCatalogName; 
			int status = system(dataCMD.c_str()); 
		} 
	}	

	string fileNameTail = "_x_0.0_y_-1.0_z_0.0_phi_-216000_psi_0.0_theta_0.0_seeing_0.7.fits"; 

	if(conf.extractSimu) {
		for(auto & chip: CHIPS) {
			string simuImageName = conf.simuDIR + "Images_" + chip +  fileNameTail;
			if(!ifstream(simuImageName)) continue; 
			string simuCatalogName = conf.simuDIR + chip + "_simuCatalog.txt"; 
			string simuCMD = "/usr/local/bin/sex -c sim.sex  " + simuImageName + " -CATALOG_NAME " + simuCatalogName; 
			int status = system(simuCMD.c_str()); 
		}
	}

	/*****************   Analyze Data *****************/

	if(conf.analyze) {
		for(auto & chip: CHIPS) {
			cout << "Analyzing " << chip << "....." << endl; 
			string dataCatalogName = conf.dataDIR + chip + "_dataCatalog.txt"; 
			string simuCatalogName = conf.simuDIR + chip+ "_simuCatalog.txt"; 
			
			if(!ifstream(dataCatalogName) || !ifstream(simuCatalogName)) 
				continue; 
			string dataImageName = conf.dataDIR + chip +  "_test_image.fits";
			string simuImageName = conf.simuDIR + "Images_" + chip +  fileNameTail;

			Image dataImage(dataImageName); 
			Image simuImage(simuImageName); 

			Star dataStarList(chip, dataCatalogName); 
			Star simuStarList(chip, simuCatalogName); 

			dataStarList.updateEllipticity(dataImage); 
			simuStarList.updateEllipticity(simuImage); 
			dataStarList.matchObj(simuStarList); 

			dataStarList.writeTxt(simuStarList, conf.simuDIR + chip + "_output_test.txt");  // data on the left; simu on the right; 
		}
	}




	catalogGenerator(conf); 


	// cout << "hello " << endl; 

	// delete conf; 


	

}



