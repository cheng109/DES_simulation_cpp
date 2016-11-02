#ifndef STAR_H_
#define STAR_H_

#include <iostream> 
#include <cmath>
#include "fitsio.h"
#include "Image.h"
#include <ctime> 
#include "commons.h"
//#include "des_catalogGenerate.h"
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std; 


void printerror( int status)
{
    /*****************************************************/
    /* Print out cfitsio error messages and exit program */
    /*****************************************************/
    if (status)
    {
       fits_report_error(stderr, status); /* print error report */
       exit( status );    /* terminate the program, returning error status */
    }
    return;
}



/***************************
Function:       getEllipticity
Description:    
Arguments:      (1): stampRegion [leftx, lefty, rightx, righty]; 
                (2): Image pointer to the dataImage; 
                (3): background value; 
Returns:        v[0] = e1; 
                v[1] = e2; 
                v[2] = e; 
                v[3] = Postion angle  [-pi, pi]; 
                v[4] = flux; 
                v[5] = rms ; 
                v[6] = number of interations; 
Notes:          
****************************/
vector<double>  getEllipticity(int* stampRegion, const Image&  dataImage, double background) {

    vector<double> ret(7, 0); 
	//clock_t begin = clock(); 
	int x1 = stampRegion[0]; 
	int y1 = stampRegion[1]; 
	int x2 = stampRegion[2]; 
	int y2 = stampRegion[3]; 

	x1 = (x1>0)?x1:0;
	y1 = (y1>0)?y1:0;
	x2 = (x2<dataImage.naxis1)?x2:dataImage.naxis1;
	y2 = (y2<dataImage.naxis2)?y2:dataImage.naxis2;

	int xLength = x2-x1; 
	int yLength = y2-y1;  
	int index = 0; 
	double t1 =0,  t2 =0, t3 =0, t4 = 0, t5 = 0, t6 =0,  t7 = 0; 
	double noBackData; 
	for(int i= 0; i< yLength; ++i ) {
		for (int j=0; j<xLength; ++j) {
			index = (i+y1)*dataImage.naxis1 + (j+x1); 
			noBackData = dataImage.data[index] - background; 
			t1 += i* j * noBackData; 
			t2 += noBackData; 
			t3 +=  i * noBackData; 
			t4 +=  j * noBackData; 
			t5 +=  i * i * noBackData; 
			t6 +=  j * j * noBackData; 
		}
	}

	double covxy = t1/t2-t3*t4/t2/t2; 
    double resultx = t5/t2-t3*t3/t2/t2; 
    double resulty = t6/t2-t4*t4/t2/t2; 

    double medx = yLength/2.0; 
    double medy = xLength/2.0; 
    double alphax = sqrt(resultx*2.0); 
    double alphay = sqrt(resulty*2.0); 
    double alphaxy = covxy*sqrt(2.0); 
    int nTrials = 100;

    double e1 = 0, e2 = 0, weight = 0, flux = 0, ellip = 0, pa = 0, rms = 0; 
    int n = 0; 
    for (n=0 ; n<nTrials; ++n ) {
		t1 =0,  t2 =0, t3 =0, t4 = 0, t5 = 0, t6 =0, t7 = 0; 

    	for(int i= 0; i< yLength; ++i ) {
			for (int j=0; j<xLength; ++j) {
				index = (i+y1)*dataImage.naxis1 + (j+x1); 
				weight = (exp(-((i-medx)*(i-medx)/alphax/alphax-2.0*alphaxy/alphax/alphax/alphay/alphay*(i-medx)*(j-medy)+(j-medy)*(j-medy)/alphay/alphay)/2.0/(1-(alphaxy/alphax/alphay)*(alphaxy/alphax/alphay))))/(2*M_PI*alphax*alphay*sqrt(1-(alphaxy/alphax/alphay)*(alphaxy/alphax/alphay))); 
				noBackData = dataImage.data[index] - background; 

				t1 += i*j*noBackData*weight; 
                t2 += noBackData*weight; 
                t3 += i*noBackData*weight; 
                t4 += j*noBackData*weight; 
                t5 += i*i*noBackData*weight; 
                t6 += j*j*noBackData*weight; 
                t7 += noBackData ; 
            }
        }

        covxy=(t1/t2-t3*t4/t2/t2) ; 
        resultx=(t5/t2-t3*t3/t2/t2); 
        resulty=(t6/t2-t4*t4/t2/t2); 
        medx=(t3/t2); 
        medy=(t4/t2); 
        flux=t7; 

        if ((resultx + resulty) < 0) 
            break; 

        rms=sqrt(resultx+resulty); 

        e1=(resulty-resultx)/(resultx+resulty); 
        e2=(2.0*covxy)/(resultx+resulty); 
        ellip= sqrt(e1*e1+e2*e2); 

        pa = 0.5* atan2(e2, e1) * 180/M_PI;     //  [-pi, pi]; 
        //pa = 0.5* real_pa ; 
        if (resultx<1.0e-6 or resulty<1.0e-6)
            break; 

        if ((abs(alphax-sqrt(2.0*resultx)) < 1e-6 and abs(alphay-sqrt(2.0*resulty)) < 1e-6 and abs(alphaxy-2.0*covxy) < 1e-6))
            break; 
        alphax=sqrt(resultx*2.0); 
        alphay=sqrt(resulty*2.0); 
        alphaxy=covxy*2.0; 
    }
/*
    cout <<" e1 = " << e1 << endl ; 
    cout <<" e2 = " << e2 << endl ; 
    cout <<" e = " << ellip << endl ; 
   	cout <<" PA = " << pa << endl ; 
    cout <<" flux = " << flux << endl ; 
    cout <<" RMS = " << rms << endl ; 
    cout << "iterations: == " << n << endl; 
*/
  //clock_t end = clock();
  //double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  //cout << "Time used: " << elapsed_secs << endl; 

  ret[0] = e1; 
  ret[1] = e2; 
  ret[2] = ellip; 
  ret[3] = pa; 
  ret[4] = flux; 
  ret[5] = rms ; 
  ret[6] = n; 

  return ret; 
}



