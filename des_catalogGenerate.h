#include "commons.h"
#include <map>
#include <string>
#include <vector>


map<string, double> getHeader(string imageName) ; 
map<string, vector<double>> parseConfigFile(string configFileName); 
void catalogGenerator() ; 