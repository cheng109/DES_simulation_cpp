#ifndef COMMONS_H_
#define COMMONS_H_
#include <map> 
#include <string> 
#include <vector> 
#include "Image.h"


using namespace std; 

void printerror( int status); 
vector<double> getEllipticity(int*  stampRegion, const Image* dataImage, double background); 
vector<string> splitString(string s); 
int getMin(vector<int> * const  v); 
int getMax(vector<int> * const  v); 


#endif