/***************************
Function:   	splitString
Description:    Split a string by whitespace;
Arguments:		(1) input string

Returns:    	string vector including all the split strings
****************************/
vector<string> splitString(string s) {
	vector<string> items;
	istringstream iss(s);
	//cout << iss << endl;
	copy(istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter(items));
	return items;
}


int getMin(vector<int> * const v) {
    int min = 1000000; 
    for(int i=0; i<v->size(); ++i) 
        if(v->at(i)< min) min = v->at(i); 
    return min; 
}

int getMax(vector<int> * const v) {
    int max = 0; 
    for(int i=0; i<v->size(); ++i) 
        if(v->at(i)> max) max = v->at(i); 
    return max; 
}


double convHMS(string RA) {
    stringstream ra(RA);
    string temp; 
    vector<string> items; 
    while(getline(ra, temp, ':')) 
        items.push_back(temp);    

    if(items.size() != 3 ) {
        cout << "HMS conversion error!" << endl; 
        exit(1) ;
    }
    int     hh = stoi(items[0]); 
    int     mm = stoi(items[1]); 
    double  ss = stod(items[2]); 

    return  hh*15.0 +  mm/4.0 + ss/240.0 ; 
}

double convDMS(string DEC) {
    stringstream dec(DEC);
    string temp; 
    vector<string> items; 
    while(getline(dec, temp, ':')) 
        items.push_back(temp);    

    if(items.size() != 3 ) {
        cout << "HMS conversion error!" << endl; 
        exit(1) ;
    }
    char Csign = items[0][0] ; 
    double sign = 0; 
    int deg ; 

    if(Csign=='-')  {
        sign = -1.0; 
        deg = stoi(items[0].substr(1)); 
    }
    else if (Csign =='+') {
        sign = 1.0 ; 
        deg = stoi(items[0].substr(1)); 
    }
    else {
        sign = 1.0; 
        deg = stoi(items[0]); 
    }
    
    int arcmin = stoi(items[1]); 
    double arcsec = stod(items[2]); 
    return sign*(deg+(arcmin*5.0/3.0+arcsec*5.0/180.0)/100.0); 

}




