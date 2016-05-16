#ifndef COMMONS_H_
#define COMMONS_H_
#include <map> 
#include <string> 
#include <vector> 
#include "Image.h"



class Conf{
public: 
	string chipID; 
	double x; 
	double y; 
	double z; 
	double psi; 
	double phi; 
	double theta; 
	double seeing; 
	double rotation; 

	double dDEC_shift; 
	double dDEC_coarse;

	double dRA_shift;
	double dRA_coarse; 

	double dROT_shift; 
	double dROT_coarse; 


	double dDEC; 
	double dRA; 
	double dROT; 


	double magCorrection; 
	map<string, vector<double> > coarseCorrectMap; 

	Conf(); 
	Conf(string chipID, double x, double y, double z, double psi, double phi, double theta, double seeing, double magCorrection, double rotation); 
	void updateShiftCorrection(); 
}; 


using namespace std; 

void printerror( int status); 
vector<double> getEllipticity(int*  stampRegion, const Image* dataImage, double background); 
vector<string> splitString(string s); 
int getMin(vector<int> * const  v); 
int getMax(vector<int> * const  v); 
double convHMS(string RA) ; 
double convDMS(string DEC) ; 
vector<double> shiftCorrection(Conf* conf); 


#endif