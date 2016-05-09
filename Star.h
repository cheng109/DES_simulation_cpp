#ifndef STAR_H_
#define STAR_H_

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Image.h"
#define CLASSIFICATION_THRESHOLD 0.95
#define PIXEL_SCALE  0.27
#define MAG_THRESHOLD  21
#define STAR 1

using namespace std; 
class Star {

public:

	string chipID; 
	int numObj; 
	int numStar; 
	int	numGood; 
	int numMatch; 
	vector<int> ID; 
	vector<double> xcenter; 
	vector<double> ycenter; 
	vector<double> ra; 
	vector<double> dec; 
	
	vector<double> mag; 
	vector<int> type;  // '1' indictate star; '0' indicates others; 
	vector<int> good;   // '1' indicates good matched star between 2 images; 

	vector<double> e; 
	vector<double> e1; 
	vector<double> e2; 
	vector<double> PA; 

	vector<double> xworld; 
	vector<double> yworld; 

	vector<double> fwhm; 
	vector<double> star_class; 
	vector<double> background; 
	vector<double> matchIndex; 

public: 
	Star() ; 
	Star(string chipID, string sexFileName) ; 
	void printStarListInfo(int n); 
	void matchObj(Star* starList); 
	void updateEllipticity(Image* image) ; 
	void writeTxt(Star* starList, string outFileName); 
}; 







#endif 