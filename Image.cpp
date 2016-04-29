
#include <iostream> 
#include <iomanip>

#include "Image.h"
#include "fitsio.h"
#include "commons.h"
#define buffsize 100000

using namespace std; 

/***************************
Function:   	Image Constructor
Description:    Construct an image object from a given FITS image file;
Arguments:		(1): Fits image name;
Returns:
Notes: 			This constructor is used to read the given lensed image,
				variance image, or PSF fits image;
****************************/
Image::Image(string imgFileName) {
	fileName = imgFileName; 
	fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */
	int status,  nfound, anynull;
	long naxes[2], fpixel, nbuffer;


	float nullval, buffer[buffsize];
	//char filename[]  = "atestfil.fit";     /* name of existing FITS file   */

	status = 0;

	if ( fits_open_file(&fptr, imgFileName.c_str(), READONLY, &status) )
		printerror( status );
	if ( fits_read_keys_lng(fptr, "NAXIS", 1, 2, naxes, &nfound, &status) )
		printerror( status );
	if(fits_get_img_type(fptr, &bitpix, &status))
		printerror( status );
	if (fits_get_img_dim(fptr, &naxis, &status))
		printerror( status );
	naxis1 = naxes[0] ;
	naxis2 = naxes[1] ;
	npixels  = naxes[0] * naxes[1];         /* number of pixels in the image */
	fpixel   = 1;
	nullval  = 0;                /* don't check for null values in the image */

	while (npixels > 0)
	{
		nbuffer = npixels;
		if (npixels > buffsize)
			nbuffer = buffsize;     /* read as many pixels as will fit in buffer */

		if ( fits_read_img(fptr, TFLOAT, fpixel, nbuffer, &nullval,
				buffer, &anynull, &status) )
			printerror( status );
		for(long i=0; i<nbuffer; ++i) {
			data.push_back(buffer[i]);
		}
		npixels -= nbuffer;    /* increment remaining number of pixels */
		fpixel  += nbuffer;    /* next pixel to be read in image */
	}

	npixels  = naxes[0] * naxes[1];
	
	updateHeader(fptr); 
	if ( fits_close_file(fptr, &status) )
			printerror( status );

}


/***************************
Function:   	writeToFile
Description:    Write an image object to a fits file;
Arguments:		(1): Name of the fits file you want to output;
Notes: 			This function only write 'data' member of the image object;
				If you want to specify other data, please use the other 'writeFilterImage' function;
Returns:		void;
****************************/

void Image::updateHeader(fitsfile *fptr) {
	double value;
	char value_str[FLEN_VALUE];  
	char* comment = NULL ; 
	int status = 0; 
	vector<string> keyword; 
	vector<string> keywordString; 

	keywordString.push_back("DATE-OBS"); 
	keywordString.push_back("DATE"); 
	keywordString.push_back("EQUINOX"); 
	keywordString.push_back("RADESYS"); 
	keywordString.push_back("CTYPE1"); 
	keywordString.push_back("CTYPE2"); 
	keywordString.push_back("CUNIT1"); 
	keywordString.push_back("CUNIT2"); 

	keyword.push_back("MJD-OBS"); 
	keyword.push_back("CRPIX1"); 
	keyword.push_back("CRPIX2"); 
	keyword.push_back("CRVAL1"); 
	keyword.push_back("CRVAL2"); 
	keyword.push_back("CD1_1"); 
	keyword.push_back("CD1_2"); 
	keyword.push_back("CD2_1"); 
	keyword.push_back("CD2_2"); 
	
	keyword.push_back("PV1_0"); 
	keyword.push_back("PV1_1"); 
	keyword.push_back("PV1_2"); 
	keyword.push_back("PV1_3"); 
	keyword.push_back("PV1_4"); 
	keyword.push_back("PV1_5"); 
	keyword.push_back("PV1_6"); 
	keyword.push_back("PV1_7"); 
	keyword.push_back("PV1_8"); 
	keyword.push_back("PV1_9"); 
	keyword.push_back("PV1_10"); 

	keyword.push_back("PV2_0"); 
	keyword.push_back("PV2_1"); 
	keyword.push_back("PV2_2"); 
	keyword.push_back("PV2_3"); 
	keyword.push_back("PV2_4"); 
	keyword.push_back("PV2_5"); 
	keyword.push_back("PV2_6"); 
	keyword.push_back("PV2_7"); 
	keyword.push_back("PV2_8"); 
	keyword.push_back("PV2_9"); 
	keyword.push_back("PV2_10"); 

	for (int i=0; i<keyword.size(); ++i) {
		int num = fits_read_key(fptr, TDOUBLE, keyword[i].c_str(), &value,comment, &status);
		headerDouble[keyword[i]] = value;  
	}//
	for (int i=0; i<keywordString.size(); ++i) {
		int num = fits_read_key(fptr, TSTRING, keywordString[i].c_str(), value_str,comment, &status);
		headerString[keywordString[i]] = string(value_str);  
	}
	headerString["RADESYS"] = "ICRS";  
}





/***************************
Function:   	writeToFile
Description:    Write an image object to a fits file;
Arguments:		(1): Name of the fits file you want to output;
Notes: 			This function only write 'data' member of the image object;
				If you want to specify other data, please use the other 'writeFilterImage' function;
Returns:		void;
****************************/

