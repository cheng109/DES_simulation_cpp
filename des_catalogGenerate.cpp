#include "commons.h"
#include "Star.h"
#include "fitsio.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <map>
#include <vector>
#include <cmath>
#include "des_catalogGenerate.h"
#include <stdlib.h>
#include <time.h>
using namespace std; 

#define COEF_ARCSEC_TO_RAD 4.8481e-6


void catalogGenerator(Conf* conf) {

   

	


	//map<string, vector<double> > correctMap = parseConfigFile("conf.txt"); 
	string dataDIR = "dataCatalog/"; 

	string dataImageName = dataDIR + conf->chipID +  "_test_image.fits";
	string dataCatalogName = dataDIR + conf->chipID + "_dataCatalog.txt"; 

	Star *dataStarList = new Star(conf->chipID, dataCatalogName); 


	map<string, double> headerMap = getHeader(dataImageName);  // include 'AZ', 'TELRA', 'TELDEC'


	srand (time(NULL));
	string suffix = to_string(int(1000000.0 + 9000000.0 * rand()/(RAND_MAX + 1.0))); 


	writePhosimCommand(conf->chipID + "_phosimCommand_ID_" + suffix, conf) ; 
	wrtiePhosimCatalog(conf->chipID + "_phosimCatalog_ID_" + suffix, dataStarList, headerMap, conf); 
	writePhosimRun	  ("run_sample.txt", suffix, conf); 
	//delete conf; 

}


void writePhosimRun(string runScriptName, string suffix,  Conf* conf) {

	string DestinationDIR = "output_fits"; 

	ofstream file; 
	file.open(runScriptName);
	string chipID = conf->chipID; 
	
	
	string workDirectory = chipID + "_work_ID_" + suffix ; 
    string outputDirectory = chipID + "_output_ID_" + suffix ; 


	string outputName = DestinationDIR + "/"+ "Images_" + chipID 
                 + "_x_" + to_string(conf->x)
                 + "_y_" + to_string(conf->y)
                 + "_z_" + to_string(conf->z)
                 + "_phi_" + to_string(conf->phi)
                 + "_psi_" + to_string(conf->psi)
                 + "_theta_" + to_string(conf->theta)
                 + "_seeing_" + to_string(conf->seeing) 
                 + ".fits" ; 



    // write the run script; 
    file 	<< "#!/bin/bash \n"
    		<< "pwd=$(pwd) \n"
    		<< "PHOSIM_PATH=/Users/cheng109/toberemoved/phosim/phosim_core/ \n"
    		<< "mkdir $pwd/"+ workDirectory +" $pwd/" + outputDirectory + "\n"  // create 'work' and 'output' directories; 
    		<< "cd $PHOSIM_PATH \n"
    		<< "./phosim $pwd/" + chipID +"_phosimCatalog_ID_" + suffix 
    			+ " -c $pwd/" + chipID +"_phosimCommand_ID_" + suffix
    			+ " -e 0 -w $pwd/"+ workDirectory + " -o $pwd/" + outputDirectory
                + " -i deCam" 
                + " -s " +chipID 
                + " && gunzip -f $pwd/" + outputDirectory + "/*"+chipID +"*.gz \n"
            << "cp $pwd/" + outputDirectory+ "/*"+chipID +"*.fits " + "$pwd/" + outputName + "\n" 
            << "rm -rf $pwd/" +  workDirectory   				 + "\n" 
            << "rm -rf $pwd/" +  outputDirectory 				 + "\n" 
			<< "rm -rf $pwd/" +  chipID + "_phosimCatalog_ID_"  + suffix + "\n" 
            << "rm -rf $pwd/" +  chipID + "_phosimCommand_ID_"  + suffix + "\n" ; 
    file.close(); 
    string chmodCMD = "chmod +x " + runScriptName;  
    system(chmodCMD.c_str()); 

}


