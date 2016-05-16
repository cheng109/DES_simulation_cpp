#include "commons.h"
#include <map>
#include <string>
#include <vector>


map<string, double> getHeader(string imageName) ; 
map<string, vector<double>> parseConfigFile(string configFileName); 
void writePhosimCommand(string phosimCommandName, Conf* conf) ; 
void wrtiePhosimCatalog(string phosimCatalogName, Star* dataStarList, map<string, double> &headerMap,Conf* conf); 
void writePhosimRun(string runScriptName, string suffix, Conf* conf); 



void catalogGenerator(Conf* conf) ; 