void Image::writeToFile(string imgFileName) {
	fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */
	int status, ii;
	long  fpixel;

	long naxes[2] = { naxis1, naxis2 };   /* image is 300 pixels wide by 200 rows */
	remove(imgFileName.c_str());               /* Delete old file if it already exists */
	status = 0;         /* initialize status before calling fitsio routines */
	if (fits_create_file(&fptr, imgFileName.c_str(), &status)) /* create new FITS file */
		printerror( status );           /* call printerror if error occurs */
	if ( fits_create_img(fptr,  bitpix, naxis, naxes, &status) )
		printerror( status );
	double **array = (double **)malloc(naxis2* sizeof(double**));
	array[0] = (double *)malloc( naxis1 * naxis2* sizeof( double ) );
	for( ii=1; ii<naxis2; ii++ )
	      array[ii] = array[ii-1] + naxis1;
	for (int i = 0; i < naxis2; i++) {
		for (int j = 0; j < naxis1; j++){
			array[i][j] = data[i*naxis1+j];
		}
	}
	fpixel = 1;                               /* first pixel to write      */
	/* write the array of unsigned integers to the FITS file */
	if (fits_write_img(fptr, TDOUBLE, fpixel, npixels, array[0], &status))
		printerror( status );

	free( array[0] );  /* free previously allocated memory */
	free( array);

	char* comment = NULL; 
	// write header, mainly the WCS information; 
	for(std::map<string, double>::iterator iter =headerDouble.begin();
		iter!= headerDouble.end(); ++iter) {
		int num = fits_write_key(fptr, TDOUBLE, iter->first.c_str(), &iter->second, comment, &status); 
	}

	for(std::map<string, string>::iterator iter =headerString.begin();
		iter!= headerString.end(); ++iter) {
		int num = fits_write_key(fptr, TSTRING, iter->first.c_str(), (char*)iter->second.c_str(), comment, &status); 
	}
	
	if ( fits_close_file(fptr, &status) )                /* close the file */
		printerror( status );
}




/***************************
Function:   	printImageInfo
Description:    Print out some basic information of the FITS image, and value of the image;
Arguments:		(1): left down x1;
				(2): left down y1;
				(3): right up x2;
				(4): right up y2;
Returns:		void
Notes: 			Basic info: filename, naxis1, naxis2, bitpix, npixels and so on;
				Image info: left-down(x1,y1);  right-up(x2, y2);
****************************/
void Image::printImageInfo(int x1, int y1, int x2, int y2, int header) {
	cout << "************************" << endl;
	cout << "File:   " << fileName << endl;
	cout << "NAXIS:  " << naxis << endl;
	cout << "NAXIS1: " << naxis1 << endl;
	cout << "NAXIS2: " << naxis2 << endl;
	cout << "Total:  " << npixels << endl;
	cout << "TYPE:   " << bitpix << endl;
	cout << "************************" << endl;

	//cout << counter << endl;
	x1 = (x1>0)?x1:0;
	y1 = (y1>0)?y1:0;
	x2 = (x2<naxis1)?x2:naxis1;
	y2 = (y2<naxis2)?y2:naxis2;
	// in order of DS9 show.
	for (int y=y2; y>=y1; --y) {
		for(int x=x1; x<=x2; ++x) {
			cout <<setprecision(4) << data[y*naxis1+x] << "\t";
		}
		cout << endl;

	}
	cout << endl;
	// print Header; 
	if(header==1) {
		for(std::map<string, double>::iterator iter =headerDouble.begin();
			iter!= headerDouble.end(); ++iter) {
			cout << iter->first << "\t=\t" << iter->second << endl ; 
		}
	
		for(std::map<string, string>::iterator iter =headerString.begin();
			iter!= headerString.end(); ++iter) {
			cout << iter->first << "\t=\t" << iter->second << endl ; 
		}
	}
}
	
template <typename T> 
Image::Image(vector<T> xpos, vector<T> ypos, vector<double> *briList, long naxis1, long naxis2, int bitpix):
			naxis(2), naxis1(naxis1), naxis2(naxis2), bitpix(bitpix), data(naxis1*naxis2, 0) {
	npixels = naxis1*naxis2;
	long iList=0, x, y;
	for(int i=0; i< briList->size(); ++i) {
		x = xpos[i];
		y = ypos[i];
		if(x>=0 && x< naxis1 && y>=0 && y<naxis2) {
			iList = naxis1*y+x;	
			data[iList] += briList->at(i);		
		}
	}
}

void Image::cropStamp(int x1, int y1, int x2, int y2, string stampFileName) {
	x1 = (x1>0)?x1:0;
	y1 = (y1>0)?y1:0;
	x2 = (x2<naxis1)?x2:naxis1;
	y2 = (y2<naxis2)?y2:naxis2;

	long stampNaxis1 = x2-x1; 
	long stampNaxis2 = y2-y1; 
	

	vector<double> stampData;
	vector<int> stampX; 
	vector<int> stampY;  
	int xIndex = 0 ; 
	int yIndex = 0 ; 
	for (int y=y1; y<=y2; ++y) {
		xIndex = 0; 
		for(int x=x1; x<=x2; ++x) {
			stampX.push_back(xIndex); 
			stampY.push_back(yIndex); 
			stampData.push_back(data[y*naxis1+x]) ; 
			xIndex ++; 
		}
		yIndex ++; 

	}

	Image* stampImage= new Image(stampX, stampY, &stampData, stampNaxis1, stampNaxis2, bitpix); 
	stampImage->headerDouble = headerDouble; 
	stampImage->headerString = headerString; 
	stampImage->writeToFile(stampFileName); 
	delete stampImage; 

}


