
#include <iostream> 
#include <string>
#include <fstream>
#include "Star.h"
#include "commons.h"
#include <cmath>
using namespace std; 


Star::Star(string chipID, string sexFileName):chipID(chipID) {

	ifstream sexFile(sexFileName.c_str());
	string line;
	//string modelString;
	numObj  = 0; 
	numStar = 0; 
	numGood = 0; 
	numMatch = 0; 
	while (getline(sexFile, line)) {
		if(line.size() > 0 and line[0]!='#') {
			vector<string> items = splitString(line);
			if (items.size() >2) {

				ID.push_back(stoi(items[0])); 
				mag.push_back(stod(items[1])); 
				xcenter.push_back(stod(items[2])); 
				ycenter.push_back(stod(items[3])); 
				xworld.push_back(stod(items[4])); 
				yworld.push_back(stod(items[5])); 

				fwhm.push_back(stod(items[6])); 				
				star_class.push_back(stod(items[7])); 
				background.push_back(stod(items[8])); 

				numObj ++;
			}
		}

	}
	e.resize(numObj); 
	e1.resize(numObj); 
	e2.resize(numObj); 	
	PA.resize(numObj); 
	matchIndex.resize(numObj, -1); 
	good.resize(numObj); 
	type.resize(numObj); 
	// update Type; 
	for (int i=0; i<type.size(); ++i) {
		if(mag[i] < MAG_THRESHOLD and star_class[i] > CLASSIFICATION_THRESHOLD )   {
			type[i] = STAR;     // '1' indicate star; 
			numStar ++; 
		}
	}
}

void Star::matchObj(Star* starList) {
	// update 'matchIndex' for both starList; 
	// match all objects;
	double tol = 15 ; // unit: pixel 
	for(int i=0; i<numObj; ++i) {
		for (int j=0; j<starList->numObj ; ++j) {
			if( starList->matchIndex[j] == -1 and starList->type[i] == this->type[i]) {

				double dx = starList->xcenter[j] - xcenter[i]; 
				double dy = starList->ycenter[j] - ycenter[i]; 
				double dr2 = dx*dx + dy*dy; 
				//cout << "dr2: " << dr2 << endl; 
				if (dr2 < tol*tol) {

					this->matchIndex[i] = j ;
					starList->matchIndex[j] = i; 
					if (starList->type[i]== STAR) {

						this->good[i] 	  = 1; 
						starList->good[i] = 1; 
					}
				}

			}
		}
		numGood += this->good[i] ; 

	}
	starList->numGood = this->numGood; 

	for(int i=0; i<numObj; ++i) {
		if(this->matchIndex[i]!=-1) 
			this->numMatch ++ ; 	
	
	}
	starList->numMatch = this->numMatch; 
}

void Star::updateEllipticity(Image* image) {
	/*
	Returns:    v[0] = e1; 
                v[1] = e2; 
                v[2] = e; 
                v[3] = Postion angle  [-pi, pi]; 
                v[4] = flux; 
                v[5] = rms ; 
                v[6] = number of interations; 
*/
    double winSizeX = 8; 
    double winSizeY = 8; 
    int  stampRegion[4]; 
    for(int i=0; i<numObj; ++i) {
    	stampRegion[0] = xcenter[i] - winSizeX ; 
    	stampRegion[1] = ycenter[i] - winSizeX ; 
    	stampRegion[2] = xcenter[i] + winSizeX ; 
    	stampRegion[3] = ycenter[i] + winSizeX ;
    	vector<double> result = getEllipticity(stampRegion, image,  background[i]); 
    	if(isnan(result[0]) or isnan(result[0]) or isnan(result[0])) {
    		good[i] = 0; 
    		continue; 
    	}
    	else {
	    	e1[i] = result[0]; 
    		e2[i] = result[1]; 
    		e[i]  = result[2]; 
    		PA[i] = result[3];   // Position angle [-pi, pi]
    	}
    }
	//getEllipticity(int* stampRegion, const Image* const dataImage, double background)
	//getEllipticity(int* stampRegion, const Image* const dataImage, double background)

}


void Star::writeTxt(Star* starList, string outFileName) {

	// writeOut only 'good' stars; 
	// 'this' on the left and 'starList' on the right; 
	ofstream outFile; 
	outFile.open(outFileName); 
	for(int i=0; i<numObj; ++i) {
		if(good[i] == 1) {
			outFile << to_string(this->e[i]) + "\t"      // C0
					<< to_string(this->PA[i]) + "\t" 	 
					<< to_string(this->e1[i]) + "\t" 
					<< to_string(this->e2[i]) + "\t" 
					<< to_string(this->xcenter[i]) + "\t" 
					<< to_string(this->ycenter[i]) + "\t" 
					<< to_string(this->xworld[i]) + "\t" 
					<< to_string(this->yworld[i]) + "\t" ; 


			outFile << to_string(starList->e[matchIndex[i]]) + "\t"  // C8
					<< to_string(starList->PA[matchIndex[i]]) + "\t" 
					<< to_string(starList->e1[matchIndex[i]]) + "\t" 
					<< to_string(starList->e2[matchIndex[i]]) + "\t" 
					<< to_string(starList->xcenter[matchIndex[i]]) + "\t" 
					<< to_string(starList->ycenter[matchIndex[i]]) + "\t" 
					<< to_string(starList->xworld[matchIndex[i]]) + "\t" 
					<< to_string(starList->yworld[matchIndex[i]]) + "\t" ; 
			outFile << endl; 
		}



	}
	outFile.close(); 

}

void Star::printStarListInfo( int num) {
	cout << "************************" 	<< endl; 
	cout << "chipID:   " << chipID  	<< endl; 
	cout << "numObject:" << numObj  	<< endl; 
	cout << "numStar:  " << numStar 	<< endl; 
	cout << "numGood:  " << numGood		<< endl; 
	cout << "numMatch: " << numMatch 	<< endl; 
	cout << "************************" 	<< endl; 
	
	int n = (num<ID.size())?num:ID.size(); 
	for(int i=0 ; i< n; ++i) {

		cout << ID[i] 
			<< "\t" << xcenter[i]
			<< "\t" << ycenter[i]
			<< "\t" << xworld[i]
			<< "\t" << yworld[i]
			<< "\t" << fwhm[i]
			<< "\t" << background[i]
			<< "\t" << e[i]
			<< "\t" << PA[i]
			<< "\t" << type[i]
			<< "\t" << matchIndex[i]
			<< "\t" << good[i]	
			<< endl; 
		

	}
	


}
