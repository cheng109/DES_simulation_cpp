#ifndef COMMONS_H_
#define COMMONS_H_
#include <map> 
#include <string> 
#include <vector> 
#include "Image.h"


void printerror( int status); 
void getEllipticity(int*  stampRegion, const Image* dataImage, double background); 

vector<string> splitString(string s); 


#endif