void wrtiePhosimCatalog(string phosimCatalogName, Star* dataStarList, map<string, double> &headerMap,  Conf* conf) {
	ofstream file; 
	file.open(phosimCatalogName); 
	double factor = cos(headerMap["TELDEC"]*M_PI /180.0); 

	file    << "Unrefracted_RA_deg "   + to_string(headerMap["TELRA"] + conf->dRA*factor) + "\n"
            << "Unrefracted_Dec_deg "  + to_string(headerMap["TELDEC"]+ conf->dDEC) 		+ "\n"
            << "Unrefracted_Azimuth "  + to_string(headerMap["AZ"])            					+ "\n"
            << "Unrefracted_Altitude " + to_string(90.0-headerMap["ZD"])						+ "\n"
            << "Opsim_rotskypos "      + to_string(conf->rotation) 								+ "\n"
            << "Opsim_rawseeing "	   + to_string(conf->seeing)   								+ "\n"
            << "SIM_VISTIME " 		   + to_string(headerMap["EXPTIME"]) 						+ "\n"
            << "Opsim_rottelpos 0 \n" 
			<<"Opsim_moondec -90 \n" 
			<<"Opsim_moonra 180 \n" 
			<<"Opsim_expmjd 49552.3 \n" 
			<<"Opsim_moonalt -90 \n" 
			<<"Opsim_sunalt -90 \n" 
			<<"Opsim_filter 1 \n" 
			<<"Slalib_date 1994/7/19/0.298822999997 \n" 
			<<"Opsim_dist2moon 180.0 \n" 
			<<"Opsim_moonphase 10.0 \n" 
			<<"Opsim_obshistid 99999999 \n" 
			<<"SIM_SEED     1000 \n" 
			<<"SIM_MINSOURCE 1 \n" 
			<<"SIM_TELCONFIG 0 \n" 
			<<"SIM_CAMCONFIG 1 \n" 
			<<"SIM_NSNAP 1 \n" ; 


	double magCorrection = 4.0 ; 
	for (int i=0; i<dataStarList->numObj; ++i) {

		file 	<< "object " 
				<< to_string(dataStarList->ID[i]) + " " 
				<< to_string(dataStarList->xworld[i]) + " " 
				<< to_string(dataStarList->yworld[i]) + " " 
				<< to_string(dataStarList->mag[i] + magCorrection ) + " "
				<< (dataStarList->sed[i]) + " " 
				<< to_string(dataStarList->z[i]) + " " 
				<< to_string(dataStarList->gamma1[i]) + " "
            	<< to_string(dataStarList->gamma2[i]) + " "
            	<< to_string(dataStarList->mu[i]) + " "
            	<< to_string(dataStarList->delta_ra[i]) + " "
            	<< to_string(dataStarList->delta_dec[i]) + " "
            	<< (dataStarList->type_str[i]) + " "; 

        if( dataStarList->type[i]==STAR) 
        	file << "none none\n"; 
        else 
        	file << to_string(dataStarList->gauss_sigma[i]) + " none none\n"; 
	}


	file.close(); 


}


void writePhosimCommand(string phosimCommandName, Conf* conf) {
	ofstream file; 
	file.open(phosimCommandName) ; 
	file    << "zenith_v 1000.0\n"
            << "raydensity 0.0\n"
            << "clearperturbations\n"
            << "overdepbias -40.0\n"
            << "siliconthickness 250\n"
               //#+ "throughputfile 1\n"
            << "domeseeing 0.0\n"
            << "lascatprob 0.0\n"
            << "body 0 0 " + to_string(conf->phi   * COEF_ARCSEC_TO_RAD) + "\n"
            << "body 0 1 " + to_string(conf->psi   * COEF_ARCSEC_TO_RAD) + "\n"
            << "body 0 2 " + to_string(conf->theta * COEF_ARCSEC_TO_RAD) + "\n"
            << "body 0 3 " + to_string(conf->x) + "\n"
            << "body 0 4 " + to_string(conf->y) + "\n"
            << "body 0 5 " + to_string(conf->z) + "\n"; 
    file.close() ; 

}


map<string, double> getHeader(string imageName) {
	int status = 0 ; 
	fitsfile *fptr; 
	if ( fits_open_file(&fptr, imageName.c_str(), READONLY, &status) )
		printerror( status );
	char* comment = NULL ; 
	vector<string> keywordDouble; 
	vector<string> keywordString; 

	double value = 0 ;
	char dec_str[FLEN_VALUE];  
	char ra_str[FLEN_VALUE];  


	map<string, double> header; 

	//keywordString.push_back("TELRA");  // 20:38:35.286  ; string
	//keywordString.push_back("TELDEC");  // -57:12:39.294 ;  string
	keywordDouble.push_back("AZ");    
	keywordDouble.push_back("ZD");  
	keywordDouble.push_back("EXPTIME");    // seconds ; double 
	for (auto keyword : keywordDouble) {
		fits_read_key(fptr, TDOUBLE, keyword.c_str(), &value,comment, &status); 
		header[keyword] = value;  
	}

	fits_read_key(fptr, TSTRING, "TELDEC", dec_str,comment, &status);
	fits_read_key(fptr, TSTRING, "TELRA" , ra_str ,comment, &status);
	
	header["TELDEC"] = convDMS(dec_str);  
	header["TELRA"]  = convHMS(ra_str) ; 

	if ( fits_close_file(fptr, &status) )
		printerror( status );
	return header; 

}


map<string, vector<double> > parseConfigFile(string configFileName) {

	//configFileName = "conf.txt"; 
	ifstream configFile(configFileName.c_str());
	string line;
	map<string, vector<double> > confMap; 
	while (getline(configFile, line)) {
		//cout << line.size() << endl; 
		if(line.size() > 0 and line.at(0)!='#') {
			vector<string> items = splitString(line);
			if (items.size() ==4) {

				vector<double> shift(2); 
				shift[0] = stod(items[2]); 
				shift[1] = stod(items[3]); 
				confMap[items[0]] = shift; 
			}
		}
	}
	configFile.close() ; 
	return confMap; 
}


Conf::Conf(string chipID, double x, double y, double z, double phi, double psi, double theta, double seeing, double magCorrection,  double rotation): 
            chipID(chipID), x(x), y(y), z(z), phi(phi), psi(psi), theta(theta), seeing(seeing), magCorrection(magCorrection), rotation(rotation) {

        coarseCorrectMap = parseConfigFile("conf.txt"); 
        dDEC_coarse = coarseCorrectMap[chipID][0]; 
        dRA_coarse  = coarseCorrectMap[chipID][1]; 
        dROT_coarse = rotation ; // coarseCorrectMap[chipID][2];
        //vector<double> shiftCorrect =  shiftCorrection(conf); 
    } 

