
#include <iostream> 
#include <string>
#include "Star.h"
#include "commons.h"
using namespace std; 


Star::Star(string chipID, string sexFileName):chipID(chipID) {

	ifstream sexFile(sexFileName.c_str());
	string line;
	//string modelString;
	while (getline(sexFile, line)) {
		if(line[0]!='#') {
			vector<string> items = splitString(line);
			if (items.size() >2) {
				for(int i=0; i<items.size(); ++i) {
					starID.push_back(stod(items[0])); 
					mag.push_back(stod(items[1])); 
					xcenter.push_back(stod(items[2])); 
					ycenter.push_back(stod(items[3])); 
					xworld.push_back(stod(items[4])); 
					yworld.push_back(stod(items[5])); 

					fwhm.push_back(stod(items[6])); 				}
					star_class.push_back(stod(items[7])); 
			}
		}

	}
}

void Star::printStarListInfo() {
	cout << "************************" << endl; 
	cout << "chipID:   " << chipID << endl; 
	cout << "numObject:" << starID.size() << endl; 
	cout << "************************" << endl; 
	/*
	for(int i=0 ; i< starID.size(); ++i) {

		cout << starID[i] << "\t" << xcenter[i] << endl; 
		

	}
	*/


}
