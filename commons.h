#ifndef COMMONS_H_
#define COMMONS_H_
#include <map> 
#include <utility> 
#include <unordered_map> 
#include <string> 
#include <vector> 
#include "Image.h"


class Conf{
public: 
	string chipID; 
	double x; 
	double y; 
	double z; 
	 
	double phi; 
	double psi;
	double theta; 
	double seeing; 
	double rotation; 

	/******** coarse **********/ 
	double dDEC_coarse;
	double dRA_coarse; 
	double dROT_coarse; 

	/******** 		 **********/ 
	double dDEC_shift; 
	double dRA_shift;
	double dROT_shift; 

	/******** overall **********/ 
	double dDEC; 
	double dRA; 
	double dROT; 

	double tolerance; 
	double magCorrection; 

	/**************common configurations **************/; 
	string originDataDIR; 
	string dataDIR; 
	string simuDIR; 
	unordered_map<string, pair<double, double>> coarseCorrectMap; 
	bool extractData; 
	bool extractSimu; 
	bool phosimScript; 
	bool runPhosim; 
	bool analyze; 


	string phosimFileDIR ; 
	
	/************** common configurations **************/

	Conf(); 
	Conf(string fileName); 
	void printConf(); 
	void updateShiftCorrection(); 
}; 


using namespace std; 

void printerror( int status); 
vector<double> getEllipticity(int*  stampRegion, const Image& dataImage, double background); 
vector<string> splitString(string s); 
int getMin(vector<int> * const  v); 
int getMax(vector<int> * const  v); 
double convHMS(string RA) ; 
double convDMS(string DEC) ; 
vector<double> shiftCorrection(Conf* conf); 


#endif