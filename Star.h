#ifndef STAR_H_
#define STAR_H_

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#define CLASSIFICATION_THRESHOLD 0.95
#define PIXEL_SCALE  0.27
#define MAGNITUDE_THRESHOLD  22.5

using namespace std; 
class Star {

	string chipID; 
	vector<double> xcenter; 
	vector<double> ycenter; 
	vector<double> ra; 
	vector<double> dec; 
	vector<double> starID; 
	vector<double> mag; 
	vector<string> type; 

	vector<double> e; 
	vector<double> e1; 
	vector<double> e2; 
	vector<double> PA; 

	vector<double> xworld; 
	vector<double> yworld; 

	vector<double> fwhm; 
	vector<double> star_class; 

public: 
	Star() ; 
	Star(string chipID, string sexFileName) ; 
	void printStarListInfo(); 

}; 







#endif 