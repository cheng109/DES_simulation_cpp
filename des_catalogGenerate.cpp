#include "commons.h"
#include "Star.h"
#include "fitsio.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <map>
#include <vector>
#include "des_catalogGenerate.h"
using namespace std; 




void catalogGenerator() {

	map<string, vector<double> > confMap = parseConfigFile("conf.txt"); 
	string dataDIR = "dataCatalog/"; 

	string dataImageName = dataDIR + "N10" +  "_test_image.fits";
	string dataCatalogName = dataDIR + "N10_dataCatalog.txt"; 

	Star *dataStarList = new Star("N10", dataCatalogName); 


	map<string, double> headerMap = getHeader(dataImageName); 

}


map<string, double> getHeader(string imageName) {
	int status = 0 ; 
	fitsfile *fptr; 
	cout << imageName << endl; 
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
		int num = fits_read_key(fptr, TDOUBLE, keyword.c_str(), &value,comment, &status); 
		header[keyword] = value;  
		cout << keyword << "\t" << value << endl; 
	}

	int num1 = fits_read_key(fptr, TSTRING, "TELDEC", dec_str,comment, &status);
	int num2 = fits_read_key(fptr, TSTRING, "TELRA" , ra_str ,comment, &status);
	
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