Conf::Conf (string configFileName){
           //configFileName = "conf.txt"; 
    ifstream configFile(configFileName.c_str());
    string line;
    //map<string, vector<double> > confMap; 
    unordered_map<string, string> tempMp; 
    while (getline(configFile, line)) {
        //cout << line.size() << endl; 
        if(line.size() > 0 and line.at(0)!='#') {
            vector<string> items = splitString(line);
            if (items.size() ==4) 
                coarseCorrectMap[items[0]] = {stod(items[2]), stod(items[3])}; 
            if(items.size() ==2)  
                tempMp[items[0]] = items[1]; 
        }
    }
    //   Assign all the other configuration parameters; 
    originDataDIR   = tempMp["originDataDIR"    ]; 
    dataDIR         = tempMp["dataDIR"          ]; 
    simuDIR         = tempMp["simuDIR"          ]; 
    chipID          = tempMp["chipID"           ]; 
    phosimFileDIR   = tempMp["phosimFileDIR"    ]; 

    extractData     = stoi(tempMp["extractData" ]); 
    extractSimu     = stoi(tempMp["extractSimu" ]); 
    analyze         = stoi(tempMp["analyze"     ]); 
    phosimScript    = stoi(tempMp["phosimScript"]); 
    runPhosim       = stoi(tempMp["runPhosim"   ]); 
    
    x               = stod(tempMp["x"            ]); 
    y               = stod(tempMp["y"            ]); 
    z               = stod(tempMp["z"            ]); 
    phi             = stod(tempMp["phi"          ]); 
    psi             = stod(tempMp["psi"          ]); 
    theta           = stod(tempMp["theta"        ]); 
    seeing          = stod(tempMp["seeing"       ]); 
    magCorrection   = stod(tempMp["magCorrection"]); 
    rotation        = stod(tempMp["rotation"     ]);   
    tolerance       = stod(tempMp["tolerance"    ]);


    //   update single chipID shift correction; 
    dDEC_coarse = coarseCorrectMap[chipID].first;
    dRA_coarse  = coarseCorrectMap[chipID].second; 
    dROT_coarse = rotation; 
 
    configFile.close() ;      
    } 


void Conf::updateShiftCorrection() {

    double TOL = 1.0e-3; 

    /********  correction due to 'x & y' **********/
    double dDEC1 = -72.933*x - 0.3333 ; 
    double dRA1  = 240.47*y ; 

    /********  correction due to 'phi & theta' **********/
    double dDEC2 = 0; 
    double dRA2  = 0;
    double dRotation = 0; 


    if (fabs(phi-324000.0)<TOL) {
        dDEC2 = -7.5435*theta -0.7778; 
    }
    else if (fabs(phi-108000.0)<TOL) {
        dDEC2 = -3.8*theta; 
        dRA2 = -21.801*theta-2.1316; 
    }
    else if (fabs(phi-216000.0)<TOL) {
        dDEC2 = -6.5618*theta-0.4; 
        dRA2 = -12.598*theta -2.1316; 
    }
    else if (fabs(phi+108000.0)<TOL) {
        dDEC2 = 3.7882*theta + 0.2; 
        dRA2 = -21.801*theta -2.1316 ; 
    }
    else if (fabs(phi+216000.0)<TOL) {
        dDEC2 = 6.5618*theta + 0.4 ; 
        dRA2 = -12.598*theta -2.1316 ; 
    }
    else if (fabs(phi-0.0)<TOL) {
        dRA2 = -24.958*theta -1.6667 ; 
    }
    else {
        cout << "Angle configuration error!" << endl; 
        exit(1); 
    } 

    /************** for single chip **************/ 
    double singleDEC = 0.3;       // dx ; 
    double singleRA  = 14.5;    // dy ; 
    double singleROT = -0.21; 

    dDEC_shift = dDEC1 + dDEC2; 
    dRA_shift  = dRA1 + dRA2; 
    dROT_shift = dRotation; 



    dRA  = (dRA_shift  + dRA_coarse  + singleRA )*0.27/3600; 
    dDEC = (dDEC_shift + dDEC_coarse + singleDEC)*0.27/3600; 
    dROT = dROT_shift  + dROT_coarse + singleROT; 
    cout << dROT << endl; 
}

#endif 

