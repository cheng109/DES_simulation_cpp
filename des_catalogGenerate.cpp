#include "commons.h"
#include "Star.h"
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


