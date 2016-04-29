#ifndef IMAGE_H_
#define IMAGE_H_
#include <vector> 
#include <string> 
#include <map>
#include "fitsio.h"

using namespace std; 
class Image {

public: 
	string fileName;
	int naxis;
	long naxis1;
	long naxis2;
	long npixels;

	int bitpix;
	double res;

	vector<double> data;

	vector<int> xList;
	vector<int> yList;
	double length;

	map<string, double> headerDouble;
	map<string, string> headerString;  

public:
	Image();
	Image(string imgFileName);
	template <typename T> Image(vector<T> xpos, vector<T> ypos, vector<double> *briList, long naxis1, long naxis2, int bitpix); 
	void writeToFile(string imgFileName);
	void printImageInfo(int x1=0, int y1=0, int x2=0, int y2=0, int header=0) ;
	void cropStamp(int x1, int y1, int x2, int y2,  string stampFileName); 
	void updateHeader(fitsfile *fptr); 



}; 


#endif